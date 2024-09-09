
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
#define TIMER_DISP_MOUSPOS (100)
#define TIMER_THREAD_WATCH (101)
#define TIMER_WAKE_UP (102)

CStdioFile g_cf[MAX_THREAD];
CString g_sLogFilePath[MAX_THREAD];


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
	DDX_Text(pDX, IDC_EDIT_MOUSEPOS_C, m_sEditMousePosC);
	DDX_Text(pDX, IDC_EDIT_MOUSEPOS_R, m_sEditMousePosR);
	DDX_Control(pDX, IDC_COMBO_ENABLE_HOTKEY, m_comboEnable);

	DDX_Text(pDX, IDC_EDIT_FILE_00, (m_sEditFileName[0]));
	DDX_Text(pDX, IDC_EDIT_FILE_01, (m_sEditFileName[1]));
	DDX_Text(pDX, IDC_EDIT_FILE_02, (m_sEditFileName[2]));
	DDX_Text(pDX, IDC_EDIT_FILE_03, (m_sEditFileName[3]));
	DDX_Text(pDX, IDC_EDIT_FILE_04, (m_sEditFileName[4]));
	DDX_Text(pDX, IDC_EDIT_FILE_05, (m_sEditFileName[5]));
	DDX_Text(pDX, IDC_EDIT_FILE_06, (m_sEditFileName[6]));
	DDX_Text(pDX, IDC_EDIT_FILE_07, (m_sEditFileName[7]));
	DDX_Text(pDX, IDC_EDIT_FILE_08, (m_sEditFileName[8]));
	DDX_Text(pDX, IDC_EDIT_FILE_09, (m_sEditFileName[9]));
	DDX_Text(pDX, IDC_EDIT_FILE_10, (m_sEditFileName[10]));
	DDX_Text(pDX, IDC_EDIT_FILE_11, (m_sEditFileName[11]));
	DDX_Text(pDX, IDC_EDIT_FILE_12, (m_sEditFileName[12]));
	DDX_Text(pDX, IDC_EDIT_FILE_13, (m_sEditFileName[13]));
	DDX_Text(pDX, IDC_EDIT_FILE_14, (m_sEditFileName[14]));
	DDX_Text(pDX, IDC_EDIT_FILE_15, (m_sEditFileName[15]));

	DDX_Text(pDX, IDC_EDIT_STATUS_00, (m_sEditStatus[0]));
	DDX_Text(pDX, IDC_EDIT_STATUS_01, (m_sEditStatus[1]));
	DDX_Text(pDX, IDC_EDIT_STATUS_02, (m_sEditStatus[2]));
	DDX_Text(pDX, IDC_EDIT_STATUS_03, (m_sEditStatus[3]));
	DDX_Text(pDX, IDC_EDIT_STATUS_04, (m_sEditStatus[4]));
	DDX_Text(pDX, IDC_EDIT_STATUS_05, (m_sEditStatus[5]));
	DDX_Text(pDX, IDC_EDIT_STATUS_06, (m_sEditStatus[6]));
	DDX_Text(pDX, IDC_EDIT_STATUS_07, (m_sEditStatus[7]));
	DDX_Text(pDX, IDC_EDIT_STATUS_08, (m_sEditStatus[8]));
	DDX_Text(pDX, IDC_EDIT_STATUS_09, (m_sEditStatus[9]));
	DDX_Text(pDX, IDC_EDIT_STATUS_10, (m_sEditStatus[10]));
	DDX_Text(pDX, IDC_EDIT_STATUS_11, (m_sEditStatus[11]));
	DDX_Text(pDX, IDC_EDIT_STATUS_12, (m_sEditStatus[12]));
	DDX_Text(pDX, IDC_EDIT_STATUS_13, (m_sEditStatus[13]));
	DDX_Text(pDX, IDC_EDIT_STATUS_14, (m_sEditStatus[14]));
	DDX_Text(pDX, IDC_EDIT_STATUS_15, (m_sEditStatus[15]));

	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_00, (m_combo[0]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_01, (m_combo[1]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_02, (m_combo[2]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_03, (m_combo[3]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_04, (m_combo[4]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_05, (m_combo[5]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_06, (m_combo[6]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_07, (m_combo[7]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_08, (m_combo[8]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_09, (m_combo[9]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_10, (m_combo[10]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_11, (m_combo[11]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_12, (m_combo[12]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_13, (m_combo[13]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_14, (m_combo[14]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_15, (m_combo[15]));

	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_00, (m_comboUseCtrl[0]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_01, (m_comboUseCtrl[1]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_02, (m_comboUseCtrl[2]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_03, (m_comboUseCtrl[3]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_04, (m_comboUseCtrl[4]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_05, (m_comboUseCtrl[5]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_06, (m_comboUseCtrl[6]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_07, (m_comboUseCtrl[7]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_08, (m_comboUseCtrl[8]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_09, (m_comboUseCtrl[9]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_10, (m_comboUseCtrl[10]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_11, (m_comboUseCtrl[11]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_12, (m_comboUseCtrl[12]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_13, (m_comboUseCtrl[13]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_14, (m_comboUseCtrl[14]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_15, (m_comboUseCtrl[15]));

	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_00, (m_comboUseShift[0]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_01, (m_comboUseShift[1]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_02, (m_comboUseShift[2]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_03, (m_comboUseShift[3]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_04, (m_comboUseShift[4]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_05, (m_comboUseShift[5]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_06, (m_comboUseShift[6]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_07, (m_comboUseShift[7]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_08, (m_comboUseShift[8]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_09, (m_comboUseShift[9]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_10, (m_comboUseShift[10]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_11, (m_comboUseShift[11]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_12, (m_comboUseShift[12]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_13, (m_comboUseShift[13]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_14, (m_comboUseShift[14]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_15, (m_comboUseShift[15]));

	DDX_Control(pDX, IDC_COMBO_WINDOW_NAME, m_comboWindowName);

	DDX_Control(pDX, IDC_COMBO_LOG_LEVEL, m_comboLogLevel);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_sEditSpeed);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_sliderSpeed);
}

BEGIN_MESSAGE_MAP(CSAutomationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_00, &CSAutomationDlg::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_01, &CSAutomationDlg::OnBnClickedButton01)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_02, &CSAutomationDlg::OnBnClickedButton02)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_03, &CSAutomationDlg::OnBnClickedButton03)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_04, &CSAutomationDlg::OnBnClickedButton04)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_05, &CSAutomationDlg::OnBnClickedButton05)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_06, &CSAutomationDlg::OnBnClickedButton06)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_07, &CSAutomationDlg::OnBnClickedButton07)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_08, &CSAutomationDlg::OnBnClickedButton08)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_09, &CSAutomationDlg::OnBnClickedButton09)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_10, &CSAutomationDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_11, &CSAutomationDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_12, &CSAutomationDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_13, &CSAutomationDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_14, &CSAutomationDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_15, &CSAutomationDlg::OnBnClickedButton15)

	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_00, &CSAutomationDlg::OnSelchangeCombo00)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_01, &CSAutomationDlg::OnSelchangeCombo01)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_02, &CSAutomationDlg::OnSelchangeCombo02)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_03, &CSAutomationDlg::OnSelchangeCombo03)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_04, &CSAutomationDlg::OnSelchangeCombo04)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_05, &CSAutomationDlg::OnSelchangeCombo05)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_06, &CSAutomationDlg::OnSelchangeCombo06)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_07, &CSAutomationDlg::OnSelchangeCombo07)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_08, &CSAutomationDlg::OnSelchangeCombo08)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_09, &CSAutomationDlg::OnSelchangeCombo09)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_10, &CSAutomationDlg::OnSelchangeCombo10)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_11, &CSAutomationDlg::OnSelchangeCombo11)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_12, &CSAutomationDlg::OnSelchangeCombo12)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_13, &CSAutomationDlg::OnSelchangeCombo13)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_14, &CSAutomationDlg::OnSelchangeCombo14)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_15, &CSAutomationDlg::OnSelchangeCombo15)

	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_00, &CSAutomationDlg::OnSelchangeComboCtrl00)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_01, &CSAutomationDlg::OnSelchangeComboCtrl01)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_02, &CSAutomationDlg::OnSelchangeComboCtrl02)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_03, &CSAutomationDlg::OnSelchangeComboCtrl03)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_04, &CSAutomationDlg::OnSelchangeComboCtrl04)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_05, &CSAutomationDlg::OnSelchangeComboCtrl05)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_06, &CSAutomationDlg::OnSelchangeComboCtrl06)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_07, &CSAutomationDlg::OnSelchangeComboCtrl07)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_08, &CSAutomationDlg::OnSelchangeComboCtrl08)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_09, &CSAutomationDlg::OnSelchangeComboCtrl09)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_10, &CSAutomationDlg::OnSelchangeComboCtrl10)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_11, &CSAutomationDlg::OnSelchangeComboCtrl11)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_12, &CSAutomationDlg::OnSelchangeComboCtrl12)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_13, &CSAutomationDlg::OnSelchangeComboCtrl13)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_14, &CSAutomationDlg::OnSelchangeComboCtrl14)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_15, &CSAutomationDlg::OnSelchangeComboCtrl15)

	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_00, &CSAutomationDlg::OnSelchangeComboShift00)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_01, &CSAutomationDlg::OnSelchangeComboShift01)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_02, &CSAutomationDlg::OnSelchangeComboShift02)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_03, &CSAutomationDlg::OnSelchangeComboShift03)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_04, &CSAutomationDlg::OnSelchangeComboShift04)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_05, &CSAutomationDlg::OnSelchangeComboShift05)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_06, &CSAutomationDlg::OnSelchangeComboShift06)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_07, &CSAutomationDlg::OnSelchangeComboShift07)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_08, &CSAutomationDlg::OnSelchangeComboShift08)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_09, &CSAutomationDlg::OnSelchangeComboShift09)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_10, &CSAutomationDlg::OnSelchangeComboShift10)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_11, &CSAutomationDlg::OnSelchangeComboShift11)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_12, &CSAutomationDlg::OnSelchangeComboShift12)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_13, &CSAutomationDlg::OnSelchangeComboShift13)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_14, &CSAutomationDlg::OnSelchangeComboShift14)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_15, &CSAutomationDlg::OnSelchangeComboShift15)

	ON_BN_CLICKED(IDC_BUTTON_OPERATE_00, &CSAutomationDlg::OnBnClickedButtonOperate00)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_01, &CSAutomationDlg::OnBnClickedButtonOperate01)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_02, &CSAutomationDlg::OnBnClickedButtonOperate02)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_03, &CSAutomationDlg::OnBnClickedButtonOperate03)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_04, &CSAutomationDlg::OnBnClickedButtonOperate04)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_05, &CSAutomationDlg::OnBnClickedButtonOperate05)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_06, &CSAutomationDlg::OnBnClickedButtonOperate06)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_07, &CSAutomationDlg::OnBnClickedButtonOperate07)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_08, &CSAutomationDlg::OnBnClickedButtonOperate08)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_09, &CSAutomationDlg::OnBnClickedButtonOperate09)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_10, &CSAutomationDlg::OnBnClickedButtonOperate10)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_11, &CSAutomationDlg::OnBnClickedButtonOperate11)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_12, &CSAutomationDlg::OnBnClickedButtonOperate12)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_13, &CSAutomationDlg::OnBnClickedButtonOperate13)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_14, &CSAutomationDlg::OnBnClickedButtonOperate14)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_15, &CSAutomationDlg::OnBnClickedButtonOperate15)
	
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_DISP_STANDBY, &CSAutomationDlg::OnDispStandby)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_HOTKEY, &CSAutomationDlg::OnBnClickedCheckEnableHotkey)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_HOTKEY, &CSAutomationDlg::OnSelchangeCombo0Enable)

	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FOLDER, &CSAutomationDlg::OnBnClickedButton0OpenFolder)
	ON_EN_CHANGE(IDC_EDIT_SPEED, &CSAutomationDlg::OnChangeEditSpeed)
	ON_EN_KILLFOCUS(IDC_EDIT_SPEED, &CSAutomationDlg::OnKillfocusEditSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &CSAutomationDlg::OnCustomdrawSliderSpeed)
	ON_BN_CLICKED(IDC_BUTTON_CONFING, &CSAutomationDlg::OnBnClickedButton0Confing)
	ON_BN_CLICKED(IDC_CHECK_TASKTRAY, &CSAutomationDlg::OnBnClickedCheckTasktray)
	ON_BN_CLICKED(IDC_BUTTON_WINDOW_NAME_REFRESH, &CSAutomationDlg::OnBnClickedButton0WindowNameRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_WINDOW_NAME, &CSAutomationDlg::OnSelchangeWindowName)
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

