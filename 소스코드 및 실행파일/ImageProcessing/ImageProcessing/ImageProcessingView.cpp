
// ImageProcessingView.cpp : CImageProcessingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//다이얼로그를 위한 헤더파일 추가
#include "SquareDlg.h"
#include "LightAdjustmentDlg.h"

// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_CONVERSION, &CImageProcessingView::OnConversion)
	ON_COMMAND(IDM_SQUAREDRAW, &CImageProcessingView::OnSquaredraw)
	ON_COMMAND(IDM_LIGHTADJUST, &CImageProcessingView::OnLightadjust)
	ON_COMMAND(IDM_BINARIZATION, &CImageProcessingView::OnBinarization)
	ON_COMMAND(IDM_IMAGEMIRROR, &CImageProcessingView::OnImagemirror)
	ON_COMMAND(IDM_Decalcomanie, &CImageProcessingView::OnDecalcomanie)
	ON_COMMAND(IDM_IMAGEFLIP, &CImageProcessingView::OnImageflip)
	ON_COMMAND(IDM_EDGEDETECT, &CImageProcessingView::OnEdgedetect)
END_MESSAGE_MAP()

// CImageProcessingView 생성/소멸

CImageProcessingView::CImageProcessingView()
	: m_x1(0)
	, m_y1(0)
	, m_x2(0)
	, m_y2(0)
	, m_LightInput(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView 그리기

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	BYTE R,G,B;
	int i,j;

	//파일 정보 출력
	pDC->TextOutW(10,100,pDoc->m_FileName);

	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		pDoc->m_FileSizeFormat.Format(L"영상 크기 : %dKB    영상 사이즈 : %d x %d ",pDoc->m_FileSize/1000,pDoc->m_width,pDoc->m_height);
		pDC->TextOutW(10,10,pDoc->m_FileSizeFormat);
		pDC->TextOutW(10,40,L"파일 유형 : 8-bit-grayscale 영상");
		if(pDoc->m_CompressionCheck)
			pDC->TextOutW(10,70,L"압축 유형 : RLE 압축");
		else
			pDC->TextOutW(10,70,L"압축 유형 : 압축되어있지않음");

		for(i=0;i<pDoc->m_height;i++)
		{
			for(j=0;j<pDoc->m_width;j++)
			{
				R=G=B=pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j];	//RGB
				pDC->SetPixel(50+j,pDoc->m_height-1-(-130+i),RGB(R,G,B));
			}
		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		pDoc->m_FileSizeFormat.Format(L"영상 크기 : %dKB    영상 사이즈 : %d x %d ",pDoc->m_fileheader.bfSize/1000,pDoc->m_width,pDoc->m_height);
		pDC->TextOutW(10,10,pDoc->m_FileSizeFormat);
		pDC->TextOutW(10,40,L"파일 유형 : 24-bit-truecolor 영상");
		if(pDoc->m_CompressionCheck)
			pDC->TextOutW(10,70,L"압축 유형 : RLE 압축");
		else
			pDC->TextOutW(10,70,L"압축 유형 : 압축되어있지않음");

		for(i=0;i<pDoc->m_height;i++)
		{
			for(j=0;j<pDoc->m_width;j++)
			{
				R=pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j + 2];	//R
				G=pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j + 1];	//G
				B=pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j];		//B
				pDC->SetPixel(50+j,pDoc->m_height-1-(-130+i),RGB(R,G,B));
			}
		}
	}

}


// CImageProcessingView 인쇄

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingView 진단

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 메시지 처리기

//영상 반전 처리
void CImageProcessingView::OnConversion()
{
	
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j] = 255 - pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j] ;	//RGB
				
			}
		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j + 2] = 255 - pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j + 2];	//R
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j + 1] = 255 - pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j + 1];	//G
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j] = 255 - pDoc->m_OutputImage[i*(pDoc->m_rwsize) + 3*j];			//B
			}
		}
	}

	Invalidate();
}

