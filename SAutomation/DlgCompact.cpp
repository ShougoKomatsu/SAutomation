// DlgCompact.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "DlgCompact.h"
#include "afxdialogex.h"


#define TIMER_COMPACT_DISP_MOUSPOS (100)


// CDlgCompact ダイアログ

IMPLEMENT_DYNAMIC(CDlgCompact, CDialogEx)

CDlgCompact::CDlgCompact(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCompact::IDD, pParent)
	, m_sEditCompactMouseR(_T(""))
{
	m_hIconStandby = AfxGetApp()->LoadIcon(IDI_ICON_STANDBY);
	m_hIconRunning = AfxGetApp()->LoadIcon(IDI_ICON_RUNNING);

}

CDlgCompact::~CDlgCompact()
{
}

void CDlgCompact::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COMPACT_MOUSE_R, m_sEditCompactMouseR);
	DDX_Text(pDX, IDC_EDIT_COMPACT_MOUSE_C, m_sEditCompactMouseC);
}


BEGIN_MESSAGE_MAP(CDlgCompact, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMPACT_EXIT, &CDlgCompact::OnBnClickedButtonCompactExit)
	ON_WM_TIMER()
	ON_MESSAGE(WM_DISP_STANDBY, &CDlgCompact::OnDispStandby)
END_MESSAGE_MAP()


// CDlgCompact メッセージ ハンドラー


void CDlgCompact::OnBnClickedButtonCompactExit()
{
	CDialog::OnOK();
}

BOOL CDlgCompact::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(TIMER_COMPACT_DISP_MOUSPOS,200, NULL);

	CRect rectDisp;
	SystemParametersInfo( SPI_GETWORKAREA, NULL, &rectDisp, NULL);
	
	CRect rectDlg;
	GetWindowRect(&rectDlg);

	MoveWindow(rectDisp.Width()-rectDlg.Width(), rectDisp.Height()-rectDlg.Height(),rectDlg.Width(),rectDlg.Height());

		::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);
		
	SetIcon(m_hIconStandby, TRUE);
	SetIcon(m_hIconStandby, FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CDlgCompact::OnTimer(UINT_PTR nIDEvent)
{
	
	if(nIDEvent == TIMER_COMPACT_DISP_MOUSPOS)
	{
		UpdateData(TRUE);
		m_sEditCompactMouseR.Format(_T("%d"),g_iR);
		m_sEditCompactMouseC.Format(_T("%d"),g_iC);
		UpdateData(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CDlgCompact::ChangeIcon(int iIcon)
{
	switch(iIcon)
	{
	case IDI_ICON_STANDBY:
		{
			SetIcon(m_hIconStandby, TRUE);
			SetIcon(m_hIconStandby, FALSE);	
			break;
		}
	case IDI_ICON_RUNNING:
		{
			SetIcon(m_hIconRunning, TRUE);
			SetIcon(m_hIconRunning, FALSE);	
			break;
		}
	}

	return TRUE;
}


LRESULT CDlgCompact::OnDispStandby(WPARAM wParam, LPARAM lParam)
{

	UpdateData(TRUE);

	if(wParam==0)
	{
		ChangeIcon(IDI_ICON_STANDBY);
	}
	else
	{
		ChangeIcon(IDI_ICON_RUNNING);
	}

	return 0;
}
