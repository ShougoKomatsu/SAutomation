
// SAutomationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "psapi.h"
#include "SAutomation.h"
#include "SAutomationDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_COMPACT_DISP_MOUSPOS (100)

#define TIMER_THREAD_WATCH (101)
#define TIMER_WAKE_UP (102)
#define TIMER_REHOOK (103)
#define ID_TRAY (1101)

// CSAutomationDlg ダイアログ


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	// 実装
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CSAutomationDlg::CSAutomationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSAutomationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hIconStandby = AfxGetApp()->LoadIcon(IDI_ICON_STANDBY);
	m_hIconRunning = AfxGetApp()->LoadIcon(IDI_ICON_RUNNING);
	m_hIconMinimize = AfxGetApp()->LoadIcon(IDI_ICON_MINIMIZE);
	m_hIconClose = AfxGetApp()->LoadIcon(IDI_ICON_CLOSE);
	
	m_brRed.CreateSolidBrush(RGB(255,75,0));
	m_brGreen.CreateSolidBrush(RGB(64, 255, 89));
	m_brBlack.CreateSolidBrush(RGB(0,0,0));
}

CSAutomationDlg::~CSAutomationDlg()
{
	DestroyIcon(m_hIconStandby);
	DestroyIcon(m_hIconRunning);
	DestroyIcon(m_hIconMinimize);
	DestroyIcon(m_hIconClose);
}
void CSAutomationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMPACT_EDIT_MOUSE_R, m_sEditCompactMouseR);
	DDX_Text(pDX, IDC_COMPACT_EDIT_MOUSE_C, m_sEditCompactMouseC);
	DDX_Control(pDX, IDC_COMPACT_BUTTON_MINIMIZE, m_ButtonMinimize);
	DDX_Control(pDX, IDC_COMPACT_BUTTON_CLOSE, m_ButtonClose);
}

BEGIN_MESSAGE_MAP(CSAutomationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_COMPACT_BUTTON_EXIT, &CSAutomationDlg::OnBnClickedButtonCompactExit)
	ON_WM_TIMER()
	ON_MESSAGE(WM_DISP_STANDBY, &CSAutomationDlg::OnDispStandby)
	ON_MESSAGE(WM_DISP_COMMAND, &CSAutomationDlg::OnDispCommand)
	ON_BN_CLICKED(IDC_COMPACT_BUTTON_MINIMIZE, &CSAutomationDlg::OnBnClickedCompactButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_COMPACT_BUTTON_CLOSE, &CSAutomationDlg::OnBnClickedCompactButtonClose)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
END_MESSAGE_MAP()


LRESULT CSAutomationDlg::OnDispStandby(WPARAM wParam, LPARAM lParam)
{

	UpdateData(TRUE);
	if(wParam<0){return 0;}
	if(wParam>=MAX_THREAD){return 0;}
	g_hThread[wParam]=NULL;

	g_Automation.m_OpeInfo[wParam].m_bRunning=FALSE;
	
	BOOL bRunningAny=FALSE;
	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		if(g_Automation.m_OpeInfo[iScene].m_bRunning != TRUE){continue;}
		bRunningAny=TRUE;
		break;
	}

	if(bRunningAny == FALSE)
	{
		ChangeIcon(IDI_ICON_STANDBY);
		((CButton*)GetDlgItem(IDC_COMPACT_EDIT_COMMAND))->SetWindowText(_T(""));
		((CButton*)GetDlgItem(IDC_COMPACT_EDIT_STEP))->SetWindowText(_T(""));
	}
	else
	{
		ChangeIcon(IDI_ICON_RUNNING);
	}
	
	return 0;
}

LRESULT CSAutomationDlg::OnDispCommand(WPARAM wParam, LPARAM lParam)
{
	CString sCommand;
	CString sStep;
	if(g_lLockCommandDisplay==0)
	{
		InterlockedExchange(&g_lLockCommandDisplay, 1);
		sStep.Format(_T("%d"), lParam);
		sCommand.Format(_T("%s"), g_sCommand[wParam]);
		InterlockedExchange(&g_lLockCommandDisplay, 0);

		((CButton*)GetDlgItem(IDC_COMPACT_EDIT_COMMAND))->SetWindowText(sCommand);
		((CButton*)GetDlgItem(IDC_COMPACT_EDIT_STEP))->SetWindowText(sStep);
	}
	return 0;
}

