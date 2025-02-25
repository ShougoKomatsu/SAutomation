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
	m_hIconMinimize = AfxGetApp()->LoadIcon(IDI_ICON_MINIMIZE);
	m_hIconClose = AfxGetApp()->LoadIcon(IDI_ICON_CLOSE);

}

CDlgCompact::~CDlgCompact()
{
DestroyIcon(m_hIconStandby);
DestroyIcon(m_hIconRunning);
DestroyIcon(m_hIconMinimize);
DestroyIcon(m_hIconClose);
}

void CDlgCompact::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMPACT_EDIT_MOUSE_R, m_sEditCompactMouseR);
	DDX_Text(pDX, IDC_COMPACT_EDIT_MOUSE_C, m_sEditCompactMouseC);
	DDX_Control(pDX, IDC_COMPACT_BUTTON_MINIMIZE, m_ButtonMinimize);
	DDX_Control(pDX, IDC_COMPACT_BUTTON_CLOSE, m_ButtonClose);
}


BEGIN_MESSAGE_MAP(CDlgCompact, CDialogEx)
	ON_BN_CLICKED(IDC_COMPACT_BUTTON_EXIT, &CDlgCompact::OnBnClickedButtonCompactExit)
	ON_WM_TIMER()
	ON_MESSAGE(WM_DISP_STANDBY, &CDlgCompact::OnDispStandby)
	ON_BN_CLICKED(IDC_COMPACT_BUTTON_MINIMIZE, &CDlgCompact::OnBnClickedCompactButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_COMPACT_BUTTON_CLOSE, &CDlgCompact::OnBnClickedCompactButtonClose)
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
	SetWindowText(_T("SAutomation"));
	MoveWindow(rectDisp.Width()-rectDlg.Width(), rectDisp.Height()-rectDlg.Height(),rectDlg.Width(),rectDlg.Height());
	m_ButtonMinimize.SetIcon(m_hIconMinimize);
	m_ButtonClose.SetIcon(m_hIconClose);
	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);
	SetIcon(m_hIconStandby, FALSE);
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


BOOL CDlgCompact::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN){return TRUE;}
		if(pMsg->wParam == VK_ESCAPE){return TRUE;}
		if(pMsg->wParam == VK_SPACE){return TRUE;}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgCompact::OnBnClickedCompactButtonMinimize()
{
	pParent->ShowWindow(SW_MINIMIZE);
}


int CDlgCompact::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CDlgCompact::OnBnClickedCompactButtonClose()
{
	CDialog::EndDialog(2);
}
