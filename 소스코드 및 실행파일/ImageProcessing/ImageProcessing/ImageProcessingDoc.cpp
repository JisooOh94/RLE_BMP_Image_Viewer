
// ImageProcessingDoc.cpp : CImageProcessingDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CImageProcessingDoc ����/�Ҹ�

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
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessingDoc ����

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


// CImageProcessingDoc ���

//���� �ҷ����� �Լ�
BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	CFile File;	//���� ��ü ����
	File.Open(lpszPathName,CFile::modeRead | CFile::typeBinary);	
	//���� ���� ��ȭ���ڿ��� ������ ������ �����ϰ� �б� ��� ����

	//������� �б�
	File.Read(&m_fileheader,sizeof(BITMAPFILEHEADER));
	
	//BMP������ �ƴ϶�� �ҷ����� �ʰ�, �����޼��� ���
	if(m_fileheader.bfType != 0x4D42){
		AfxMessageBox(L"���������ʴ� �����Դϴ�!");
		return FALSE;
	}

	//��Ʈ��������� �б�
	File.Read(&m_infoheader,sizeof(BITMAPINFOHEADER));

	//8-bit-grascale ���� , 24-bit-truecolor ���� �̿��� ������ �ҷ����� ���ϵ��� �����޼��� ���
	if(m_infoheader.biBitCount != 8 && m_infoheader.biBitCount != 24)
	{
		AfxMessageBox(L"8-bit-grayscale ���� �Ǵ� 24-bit-truecolor ���� �����մϴ�!");
		return FALSE;
	}

	//�ȷ�Ʈ �б�(8-bit-grascale ���� ó��)
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

	File.Read(m_InputImage,m_size);		//�Է� ������
	
	m_FileSize = m_size;
	m_width = m_infoheader.biWidth;
	m_height = m_infoheader.biHeight; 
	m_rwsize =  WIDTHBYTES(m_infoheader.biBitCount*m_width);

	//��� ������ ����
	if(m_infoheader.biCompression == BI_RLE8)	//RLE�� ����Ǿ� �ִٸ�,
	{
		m_CompressionCheck = TRUE;
		RLEDecompression();	//RLE ��������
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

//���� �����ϱ� �Լ�
BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	//���� ��ü ����
	CFile OutputFile;

	OutputFile.Open(lpszPathName,CFile::modeCreate |CFile::modeWrite | CFile::modeNoTruncate);
		
	//��� ������ ����
	OutputFile.Write(&m_fileheader,sizeof(BITMAPFILEHEADER));	//�������
	OutputFile.Write(&m_infoheader,sizeof(BITMAPINFOHEADER));	//��Ʈ���������
	if(m_infoheader.biBitCount == 8)	//�ȷ�Ʈ �迭
		OutputFile.Write(m_pRGB,sizeof(RGBQUAD)*256);

	OutputFile.Write(m_OutputImage,m_size);	//��������

		//���� �ݱ�
		OutputFile.Close();
	return TRUE;
}

//RLE BMP �������� �Լ�
void CImageProcessingDoc::RLEDecompression(void)
{
	int firstbyte,secondbyte=0;	//ù��°����Ʈ,�ι�°����Ʈ
	int xOffset,yOffset=0;		//���������,����������(Delta)
	int xDelta,yDelta;			//��Ÿ�� ���� ����(Delta)
	int x=0,y=0,i=0,length=0,value=0,k=0;

	m_OutputImage = new BYTE[m_rwsize*m_infoheader.biHeight];
	while (i <= m_infoheader.biSizeImage)	//���������� �������� �����Ҷ����� �ݺ�,
	{
		firstbyte = m_InputImage[i];		//ù��° ����Ʈ �б�
		secondbyte = m_InputImage[++i];		//�ι�° ����Ʈ �б�

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
				//���� ���� �̵�
				x=0; y++;
				break;
			case 1: // End Of Bitmap(00 01)
				if (y <= m_infoheader.biHeight || x <= m_infoheader.biWidth)//���� ������ ��ä���� ���ߴٸ�,
				{
					for (; y < m_infoheader.biHeight; y++)//���������� ���ؼ�  ���������� ä��
					{
						for (; x < m_infoheader.biWidth; x++)
						{
							m_OutputImage[y*m_rwsize + x] = 0;
						}
						x = 0;
					}
				}
				//�ݺ��� ����
				i = m_infoheader.biSizeImage;
				break;
				case 2:	//Delta(00 02)
					xOffset = m_InputImage[++i];	//x������ ����
					yOffset = m_InputImage[++i];	//y������ ����
					xDelta = x;
					yDelta = y;
					//y������ ��ŭ, ���������� ä������.
					for (; y < yDelta + yOffset; y++)
					{
						for (; x < m_infoheader.biWidth; x++)
						{
							m_OutputImage[y*m_rwsize + x] = 0;
						}
						x = 0;
					}
					//x������ ��ŭ, ���������� ä������.
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
					if(length % 2 == 1)	//���̰� Ȧ�����,
						i++;	//��������(00)�� ��ȣȭ ��������)
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
		i++;	//���� �ε��� �̵�
	}//EndWhile

	m_infoheader.biCompression = BI_RGB;	//������� ������� BI_RGB ���� ����
	m_infoheader.biSizeImage = m_size = m_rwsize * m_infoheader.biHeight;	//���������� ũ��
	m_fileheader.bfSize =  54 + m_infoheader.biSizeImage;			//�� ����Ʈ����
	
}
