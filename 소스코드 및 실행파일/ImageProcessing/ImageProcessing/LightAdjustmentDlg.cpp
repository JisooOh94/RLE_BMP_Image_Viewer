// LightAdjustmentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "LightAdjustmentDlg.h"
#include "afxdialogex.h"


// CLightAdjustmentDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLightAdjustmentDlg, CDialogEx)

CLightAdjustmentDlg::CLightAdjustmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLightAdjustmentDlg::IDD, pParent)
	, m_LightInput(0)
{

}

CLightAdjustmentDlg::~CLightAdjustmentDlg()
{
}

void CLightAdjustmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_LightInput);
}


BEGIN_MESSAGE_MAP(CLightAdjustmentDlg, CDialogEx)
END_MESSAGE_MAP()


// CLightAdjustmentDlg �޽��� ó�����Դϴ�.