LRESULT CSAutomationDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONUP: 
		{
			if (wParam == IDI_ICON_STANDBY)
			{
				ShowWindow(SW_NORMAL);
				SetForegroundWindow();
				SetFocus();
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


void SetComboItem(CComboBox* combo, CString m_sHotkey)
{
	combo->ResetContent();
	combo->AddString(_T(" "));
	combo->AddString(_T("0"));
	combo->AddString(_T("1"));
	combo->AddString(_T("2"));
	combo->AddString(_T("3"));
	combo->AddString(_T("4"));
	combo->AddString(_T("5"));
	combo->AddString(_T("6"));
	combo->AddString(_T("7"));
	combo->AddString(_T("8"));
	combo->AddString(_T("9"));
	combo->AddString(_T("a"));
	combo->AddString(_T("b"));
	combo->AddString(_T("c"));
	combo->AddString(_T("d"));
	combo->AddString(_T("e"));
	combo->AddString(_T("f"));
	combo->AddString(_T("g"));
	combo->AddString(_T("h"));
	combo->AddString(_T("i"));
	combo->AddString(_T("j"));
	combo->AddString(_T("k"));
	combo->AddString(_T("l"));
	combo->AddString(_T("m"));
	combo->AddString(_T("n"));
	combo->AddString(_T("o"));
	combo->AddString(_T("p"));
	combo->AddString(_T("q"));
	combo->AddString(_T("r"));
	combo->AddString(_T("s"));
	combo->AddString(_T("t"));
	combo->AddString(_T("u"));
	combo->AddString(_T("v"));
	combo->AddString(_T("w"));
	combo->AddString(_T("x"));
	combo->AddString(_T("y"));
	combo->AddString(_T("z"));
	combo->AddString(_T("F1"));
	combo->AddString(_T("F2"));
	combo->AddString(_T("F3"));
	combo->AddString(_T("F4"));
	combo->AddString(_T("F5"));
	combo->AddString(_T("F6"));
	combo->AddString(_T("F7"));
	combo->AddString(_T("F8"));
	combo->AddString(_T("F9"));
	combo->AddString(_T("F10"));
	combo->AddString(_T("F11"));
	combo->AddString(_T("F12"));
	combo->AddString(_T("Insert"));


	BOOL bFound;
	bFound = FALSE;
	for(int i=0; i<combo->GetCount(); i++)
	{
		TCHAR tch[8];
		combo->GetLBText(i, tch);
		if(m_sHotkey.Compare(tch)==0){combo->SetCurSel(i); bFound = TRUE;break;}
	}
	if(bFound != TRUE){combo->SetCurSel(0);}
}

LRESULT CSAutomationDlg::OnDispStandby(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	if(wParam<0){return 0;}
	if(wParam>=MAX_THREAD){return 0;}
	g_hThread[wParam]=NULL;
	m_sEditStatus[wParam].Format(_T("Stand by"));
	UpdateData(FALSE);

	m_OpeInfo[wParam].m_bRunning=FALSE;

	m_bRunningAny=FALSE;
	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		if(m_OpeInfo[iScene].m_bRunning==TRUE){m_bRunningAny=TRUE;break;}
	}

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

	GetPrivateProfileString(_T("Common"),_T("MinimizeToTasktray"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bMinimizeToTaskTray=TRUE;}
	else{m_bMinimizeToTaskTray=FALSE;}

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

		WritePrivateProfileString(sSection,_T("FileName"),m_sEditFileName[iScene],sFilePath);

		CString sData;
		TCHAR tch[8];
		if(m_combo[iScene].GetCurSel()<0){sData.Format(_T("b"));}
		else{m_combo[iScene].GetLBText(m_combo[iScene].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
		WritePrivateProfileString(sSection,_T("Hotkey"),sData,sFilePath);

		sUseCtrl.Format(_T("0"));
		sUseShift.Format(_T("0"));
		sUseAlt.Format(_T("0"));
		sUseWin.Format(_T("0"));

		if(m_comboUseCtrl[iScene].GetCurSel()<0){sData.Format(_T("0"));}
		else
		{
			m_comboUseCtrl[iScene].GetLBText(m_comboUseCtrl[iScene].GetCurSel(),tch);
			if(wcscmp(tch,_T("Ctrl"))==0){sUseCtrl.Format(_T("1"));}
			if(wcscmp(tch,_T("Shift"))==0){sUseShift.Format(_T("1"));}
			if(wcscmp(tch,_T("Alt"))==0){sUseAlt.Format(_T("1"));}
			if(wcscmp(tch,_T("Win"))==0){sUseWin.Format(_T("1"));}
		}

		if(m_comboUseShift[iScene].GetCurSel()<0){sData.Format(_T("0"));}
		else
		{
			m_comboUseShift[iScene].GetLBText(m_comboUseShift[iScene].GetCurSel(),tch);
			if(wcscmp(tch,_T("Ctrl"))==0){sUseCtrl.Format(_T("1"));}
			if(wcscmp(tch,_T("Shift"))==0){sUseShift.Format(_T("1"));}
			if(wcscmp(tch,_T("Alt"))==0){sUseAlt.Format(_T("1"));}
			if(wcscmp(tch,_T("Win"))==0){sUseWin.Format(_T("1"));}
		}

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

	if(((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),sFilePath);
	}


	if(((CButton*)GetDlgItem(IDC_CHECK_AUTO_MINIMIZE))->GetCheck()==1)
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),sFilePath);
	}
	if(((CButton*)GetDlgItem(IDC_CHECK_TASKTRAY))->GetCheck()==1)
	{
		WritePrivateProfileString(_T("Common"),_T("MinimizeToTasktray"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("MinimizeToTasktray"),_T("0"),sFilePath);
	}

	if(((CButton*)GetDlgItem(IDC_CHECK_LOG))->GetCheck()==1)
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

#include "ImgProc.h"
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
	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);
	if(g_hhook == NULL){CString sss; sss.Format(_T("SetWindowsHookEx failed %d"), GetLastError()); AfxMessageBox(sss); OnOK();}


	SetTimer(TIMER_DISP_MOUSPOS,200, NULL);
	SetTimer(TIMER_THREAD_WATCH,200, NULL);
	SetTimer(TIMER_WAKE_UP, 100, NULL);

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

	CFileFind cf;
	if(cf.FindFile(sMacroFolderPath) != TRUE){_tmkdir(sMacroFolderPath);}
	if(cf.FindFile(sLogFolderPath) != TRUE){_tmkdir(sLogFolderPath);}
	if(cf.FindFile(sModelFolderPath) != TRUE){_tmkdir(sModelFolderPath);}
	ReadSettings();
	g_dlg=this;
	SetComboItem(&m_comboEnable,m_sHotkeyEnable);
	for(int iScene= 0 ; iScene<MAX_THREAD; iScene++)
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
		m_sEditStatus[iScene].Format(_T("Stand by"));
		m_sEditFileName[iScene].Format(_T("%s"),m_OpeInfo[iScene].sFileName);
		UpdateData(FALSE);

		SetComboItem(&m_combo[iScene],m_OpeInfo[iScene].sHotkey);
		SetComboItemCtrl(&m_comboUseCtrl[iScene],&(m_OpeInfo[iScene]));
		SetComboItemShift(&m_comboUseShift[iScene],&(m_OpeInfo[iScene]));
	}

	g_bHalt = FALSE;

	if(m_sHotkeyEnable.GetLength()==1)
	{
		if((char(m_sHotkeyEnable.GetAt(0))>='a') && (char(m_sHotkeyEnable.GetAt(0))<='z')){m_dwHotKeyEnable = char(m_sHotkeyEnable.GetAt(0))-'a'+0x41;}
		if((char(m_sHotkeyEnable.GetAt(0))>='0') && (char(m_sHotkeyEnable.GetAt(0))<='9')){m_dwHotKeyEnable = char(m_sHotkeyEnable.GetAt(0))-'0'+0x30;}
		RegisterHotKey(NULL, HOTKEY_ENABLE, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKeyEnable);
	}


	if(m_bAutoMinimize==TRUE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_AUTO_MINIMIZE))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_AUTO_MINIMIZE))->SetCheck(0);
	}

	if(m_bMinimizeToTaskTray==TRUE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_TASKTRAY))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_TASKTRAY))->SetCheck(0);
	}

	if(m_bLog==TRUE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_LOG))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_LOG))->SetCheck(0);
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
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->SetCheck(1);
		for(int iScene=0; iScene<MAX_THREAD; iScene++){ResetHotkey(iScene);}
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->SetCheck(0);
	}
	m_sEditSpeed.Format(_T("1.00"));
	m_sliderSpeed.SetRangeMin(0);	
	m_sliderSpeed.SetRangeMax(100);
	m_sliderSpeed.SetPos(50);

	WindowNameRefresh();
	RefreshTargetWindowPos();
	UpdateData(FALSE);

	ImgRGB imgTest;
	imgTest.Assign(_T("D:\\GitHub\\SAutomation\\SAutomation\\SAutomation\\Macro\\Model\\test.bmp"));
	ImgRGBPyramid imgTestPyram;
	imgTestPyram.SetPyramid(&imgTest);
	WriteImage(&imgTestPyram.imgRGB, _T("D:\\GitHub\\SAutomation\\SAutomation\\SAutomation\\Macro\\Model\\test2.bmp"));
	TrayNotifyIconMessage(NIM_ADD);
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


	CString sTip = _T("SAutomation.exe");
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd   = GetSafeHwnd();
	nid.uID    = IDI_ICON_STANDBY;
	nid.uFlags = NIF_MESSAGE | NIF_ICON;
	nid.uCallbackMessage = WM_TRAYNOTIFY;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.hIcon  = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(iIcon));
	_tcscpy_s(nid.szTip, _countof(nid.szTip), (LPCTSTR)sTip);


	return Shell_NotifyIcon(NIM_MODIFY , &nid);
}

