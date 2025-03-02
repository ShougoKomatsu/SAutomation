// SettingDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "Common.h"
#include "Window.h"
#include "math.h"
// CSettingDlg ダイアログ
#define TIMER_DISP_MOUSPOS (100)
IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
{
	m_hIconStandby = AfxGetApp()->LoadIcon(IDI_ICON_STANDBY);
	m_hIconRunning = AfxGetApp()->LoadIcon(IDI_ICON_RUNNING);

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SETTING_EDIT_MOUSEPOS_C, m_sEditMousePosC);
	DDX_Text(pDX, IDC_SETTING_EDIT_MOUSEPOS_R, m_sEditMousePosR);
	DDX_Control(pDX, IDC_SETTING_COMBO_ENABLE_HOTKEY, m_comboEnable);

	DDX_Control(pDX, IDC_SETTING_COMBO_WINDOW_NAME, m_comboWindowName);

	DDX_Control(pDX, IDC_SETTING_COMBO_LOG_LEVEL, m_comboLogLevel);
	DDX_Text(pDX, IDC_SETTING_EDIT_SPEED, m_sEditSpeed);
	DDX_Control(pDX, IDC_SETTING_SLIDER_SPEED, m_sliderSpeed);
	DDX_Control(pDX, IDC_COMPACT_TAB_OPERATION, m_tab);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SETTING_CHECK_ENABLE_HOTKEY, &CSettingDlg::OnBnClickedCheckEnableHotkey)
	ON_CBN_SELCHANGE(IDC_SETTING_COMBO_ENABLE_HOTKEY, &CSettingDlg::OnSelchangeCombo0Enable)
	ON_BN_CLICKED(IDC_SETTING_BUTTON_OPEN_FOLDER, &CSettingDlg::OnBnClickedButton0OpenFolder)
	ON_EN_KILLFOCUS(IDC_SETTING_EDIT_SPEED, &CSettingDlg::OnKillfocusEditSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_SLIDER_SPEED, &CSettingDlg::OnCustomdrawSliderSpeed)
	ON_BN_CLICKED(IDC_SETTING_BUTTON_REFRESH_WINDOW_NAME, &CSettingDlg::OnBnClickedButton0WindowNameRefresh)
	ON_CBN_SELCHANGE(IDC_SETTING_COMBO_WINDOW_NAME, &CSettingDlg::OnSelchangeWindowName)
	ON_NOTIFY(TCN_SELCHANGE, IDC_COMPACT_TAB_OPERATION, &CSettingDlg::OnTcnSelchangeTabOperation)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SETTING_BUTTON_CANCEL, &CSettingDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_SETTING_CHECK_AUTO_MINIMIZE, &CSettingDlg::OnClickedCheckAutoMinimize)
	ON_BN_CLICKED(IDC_SETTING_CHECK_LOG, &CSettingDlg::OnBnClickedCheckLog)
	ON_CBN_SELCHANGE(IDC_SETTING_COMBO_LOG_LEVEL, &CSettingDlg::OnSelchangeComboLogLevel)
	ON_BN_CLICKED(IDC_SETTING_CHECK_TASKTRAY, &CSettingDlg::OnBnClickedCheckTasktray)
