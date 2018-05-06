
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
	: m_InputImage(NULL)
	, m_width(0)
	, m_height(0)
	, m_size(0)
	, m_pRGB(NULL)
	, m_OutputImage(NULL)
	, m_rwsize(0)
	, m_CompressionCheck(false)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령

//영상 불러오기 함수
BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CFile File;	//파일 객체 선언
	File.Open(lpszPathName,CFile::modeRead | CFile::typeBinary);	
	//파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

	//파일헤더 읽기
	File.Read(&m_fileheader,sizeof(BITMAPFILEHEADER));
	
	//BMP파일이 아니라면 불러오지 않고, 에러메세지 출력
	if(m_fileheader.bfType != 0x4D42){
		AfxMessageBox(L"지원하지않는 포멧입니다!");
		return FALSE;
	}

	//비트맵정보헤더 읽기
	File.Read(&m_infoheader,sizeof(BITMAPINFOHEADER));

	//8-bit-grascale 영상 , 24-bit-truecolor 영상 이외의 영상은 불러오지 못하도록 에러메세지 출력
	if(m_infoheader.biBitCount != 8 && m_infoheader.biBitCount != 24)
	{
		AfxMessageBox(L"8-bit-grayscale 영상 또는 24-bit-truecolor 영상만 지원합니다!");
		return FALSE;
	}

	//팔레트 읽기(8-bit-grascale 영상 처리)
	if(m_infoheader.biBitCount == 8)
	{
		m_pRGB = new RGBQUAD[256];
		File.Read(m_pRGB,sizeof(RGBQUAD)*256);
	}

	if(m_infoheader.biBitCount==8)
		m_size = File.GetLength()-sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER)-256*sizeof(RGBQUAD);

	if(m_infoheader.biBitCount==24) 
		m_size = File.GetLength()-sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER);

	m_InputImage = new BYTE[m_size];

	File.Read(m_InputImage,m_size);		//입력 데이터
	
	m_FileSize = m_size;
	m_width = m_infoheader.biWidth;
	m_height = m_infoheader.biHeight; 
	m_rwsize =  WIDTHBYTES(m_infoheader.biBitCount*m_width);

	//출력 데이터 저장
	if(m_infoheader.biCompression == BI_RLE8)	//RLE로 압축되어 있다면,
	{
		m_CompressionCheck = TRUE;
		RLEDecompression();	//RLE 압축해제
	}
	else if(m_infoheader.biBitCount == 8 && m_infoheader.biCompression == BI_RGB)
	{
		m_CompressionCheck = FALSE;
		m_OutputImage = new BYTE[m_size];
		for(int i=0;i<m_height;i++)
		{
			for(int j=0;j<m_width;j++)
			{
				m_OutputImage[i*(m_rwsize) + j] = m_InputImage[i*(m_rwsize) + j];	//RGB
			}
		}
	}
	else if(m_infoheader.biBitCount == 24 && m_infoheader.biCompression == BI_RGB)
	{
		m_CompressionCheck = FALSE;
		m_OutputImage = new BYTE[m_size];
		for(int i=0;i<m_height;i++)
		{
			for(int j=0;j<m_width;j++)
			{
				m_OutputImage[i*(m_rwsize) + 3*j + 2] = m_InputImage[i*(m_rwsize) + 3*j + 2];	//R
				m_OutputImage[i*(m_rwsize) + 3*j + 1] = m_InputImage[i*(m_rwsize) + 3*j + 1];	//G
				m_OutputImage[i*(m_rwsize) + 3*j] = m_InputImage[i*(m_rwsize) + 3*j];		//B
			}
		}
	}



	File.Close();
	
	return TRUE;
}