BOOL CSAutomationDlg::TrayNotifyIconMessage(DWORD dwMessage)
{
	CString sTip = _T("SAutomation.exe");
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd   = GetSafeHwnd();
	nid.uID    = IDI_ICON_STANDBY;
	nid.uFlags = NIF_MESSAGE | NIF_ICON;
	nid.uCallbackMessage = WM_TRAYNOTIFY;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.hIcon  = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_STANDBY));
	_tcscpy_s(nid.szTip, _countof(nid.szTip), (LPCTSTR)sTip);

	return Shell_NotifyIcon(dwMessage, &nid);
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
		if(iKey == m_OpeInfo[0].dwHotKey){Operate(0);return TRUE;}
		if(iKey == m_OpeInfo[1].dwHotKey){Operate(1);return TRUE;}
		if(iKey == m_OpeInfo[2].dwHotKey){Operate(2);return TRUE;}
		if(iKey == m_OpeInfo[3].dwHotKey){Operate(3);return TRUE;}
		if(iKey == m_OpeInfo[4].dwHotKey){Operate(4);return TRUE;}
		if(iKey == m_OpeInfo[5].dwHotKey){Operate(5);return TRUE;}
		if(iKey == m_OpeInfo[6].dwHotKey){Operate(6);return TRUE;}
		if(iKey == m_OpeInfo[7].dwHotKey){Operate(7);return TRUE;}
		if(iKey == m_OpeInfo[8].dwHotKey){Operate(8);return TRUE;}
		if(iKey == m_OpeInfo[9].dwHotKey){Operate(9);return TRUE;}
		if(iKey == m_OpeInfo[10].dwHotKey){Operate(10);return TRUE;}
		if(iKey == m_OpeInfo[11].dwHotKey){Operate(11);return TRUE;}
		if(iKey == m_OpeInfo[12].dwHotKey){Operate(12);return TRUE;}
		if(iKey == m_OpeInfo[13].dwHotKey){Operate(13);return TRUE;}
		if(iKey == m_OpeInfo[14].dwHotKey){Operate(14);return TRUE;}
		if(iKey == m_OpeInfo[15].dwHotKey){Operate(15);return TRUE;}
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
	ChangeMouseOrigin(0, 0);
	m_comboWindowName.SetCurSel(0);
	UpdateData(FALSE);

	DWORD dwThreadID;
	if(g_hThread[iScene] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iScene], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iScene].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iScene]);
	int iParam;
	int iChecked;
	int iLogLevel;
	iChecked = ((CButton*)GetDlgItem(IDC_CHECK_LOG))->GetCheck();
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

	iParam = iLogLevel<<PARAM_LOGLEVEL_SHIFT;
	iParam += iScene;
	m_OpeInfo[iScene].m_bRunning=TRUE;
	g_hThread[iScene] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);

	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iScene].Format(_T("Running"));
	UpdateData(FALSE);
	ChangeIcon(IDI_ICON_RUNNING);
}




