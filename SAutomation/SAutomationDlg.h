
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "thread.h"
#include "afxcmn.h"

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

#define HOTKEY_ENABLE (20)

#define HOTKEY_ID_ESCAPE (100)

struct OperationInfo
{
	BOOL bLoop;
	
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
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();

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
	afx_msg void OnSelchangeCombo0();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnSelchangeCombo5();
	afx_msg void OnSelchangeCombo6();
	afx_msg void OnSelchangeCombo7();
	afx_msg void OnSelchangeCombo8();
	afx_msg void OnSelchangeCombo9();
	afx_msg void OnSelchangeCombo10();
	afx_msg void OnSelchangeCombo11();
	afx_msg void OnSelchangeCombo12();
	afx_msg void OnSelchangeCombo13();
	afx_msg void OnSelchangeCombo14();
	afx_msg void OnSelchangeCombo15();

	afx_msg void OnSelchangeComboCtrl0();
	afx_msg void OnSelchangeComboCtrl1();
	afx_msg void OnSelchangeComboCtrl2();
	afx_msg void OnSelchangeComboCtrl3();
	afx_msg void OnSelchangeComboCtrl4();
	afx_msg void OnSelchangeComboCtrl5();
	afx_msg void OnSelchangeComboCtrl6();
	afx_msg void OnSelchangeComboCtrl7();
	afx_msg void OnSelchangeComboCtrl8();
	afx_msg void OnSelchangeComboCtrl9();
	afx_msg void OnSelchangeComboCtrl10();
	afx_msg void OnSelchangeComboCtrl11();
	afx_msg void OnSelchangeComboCtrl12();
	afx_msg void OnSelchangeComboCtrl13();
	afx_msg void OnSelchangeComboCtrl14();
	afx_msg void OnSelchangeComboCtrl15();

	afx_msg void OnSelchangeComboShift0();
	afx_msg void OnSelchangeComboShift1();
	afx_msg void OnSelchangeComboShift2();
	afx_msg void OnSelchangeComboShift3();
	afx_msg void OnSelchangeComboShift4();
	afx_msg void OnSelchangeComboShift5();
	afx_msg void OnSelchangeComboShift6();
	afx_msg void OnSelchangeComboShift7();
	afx_msg void OnSelchangeComboShift8();
	afx_msg void OnSelchangeComboShift9();
	afx_msg void OnSelchangeComboShift10();
	afx_msg void OnSelchangeComboShift11();
	afx_msg void OnSelchangeComboShift12();
	afx_msg void OnSelchangeComboShift13();
	afx_msg void OnSelchangeComboShift14();
	afx_msg void OnSelchangeComboShift15();

	afx_msg void OnSelchangeComboEnable();

	afx_msg void OnBnClickedButtonOperate0();
	afx_msg void OnBnClickedButtonOperate1();
	afx_msg void OnBnClickedButtonOperate2();
	afx_msg void OnBnClickedButtonOperate3();
	afx_msg void OnBnClickedButtonOperate4();
	afx_msg void OnBnClickedButtonOperate5();
	afx_msg void OnBnClickedButtonOperate6();
	afx_msg void OnBnClickedButtonOperate7();
	afx_msg void OnBnClickedButtonOperate8();
	afx_msg void OnBnClickedButtonOperate9();
	afx_msg void OnBnClickedButtonOperate10();
	afx_msg void OnBnClickedButtonOperate11();
	afx_msg void OnBnClickedButtonOperate12();
	afx_msg void OnBnClickedButtonOperate13();
	afx_msg void OnBnClickedButtonOperate14();
	afx_msg void OnBnClickedButtonOperate15();

	afx_msg void OnBnClickedCheckEnableHotkey();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonOpenFolder();
	CString m_sEditSpeed;
	afx_msg void OnChangeEditSpeed();
	CSliderCtrl m_sliderSpeed;
	afx_msg void OnKillfocusEditSpeed();
	afx_msg void OnCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonConfing();
	afx_msg void OnBnClickedCheckTasktray();
	afx_msg void OnBnClickedButtonWindowNameRefresh();
};