VOID GetExeOtherProcessIds(CString sTargetExeName, DWORD* dwExeProcessIds, DWORD dwIgnoreProcessId)
{
	DWORD dwAllProcessIds[1024] = { 0 };
	DWORD cbNeeded = 0;
	BOOL bRet;
	bRet = EnumProcesses(dwAllProcessIds, sizeof(dwAllProcessIds), &cbNeeded);
	if (bRet != TRUE){return;}

	int j = 0;
	int nProc = cbNeeded / sizeof(DWORD);
	for (int i = 0; i < nProc; i++)
	{
		if (dwAllProcessIds[i] == dwIgnoreProcessId){continue;}

		wchar_t szProcessName[MAX_PATH] = _T("<unknown>");

		HANDLE hProcess = NULL;
		hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwAllProcessIds[i]);
		if (hProcess == NULL){continue;}

		HMODULE hMod;
		DWORD cbNeeded;
		bRet = EnumProcessModules(hProcess, &hMod, sizeof(hMod),&cbNeeded);
		if (bRet != TRUE)
		{
			CloseHandle(hProcess);
			continue;
		}

		GetModuleBaseName(hProcess, hMod, szProcessName,sizeof(szProcessName) / sizeof(wchar_t));

		if (sTargetExeName.CompareNoCase(szProcessName)==0)
		{
			dwExeProcessIds[j] = dwAllProcessIds[i];
			j++;
		}
		CloseHandle(hProcess);
	}
}

BOOL CSAutomationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	DWORD dwCurrentProcessId = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwCurrentProcessId);
	wchar_t szModuleName[MAX_PATH];
	GetModuleBaseName(hProcess, NULL, szModuleName, MAX_PATH);
	//	AfxMessageBox(szModuleName);

//	CString sToken;
//	ExtractToken(_T("aaa,bbb,ccc"),2,&sToken);
//	ExtractToken(_T("aaa,bbb,ccc"),1,&sToken);
//	ExtractToken(_T("aaa,bbb,ccc"),2,&sToken);
//	CStringArray aaaa;
//	aaaa.Add(_T("1234"));
//	aaaa.Add(_T("%%d"));
//	AfxMessageBox(Int2Str(0, _T("1234"),_T("%d")));
	DWORD dwExeProcessIds[1024] = { 0 };
	GetExeOtherProcessIds(szModuleName, dwExeProcessIds, dwCurrentProcessId);

	if (dwExeProcessIds[0]>0)
	{
		AfxMessageBox(_T("多重起動"));
		//		return CDialogEx::DestroyWindow();
	}

	SetWindowText(_T("SAutomation"));
	g_hWnd = this->m_hWnd;
	
	POINT p;
	GetCursorPos(&p);
	g_iR=p.y-g_iOriginR;
	g_iC=p.x-g_iOriginC;
	g_hhook = NULL;
	
	SetTimer(TIMER_THREAD_WATCH,200, NULL);
	SetTimer(TIMER_WAKE_UP, 100, NULL);
	SetTimer(TIMER_REHOOK, 10000, NULL);
	
	wchar_t szData[MAX_PATH];
	GetCurrentDirectory(sizeof(szData)/sizeof(wchar_t),szData);

	g_Automation.m_sDir.Format(_T("%s"),szData);
	g_sDir.Format(_T("%s"),szData);

	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),g_Automation.m_sDir);

	CString sLogFolderPath;
	sLogFolderPath.Format(_T("%s\\Log"),g_Automation.m_sDir);

	CString sModelFolderPath;
	sModelFolderPath.Format(_T("%s\\Macro\\Model"),g_Automation.m_sDir);
	
	CFileFind cf;
	if(cf.FindFile(sMacroFolderPath) != TRUE){_tmkdir(sMacroFolderPath);}
	if(cf.FindFile(sLogFolderPath) != TRUE){_tmkdir(sLogFolderPath);}
	if(cf.FindFile(sModelFolderPath) != TRUE){_tmkdir(sModelFolderPath);}
	g_Automation.ReadSettings();
	
	g_bHalt = FALSE;
	
	if(g_Automation.m_bEnableHotkey==TRUE)
	{
		for(int iScene=0; iScene<MAX_NORMAL_THREAD; iScene++){ResetHotkey(iScene);}
		for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++){ResetHotkey(MAX_NORMAL_THREAD+iExScene);}
	}

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
	SetIcon(m_hIconStandby, TRUE);
	
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


