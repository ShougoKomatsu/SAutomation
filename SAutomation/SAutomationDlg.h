
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "thread.h"
#include "afxcmn.h"
#include "InputDialog.h"
#include "TabItem.h"
#include "DlgCompact.h"

extern BOOL g_bCompactBiew;
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
#define HOTKEY_SCENE_16 (26)
#define HOTKEY_SCENE_17 (27)
#define HOTKEY_SCENE_18 (28)
#define HOTKEY_SCENE_19 (29)
#define HOTKEY_SCENE_20 (30)
#define HOTKEY_SCENE_21 (31)
#define HOTKEY_SCENE_22 (32)
#define HOTKEY_SCENE_23 (33)
#define HOTKEY_SCENE_24 (34)
#define HOTKEY_SCENE_25 (35)
#define HOTKEY_SCENE_26 (36)
#define HOTKEY_SCENE_27 (37)
#define HOTKEY_SCENE_28 (38)
#define HOTKEY_SCENE_29 (39)
#define HOTKEY_SCENE_30 (40)
#define HOTKEY_SCENE_31 (41)
#define HOTKEY_SCENE_32 (42)
#define HOTKEY_SCENE_33 (43)
#define HOTKEY_SCENE_34 (44)
#define HOTKEY_SCENE_35 (45)
#define HOTKEY_SCENE_36 (46)
#define HOTKEY_SCENE_37 (47)
#define HOTKEY_SCENE_38 (48)
#define HOTKEY_SCENE_39 (49)
#define HOTKEY_SCENE_40 (50)
#define HOTKEY_SCENE_41 (51)
#define HOTKEY_SCENE_42 (52)
#define HOTKEY_SCENE_43 (53)
#define HOTKEY_SCENE_44 (54)
#define HOTKEY_SCENE_45 (55)
#define HOTKEY_SCENE_46 (56)
#define HOTKEY_SCENE_47 (57)
#define HOTKEY_SCENE_48 (58)
#define HOTKEY_SCENE_49 (59)
#define HOTKEY_SCENE_50 (60)
#define HOTKEY_SCENE_51 (61)
#define HOTKEY_SCENE_52 (62)
#define HOTKEY_SCENE_53 (63)
#define HOTKEY_SCENE_54 (64)
#define HOTKEY_SCENE_55 (65)
#define HOTKEY_SCENE_56 (66)
#define HOTKEY_SCENE_57 (67)
#define HOTKEY_SCENE_58 (68)
#define HOTKEY_SCENE_59 (69)
#define HOTKEY_SCENE_60 (70)
#define HOTKEY_SCENE_61 (71)
#define HOTKEY_SCENE_62 (72)
#define HOTKEY_SCENE_63 (73)


#define HOTKEY_ENABLE (80)

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
	void ChangeToCompact();
	void SaveSettings();
	void ResetHotkey(int iScene);
	void Operate(int iScene);
	CInputDialog cInput;
	OperationInfo m_OpeInfo[MAX_THREAD];
	CString m_sDir;
	BOOL ReHookWindowsHook();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	BOOL ChangeIcon(int iIcon);



	void ToggleEnable();


	BOOL m_bEnableHotkey;
	BOOL m_bAutoMinimize;
	CString m_sHotkeyEnable;
	CString m_sTargetWindowName;
	int m_iLogLevel;
	BOOL m_bLog;
	
	void RefreshTargetWindowPos();
	DWORD m_dwHotKeyEnable;
	
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
	
	CDlgCompact m_cDlgCompact;

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
	afx_msg void OnBnClickedButton0WindowNameRefresh();
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTabOperation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonOpenCompact();
	afx_msg void OnBnClickedOk();
};

void SetComboItemCtrl(CComboBox* combo, OperationInfo* op);

void SetComboItemShift(CComboBox* combo,OperationInfo* op);

void SetComboItem(CComboBox* combo, CString m_sHotkey);