//영상 저장하기 함수
BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	//파일 객체 선언
	CFile OutputFile;

	OutputFile.Open(lpszPathName,CFile::modeCreate |CFile::modeWrite | CFile::modeNoTruncate);
		
	//출력 데이터 저장
	OutputFile.Write(&m_fileheader,sizeof(BITMAPFILEHEADER));	//파일헤더
	OutputFile.Write(&m_infoheader,sizeof(BITMAPINFOHEADER));	//비트맵정보헤더
	if(m_infoheader.biBitCount == 8)	//팔레트 배열
		OutputFile.Write(m_pRGB,sizeof(RGBQUAD)*256);

	OutputFile.Write(m_OutputImage,m_size);	//영상데이터

		//파일 닫기
		OutputFile.Close();
	return TRUE;
}

//RLE BMP 압축해제 함수
void CImageProcessingDoc::RLEDecompression(void)
{
	int firstbyte,secondbyte=0;	//첫번째바이트,두번째바이트
	int xOffset,yOffset=0;		//수평오프셋,수직오프셋(Delta)
	int xDelta,yDelta;			//델타를 위한 변수(Delta)
	int x=0,y=0,i=0,length=0,value=0,k=0;

	m_OutputImage = new BYTE[m_rwsize*m_infoheader.biHeight];
	while (i <= m_infoheader.biSizeImage)	//영상데이터의 마지막에 도달할때까지 반복,
	{
		firstbyte = m_InputImage[i];		//첫번째 바이트 읽기
		secondbyte = m_InputImage[++i];		//두번째 바이트 읽기

		if(firstbyte == 0)	//Absolute Mode
		{
			switch(secondbyte)
			{
			case 0: // End Of Line(00 00)
				while(x <= m_infoheader.biWidth)
				{
					m_OutputImage[y*m_rwsize + x] = 0;
					x++;
				}
				//다음 라인 이동
				x=0; y++;
				break;
			case 1: // End Of Bitmap(00 01)
				if (y <= m_infoheader.biHeight || x <= m_infoheader.biWidth)//아직 영역을 다채우지 못했다면,
				{
					for (; y < m_infoheader.biHeight; y++)//남은영역에 대해서  검은색으로 채움
					{
						for (; x < m_infoheader.biWidth; x++)
						{
							m_OutputImage[y*m_rwsize + x] = 0;
						}
						x = 0;
					}
				}
				//반복문 종료
				i = m_infoheader.biSizeImage;
				break;
				case 2:	//Delta(00 02)
					xOffset = m_InputImage[++i];	//x오프셋 저장
					yOffset = m_InputImage[++i];	//y오프셋 저장
					xDelta = x;
					yDelta = y;
					//y오프셋 만큼, 검은색으로 채워넣음.
					for (; y < yDelta + yOffset; y++)
					{
						for (; x < m_infoheader.biWidth; x++)
						{
							m_OutputImage[y*m_rwsize + x] = 0;
						}
						x = 0;
					}
					//x오프셋 만큼, 검은색으로 채워넣음.
					for (; x < xDelta + xOffset;x++)
						m_OutputImage[y*m_rwsize + x] = 0;
					break;
				default:
					length = secondbyte;
					for(k = 0; k < length ;k++)
					{
						i++;
						m_OutputImage[y*m_rwsize + x] = m_InputImage[i];
						x++;
					}
					if(length % 2 == 1)	//길이가 홀수라면,
						i++;	//마지막값(00)은 복호화 하지않음)
					break;
			}
		}
		else //Encoded Mode
		{
			length = firstbyte;
			value = secondbyte;
			for(k=0;k<length;k++)
			{
				m_OutputImage[y*m_rwsize + x] = value;
				x++;
			}
		}
		i++;	//다음 인덱스 이동
	}//EndWhile

	m_infoheader.biCompression = BI_RGB;	//압축되지 않은경우 BI_RGB 값을 가짐
	m_infoheader.biSizeImage = m_size = m_rwsize * m_infoheader.biHeight;	//압축해제된 크기
	m_fileheader.bfSize =  54 + m_infoheader.biSizeImage;			//총 바이트저장
	
}