BOOL CSAutomationDlg::ChangeIcon(int iIcon)
{
	switch(iIcon)
	{
	case IDI_ICON_STANDBY:
		{
			SetIcon(m_hIconStandby, FALSE);
			m_bRunning=FALSE;
			Invalidate();
			//		::PostMessage(m_cDlgSetting.m_hWnd,WM_DISP_STANDBY,0,0);
			break;
		}
	case IDI_ICON_RUNNING:
		{
			SetIcon(m_hIconRunning, FALSE);
			m_bRunning=TRUE;
			Invalidate();
			//		::PostMessage(m_cDlgSetting.m_hWnd,WM_DISP_STANDBY,1,0);
			break;
		}
	}
	
	TrayNotifyIconMessage(NIM_MODIFY, iIcon);

	return TRUE;
}

void CSAutomationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBrush* pOldBrush;
	
	if(m_bRunning==TRUE)
	{
		pOldBrush = dc.SelectObject(&m_brGreen);
		dc.Rectangle(2,2,2+12,2+12);
		dc.SelectObject(pOldBrush);
	}
	else
	{
		CBrush* pOldBrush = dc.SelectObject(&m_brBlack);
		dc.Rectangle(2,2,2+12,2+12);
		dc.SelectObject(pOldBrush);
	}

}

BOOL CSAutomationDlg::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		{
			if(pMsg->wParam == VK_RETURN){return TRUE;}
			if(pMsg->wParam == VK_ESCAPE){return TRUE;}
			if(pMsg->wParam == VK_SPACE){return TRUE;}
			break;
		}
	case WM_HOTKEY:
		{
			int iKey;
			iKey = (pMsg->lParam)>>16;
			for(int iScene=0; iScene<MAX_NORMAL_THREAD; iScene++)
			{
				if(iKey == g_Automation.m_OpeInfo[iScene].dwHotKey){Operate(iScene);return TRUE;}
			}
			for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++)
			{
				if(iKey == g_Automation.m_OpeInfo[MAX_NORMAL_THREAD+iExScene].dwHotKey){SelectAndOperate(iExScene);return TRUE;}

			}
			if(iKey == g_Automation.m_dwHotKeyEnable){ToggleEnable();return TRUE;}
			if(iKey == VK_ESCAPE){g_bHalt = TRUE;}
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSAutomationDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_REHOOK)
	{
		ReHookWindowsHook();
		return;
	}
	if(nIDEvent == TIMER_THREAD_WATCH)
	{
		for(int iScene = 0; iScene< MAX_THREAD; iScene++)
		{
			if(g_hThread[iScene] == NULL){continue;}
			if(g_iWatching == 0)
			{
				RegisterHotKey(NULL, HOTKEY_ESCAPE, MOD_NOREPEAT, VK_ESCAPE);
				g_iWatching=1;
			}
			return;
		}
		if(g_iWatching==1){UnregisterHotKey(NULL, HOTKEY_ESCAPE); g_iWatching=0;}
	}
	if(nIDEvent == TIMER_WAKE_UP)
	{
		KillTimer(TIMER_WAKE_UP);
		ReHookWindowsHook();
		if(g_Automation.m_bAutoMinimize==TRUE)
		{
			ShowWindow(SW_MINIMIZE);
		}
	}
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


void CSAutomationDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bMoving==TRUE)
	{
		WinodowMove(m_iX, m_iY, point.x,point.y);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CSAutomationDlg::Operate(int iScene)
{
	ChangeIcon(IDI_ICON_RUNNING);
	g_Automation.Operate(iScene);
}


void CSAutomationDlg::SelectAndOperate(int iExScene)
{
	for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
	{
		m_cDlgSelect.m_sSelectKeys[iSelect].Format(_T("%s"), g_Automation.m_sSelectKeys[iExScene][iSelect]);
		m_cDlgSelect.m_sSelectFiles[iSelect].Format(_T("%s"), g_Automation.m_sSelectFiles[iExScene][iSelect]);
	}
	m_cDlgSelect.m_iModeOperate=1;
	int iRet = m_cDlgSelect.DoModal();
	if(iRet != IDOK){return;}

	
	SetSelection(iExScene, m_cDlgSelect.m_sResultFileName);
	Operate(MAX_NORMAL_THREAD+iExScene);
}
void CSAutomationDlg::SetSelection(int iExScene, CString sFilePath)
{
	g_Automation.m_OpeInfo[MAX_NORMAL_THREAD+ iExScene].sFileName.Format(_T("%s"), sFilePath);
}

BOOL CSAutomationDlg::DestroyWindow()
{
	g_bHalt = TRUE;
	Sleep(1000);

	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}

	UpdateData(TRUE);

	return CDialogEx::DestroyWindow();
}

