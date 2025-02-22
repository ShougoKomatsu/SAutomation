
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

CStdioFile g_cf[MAX_THREAD];
CString g_sLogFilePath[MAX_THREAD];
int g_iLogLevel[MAX_THREAD];
BOOL g_bCompactBiew;

HWND g_hWnd;
double g_dSpeedMult=1.0;

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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
	ON_EN_CHANGE(IDC_MAIN_EDIT_SPEED, &CSAutomationDlg::OnChangeEditSpeed)
	ON_EN_KILLFOCUS(IDC_MAIN_EDIT_SPEED, &CSAutomationDlg::OnKillfocusEditSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAIN_SLIDER_SPEED, &CSAutomationDlg::OnCustomdrawSliderSpeed)
	ON_BN_CLICKED(IDC_MAIN_BUTTON_REFRESH_WINDOW_NAME, &CSAutomationDlg::OnBnClickedButton0WindowNameRefresh)
	ON_CBN_SELCHANGE(IDC_MAIN_COMBO_WINDOW_NAME, &CSAutomationDlg::OnSelchangeWindowName)
	ON_NOTIFY(TCN_SELCHANGE, IDC_COMPACT_TAB_OPERATION, &CSAutomationDlg::OnTcnSelchangeTabOperation)
	ON_BN_CLICKED(IDC_MAIN_BUTTON_OPEN_COMPACT, &CSAutomationDlg::OnBnClickedButtonOpenCompact)
	ON_BN_CLICKED(IDOK, &CSAutomationDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSAutomationDlg メッセージ ハンドラー
HHOOK g_hhook=NULL;
int g_iR=0;
int g_iC=0;
int g_iOriginR=0;
int g_iOriginC=0;


HANDLE g_hHotkey[MAX_THREAD];
BOOL g_iMninizedOnce=FALSE;

LRESULT CALLBACK MouseHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case WM_MOUSEMOVE:
		{
			g_iR = ((LPMSLLHOOKSTRUCT)lParam)->pt.y-g_iOriginR;
			g_iC = ((LPMSLLHOOKSTRUCT)lParam)->pt.x-g_iOriginC;
			break;
		}
	default: break;
	}
	return CallNextHookEx(g_hhook, code, wParam, lParam);
}


void SetComboItemCtrl(CComboBox* combo, OperationInfo* op)
{
	combo->ResetContent();
	combo->AddString(_T(" "));
	combo->AddString(_T("Ctrl"));
	combo->AddString(_T("Shift"));
	combo->AddString(_T("Alt"));
	combo->AddString(_T("Win"));

	const int NOTHING = 0;
	const int CTRL = 1;
	const int SHIFT = 2;
	const int ALT = 4;
	const int WIN = 8;

	int iCombi = NOTHING;
	int iKeyCount = 0;
	if(op->bUseCtrl==TRUE){iKeyCount++; iCombi |= CTRL;}
	if(op->bUseShift==TRUE){iKeyCount++;iCombi |= SHIFT;}
	if(op->bUseAlt==TRUE){iKeyCount++;iCombi |= ALT;}
	if(op->bUseWin==TRUE){iKeyCount++;iCombi |= WIN;}
	
	if(iKeyCount >= 3){combo->SetCurSel(0); return;}
	
	if((iCombi&WIN) == WIN)		{if(iCombi != WIN){iCombi -= WIN;}}
	if((iCombi&ALT) == ALT)		{if(iCombi != ALT){iCombi -= ALT;}}
	if((iCombi&SHIFT) == SHIFT) {if(iCombi != SHIFT){iCombi -= SHIFT;}}

	switch(iCombi)
	{
	case NOTHING:{combo->SetCurSel(0); return;}
	case CTRL:{combo->SetCurSel(1); return;}
	case SHIFT:{combo->SetCurSel(2); return;}
	case ALT:{combo->SetCurSel(3); return;}
	case WIN:{combo->SetCurSel(4); return;}

	default:{combo->SetCurSel(0); return;}
	}
	combo->SetCurSel(0); 
	return;

}

