#pragma once


// CSquareDlg 대화 상자입니다.

class CSquareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSquareDlg)

public:
	CSquareDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSquareDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
};