void CSAutomationDlg::ResetHotkey(int iScene)
{
	UpdateData(TRUE);
	UnregisterHotKey(NULL, HOTKEY_SCENE_0+iScene);

	if(g_Automation.m_bEnableHotkey==TRUE)
	{
		RegisterHotKey(NULL, HOTKEY_SCENE_0+iScene, 
			(MOD_SHIFT*g_Automation.m_OpeInfo[iScene].bUseShift) 
			| (MOD_CONTROL*g_Automation.m_OpeInfo[iScene].bUseCtrl) 
			| (MOD_ALT*g_Automation.m_OpeInfo[iScene].bUseAlt) 
			| (MOD_WIN*g_Automation.m_OpeInfo[iScene].bUseWin) 
			| MOD_NOREPEAT
			, g_Automation.m_OpeInfo[iScene].dwHotKey);
	}
	UpdateData(FALSE);
}

void CSAutomationDlg::ToggleEnable()
{
	if(g_Automation.m_bEnableHotkey==TRUE)
	{
		g_Automation.m_bEnableHotkey=FALSE;
	}
	else
	{
		g_Automation.m_bEnableHotkey=TRUE;
	}
	for(int iScene=0; iScene<MAX_NORMAL_THREAD; iScene++){ResetHotkey(iScene);}
	for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++){ResetHotkey(MAX_NORMAL_THREAD+iExScene);}
}

BOOL CSAutomationDlg::ReHookWindowsHook()
{
	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	Sleep(100);
	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);
	if(g_hhook == NULL){return FALSE;}
	return TRUE;
}



void CSAutomationDlg::OnBnClickedButtonCompactExit()
{
	CSettingDlg settingDlg;
	settingDlg.m_sDir.Format(_T("%s"),g_sDir);
	settingDlg.DoModal();
	
	if(g_Automation.m_bEnableHotkey==TRUE)
	{
		for(int iScene=0; iScene<MAX_NORMAL_THREAD; iScene++){ResetHotkey(iScene);}
		for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++){ResetHotkey(MAX_NORMAL_THREAD+iExScene);}
	}
}




void CSAutomationDlg::OnBnClickedCompactButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


int CSAutomationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1){return -1;}

	return 0;
}


void CSAutomationDlg::OnBnClickedCompactButtonClose()
{
	CDialogEx::OnOK();
}


void CSAutomationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_COMPACT_BUTTON_CLOSE);

	m_iX=point.x;
	m_iY=point.y;
	m_bMoving=TRUE;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSAutomationDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	m_bMoving=FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}

	void CSAutomationDlg::WinodowMove(int ixFrom, int iyFrom, int ixTo, int iyTo)
	{
		CRect rect;
		GetWindowRect(&rect);
		MoveWindow(rect.left+ixTo-ixFrom, rect.top+iyTo-iyFrom,rect.Width(), rect.Height());
	}



HBRUSH CSAutomationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}



void CSAutomationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	if (nType == SIZE_MINIMIZED)
	{
		if(g_Automation.m_bMinimizeToTaskTray==TRUE)
		{
			TrayNotifyIconMessage(NIM_ADD, IDI_ICON_STANDBY);
			ShowWindow(SW_HIDE);
			KillTimer(TIMER_WAKE_UP);
		}
	}
}

LRESULT CSAutomationDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONUP: 
		{
			if (wParam == ID_TRAY)
			{
				ShowWindow(SW_NORMAL);
				SetForegroundWindow();
				SetFocus();
				TrayNotifyIconMessage(NIM_DELETE, IDI_ICON_STANDBY);
			} 
			break;
		}
	default:
		{
			break;
		}
	} 

	return 0;
}

BOOL CSAutomationDlg::TrayNotifyIconMessage(DWORD dwMessage, int iIconID)
{
	CString sTip = _T("SAutomation.exe");
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd   = GetSafeHwnd();
	nid.uID    = ID_TRAY;
	nid.uFlags = NIF_MESSAGE | NIF_ICON;
	nid.uCallbackMessage = WM_TRAYNOTIFY;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.hIcon  = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(iIconID));
	_tcscpy_s(nid.szTip, _countof(nid.szTip), (LPCTSTR)sTip);

	return Shell_NotifyIcon(dwMessage, &nid);
}
