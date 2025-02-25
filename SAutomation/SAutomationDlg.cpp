
// SAutomationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "psapi.h"
#include "SAutomation.h"
#include "SAutomationDlg.h"
#include "afxdialogex.h"
#include "Thread.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "InputDialog.h"
#include "Window.h"
#include "variables.h"
#include "ImgProc.h"

#define TIMER_DISP_MOUSPOS (100)
#define TIMER_THREAD_WATCH (101)
#define TIMER_WAKE_UP (102)
#define TIMER_REHOOK (103)



BOOL g_bCompactBiew;


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

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


// CSAutomationDlg ダイアログ  




CSAutomationDlg::CSAutomationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSAutomationDlg::IDD, pParent)
	, m_sEditMousePosC(_T(""))
	, m_sEditMousePosR(_T(""))
	, m_sEditSpeed(_T(""))
{
	m_hIconStandby = AfxGetApp()->LoadIcon(IDI_ICON_STANDBY);
	m_hIconRunning = AfxGetApp()->LoadIcon(IDI_ICON_RUNNING);
}

void CSAutomationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAIN_EDIT_MOUSEPOS_C, m_sEditMousePosC);
	DDX_Text(pDX, IDC_MAIN_EDIT_MOUSEPOS_R, m_sEditMousePosR);
	DDX_Control(pDX, IDC_MAIN_COMBO_ENABLE_HOTKEY, m_comboEnable);

	DDX_Control(pDX, IDC_MAIN_COMBO_WINDOW_NAME, m_comboWindowName);

	DDX_Control(pDX, IDC_MAIN_COMBO_LOG_LEVEL, m_comboLogLevel);
	DDX_Text(pDX, IDC_MAIN_EDIT_SPEED, m_sEditSpeed);
	DDX_Control(pDX, IDC_MAIN_SLIDER_SPEED, m_sliderSpeed);
	DDX_Control(pDX, IDC_COMPACT_TAB_OPERATION, m_tab);
}

