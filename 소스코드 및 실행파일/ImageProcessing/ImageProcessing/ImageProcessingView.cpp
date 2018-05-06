
// ImageProcessingView.cpp : CImageProcessingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//���̾�α׸� ���� ������� �߰�
#include "SquareDlg.h"
#include "LightAdjustmentDlg.h"

// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// ǥ�� �μ� ����Դϴ�.
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

// CImageProcessingView ����/�Ҹ�

CImageProcessingView::CImageProcessingView()
	: m_x1(0)
	, m_y1(0)
	, m_x2(0)
	, m_y2(0)
	, m_LightInput(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView �׸���

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	
	BYTE R,G,B;
	int i,j;

	//���� ���� ���
	pDC->TextOutW(10,100,pDoc->m_FileName);

	//8-bit-grayscale ���� ó��
	if(pDoc->m_infoheader.biBitCount == 8)
	{
		pDoc->m_FileSizeFormat.Format(L"���� ũ�� : %dKB    ���� ������ : %d x %d ",pDoc->m_FileSize/1000,pDoc->m_width,pDoc->m_height);
		pDC->TextOutW(10,10,pDoc->m_FileSizeFormat);
		pDC->TextOutW(10,40,L"���� ���� : 8-bit-grayscale ����");
		if(pDoc->m_CompressionCheck)
			pDC->TextOutW(10,70,L"���� ���� : RLE ����");
		else
			pDC->TextOutW(10,70,L"���� ���� : ����Ǿ���������");

		for(i=0;i<pDoc->m_height;i++)
		{
			for(j=0;j<pDoc->m_width;j++)
			{
				R=G=B=pDoc->m_OutputImage[i*(pDoc->m_rwsize) + j];	//RGB
				pDC->SetPixel(50+j,pDoc->m_height-1-(-130+i),RGB(R,G,B));
			}
		}
	}

	//24-bit-truecolor ���� ó��
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		pDoc->m_FileSizeFormat.Format(L"���� ũ�� : %dKB    ���� ������ : %d x %d ",pDoc->m_fileheader.bfSize/1000,pDoc->m_width,pDoc->m_height);
		pDC->TextOutW(10,10,pDoc->m_FileSizeFormat);
		pDC->TextOutW(10,40,L"���� ���� : 24-bit-truecolor ����");
		if(pDoc->m_CompressionCheck)
			pDC->TextOutW(10,70,L"���� ���� : RLE ����");
		else
			pDC->TextOutW(10,70,L"���� ���� : ����Ǿ���������");

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


// CImageProcessingView �μ�

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CImageProcessingView ����

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView �޽��� ó����

//���� ���� ó��
void CImageProcessingView::OnConversion()
{
	
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//8-bit-grayscale ���� ó��
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

	//24-bit-truecolor ���� ó��
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

//���� �簢�� �׸��� ó��
void CImageProcessingView::OnSquaredraw()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
		//�簢���� ��ǥ�� �ùٸ��� �������,
		if (m_x1 >= m_x2 || m_y1 >= m_y2 || m_x1 < 0 || m_y1 < 0 || m_x2 < 0 || m_y2 < 0 ||
			m_x1 > pDoc->m_infoheader.biWidth || m_y1 >  pDoc->m_infoheader.biHeight ||
			m_x2 >  pDoc->m_infoheader.biWidth || m_y2 >  pDoc->m_infoheader.biHeight)
		{
			AfxMessageBox(L"�簢���� ��ǥ�� �ùٸ��� �ʽ��ϴ�!");
			return;
		}

	//8-bit-grayscale ���� ó��
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

	//24-bit-truecolor ���� ó��
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i=m_x1*3; i < m_x1*3 + (m_x2 - m_x1)*3 ;i+=3)
		{
			for(int j=m_y1; j < m_y1 + (m_y2 - m_y1); j++)
			{
				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i + 2] = 0;  //�簢�� �׸���(R)
				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i + 1] = 0;  //�簢�� �׸���(G)
				pDoc->m_OutputImage[(pDoc->m_infoheader.biHeight - 1 - j)*(pDoc->m_rwsize) + i] = 0;	
			}
		}
	}

	Invalidate();

}

