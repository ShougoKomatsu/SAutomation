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
	
	m_brRed.CreateSolidBrush(RGB(255,75,0));
	m_brGreen.CreateSolidBrush(RGB(64, 255, 89));
	m_brBlack.CreateSolidBrush(RGB(0,0,0));
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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
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
	
	CRect rect;
	GetClientRect(&rect);

	CWnd* cwnd;
	cwnd=GetDlgItem(IDC_COMPACT_BUTTON_CLOSE);
	cwnd->MoveWindow(rect.Width()-20,0,20,20);
	cwnd=GetDlgItem(IDC_COMPACT_BUTTON_MINIMIZE);
	cwnd->MoveWindow(rect.Width()-40,0,20,20);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CDlgCompact::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_COMPACT_DISP_MOUSPOS)
	{
		if(m_bMoving==TRUE)
		{
			CPoint point;		
			GetCursorPos(&point);

			CRect rect;
			GetWindowRect(&rect);

			WinodowMove(m_iX, m_iY,point.x-rect.left, point.y-rect.top);
		}
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
		m_bRunning=FALSE;
	Invalidate();
	}
	else
	{
		ChangeIcon(IDI_ICON_RUNNING);
		m_bRunning=TRUE;
	Invalidate();
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


void CDlgCompact::OnLButtonDown(UINT nFlags, CPoint point)
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_COMPACT_BUTTON_CLOSE);
	int iCheck;

	m_iX=point.x;
	m_iY=point.y;
	m_bMoving=TRUE;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgCompact::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	m_bMoving=FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}

	void CDlgCompact::WinodowMove(int ixFrom, int iyFrom, int ixTo, int iyTo)
	{
		CRect rect;
		GetWindowRect(&rect);
		MoveWindow(rect.left+ixTo-ixFrom, rect.top+iyTo-iyFrom,rect.Width(), rect.Height());
	}

void CDlgCompact::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bMoving==TRUE)
	{
		WinodowMove(m_iX, m_iY, point.x,point.y);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDlgCompact::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBrush* pOldBrush;
	
	if(m_bRunning==TRUE)
	{
		pOldBrush = dc.SelectObject(&m_brGreen);
		dc.Rectangle(2,2,2+12,2+12);
		dc.SelectObject(pOldBrush);

		pOldBrush = dc.SelectObject(&m_brBlack);
		dc.Rectangle(2+16,2,2+16+12,2+12);
		dc.SelectObject(pOldBrush);
	}
	else
	{
		CBrush* pOldBrush = dc.SelectObject(&m_brBlack);
		dc.Rectangle(2,2,2+12,2+12);
		dc.SelectObject(pOldBrush);

		pOldBrush = dc.SelectObject(&m_brRed);
		dc.Rectangle(2+16,2,2+16+12,2+12);
		dc.SelectObject(pOldBrush);
	}

}


HBRUSH CDlgCompact::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}
