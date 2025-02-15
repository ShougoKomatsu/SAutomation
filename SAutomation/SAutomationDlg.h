
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "thread.h"
#include "afxcmn.h"
#include "InputDialog.h"
#include "TabItem.h"
extern CStdioFile g_cf[MAX_THREAD];
extern CString g_sLogFilePath[MAX_THREAD];


#define HOTKEY_SCENE_0 (10)
#define HOTKEY_SCENE_1 (11)
#define HOTKEY_SCENE_2 (12)
#define HOTKEY_SCENE_3 (13)
#define HOTKEY_SCENE_4 (14)
#define HOTKEY_SCENE_5 (15)
#define HOTKEY_SCENE_6 (16)
#define HOTKEY_SCENE_7 (17)
#define HOTKEY_SCENE_8 (18)
#define HOTKEY_SCENE_9 (19)
#define HOTKEY_SCENE_10 (20)
#define HOTKEY_SCENE_11 (21)
#define HOTKEY_SCENE_12 (22)
#define HOTKEY_SCENE_13 (23)
#define HOTKEY_SCENE_14 (24)
#define HOTKEY_SCENE_15 (25)

#define HOTKEY_ENABLE (30)

#define HOTKEY_ESCAPE (100)

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
	
	void RefleshDialog(int iSlot);
	void SaveSettings();
	void FileSelect(int iScene);
	void ResetHotkey(int iScene);
	void Operate(int iScene);
		CInputDialog cInput;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	BOOL TrayNotifyIconMessage(DWORD dwMessage);
	BOOL ChangeIcon(int iIcon);



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

	CTabItem m_tabItem;

	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sEditMousePosC;
	CString m_sEditMousePosR;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL DestroyWindow();

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
	CTabCtrl m_tab;
};