//���� ��� ���� ó��
void CImageProcessingView::OnLightadjust()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CLightAdjustmentDlg dlg;
	if(dlg.DoModal() == IDOK){
		m_LightInput = dlg.m_LightInput;
	}
	else{
		m_LightInput = 0;
	}

	if (m_LightInput > 50 || m_LightInput < -50)
	{
		AfxMessageBox(L"��� �Է°��� �ùٸ��� �ʽ��ϴ�!");
		return;
	}

	if (pDoc->m_infoheader.biBitCount == 8) //8-bit grayscale ���� ó��
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
	else if (pDoc->m_infoheader.biBitCount == 24) // Ʈ�� Į�� ���� ó��
	{
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				//������ �ִ� ��⳪, �ּҹ�⸦ ����ٸ�,
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

//���� ����ȭ ó��
void CImageProcessingView::OnBinarization()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int ThresholdValue = 0;
	int RedThresholdValue = 0;
	int GreenThresholdValue = 0;
	int BlueThresholdValue = 0;
		//���� ����ȭ ó��

	if (pDoc->m_infoheader.biBitCount == 8) //8-bit grayscale ���� ó��
	{
		//��� �ȼ����� ��� ��
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
				ThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + j];

		//��� �ȼ����� ��� ���(����ȭ�� ���� �Ӱ谪)
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
	else if (pDoc->m_infoheader.biBitCount == 24) // Ʈ�� Į�� ���� ó��
	{
		//��� RGB ���� �ȼ����� ��� ��
		for (int i = 0; i<pDoc->m_infoheader.biHeight; i++)
		{
			for (int j = 0; j<pDoc->m_infoheader.biWidth; j++)
			{
				RedThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 2];
				GreenThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j + 1];
				BlueThresholdValue += pDoc->m_OutputImage[i*pDoc->m_rwsize + 3 * j];
			}
		}
		//��� R�ȼ����� ��� ���(����ȭ�� ���� �Ӱ谪)
		RedThresholdValue /= (pDoc->m_infoheader.biHeight*pDoc->m_infoheader.biWidth);
		//��� G�ȼ����� ��� ���(����ȭ�� ���� �Ӱ谪)
		GreenThresholdValue /= (pDoc->m_infoheader.biHeight*pDoc->m_infoheader.biWidth);
		//��� B�ȼ����� ��� ���(����ȭ�� ���� �Ӱ谪)
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//8-bit-grayscale ���� ó��
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

	//24-bit-truecolor ���� ó��
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//���� ó���� ���ؼ�, �������� ����
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


	//8-bit-grayscale ���� ó��
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

	//24-bit-truecolor ���� ó��
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

	//�޸� �Ҵ� ����
	delete CopyImage;

	Invalidate();
}



void CImageProcessingView::OnImageflip()
{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//���� ó���� ���ؼ�, �������� ����
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


	//8-bit-grayscale ���� ó��
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

	//24-bit-truecolor ���� ó��
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

	//�޸� �Ҵ� ����
	delete CopyImage;

	Invalidate();
}

//���� ���� �Լ�
void CImageProcessingView::OnEdgedetect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//LaplacianMask(���ö�þ� ����ũ)
	int LaplacianMask[3][3] = {
		{-1,-1,-1},
		{-1,8,-1},
		{-1,-1,-1}};


	//���� ó���� ���ؼ�, �������� ����
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

	//8-bit-grayscale ���� ó��
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

				//���� �������� ������ �Ӱ谪���� ����ȭ
				if(result > 255)
					result = 255;
				else if(result < 0)
					result = 0;
	
				pDoc->m_OutputImage[i*pDoc->m_rwsize + j] = result;
			}

		}
	}

	//24-bit-truecolor ���� ó��
	if(pDoc->m_infoheader.biBitCount == 24)
	{
		for(int i = 1; i < pDoc->m_height;i++)
		{
			for( int  j = 1; j < pDoc->m_width;j++)
			{

				int result = 0;
				int grayscale = 0;

				//24bit turecolor�� ���, 8-bit-grayscale �������� ��ȯ��, ���� �����ؾ���
				//������ ������, 24bit-truecolor ������ 8-bit-grayscale�������� ��ȯ���Ѽ� ���� �����ִ� ������.
				for(int y=0; y<3; y++)
					for(int x=0; x<3; x++)
					{
						grayscale += 0.299*CopyImage[(i + y - 1)*pDoc->m_rwsize + j*3 + 2 + x - 1];
						grayscale += 0.587*CopyImage[(i + y - 1)*pDoc->m_rwsize + j*3 + 1 + x - 1];
						grayscale += 0.114*CopyImage[(i + y - 1)*pDoc->m_rwsize + j*3 + x - 1];
						result += LaplacianMask[y][x]*grayscale;
					}

				//���� �������� ������ �Ӱ谪���� ����ȭ
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
