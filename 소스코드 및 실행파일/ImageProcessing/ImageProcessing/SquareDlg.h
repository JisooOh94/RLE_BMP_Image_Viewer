#pragma once


// CSquareDlg ��ȭ �����Դϴ�.

class CSquareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSquareDlg)

public:
	CSquareDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSquareDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
};