BEGIN_MESSAGE_MAP(CSAutomationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_DISP_STANDBY, &CSAutomationDlg::OnDispStandby)
	ON_BN_CLICKED(IDC_MAIN_CHECK_ENABLE_HOTKEY, &CSAutomationDlg::OnBnClickedCheckEnableHotkey)
	ON_CBN_SELCHANGE(IDC_MAIN_COMBO_ENABLE_HOTKEY, &CSAutomationDlg::OnSelchangeCombo0Enable)

	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MAIN_BUTTON_OPEN_FOLDER, &CSAutomationDlg::OnBnClickedButton0OpenFolder)
	ON_EN_KILLFOCUS(IDC_MAIN_EDIT_SPEED, &CSAutomationDlg::OnKillfocusEditSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAIN_SLIDER_SPEED, &CSAutomationDlg::OnCustomdrawSliderSpeed)
	ON_BN_CLICKED(IDC_MAIN_BUTTON_REFRESH_WINDOW_NAME, &CSAutomationDlg::OnBnClickedButton0WindowNameRefresh)
	ON_CBN_SELCHANGE(IDC_MAIN_COMBO_WINDOW_NAME, &CSAutomationDlg::OnSelchangeWindowName)
	ON_NOTIFY(TCN_SELCHANGE, IDC_COMPACT_TAB_OPERATION, &CSAutomationDlg::OnTcnSelchangeTabOperation)
	ON_BN_CLICKED(IDC_MAIN_BUTTON_OPEN_COMPACT, &CSAutomationDlg::OnBnClickedButtonOpenCompact)
	ON_BN_CLICKED(IDOK, &CSAutomationDlg::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CSAutomationDlg メッセージ ハンドラー
BOOL g_iMninizedOnce=FALSE;




LRESULT CSAutomationDlg::OnDispStandby(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);
	if(wParam<0){return 0;}
	if(wParam>=MAX_THREAD){return 0;}
	g_hThread[wParam]=NULL;
	//m_tabItem.m_sEditStatus[wParam].Format(_T("Stand by"));
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);

	g_Automation.m_OpeInfo[wParam].m_bRunning=FALSE;

	m_bRunningAny=FALSE;
	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		if(g_Automation.m_OpeInfo[iScene].m_bRunning==TRUE)
		{
			m_bRunningAny=TRUE;
			if(m_cDlgCompact.m_hWnd != NULL)
			{
				::PostMessage(m_cDlgCompact.m_hWnd,WM_DISP_STANDBY,1,0);
			}
			break;
		}
	}
	
	if(m_cDlgCompact.m_hWnd != NULL){::PostMessage(m_cDlgCompact.m_hWnd,WM_DISP_STANDBY,0,0);}
	if(m_bRunningAny==FALSE){ChangeIcon(IDI_ICON_STANDBY);}

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

		TCHAR szProcessName[MAX_PATH] = _T("<unknown>");

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

		GetModuleBaseName(hProcess, hMod, szProcessName,sizeof(szProcessName) / sizeof(TCHAR));

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

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	DWORD dwCurrentProcessId = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwCurrentProcessId);
	TCHAR szModuleName[MAX_PATH];
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
	
	SetTimer(TIMER_DISP_MOUSPOS,200, NULL);
	SetTimer(TIMER_THREAD_WATCH,200, NULL);
	SetTimer(TIMER_WAKE_UP, 100, NULL);
	SetTimer(TIMER_REHOOK, 10000, NULL);

	TCHAR szData[MAX_PATH];
	GetCurrentDirectory(sizeof(szData)/sizeof(TCHAR),szData);

	g_Automation.m_sDir.Format(_T("%s"),szData);
	g_sDir.Format(_T("%s"),szData);

	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),g_Automation.m_sDir);

	CString sLogFolderPath;
	sLogFolderPath.Format(_T("%s\\Log"),g_Automation.m_sDir);

	CString sModelFolderPath;
	sModelFolderPath.Format(_T("%s\\Macro\\Model"),g_Automation.m_sDir);


	m_tab.SubclassDlgItem(IDC_COMPACT_TAB_OPERATION, this);

	m_tab.InsertItem(0, _T("0 - 15"));
	m_tab.InsertItem(1, _T("16 - 31"));
	m_tab.InsertItem(3, _T("32 - 47"));
	m_tab.InsertItem(3, _T("48 - 63"));


	m_tabItem.Create(IDD_DIALOG_TAB_ITEMS, &m_tab);
	m_tabItem.pParent=this;	
	CRect rect;
	m_tab.GetWindowRect(rect);
	m_tab.AdjustRect(FALSE, rect);
	m_tab.ScreenToClient(rect);

	m_tabItem.MoveWindow(rect);

	m_tabItem.ShowWindow(SW_SHOW);

	CFileFind cf;
	if(cf.FindFile(sMacroFolderPath) != TRUE){_tmkdir(sMacroFolderPath);}
	if(cf.FindFile(sLogFolderPath) != TRUE){_tmkdir(sLogFolderPath);}
	if(cf.FindFile(sModelFolderPath) != TRUE){_tmkdir(sModelFolderPath);}
	g_Automation.ReadSettings();
	SetComboItem(&m_comboEnable,g_Automation.m_sHotkeyEnable);

	m_tabItem.m_iSlot=0;
	m_tabItem.RefleshDialog(0);
	g_bCompactBiew=FALSE;

	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);

	g_bHalt = FALSE;

	if(g_Automation.m_sHotkeyEnable.GetLength()==1)
	{
		RegisterHotKey(NULL, HOTKEY_ENABLE, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, g_Automation.m_dwHotKeyEnable);
	}


	if(g_Automation.m_bAutoMinimize==TRUE)
	{
		((CButton*)GetDlgItem(IDC_MIAIN_CHECK_AUTO_MINIMIZE))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_MIAIN_CHECK_AUTO_MINIMIZE))->SetCheck(0);
	}


	if(g_Automation.m_bLog==TRUE)
	{
		((CButton*)GetDlgItem(IDC_MAIN_CHECK_LOG))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_MAIN_CHECK_LOG))->SetCheck(0);
	}

	m_comboLogLevel.ResetContent();
	m_comboLogLevel.AddString(_T("OnlyCritical"));
	m_comboLogLevel.AddString(_T("4"));
	m_comboLogLevel.AddString(_T("3"));
	m_comboLogLevel.AddString(_T("2"));
	m_comboLogLevel.AddString(_T("All"));
	m_comboLogLevel.SetCurSel(g_Automation.m_iLogLevel-1);


	if(g_Automation.m_bEnableHotkey==TRUE)
	{
		((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->SetCheck(1);
		for(int iScene=0; iScene<MAX_THREAD; iScene++){ResetHotkey(iScene);}
	}
	else
	{
		((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->SetCheck(0);
	}
	m_sEditSpeed.Format(_T("1.00"));
	m_sliderSpeed.SetRangeMin(0);	
	m_sliderSpeed.SetRangeMax(100);
	m_sliderSpeed.SetPos(50);

	WindowNameRefresh();
	RefreshTargetWindowPos();
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);


/*	ImgRGB imgTest;
	imgTest.Assign(_T("D:\\GitHub\\SAutomation\\SAutomation\\SAutomation\\Macro\\Model\\test.bmp"));
	ImgRGBPyramid imgTestPyram;
	imgTestPyram.SetPyramid(&imgTest);
	WriteImage(&imgTestPyram.imgRGB, _T("D:\\GitHub\\SAutomation\\SAutomation\\SAutomation\\Macro\\Model\\test2.bmp"));
	*/
	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIconStandby, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIconStandby, FALSE);		// 小さいアイコンの設定
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

BOOL CSAutomationDlg::ChangeIcon(int iIcon)
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


void CSAutomationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSAutomationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIconStandby);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSAutomationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIconStandby);
}