//영상 사각형 그리기 처리
void CImageProcessingView::OnSquaredraw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSquareDlg dlg;
	if(dlg.DoModal() == IDOK){
		m_x1 = dlg.m_x1;
		m_y1 = dlg.m_y1;
		m_x2 = dlg.m_x2;
		m_y2 = dlg.m_y2;
	}
	else{
		m_x1 = m_y1 = 0;
		m_x2 = m_y2 = 1;
	}
		//사각형의 좌표가 올바르지 않을경우,
		if (m_x1 >= m_x2 || m_y1 >= m_y2 || m_x1 < 0 || m_y1 < 0 || m_x2 < 0 || m_y2 < 0 ||
			m_x1 > pDoc->m_infoheader.biWidth || m_y1 >  pDoc->m_infoheader.biHeight ||
			m_x2 >  pDoc->m_infoheader.biWidth || m_y2 >  pDoc->m_infoheader.biHeight)
		{
			AfxMessageBox(L"사각형의 좌표가 올바르지 않습니다!");
			return;
		}

	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=m_x1; i < m_x1 + (m_x2 - m_x1); i++)
		{
			for(int j=m_y1; j < m_y1 + (m_y2 - m_y1); j++)
			{

				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i] = 0;
			}
		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=m_x1*3; i < m_x1*3 + (m_x2 - m_x1)*3 ;i+=3)
		{
			for(int j=m_y1; j < m_y1 + (m_y2 - m_y1); j++)
			{
				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i + 2] = 0;  //사각형 그리기(R)
				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i + 1] = 0;  //사각형 그리기(G)
				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i] = 0;	
			}
		}
	}

	Invalidate();

}

//영상 밝기 조절 처리
void CImageProcessingView::OnLightadjust()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CLightAdjustmentDlg dlg;
	if(dlg.DoModal() == IDOK){
		m_LightInput = dlg.m_LightInput;
	}
	else{
		m_LightInput = 0;
	}

	if (m_LightInput > 50 || m_LightInput < -50)
	{
		AfxMessageBox(L"밝기 입력값이 올바르지 않습니다!");
		return;
	}

	if (pDoc->m_infoheader.biBitCount == 8) //8-bit grayscale 영상 처리
	{
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				if(pDoc->m_OutputImage[i*pDoc->m_rwsize + j] + m_LightInput > 255)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + j] = 255;
				else if(pDoc->m_OutputImage[i*pDoc->m_rwsize + j] + m_LightInput < 0)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + j] = 0;
				else
					pDoc->m_OutputImage[i*pDoc->m_rwsize + j] += m_LightInput;
			}
		}
	}
	else if (pDoc->m_infoheader.biBitCount == 24) // 트루 칼라 영상 처리
	{
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				//영상의 최대 밝기나, 최소밝기를 벗어난다면,
				if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] + m_LightInput > 255)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] = 255;
				else if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] + m_LightInput < 0)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] = 0;
				else
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] += m_LightInput;;	//R

				if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] + m_LightInput > 255)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] = 255;
				else if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] + m_LightInput < 0)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] = 0;
				else
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] += m_LightInput;;	//G

				if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] + m_LightInput > 255)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] = 255;
				else if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] + m_LightInput < 0)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] = 0;
				else
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] += m_LightInput;;	//B
			}
		}
	}

	Invalidate();
}

