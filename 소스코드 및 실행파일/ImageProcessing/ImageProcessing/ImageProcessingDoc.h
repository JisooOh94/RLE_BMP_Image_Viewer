
// ImageProcessingDoc.h : CImageProcessingDoc Ŭ������ �������̽�
//


#pragma once
#define WIDTHBYTES(bits) (((bits)+31)/32*4)  //4����Ʈ ������ �࿡ ���� �����;��� ����ϱ� ���� ��ũ��
#define BYTE unsigned char

class CImageProcessingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	BYTE * m_InputImage;		//�Է� ���� ������
	BYTE * m_OutputImage;		//��� ���� ������
	int m_width;				//���� ����
	int m_height;				//���� ����
	int m_size;					//���� ������ ũ��
	BITMAPFILEHEADER m_fileheader;	//���� ���
	BITMAPINFOHEADER m_infoheader;	//��Ʈ�� ���� ���
	RGBQUAD* m_pRGB;				//�ȷ�Ʈ �迭
	int m_rwsize;					//�� ��� 4btye�� ���
	CString m_FileSizeFormat;
	int m_FileSize;
	bool m_CompressionCheck;
	LPCTSTR m_FileName;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void RLEDecompression(void);	//RLE ���� ���� �Լ�
};
