#pragma once


// CLightAdjustmentDlg ��ȭ �����Դϴ�.

class CLightAdjustmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightAdjustmentDlg)

public:
	CLightAdjustmentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLightAdjustmentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_LightInput;
};