BOOL CSAutomationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN){return TRUE;}
		if(pMsg->wParam == VK_ESCAPE){return TRUE;}
		if(pMsg->wParam == VK_SPACE){return TRUE;}
		//		if(pMsg->wParam == VK_LEFT){return MouseMoveAndDisp(VK_LEFT,10);}
		//		if(pMsg->wParam == VK_RIGHT){return MouseMoveAndDisp(VK_RIGHT,10);}
		//		if(pMsg->wParam == VK_UP){return MouseMoveAndDisp(VK_UP,10);}
		//		if(pMsg->wParam == VK_DOWN){return MouseMoveAndDisp(VK_DOWN,10);}
	}
	if(pMsg->message == WM_HOTKEY)
	{
		int iKey;
		iKey = (pMsg->lParam)>>16;
		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			if(iKey == g_Automation.m_OpeInfo[iScene].dwHotKey){Operate(iScene);return TRUE;}
		}
		if(iKey == g_Automation.m_dwHotKeyEnable){ToggleEnable();return TRUE;}
		if(iKey == VK_ESCAPE){g_bHalt = TRUE;}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSAutomationDlg::RefreshTargetWindowPos()
{
	if(g_Automation.m_sTargetWindowName.Compare(_T("Desktop"))==0)
	{
		ChangeMouseOrigin(0, 0);
		return;
	}

	RECT rect;
	BOOL bRet;
	bRet = GetWindowRectByName(g_Automation.m_sTargetWindowName,&rect);
	if(bRet!=TRUE)
	{
		ChangeMouseOrigin(0, 0);
	}

	ChangeMouseOrigin(rect.left, rect.top);
}

void CSAutomationDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	if(nIDEvent == TIMER_REHOOK)
	{
		ReHookWindowsHook();
		return;
	}
	if(nIDEvent == TIMER_DISP_MOUSPOS)
	{
		UpdateData(TRUE);
		m_sEditMousePosR.Format(_T("%d"),g_iR);
		m_sEditMousePosC.Format(_T("%d"),g_iC);
		UpdateData(FALSE);
	}
	if(nIDEvent == TIMER_THREAD_WATCH)
	{
		BOOL bAnyArrive = FALSE;
		for(int iScene = 0; iScene< MAX_THREAD; iScene++)
		{
			if(g_hThread[iScene] != NULL)
			{
				if(g_iWatching==0)
				{
					RegisterHotKey(NULL, HOTKEY_ESCAPE, MOD_NOREPEAT, VK_ESCAPE);
					g_iWatching=1;
				}
				return;
			}
		}
		if(g_iWatching==1){UnregisterHotKey(NULL, HOTKEY_ESCAPE); g_iWatching=0;}
	}
	if(nIDEvent == TIMER_WAKE_UP)
	{
		KillTimer(TIMER_WAKE_UP);
		ReHookWindowsHook();
		if(g_Automation.m_bAutoMinimize==TRUE)
		{
			ChangeToCompact();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CSAutomationDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	CDialogEx::OnMouseMove(nFlags, point);
}

void CSAutomationDlg::GetLogLavel(AutomationInfo* autoInfo)
{
	autoInfo->m_bLog = ((CButton*)GetDlgItem(IDC_MAIN_CHECK_LOG))->GetCheck();
	if(autoInfo->m_bLog==0)
	{
		autoInfo->m_iLogLevel=0;
	}
	else
	{
		TCHAR tch[32];
		m_comboLogLevel.GetLBText(m_comboLogLevel.GetCurSel(),tch);
		if(wcscmp(tch,_T("OnlyCritical"))==0){autoInfo->m_iLogLevel=1;}
		if(wcscmp(tch,_T("4"))==0){autoInfo->m_iLogLevel=2;}
		if(wcscmp(tch,_T("3"))==0){autoInfo->m_iLogLevel=3;}
		if(wcscmp(tch,_T("2"))==0){autoInfo->m_iLogLevel=4;}
		if(wcscmp(tch,_T("All"))==0){autoInfo->m_iLogLevel=5;}
	}
	return;
}
void CSAutomationDlg::Operate(int iScene)
{
	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);

	m_comboWindowName.SetCurSel(0);
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);

	GetLogLavel(&g_Automation);

	g_Automation.Operate(iScene);

	if(m_cDlgCompact.m_hWnd != NULL){::PostMessage(m_cDlgCompact.m_hWnd,WM_DISP_STANDBY,1,0);}


	//m_tabItem.m_sEditStatus[iScene].Format(_T("Running"));
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);
	ChangeIcon(IDI_ICON_RUNNING);
}



BOOL CSAutomationDlg::UpdateAutomationInfo(AutomationInfo* autoInfo)
{
	
	CString sData;
	TCHAR tch[32];



	if(m_comboEnable.GetCurSel()<0){autoInfo->m_sHotkeyEnable.Format(_T("b"));}
	else{m_comboEnable.GetLBText(m_comboEnable.GetCurSel(),tch); autoInfo->m_sHotkeyEnable.Format(_T("%s"), tch);}

	if(((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		autoInfo->m_bEnableHotkey=TRUE;
	}
	else
	{
		autoInfo->m_bEnableHotkey=FALSE;
	}


	if(((CButton*)GetDlgItem(IDC_MIAIN_CHECK_AUTO_MINIMIZE))->GetCheck()==1)
	{
		autoInfo->m_bAutoMinimize=TRUE;
	}
	else
	{
		autoInfo->m_bAutoMinimize=FALSE;
	}
	GetLogLavel(autoInfo);

	return TRUE;
}

BOOL CSAutomationDlg::DestroyWindow()
{
	g_bHalt = TRUE;
	Sleep(1000);

	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}

	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);
	UpdateAutomationInfo(&g_Automation);
	g_Automation.SaveSettings();

	return CDialogEx::DestroyWindow();
}




void CSAutomationDlg::OnSelchangeCombo0Enable()
{
	if(g_Automation.m_sHotkeyEnable.GetLength()==1)
	{
		UnregisterHotKey(NULL, HOTKEY_ENABLE);
	}

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_comboEnable.GetCurSel()<0){g_Automation.m_sHotkeyEnable.Format(_T(""));return;}
	m_comboEnable.GetLBText(m_comboEnable.GetCurSel(),tch);

	g_Automation.m_sHotkeyEnable.Format(_T("%s"), tch);
	if(wcscmp(tch,_T(" "))==0){return;}
	if((tch[0]>='a') && (tch[0]<='z')){g_Automation.m_dwHotKeyEnable = char(tch[0])-'a'+0x41;}
	if((tch[0]>='0') && (tch[0]<='9')){g_Automation.m_dwHotKeyEnable = char(tch[0])-'0'+0x30;}
	RegisterHotKey(NULL, HOTKEY_ENABLE, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, g_Automation.m_dwHotKeyEnable);
}