//영상 이진화 처리
void CImageProcessingView::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int ThresholdValue = 0;
	int RedThresholdValue = 0;
	int GreenThresholdValue = 0;
	int BlueThresholdValue = 0;
		//영상 이진화 처리

	if (pDoc->m_infoheader.biBitCount == 8) //8-bit grayscale 영상 처리
	{
		//모든 픽셀들의 밝기 합
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
				ThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + j];

		//모든 픽셀들의 밝기 평균(이진화를 위한 임계값)
		ThresholdValue /= (pDoc->m_infoheader.biHeight*pDoc->m_infoheader.biWidth);

		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				if(pDoc->m_OutputImage[i*pDoc->m_rwsize + j] > ThresholdValue)
					pDoc->m_OutputImage[i*pDoc->m_rwsize + j] = 255;
				else
					pDoc->m_OutputImage[i*pDoc->m_rwsize + j] = 0;
			}
		}
	}
	else if (pDoc->m_infoheader.biBitCount == 24) // 트루 칼라 영상 처리
	{
		//모든 RGB 각각 픽셀들의 밝기 합
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				RedThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2];
				GreenThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1];
				BlueThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j];
			}
		}
		//모든 R픽셀들의 밝기 평균(이진화를 위한 임계값)
		RedThresholdValue /= (pDoc->m_infoheader.biHeight*pDoc->m_infoheader.biWidth);
		//모든 G픽셀들의 밝기 평균(이진화를 위한 임계값)
		GreenThresholdValue /= (pDoc->m_infoheader.biHeight*pDoc->m_infoheader.biWidth);
		//모든 B픽셀들의 밝기 평균(이진화를 위한 임계값)
		BlueThresholdValue /= (pDoc->m_infoheader.biHeight*pDoc->m_infoheader.biWidth);


		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				if(pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] > RedThresholdValue && 
					 pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] > GreenThresholdValue &&
					 pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] > BlueThresholdValue){
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] = 255;	//R
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] = 255;	//G	
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] = 255;		//B
				}
				else
				{
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2] = 0;		//R
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1] = 0;		//G	
					pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j] = 0;			//B
				}
			}
		}
	}


	Invalidate();
}


void CImageProcessingView::OnDecalcomanie()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + pDoc->m_width - 1 - j] ;//RGB
				
			}
		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 2] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + pDoc->m_width*3 - 1 - j*3];	//R
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 1] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + pDoc->m_width*3 - 1 - j*3 - 1];//G
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + pDoc->m_width*3 - 1 - j*3 - 2];	//B
			}
		}
	}

	Invalidate();
}


void CImageProcessingView::OnImagemirror()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//영상 처리를 위해서, 영상데이터 복사
	BYTE * CopyImage = new BYTE[pDoc->m_size];
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
			for(int j=0;j<pDoc->m_width;j++)
				CopyImage[i*(pDoc->m_rwsize) + j] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j];
	}
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
			for(int j=0;j<pDoc->m_width;j++)
			{
				CopyImage[i*(pDoc->m_rwsize) + j*3 + 2] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 2];	//R
				CopyImage[i*(pDoc->m_rwsize) + j*3 + 1] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 1];	//G
				CopyImage[i*(pDoc->m_rwsize) + j*3] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3];			//B
			}
	}


	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j] = CopyImage[i*(pDoc->m_rwsize) + pDoc->m_width - 1 - j] ;//RGB
				
			}
		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 2] = CopyImage[i*(pDoc->m_rwsize) + pDoc->m_width*3 - 1 - j*3];	//R
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 1] = CopyImage[i*(pDoc->m_rwsize) + pDoc->m_width*3 - 1 - j*3 - 1];//G
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3] = CopyImage[i*(pDoc->m_rwsize) + pDoc->m_width*3 - 1 - j*3 - 2];	//B
			}
		}
	}

	//메모리 할당 해제
	delete CopyImage;

	Invalidate();
}