void SetComboItemShift(CComboBox* combo,OperationInfo* op)
{
	combo->ResetContent();
	combo->AddString(_T(" "));
	combo->AddString(_T("Shift"));
	combo->AddString(_T("Alt"));
	combo->AddString(_T("Win"));
	
	const int NOTHING = 0;
	const int CTRL = 1;
	const int SHIFT = 2;
	const int ALT = 4;
	const int WIN = 8;
	
	int iCombi = NOTHING;
	int iKeyCount = 0;
	if(op->bUseCtrl==TRUE){iKeyCount++;iCombi |= CTRL;}
	if(op->bUseShift==TRUE){iKeyCount++;iCombi |= SHIFT;}
	if(op->bUseAlt==TRUE){iKeyCount++;iCombi |= ALT;}
	if(op->bUseWin==TRUE){iKeyCount++;iCombi |= WIN;}
	
	if(iKeyCount != 2){combo->SetCurSel(0); return;}
	
	if((iCombi&CTRL) == CTRL)	{iCombi -= CTRL;}
	if((iCombi&SHIFT) == SHIFT) {if(iCombi != SHIFT){iCombi -= SHIFT;}}
	if((iCombi&ALT) == ALT)		{if(iCombi != ALT){iCombi -= ALT;}}
	if((iCombi&WIN) == WIN)		{if(iCombi != WIN){iCombi -= WIN;}}
	
	switch(iCombi)
	{
	case NOTHING:{combo->SetCurSel(0); return;}
	case CTRL:{combo->SetCurSel(0); return;}
	case SHIFT:{combo->SetCurSel(1); return;}
	case ALT:{combo->SetCurSel(2); return;}
	case WIN:{combo->SetCurSel(3); return;}

	default:{combo->SetCurSel(0); return;}
	}
	combo->SetCurSel(0); 
	return;
}



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

	m_OpeInfo[wParam].m_bRunning=FALSE;

	m_bRunningAny=FALSE;
	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		if(m_OpeInfo[iScene].m_bRunning==TRUE){m_bRunningAny=TRUE;if(m_cDlgCompact.m_hWnd != NULL){::PostMessage(m_cDlgCompact.m_hWnd,WM_DISP_STANDBY,1,0);}break;}
	}
	
	
	if(m_cDlgCompact.m_hWnd != NULL){::PostMessage(m_cDlgCompact.m_hWnd,WM_DISP_STANDBY,0,0);}
	if(m_bRunningAny==FALSE){ChangeIcon(IDI_ICON_STANDBY);}

	return 0;
}

