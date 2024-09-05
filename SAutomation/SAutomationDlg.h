
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "thread.h"
#include "afxcmn.h"
#include "InputDialog.h"

#define HOTKEY_ID_0 (10)
#define HOTKEY_ID_1 (11)
#define HOTKEY_ID_2 (12)
#define HOTKEY_ID_3 (13)
#define HOTKEY_ID_4 (14)
#define HOTKEY_ID_5 (15)
#define HOTKEY_ID_6 (16)
#define HOTKEY_ID_7 (17)
#define HOTKEY_ID_8 (18)
#define HOTKEY_ID_9 (19)
#define HOTKEY_ID_10 (20)
#define HOTKEY_ID_11 (21)
#define HOTKEY_ID_12 (22)
#define HOTKEY_ID_13 (23)
#define HOTKEY_ID_14 (24)
#define HOTKEY_ID_15 (25)

#define HOTKEY_ENABLE (30)

#define HOTKEY_ID_ESCAPE (100)

struct OperationInfo
{	
	CString sHotkey;
	BOOL bUseCtrl;
	BOOL bUseShift;
	BOOL bUseAlt;
	BOOL bUseWin;
	DWORD dwHotKey;
	BOOL m_bRunning;
	CString sFileName;
	OperationInfo(){m_bRunning=FALSE;}
};

// CSAutomationDlg ダイアログ
class CSAutomationDlg : public CDialogEx
{
	// コンストラクション
public:
	CSAutomationDlg(CWnd* pParent = NULL);	// 標準コンストラクター

	// ダイアログ データ
	enum { IDD = IDD_SAUTOMATION_DIALOG };
	
		CInputDialog cInput;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	BOOL TrayNotifyIconMessage(DWORD dwMessage);
	BOOL ChangeIcon(int iIcon);

	void Operate(int iID);

	void ResetHotkey(int iID);

	void ToggleEnable();

	OperationInfo m_OpeInfo[MAX_THREAD];

	BOOL m_bEnableHotkey;
	BOOL m_bAutoMinimize;
	BOOL m_bMinimizeToTaskTray;
	CString m_sHotkeyEnable;
	CString m_sTargetWindowName;
	int m_iLogLevel;
	BOOL m_bLog;
	
	void RefreshTargetWindowPos();
	DWORD m_dwHotKeyEnable;

	CString m_sDir;
	void FileSelect(CString *sFileName);
	void SaveSettings();
	void WindowNameRefresh();
	void ReadSettings();
	BOOL m_bRunningAny;
	BOOL MouseMoveAndDisp(DWORD dwMoveDirection, int iDistance);
	// 実装
protected:
	HICON m_hIconStandby;
	HICON m_hIconRunning;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButton01();
	afx_msg void OnBnClickedButton02();
	afx_msg void OnBnClickedButton03();
	afx_msg void OnBnClickedButton04();
	afx_msg void OnBnClickedButton05();
	afx_msg void OnBnClickedButton06();
	afx_msg void OnBnClickedButton07();
	afx_msg void OnBnClickedButton08();
	afx_msg void OnBnClickedButton09();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	
	afx_msg void OnSelchangeCombo00();
	afx_msg void OnSelchangeCombo01();
	afx_msg void OnSelchangeCombo02();
	afx_msg void OnSelchangeCombo03();
	afx_msg void OnSelchangeCombo04();
	afx_msg void OnSelchangeCombo05();
	afx_msg void OnSelchangeCombo06();
	afx_msg void OnSelchangeCombo07();
	afx_msg void OnSelchangeCombo08();
	afx_msg void OnSelchangeCombo09();
	afx_msg void OnSelchangeCombo10();
	afx_msg void OnSelchangeCombo11();
	afx_msg void OnSelchangeCombo12();
	afx_msg void OnSelchangeCombo13();
	afx_msg void OnSelchangeCombo14();
	afx_msg void OnSelchangeCombo15();

	afx_msg void OnSelchangeComboCtrl00();
	afx_msg void OnSelchangeComboCtrl01();
	afx_msg void OnSelchangeComboCtrl02();
	afx_msg void OnSelchangeComboCtrl03();
	afx_msg void OnSelchangeComboCtrl04();
	afx_msg void OnSelchangeComboCtrl05();
	afx_msg void OnSelchangeComboCtrl06();
	afx_msg void OnSelchangeComboCtrl07();
	afx_msg void OnSelchangeComboCtrl08();
	afx_msg void OnSelchangeComboCtrl09();
	afx_msg void OnSelchangeComboCtrl10();
	afx_msg void OnSelchangeComboCtrl11();
	afx_msg void OnSelchangeComboCtrl12();
	afx_msg void OnSelchangeComboCtrl13();
	afx_msg void OnSelchangeComboCtrl14();
	afx_msg void OnSelchangeComboCtrl15();

	afx_msg void OnSelchangeComboShift00();
	afx_msg void OnSelchangeComboShift01();
	afx_msg void OnSelchangeComboShift02();
	afx_msg void OnSelchangeComboShift03();
	afx_msg void OnSelchangeComboShift04();
	afx_msg void OnSelchangeComboShift05();
	afx_msg void OnSelchangeComboShift06();
	afx_msg void OnSelchangeComboShift07();
	afx_msg void OnSelchangeComboShift08();
	afx_msg void OnSelchangeComboShift09();
	afx_msg void OnSelchangeComboShift10();
	afx_msg void OnSelchangeComboShift11();
	afx_msg void OnSelchangeComboShift12();
	afx_msg void OnSelchangeComboShift13();
	afx_msg void OnSelchangeComboShift14();
	afx_msg void OnSelchangeComboShift15();
	
	afx_msg void OnBnClickedButtonOperate00();
	afx_msg void OnBnClickedButtonOperate01();
	afx_msg void OnBnClickedButtonOperate02();
	afx_msg void OnBnClickedButtonOperate03();
	afx_msg void OnBnClickedButtonOperate04();
	afx_msg void OnBnClickedButtonOperate05();
	afx_msg void OnBnClickedButtonOperate06();
	afx_msg void OnBnClickedButtonOperate07();
	afx_msg void OnBnClickedButtonOperate08();
	afx_msg void OnBnClickedButtonOperate09();
	afx_msg void OnBnClickedButtonOperate10();
	afx_msg void OnBnClickedButtonOperate11();
	afx_msg void OnBnClickedButtonOperate12();
	afx_msg void OnBnClickedButtonOperate13();
	afx_msg void OnBnClickedButtonOperate14();
	afx_msg void OnBnClickedButtonOperate15();


	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sEditMousePosC;
	CString m_sEditMousePosR;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL DestroyWindow();

	CString m_sEditFileName[MAX_THREAD];
	CString m_sEditStatus[MAX_THREAD];
	CComboBox m_combo[MAX_THREAD];
	CComboBox m_comboUseCtrl[MAX_THREAD];
	CComboBox m_comboUseShift[MAX_THREAD];
	CComboBox m_comboEnable;
	CComboBox m_comboLogLevel;

	CComboBox m_comboWindowName;
	afx_msg void OnSelchangeWindowName();
	
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnDispStandby(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSelchangeCombo0Enable();

	afx_msg void OnBnClickedCheckEnableHotkey();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton0OpenFolder();
	CString m_sEditSpeed;
	afx_msg void OnChangeEditSpeed();
	CSliderCtrl m_sliderSpeed;
	afx_msg void OnKillfocusEditSpeed();
	afx_msg void OnCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton0Confing();
	afx_msg void OnBnClickedCheckTasktray();
	afx_msg void OnBnClickedButton0WindowNameRefresh();
};