void CImageProcessingView::OnImageflip()
{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//영상 처리를 위해서, 영상데이터 복사
	BYTE * CopyImage = new BYTE[pDoc->m_size];
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
			for(int j=0;j<pDoc->m_width;j++)
				CopyImage[i*(pDoc->m_rwsize) + j] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j];
	}
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
			for(int j=0;j<pDoc->m_width;j++)
			{
				CopyImage[i*(pDoc->m_rwsize) + j*3 + 2] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 2];	//R
				CopyImage[i*(pDoc->m_rwsize) + j*3 + 1] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 1];	//G
				CopyImage[i*(pDoc->m_rwsize) + j*3] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3];			//B
			}
	}


	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j] = CopyImage[(pDoc->m_height - 1 - i)*(pDoc->m_rwsize) + j] ;//RGB
				
			}
		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
		{
			for(int j=0;j<pDoc->m_width;j++)
			{
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 2] = CopyImage[(pDoc->m_height - 1 - i)*(pDoc->m_rwsize) + j*3 + 2];	//R
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 1] = CopyImage[(pDoc->m_height - 1 - i)*(pDoc->m_rwsize) + j*3 + 1];	//G
				pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3] = CopyImage[(pDoc->m_height - 1 - i)*(pDoc->m_rwsize) + j*3];			//B
			}
		}
	}

	//메모리 할당 해제
	delete CopyImage;

	Invalidate();
}

//에지 검출 함수
void CImageProcessingView::OnEdgedetect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//LaplacianMask(라플라시안 마스크)
	int LaplacianMask[3][3] = {
		{-1,-1,-1},
		{-1,8,-1},
		{-1,-1,-1}};


	//영상 처리를 위해서, 영상데이터 복사
	BYTE * CopyImage = new BYTE[pDoc->m_size];
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i=0;i<pDoc->m_height;i++)
			for(int j=0;j<pDoc->m_width;j++)
				CopyImage[i*(pDoc->m_rwsize) + j] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j];
	}
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=0;i<pDoc->m_height;i++)
			for(int j=0;j<pDoc->m_width;j++)
			{
				CopyImage[i*(pDoc->m_rwsize) + j*3 + 2] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 2];	//R
				CopyImage[i*(pDoc->m_rwsize) + j*3 + 1] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3 + 1];	//G
				CopyImage[i*(pDoc->m_rwsize) + j*3] = pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j*3];			//B
			}
	}

	//8-bit-grayscale 영상 처리
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		for(int i = 1; i < pDoc->m_height;i++)
		{
			for( int  j = 1; j < pDoc->m_width;j++)
			{

				int result = 0;

				for(int y=0; y<3; y++)
					for(int x=0; x<3; x++)
						result += LaplacianMask[y][x]*CopyImage[(i + y - 1)*pDoc->m_rwsize + j + x - 1];

				//에지 강도값을 임의의 임계값으로 이진화
				if(result > 255)
					result = 255;
				else if(result < 0)
					result = 0;
	
				pDoc->m_OutputImage[i*pDoc->m_rwsize + j] = result;
			}

		}
	}

	//24-bit-truecolor 영상 처리
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i = 1; i < pDoc->m_height;i++)
		{
			for( int  j = 1; j < pDoc->m_width;j++)
			{

				int result = 0;
				int grayscale = 0;

				//24bit turecolor의 경우, 8-bit-grayscale 영상으로 변환후, 에지 검출해야함
				//다음의 공식은, 24bit-truecolor 영상을 8-bit-grayscale영상으로 변환시켜서 값을 더해주는 공식임.
				for(int y=0; y<3; y++)
					for(int x=0; x<3; x++)
					{
						grayscale += 0.299*CopyImage[(i + y - 1)*pDoc->m_rwsize + j*3 + 2 + x - 1];
						grayscale += 0.587*CopyImage[(i + y - 1)*pDoc->m_rwsize + j*3 + 1 + x - 1];
						grayscale += 0.114*CopyImage[(i + y - 1)*pDoc->m_rwsize + j*3 + x - 1];
						result += LaplacianMask[y][x]*grayscale;
					}

				//에지 강도값을 임의의 임계값으로 이진화
				if(result > 255)
					result = 255;
				else if(result < 0)
					result = 0;
	
				pDoc->m_OutputImage[i*pDoc->m_rwsize + j*3 + 2] = result;
				pDoc->m_OutputImage[i*pDoc->m_rwsize + j*3 + 1] = result;
				pDoc->m_OutputImage[i*pDoc->m_rwsize + j*3] = result;
			}

		}
	}


	

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