void CSAutomationDlg::ReadSettings()
{

	TCHAR szData[MAX_PATH];
	CString sFilePath;

	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	GetPrivateProfileString(_T("Mouse"),_T("ClickDulation"),_T("50"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	g_iClickDulation = _ttoi(szData);

	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);
		GetPrivateProfileString(sSection,_T("FileName"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		m_OpeInfo[iScene].sFileName.Format(_T("%s"),szData);

		GetPrivateProfileString(sSection,_T("Hotkey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		m_OpeInfo[iScene].sHotkey.Format(_T("%s"), szData);

		GetPrivateProfileString(sSection,_T("UseCtrl"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseCtrl=TRUE;}
		else{m_OpeInfo[iScene].bUseCtrl=FALSE;}

		GetPrivateProfileString(sSection,_T("UseShift"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseShift=TRUE;}
		else{m_OpeInfo[iScene].bUseShift=FALSE;}

		GetPrivateProfileString(sSection,_T("UseAlt"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseAlt=TRUE;}
		else{m_OpeInfo[iScene].bUseAlt=FALSE;}

		GetPrivateProfileString(sSection,_T("UseWin"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseWin=TRUE;}
		else{m_OpeInfo[iScene].bUseWin=FALSE;}
	}

	GetPrivateProfileString(_T("Hotkey"),_T("EnableKey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkeyEnable.Format(_T("%s"), szData);

	GetPrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bEnableHotkey=TRUE;}
	else{m_bEnableHotkey=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bAutoMinimize=TRUE;}
	else{m_bAutoMinimize=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("Log"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bLog=TRUE;}
	else{m_bLog=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("LogLevel"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_iLogLevel=_ttoi(szData);
	if(m_iLogLevel<1){m_iLogLevel=1;}
	if(m_iLogLevel>5){m_iLogLevel=5;}

}

void CSAutomationDlg::SaveSettings()
{
	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);
	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	CString sUseCtrl;
	CString sUseShift;
	CString sUseAlt;
	CString sUseWin;

	for(int iScene = 0; iScene<MAX_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);

		WritePrivateProfileString(sSection,_T("FileName"),m_OpeInfo[iScene].sFileName,sFilePath);

		WritePrivateProfileString(sSection,_T("Hotkey"),m_OpeInfo[iScene].sHotkey, sFilePath);

		sUseCtrl.Format(_T("%d"), m_OpeInfo[iScene].bUseCtrl);
		sUseShift.Format(_T("%d"), m_OpeInfo[iScene].bUseShift);
		sUseAlt.Format(_T("%d"), m_OpeInfo[iScene].bUseAlt);
		sUseWin.Format(_T("%d"), m_OpeInfo[iScene].bUseWin);

		WritePrivateProfileString(sSection,_T("UseCtrl"),sUseCtrl,sFilePath);
		WritePrivateProfileString(sSection,_T("UseShift"),sUseShift,sFilePath);
		WritePrivateProfileString(sSection,_T("UseAlt"),sUseAlt,sFilePath);
		WritePrivateProfileString(sSection,_T("UseWin"),sUseWin,sFilePath);

	}

	CString sData;
	TCHAR tch[32];



	if(m_comboEnable.GetCurSel()<0){sData.Format(_T("b"));}
	else{m_comboEnable.GetLBText(m_comboEnable.GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("EnableKey"),sData,sFilePath);

	if(((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),sFilePath);
	}


	if(((CButton*)GetDlgItem(IDC_MIAIN_CHECK_AUTO_MINIMIZE))->GetCheck()==1)
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),sFilePath);
	}

	if(((CButton*)GetDlgItem(IDC_MAIN_CHECK_LOG))->GetCheck()==1)
	{
		WritePrivateProfileString(_T("Common"),_T("Log"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("Log"),_T("0"),sFilePath);
	}

	m_comboLogLevel.GetLBText(m_comboLogLevel.GetCurSel(),tch); sData.Format(_T("%s"), tch);

	if(wcscmp(tch,_T("OnlyCritical"))==0){m_iLogLevel=1;}
	if(wcscmp(tch,_T("4"))==0){m_iLogLevel=2;}
	if(wcscmp(tch,_T("3"))==0){m_iLogLevel=3;}
	if(wcscmp(tch,_T("2"))==0){m_iLogLevel=4;}
	if(wcscmp(tch,_T("All"))==0){m_iLogLevel=5;}
	sData.Format(_T("%d"),m_iLogLevel);
	WritePrivateProfileString(_T("Common"),_T("LogLevel"),sData,sFilePath);

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

	m_sDir.Format(_T("%s"),szData);
	g_sDir.Format(_T("%s"),szData);

	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),m_sDir);

	CString sLogFolderPath;
	sLogFolderPath.Format(_T("%s\\Log"),m_sDir);

	CString sModelFolderPath;
	sModelFolderPath.Format(_T("%s\\Macro\\Model"),m_sDir);


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
	ReadSettings();
	g_dlg=this;
	SetComboItem(&m_comboEnable,m_sHotkeyEnable);
	
	m_tabItem.m_iSlot=0;
		m_tabItem.RefleshDialog();
		g_bCompactBiew=FALSE;

	for(int iScene= 0; iScene<MAX_THREAD; iScene++)
	{
		g_hThread[iScene] = NULL;
		if(m_OpeInfo[iScene].sHotkey.GetLength()>=2)
		{
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F1"))==0){m_OpeInfo[iScene].dwHotKey = VK_F1;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F2"))==0){m_OpeInfo[iScene].dwHotKey = VK_F2;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F3"))==0){m_OpeInfo[iScene].dwHotKey = VK_F3;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F4"))==0){m_OpeInfo[iScene].dwHotKey = VK_F4;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F5"))==0){m_OpeInfo[iScene].dwHotKey = VK_F5;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F6"))==0){m_OpeInfo[iScene].dwHotKey = VK_F6;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F7"))==0){m_OpeInfo[iScene].dwHotKey = VK_F7;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F8"))==0){m_OpeInfo[iScene].dwHotKey = VK_F8;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F9"))==0){m_OpeInfo[iScene].dwHotKey = VK_F9;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F10"))==0){m_OpeInfo[iScene].dwHotKey = VK_F10;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F11"))==0){m_OpeInfo[iScene].dwHotKey = VK_F11;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F12"))==0){m_OpeInfo[iScene].dwHotKey = VK_F12;}
			if(m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("Insert"))==0){m_OpeInfo[iScene].dwHotKey = VK_INSERT;}

		}
		else
		{
			if((char(m_OpeInfo[iScene].sHotkey.GetAt(0))>='a') && (char(m_OpeInfo[iScene].sHotkey.GetAt(0))<='z')){m_OpeInfo[iScene].dwHotKey = char(m_OpeInfo[iScene].sHotkey.GetAt(0))-'a'+0x41;}
			if((char(m_OpeInfo[iScene].sHotkey.GetAt(0))>='0') && (char(m_OpeInfo[iScene].sHotkey.GetAt(0))<='9')){m_OpeInfo[iScene].dwHotKey = char(m_OpeInfo[iScene].sHotkey.GetAt(0))-'0'+0x30;}
		}
		m_tabItem.m_sEditStatus[iScene].Format(_T("Stand by"));
		m_tabItem.m_sEditFileName[iScene].Format(_T("%s"),m_OpeInfo[iScene].sFileName);

	}
		m_tabItem.RefleshDialog();
		UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);

	g_bHalt = FALSE;

	if(m_sHotkeyEnable.GetLength()==1)
	{
		if((char(m_sHotkeyEnable.GetAt(0))>='a') && (char(m_sHotkeyEnable.GetAt(0))<='z')){m_dwHotKeyEnable = char(m_sHotkeyEnable.GetAt(0))-'a'+0x41;}
		if((char(m_sHotkeyEnable.GetAt(0))>='0') && (char(m_sHotkeyEnable.GetAt(0))<='9')){m_dwHotKeyEnable = char(m_sHotkeyEnable.GetAt(0))-'0'+0x30;}
		RegisterHotKey(NULL, HOTKEY_ENABLE, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKeyEnable);
	}


	if(m_bAutoMinimize==TRUE)
	{
		((CButton*)GetDlgItem(IDC_MIAIN_CHECK_AUTO_MINIMIZE))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_MIAIN_CHECK_AUTO_MINIMIZE))->SetCheck(0);
	}


	if(m_bLog==TRUE)
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
	if(m_iLogLevel<1){m_iLogLevel=1;}
	if(m_iLogLevel>5){m_iLogLevel=5;}
	m_comboLogLevel.SetCurSel(m_iLogLevel-1);


	if(m_bEnableHotkey==TRUE)
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

