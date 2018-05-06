
// ImageProcessingDoc.h : CImageProcessingDoc 클래스의 인터페이스
//


#pragma once
#define WIDTHBYTES(bits) (((bits)+31)/32*4)  //4바이트 단위의 행에 대한 데이터양을 계산하기 위한 매크로
#define BYTE unsigned char

class CImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	BYTE * m_InputImage;		//입력 영상 데이터
	BYTE * m_OutputImage;		//출력 영상 데이터
	int m_width;				//가로 길이
	int m_height;				//세로 길이
	int m_size;					//영상 데이터 크기
	BITMAPFILEHEADER m_fileheader;	//파일 헤더
	BITMAPINFOHEADER m_infoheader;	//비트맵 정보 헤더
	RGBQUAD* m_pRGB;				//팔레트 배열
	int m_rwsize;					//한 행당 4btye로 계산
	CString m_FileSizeFormat;
	int m_FileSize;
	bool m_CompressionCheck;
	LPCTSTR m_FileName;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void RLEDecompression(void);	//RLE 압축 해제 함수
};
