// SquareDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "SquareDlg.h"
#include "afxdialogex.h"


// CSquareDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSquareDlg, CDialogEx)

CSquareDlg::CSquareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSquareDlg::IDD, pParent)
	, m_x1(0)
	, m_y1(0)
	, m_x2(0)
	, m_y2(0)
{

}

CSquareDlg::~CSquareDlg()
{
}

void CSquareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_x1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_y1);
	DDX_Text(pDX, IDC_EDIT_X2, m_x2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_y2);
}


BEGIN_MESSAGE_MAP(CSquareDlg, CDialogEx)
END_MESSAGE_MAP()


// CSquareDlg 메시지 처리기입니다.