void CSAutomationDlg::OnEnChangeEdit1()
{
}

BOOL CSAutomationDlg::MouseMoveAndDisp(DWORD dwMoveDirection, int iDistance)
{
	long lMouseX;
	long lMouseY;
	lMouseX = g_iC;
	lMouseY = g_iR;
	if(dwMoveDirection == VK_LEFT){lMouseX -= iDistance;}
	if(dwMoveDirection == VK_RIGHT){lMouseX += iDistance;}
	if(dwMoveDirection == VK_UP){lMouseY -= iDistance;}
	if(dwMoveDirection == VK_DOWN){lMouseY += iDistance;}

	if(lMouseX<0){lMouseX=0;}
	if(lMouseY<0){lMouseY=0;}
	if(lMouseX>=::GetSystemMetrics(SM_CXSCREEN)){lMouseX = ::GetSystemMetrics(SM_CXSCREEN)-1;}
	if(lMouseY>=::GetSystemMetrics(SM_CXSCREEN)){lMouseY = ::GetSystemMetrics(SM_CYSCREEN)-1;}

	DWORD dwX, dwY;
	dwX = (lMouseX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (lMouseY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, dwX, dwY, NULL, NULL);

	return TRUE;
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
			if(iKey == m_OpeInfo[iScene].dwHotKey){Operate(iScene);return TRUE;}
		}
		if(iKey == m_dwHotKeyEnable){ToggleEnable();return TRUE;}
		if(iKey == VK_ESCAPE){g_bHalt = TRUE;}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

int g_iWatching=0;
void CSAutomationDlg::RefreshTargetWindowPos()
{
	if(m_sTargetWindowName.Compare(_T("Desktop"))==0)
	{
		ChangeMouseOrigin(0, 0);
		return;
	}

	RECT rect;
	BOOL bRet;
	bRet = GetWindowRectByName(m_sTargetWindowName,&rect);
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
		if(m_bAutoMinimize==TRUE)
		{
			ShowWindow( SW_MINIMIZE );
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CSAutomationDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	CDialogEx::OnMouseMove(nFlags, point);
}


void ResetVariable(int iScene)
{
	for(int i=0; i<MAX_VARIABLES; i++)
	{
		g_iVar[iScene][i]=0;
		g_sVar[iScene][i].Format(_T(""));
		g_imgRGB[iScene][i].Init();
		g_point[iScene][i].Set(0,0);
	}
	return;
}

void CSAutomationDlg::Operate(int iScene)
{
	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);
	ChangeMouseOrigin(0, 0);
	m_comboWindowName.SetCurSel(0);
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);

	DWORD dwThreadID;
	if(g_hThread[iScene] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iScene], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iScene].Format(_T("%s\\Macro\\%s"),m_sDir, m_OpeInfo[iScene].sFileName);
	int iParam[2];
	int iChecked;
	int iLogLevel;
	iChecked = ((CButton*)GetDlgItem(IDC_MAIN_CHECK_LOG))->GetCheck();
	iLogLevel=0;
	if(iChecked==0)
	{
		iLogLevel=0;
	}
	else
	{
		TCHAR tch[32];
		m_comboLogLevel.GetLBText(m_comboLogLevel.GetCurSel(),tch);
		if(wcscmp(tch,_T("OnlyCritical"))==0){iLogLevel=1;}
		if(wcscmp(tch,_T("4"))==0){iLogLevel=2;}
		if(wcscmp(tch,_T("3"))==0){iLogLevel=3;}
		if(wcscmp(tch,_T("2"))==0){iLogLevel=4;}
		if(wcscmp(tch,_T("All"))==0){iLogLevel=5;}
	}

	iParam[1] = iLogLevel<<PARAM_LOGLEVEL_SHIFT;
	iParam[0] = iScene;
	m_OpeInfo[iScene].m_bRunning=TRUE;

	g_hThread[iScene] = CreateThread(NULL, 0, CommandThread, (LPVOID)(iParam), 0, &dwThreadID);

	while(iParam[0]!=0){Sleep(10);}
	
	if(m_cDlgCompact.m_hWnd != NULL){::PostMessage(m_cDlgCompact.m_hWnd,WM_DISP_STANDBY,1,0);}
	

	//m_tabItem.m_sEditStatus[iScene].Format(_T("Running"));
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);
	ChangeIcon(IDI_ICON_RUNNING);
}