void CSAutomationDlg::FileSelect(CString *sFileName)
{

	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),m_sDir);

	CFileDialog cf(TRUE);
	cf.m_ofn.lpstrInitialDir = sMacroFolderPath;
	if(cf.DoModal()!=IDOK){sFileName->Format(_T("")); return;}
	sFileName->Format(_T("%s"), cf.GetFileName());
}


BOOL CSAutomationDlg::DestroyWindow()
{
	g_bHalt = TRUE;
	Sleep(1000);

	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	SaveSettings();

	TrayNotifyIconMessage(NIM_DELETE);
	return CDialogEx::DestroyWindow();
}



void CSAutomationDlg::OnBnClickedButton00(){FileSelect(&m_sEditFileName[0]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton01(){FileSelect(&m_sEditFileName[1]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton02(){FileSelect(&m_sEditFileName[2]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton03(){FileSelect(&m_sEditFileName[3]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton04(){FileSelect(&m_sEditFileName[4]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton05(){FileSelect(&m_sEditFileName[5]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton06(){FileSelect(&m_sEditFileName[6]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton07(){FileSelect(&m_sEditFileName[7]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton08(){FileSelect(&m_sEditFileName[8]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton09(){FileSelect(&m_sEditFileName[9]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton10(){FileSelect(&m_sEditFileName[10]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton11(){FileSelect(&m_sEditFileName[11]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton12(){FileSelect(&m_sEditFileName[12]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton13(){FileSelect(&m_sEditFileName[13]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton14(){FileSelect(&m_sEditFileName[14]);UpdateData(FALSE);SaveSettings();}
void CSAutomationDlg::OnBnClickedButton15(){FileSelect(&m_sEditFileName[15]);UpdateData(FALSE);SaveSettings();}

void CSAutomationDlg::OnSelchangeCombo00(){ResetHotkey(0);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo01(){ResetHotkey(1);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo02(){ResetHotkey(2);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo03(){ResetHotkey(3);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo04(){ResetHotkey(4);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo05(){ResetHotkey(5);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo06(){ResetHotkey(6);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo07(){ResetHotkey(7);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo08(){ResetHotkey(8);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo09(){ResetHotkey(9);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo10(){ResetHotkey(10);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo11(){ResetHotkey(11);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo12(){ResetHotkey(12);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo13(){ResetHotkey(13);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo14(){ResetHotkey(14);SaveSettings();}
void CSAutomationDlg::OnSelchangeCombo15(){ResetHotkey(15);SaveSettings();}

void CSAutomationDlg::OnSelchangeComboCtrl00(){ResetHotkey(0);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl01(){ResetHotkey(1);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl02(){ResetHotkey(2);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl03(){ResetHotkey(3);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl04(){ResetHotkey(4);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl05(){ResetHotkey(5);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl06(){ResetHotkey(6);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl07(){ResetHotkey(7);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl08(){ResetHotkey(8);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl09(){ResetHotkey(9);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl10(){ResetHotkey(10);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl11(){ResetHotkey(11);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl12(){ResetHotkey(12);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl13(){ResetHotkey(13);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl14(){ResetHotkey(14);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboCtrl15(){ResetHotkey(15);SaveSettings();}

void CSAutomationDlg::OnSelchangeComboShift00(){ResetHotkey(0);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift01(){ResetHotkey(1);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift02(){ResetHotkey(2);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift03(){ResetHotkey(3);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift04(){ResetHotkey(4);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift05(){ResetHotkey(5);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift06(){ResetHotkey(6);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift07(){ResetHotkey(7);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift08(){ResetHotkey(8);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift09(){ResetHotkey(9);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift10(){ResetHotkey(10);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift11(){ResetHotkey(11);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift12(){ResetHotkey(12);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift13(){ResetHotkey(13);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift14(){ResetHotkey(14);SaveSettings();}
void CSAutomationDlg::OnSelchangeComboShift15(){ResetHotkey(15);SaveSettings();}

void CSAutomationDlg::OnBnClickedButtonOperate00(){Operate(0);}
void CSAutomationDlg::OnBnClickedButtonOperate01(){Operate(1);}
void CSAutomationDlg::OnBnClickedButtonOperate02(){Operate(2);}
void CSAutomationDlg::OnBnClickedButtonOperate03(){Operate(3);}
void CSAutomationDlg::OnBnClickedButtonOperate04(){Operate(4);}
void CSAutomationDlg::OnBnClickedButtonOperate05(){Operate(5);}
void CSAutomationDlg::OnBnClickedButtonOperate06(){Operate(6);}
void CSAutomationDlg::OnBnClickedButtonOperate07(){Operate(7);}
void CSAutomationDlg::OnBnClickedButtonOperate08(){Operate(8);}
void CSAutomationDlg::OnBnClickedButtonOperate09(){Operate(9);}
void CSAutomationDlg::OnBnClickedButtonOperate10(){Operate(10);}
void CSAutomationDlg::OnBnClickedButtonOperate11(){Operate(11);}
void CSAutomationDlg::OnBnClickedButtonOperate12(){Operate(12);}
void CSAutomationDlg::OnBnClickedButtonOperate13(){Operate(13);}
void CSAutomationDlg::OnBnClickedButtonOperate14(){Operate(14);}
void CSAutomationDlg::OnBnClickedButtonOperate15(){Operate(15);}

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
	UnregisterHotKey(NULL, HOTKEY_SCENE_0+iScene);

	TCHAR tch[8];
	if(m_combo[iScene].GetCurSel()<0){return;}
	m_combo[iScene].GetLBText(m_combo[iScene].GetCurSel(),tch);
	if(wcscmp(tch,_T(" "))==0){return;}
	if(_tcslen(tch)>=2)
	{
		if(_tcsicmp(tch,_T("F1"))==0){m_OpeInfo[iScene].dwHotKey = VK_F1;}
		if(_tcsicmp(tch,_T("F2"))==0){m_OpeInfo[iScene].dwHotKey = VK_F2;}
		if(_tcsicmp(tch,_T("F3"))==0){m_OpeInfo[iScene].dwHotKey = VK_F3;}
		if(_tcsicmp(tch,_T("F4"))==0){m_OpeInfo[iScene].dwHotKey = VK_F4;}
		if(_tcsicmp(tch,_T("F5"))==0){m_OpeInfo[iScene].dwHotKey = VK_F5;}
		if(_tcsicmp(tch,_T("F6"))==0){m_OpeInfo[iScene].dwHotKey = VK_F6;}
		if(_tcsicmp(tch,_T("F7"))==0){m_OpeInfo[iScene].dwHotKey = VK_F7;}
		if(_tcsicmp(tch,_T("F8"))==0){m_OpeInfo[iScene].dwHotKey = VK_F8;}
		if(_tcsicmp(tch,_T("F9"))==0){m_OpeInfo[iScene].dwHotKey = VK_F9;}
		if(_tcsicmp(tch,_T("F10"))==0){m_OpeInfo[iScene].dwHotKey = VK_F10;}
		if(_tcsicmp(tch,_T("F11"))==0){m_OpeInfo[iScene].dwHotKey = VK_F11;}
		if(_tcsicmp(tch,_T("F12"))==0){m_OpeInfo[iScene].dwHotKey = VK_F12;}
		if(_tcsicmp(tch,_T("Insert"))==0){m_OpeInfo[iScene].dwHotKey = VK_INSERT;}

	}
	else
	{
		if((tch[0]>='a') && (tch[0]<='z')){m_OpeInfo[iScene].dwHotKey = char(tch[0])-'a'+0x41;}
		if((tch[0]>='0') && (tch[0]<='9')){m_OpeInfo[iScene].dwHotKey = char(tch[0])-'0'+0x30;}
	}

	m_OpeInfo[iScene].bUseShift=FALSE;
	m_OpeInfo[iScene].bUseCtrl=FALSE;
	m_OpeInfo[iScene].bUseAlt=FALSE;
	m_OpeInfo[iScene].bUseWin=FALSE;

	if(m_comboUseCtrl[iScene].GetCurSel()<0){}
	else
	{
		m_comboUseCtrl[iScene].GetLBText(m_comboUseCtrl[iScene].GetCurSel(),tch);
		if(wcscmp(tch,_T("Ctrl"))==0){m_OpeInfo[iScene].bUseCtrl=TRUE;}
		if(wcscmp(tch,_T("Shift"))==0){m_OpeInfo[iScene].bUseShift=TRUE;}
		if(wcscmp(tch,_T("Alt"))==0){m_OpeInfo[iScene].bUseAlt=TRUE;}
		if(wcscmp(tch,_T("Win"))==0){m_OpeInfo[iScene].bUseWin=TRUE;}
	}

	if(m_comboUseShift[iScene].GetCurSel()<0){}
	else
	{
		m_comboUseShift[iScene].GetLBText(m_comboUseShift[iScene].GetCurSel(),tch);
		if(wcscmp(tch,_T("Ctrl"))==0){m_OpeInfo[iScene].bUseCtrl=TRUE;}
		if(wcscmp(tch,_T("Shift"))==0){m_OpeInfo[iScene].bUseShift=TRUE;}
		if(wcscmp(tch,_T("Alt"))==0){m_OpeInfo[iScene].bUseAlt=TRUE;}
		if(wcscmp(tch,_T("Win"))==0){m_OpeInfo[iScene].bUseWin=TRUE;}
	}


	if(((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
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
}

void CSAutomationDlg::OnBnClickedCheckEnableHotkey()
{
	for(int iScene=0; iScene<MAX_THREAD; iScene++){ResetHotkey(iScene);}
	return;
}

void CSAutomationDlg::ToggleEnable()
{
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->GetCheck()==1)
	{
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->SetCheck(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE_HOTKEY))->SetCheck(1);
	}
	UpdateData(TRUE);
	OnBnClickedCheckEnableHotkey();
}


void CSAutomationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType == SIZE_MINIMIZED)
	{
		if(m_bMinimizeToTaskTray==TRUE)
		{
			ShowWindow(SW_HIDE);
			KillTimer(TIMER_WAKE_UP);
		}
	}
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


void CSAutomationDlg::OnBnClickedCheckTasktray()
{

	if(((CButton*)GetDlgItem(IDC_CHECK_TASKTRAY))->GetCheck()==1)
	{
		m_bMinimizeToTaskTray=TRUE;
	}
	else
	{
		m_bMinimizeToTaskTray=FALSE;
	}

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