void CSAutomationDlg::ResetHotkey(int iScene)
{
	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);
	UnregisterHotKey(NULL, HOTKEY_SCENE_0+iScene);


	if(((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
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
	m_tabItem.UpdateData_My(FALSE);
}

void CSAutomationDlg::OnBnClickedCheckEnableHotkey()
{
	for(int iScene=0; iScene<MAX_THREAD; iScene++){ResetHotkey(iScene);}
	return;
}

void CSAutomationDlg::ToggleEnable()
{
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->SetCheck(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->SetCheck(1);
	}
	UpdateData(TRUE);
	OnBnClickedCheckEnableHotkey();
}


void CSAutomationDlg::OnSize(UINT nType, int cx, int cy)
{
	if(nType==0)
	{
		if(g_bCompactBiew==TRUE){ChangeToCompact();return;}
	}
	CDialogEx::OnSize(nType, cx, cy);

}


void CSAutomationDlg::OnBnClickedButton0OpenFolder()
{
	CString sMacroFolder;
	sMacroFolder.Format(_T("%s\\Macro"),g_Automation.m_sDir);
	ShellExecute(NULL, NULL, sMacroFolder, NULL, NULL, SW_SHOWNORMAL);
}




void CSAutomationDlg::OnKillfocusEditSpeed()
{
	UpdateData(TRUE);

	g_dSpeedMult=_ttof(m_sEditSpeed);
	if(g_dSpeedMult==0){g_dSpeedMult=1;m_sEditSpeed.Format(_T("1.00"));}

	if(g_dSpeedMult<1){m_sliderSpeed.SetPos(int(( g_dSpeedMult-0.1)/0.016));}
	else{m_sliderSpeed.SetPos(int(sqrt(g_dSpeedMult)*50));}

	UpdateData(FALSE);
}


void CSAutomationDlg::OnCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	int iPos;
	iPos = m_sliderSpeed.GetPos();
	if(iPos<50){g_dSpeedMult = iPos*0.016+0.1;}
	else{g_dSpeedMult = iPos*iPos/2500.0;}
	m_sEditSpeed.Format(_T("%.02f"), g_dSpeedMult);
	UpdateData(FALSE);
	*pResult = 0;
}


void CSAutomationDlg::WindowNameRefresh()
{
	CStringArray caNames;
	GetWindowNameList(&caNames);
	m_comboWindowName.ResetContent();
	m_comboWindowName.AddString(_T("Desktop"));
	for(int i=0; i<caNames.GetCount(); i++)
	{
		m_comboWindowName.AddString(caNames.GetAt(i));
	}
	m_comboWindowName.SetCurSel(0);
	g_Automation.m_sTargetWindowName.Format(_T("Desktop"));
	UpdateData(FALSE);
}

void CSAutomationDlg::OnBnClickedButton0WindowNameRefresh()
{
	WindowNameRefresh();
	RefreshTargetWindowPos();
	UpdateData(FALSE);
}


void CSAutomationDlg::OnSelchangeWindowName()
{
	TCHAR tch[256];
	m_comboWindowName.GetLBText(m_comboWindowName.GetCurSel(),tch); 
	CString sWindowName;
	g_Automation.m_sTargetWindowName.Format(_T("%s"), tch);
	RefreshTargetWindowPos();
	return;
}



void CSAutomationDlg::OnTcnSelchangeTabOperation(NMHDR *pNMHDR, LRESULT *pResult)
{
	int itab = m_tab.GetCurSel();

	m_tabItem.m_iSlot=itab;
	m_tabItem.RefleshDialog(itab);
	*pResult = 0;
}

void CSAutomationDlg::ChangeToCompact()
{
	if(m_cDlgCompact.m_hWnd!=NULL){ShowWindow(SW_HIDE);return;}
	ShowWindow(SW_HIDE);

	m_cDlgCompact.pParent=this;
	g_bCompactBiew=TRUE;
	long lRet=m_cDlgCompact.DoModal();
	if(lRet == 2){OnBnClickedOk();}
	g_bCompactBiew=FALSE;
	ShowWindow(SW_SHOW);
}

void CSAutomationDlg::OnBnClickedButtonOpenCompact()
{
	ChangeToCompact();
}
BOOL CSAutomationDlg::ReHookWindowsHook()
{
	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	Sleep(100);
	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);
	if(g_hhook == NULL){return FALSE;}
	return TRUE;
}

void CSAutomationDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


int CSAutomationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1){return -1;}

	return 0;
}