BOOL CSAutomationDlg::DestroyWindow()
{
	g_bHalt = TRUE;
	Sleep(1000);

	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	SaveSettings();

	return CDialogEx::DestroyWindow();
}




void CSAutomationDlg::OnSelchangeCombo0Enable()
{
	if(m_sHotkeyEnable.GetLength()==1)
	{
		UnregisterHotKey(NULL, HOTKEY_ENABLE);
	}

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_comboEnable.GetCurSel()<0){m_sHotkeyEnable.Format(_T(""));return;}
	m_comboEnable.GetLBText(m_comboEnable.GetCurSel(),tch);

	m_sHotkeyEnable.Format(_T("%s"), tch);
	if(wcscmp(tch,_T(" "))==0){return;}
	if((tch[0]>='a') && (tch[0]<='z')){m_dwHotKeyEnable = char(tch[0])-'a'+0x41;}
	if((tch[0]>='0') && (tch[0]<='9')){m_dwHotKeyEnable = char(tch[0])-'0'+0x30;}
	RegisterHotKey(NULL, HOTKEY_ENABLE, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKeyEnable);
}




void CSAutomationDlg::ResetHotkey(int iScene)
{
	UpdateData(TRUE);
	m_tabItem.UpdateData_My(TRUE);
	UnregisterHotKey(NULL, HOTKEY_SCENE_0+iScene);


	if(((CButton*)GetDlgItem(IDC_MAIN_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		RegisterHotKey(NULL, HOTKEY_SCENE_0+iScene, 
			(MOD_SHIFT*m_OpeInfo[iScene].bUseShift) 
			| (MOD_CONTROL*m_OpeInfo[iScene].bUseCtrl) 
			| (MOD_ALT*m_OpeInfo[iScene].bUseAlt) 
			| (MOD_WIN*m_OpeInfo[iScene].bUseWin) 
			| MOD_NOREPEAT
			, m_OpeInfo[iScene].dwHotKey);
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
	CDialogEx::OnSize(nType, cx, cy);


}


void CSAutomationDlg::OnBnClickedButton0OpenFolder()
{
	CString sMacroFolder;
	sMacroFolder.Format(_T("%s\\Macro"),m_sDir);
	ShellExecute(NULL, NULL, sMacroFolder, NULL, NULL, SW_SHOWNORMAL);
}


void CSAutomationDlg::OnChangeEditSpeed()
{

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


void CSAutomationDlg::OnBnClickedButton0Confing()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
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
	m_sTargetWindowName.Format(_T("Desktop"));
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
	m_sTargetWindowName.Format(_T("%s"), tch);
	RefreshTargetWindowPos();
	return;
}

BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSAutomationDlg::OnTcnSelchangeTabOperation(NMHDR *pNMHDR, LRESULT *pResult)
{
	int itab = m_tab.GetCurSel();

	m_tabItem.m_iSlot=itab;
	m_tabItem.RefleshDialog();
	*pResult = 0;
}

void CSAutomationDlg::OnBnClickedButtonOpenCompact()
{
	if(m_cDlgCompact.m_hWnd!=NULL){return;}
	ShowWindow(SW_HIDE);

	m_cDlgCompact.pParent=this;
	g_bCompactBiew=TRUE;
	long lRet=m_cDlgCompact.DoModal();
	if(lRet == 2){OnBnClickedOk();}
	g_bCompactBiew=FALSE;
	ShowWindow(SW_SHOW);
}
BOOL CSAutomationDlg::ReHookWindowsHook()
{
	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	Sleep(100);
	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);
	if(g_hhook == NULL){CString sss; sss.Format(_T("SetWindowsHookEx failed %d"), GetLastError()); AfxMessageBox(sss); return FALSE;}
	return TRUE;
}

void CSAutomationDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();
}