END_MESSAGE_MAP()


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Automation.Copy(&g_Automation);
	m_bNotModified=TRUE;
	SetTitleNotChanged( m_bNotModified );
	
	m_tab.SubclassDlgItem(IDC_COMPACT_TAB_OPERATION, this);

	m_tab.InsertItem(0, _T("0 - 15"));
	m_tab.InsertItem(1, _T("16 - 31"));
	m_tab.InsertItem(3, _T("32 - 47"));
	m_tab.InsertItem(3, _T("48 - 63"));
	
	m_tabItem.Create(IDD_DIALOG_TAB_ITEMS, &m_tab);
	m_tabItem.m_autoInfo=&m_Automation;
	m_tabItem.pbNotModified=&m_bNotModified;
	m_tabItem.pParentWnd=this;
	CRect rect;
	m_tab.GetWindowRect(rect);
	m_tab.AdjustRect(FALSE, rect);
	m_tab.ScreenToClient(rect);


	m_tabItem.MoveWindow(rect);

	m_tabItem.ShowWindow(SW_SHOW);
	
	m_tabItem.m_iSlot=0;
	m_tabItem.RefleshDialog(0);

	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);
	
	if(m_Automation.m_bAutoMinimize==TRUE)
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_AUTO_MINIMIZE))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_AUTO_MINIMIZE))->SetCheck(0);
	}


	if(m_Automation.m_bLog==TRUE)
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_LOG))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_LOG))->SetCheck(0);
	}

	m_comboLogLevel.ResetContent();
	m_comboLogLevel.AddString(_T("OnlyCritical"));
	m_comboLogLevel.AddString(_T("4"));
	m_comboLogLevel.AddString(_T("3"));
	m_comboLogLevel.AddString(_T("2"));
	m_comboLogLevel.AddString(_T("All"));
	m_comboLogLevel.SetCurSel(m_Automation.m_iLogLevel-1);


	if(m_Automation.m_bEnableHotkey==TRUE)
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_ENABLE_HOTKEY))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_ENABLE_HOTKEY))->SetCheck(0);
	}
	
	if(m_Automation.m_bMinimizeToTaskTray==TRUE)
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_TASKTRAY))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_SETTING_CHECK_TASKTRAY))->SetCheck(0);
	}

	m_sEditSpeed.Format(_T("1.00"));
	m_sliderSpeed.SetRangeMin(0);	
	m_sliderSpeed.SetRangeMax(100);
	m_sliderSpeed.SetPos(50);
	
	SetTimer(TIMER_DISP_MOUSPOS,200, NULL);
	WindowNameRefresh();
	RefreshTargetWindowPos();
	UpdateData(FALSE);
	m_tabItem.UpdateData_My(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN){return TRUE;}
		if(pMsg->wParam == VK_ESCAPE){return TRUE;}
		if(pMsg->wParam == VK_SPACE){return TRUE;}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSettingDlg::RefreshTargetWindowPos()
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

void CSettingDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_DISP_MOUSPOS)
	{
		UpdateData(TRUE);
		m_sEditMousePosR.Format(_T("%d"),g_iR);
		m_sEditMousePosC.Format(_T("%d"),g_iC);
		UpdateData(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CSettingDlg::GetLogLavel(AutomationInfo* autoInfo)
{
	autoInfo->m_bLog = ((CButton*)GetDlgItem(IDC_SETTING_CHECK_LOG))->GetCheck();
	if(autoInfo->m_bLog==0)
	{
		autoInfo->m_iLogLevel=1;
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


BOOL CSettingDlg::UpdateAutomationInfo(AutomationInfo* autoInfo)
{
	
	CString sData;
	TCHAR tch[32];



	if(m_comboEnable.GetCurSel()<0){autoInfo->m_sHotkeyEnable.Format(_T("b"));}
	else{m_comboEnable.GetLBText(m_comboEnable.GetCurSel(),tch); autoInfo->m_sHotkeyEnable.Format(_T("%s"), tch);}

	if(((CButton*)GetDlgItem(IDC_SETTING_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		autoInfo->m_bEnableHotkey=TRUE;
	}
	else
	{
		autoInfo->m_bEnableHotkey=FALSE;
	}


	if(((CButton*)GetDlgItem(IDC_SETTING_CHECK_AUTO_MINIMIZE))->GetCheck()==1)
	{
		autoInfo->m_bAutoMinimize=TRUE;
	}
	else
	{
		autoInfo->m_bAutoMinimize=FALSE;
	}
	GetLogLavel(autoInfo);

	
	if(((CButton*)GetDlgItem(IDC_SETTING_CHECK_TASKTRAY))->GetCheck()==1)
	{
		autoInfo->m_bMinimizeToTaskTray=TRUE;
	}
	else
	{
		autoInfo->m_bMinimizeToTaskTray=FALSE;
	}


	return TRUE;
}


void CSettingDlg::OnSelchangeCombo0Enable()
{
	if(m_Automation.m_sHotkeyEnable.GetLength()==1)
	{
//		UnregisterHotKey(NULL, HOTKEY_ENABLE);
	}

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_comboEnable.GetCurSel()<0){m_Automation.m_sHotkeyEnable.Format(_T(""));return;}
	m_comboEnable.GetLBText(m_comboEnable.GetCurSel(),tch);

	m_Automation.m_sHotkeyEnable.Format(_T("%s"), tch);
	if(wcscmp(tch,_T(" "))==0){return;}
	if((tch[0]>='a') && (tch[0]<='z')){m_Automation.m_dwHotKeyEnable = char(tch[0])-'a'+0x41;}
	if((tch[0]>='0') && (tch[0]<='9')){m_Automation.m_dwHotKeyEnable = char(tch[0])-'0'+0x30;}
//	RegisterHotKey(NULL, HOTKEY_ENABLE, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_Automation.m_dwHotKeyEnable);
	
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );
}

void CSettingDlg::OnBnClickedCheckEnableHotkey()
{
	UpdateData(TRUE);
	if(((CButton*)GetDlgItem(IDC_SETTING_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		m_Automation.m_bEnableHotkey=TRUE;
	}
	else
	{
		m_Automation.m_bEnableHotkey=FALSE;
	}
	
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );

	return;
}

void CSettingDlg::OnBnClickedButton0OpenFolder()
{
	CString sMacroFolder;
	sMacroFolder.Format(_T("%s\\Macro"),m_Automation.m_sDir);
	ShellExecute(NULL, NULL, sMacroFolder, NULL, NULL, SW_SHOWNORMAL);
}

void CSettingDlg::OnKillfocusEditSpeed()
{
	UpdateData(TRUE);

	g_dSpeedMult=_ttof(m_sEditSpeed);
	if(g_dSpeedMult==0){g_dSpeedMult=1;m_sEditSpeed.Format(_T("1.00"));}

	if(g_dSpeedMult<1){m_sliderSpeed.SetPos(int(( g_dSpeedMult-0.1)/0.016));}
	else{m_sliderSpeed.SetPos(int(sqrt(g_dSpeedMult)*50));}

	UpdateData(FALSE);
}

void CSettingDlg::OnCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
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

void CSettingDlg::WindowNameRefresh()
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

void CSettingDlg::OnBnClickedButton0WindowNameRefresh()
{
	WindowNameRefresh();
	RefreshTargetWindowPos();
	UpdateData(FALSE);
}

void CSettingDlg::OnSelchangeWindowName()
{
	TCHAR tch[256];
	m_comboWindowName.GetLBText(m_comboWindowName.GetCurSel(),tch); 
	CString sWindowName;
	m_sTargetWindowName.Format(_T("%s"), tch);
	RefreshTargetWindowPos();
	return;
}

void CSettingDlg::OnTcnSelchangeTabOperation(NMHDR *pNMHDR, LRESULT *pResult)
{
	int itab = m_tab.GetCurSel();

	m_tabItem.m_iSlot=itab;
	m_tabItem.RefleshDialog(itab);
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );
	*pResult = 0;
}


void CSettingDlg::OnBnClickedSave()
{
	UpdateAutomationInfo(&m_Automation);
	g_Automation.Copy(&m_Automation);	
	g_Automation.SaveSettings();
	
	m_bNotModified=TRUE;
	SetTitleNotChanged( m_bNotModified );
}

LRESULT CSettingDlg::OnDispStandby(WPARAM wParam, LPARAM lParam)
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


BOOL CSettingDlg::ChangeIcon(int iIcon)
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



void CSettingDlg::OnBnClickedButtonCancel()
{
	if(m_bNotModified==FALSE)
	{
		int iRet=AfxMessageBox(_T("変更が保存されていません保存せずに終了しますか？"),MB_YESNO);
		if(iRet == IDNO){return;}
	}
	CDialogEx::OnOK();
}


void CSettingDlg::OnClickedCheckAutoMinimize()
{
	UpdateAutomationInfo(&m_Automation);
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );
}


void CSettingDlg::OnBnClickedCheckLog()
{
	UpdateAutomationInfo(&m_Automation);
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );
}


void CSettingDlg::OnSelchangeComboLogLevel()
{
	UpdateAutomationInfo(&m_Automation);
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );
}

void CSettingDlg::SetTitleNotChanged(BOOL bTF)
{
	if(bTF==FALSE)
	{
		SetWindowText(_T("SAutomation *"));
	}
	else
	{
		SetWindowText(_T("SAutomation"));
	}
}

void CSettingDlg::OnBnClickedCheckTasktray()
{	
	UpdateAutomationInfo(&m_Automation);
	m_bNotModified = m_Automation.IsSameAs(&g_Automation);
	SetTitleNotChanged( m_bNotModified );
}
