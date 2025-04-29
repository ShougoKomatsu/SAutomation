
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "stdafx.h"
#include "Common.h"
#include "SettingDlg.h"
#include "SelectDlg.h"
extern CStdioFile* g_cf[MAX_THREAD];
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
#define HOTKEY_SCENE_64 (74)
#define HOTKEY_SCENE_65 (75)
#define HOTKEY_SCENE_66 (76)
#define HOTKEY_SCENE_67 (77)
#define HOTKEY_SCENE_68 (78)
#define HOTKEY_SCENE_69 (79)
#define HOTKEY_SCENE_70 (80)
#define HOTKEY_SCENE_71 (81)
#define HOTKEY_SCENE_72 (82)
#define HOTKEY_SCENE_73 (83)
#define HOTKEY_SCENE_74 (84)
#define HOTKEY_SCENE_75 (85)
#define HOTKEY_SCENE_76 (86)
#define HOTKEY_SCENE_77 (87)
#define HOTKEY_SCENE_78 (88)
#define HOTKEY_SCENE_79 (89)


#define HOTKEY_ENABLE (90)

#define HOTKEY_ESCAPE (100)


// SettingDlg ダイアログ
class CSAutomationDlg : public CDialogEx
{
	// コンストラクション
public:
	CSAutomationDlg(CWnd* pParent = NULL);	// 標準コンストラクター
	~CSAutomationDlg();
	BOOL m_bMoving;
	BOOL m_iX;
	BOOL m_iY;
	BOOL m_bRunning;
	CBrush m_brRed;
	CBrush m_brGreen;
	CBrush m_brBlack;
	HICON m_hIconStandby;
	HICON m_hIconRunning;
	HICON m_hIconMinimize;
	HICON m_hIconClose;
	CSelectDlg m_cDlgSelect;
	CSettingDlg m_cDlgSetting;
	
	BOOL ChangeIcon(int iIcon);
	BOOL TrayNotifyIconMessage(DWORD dwMessage, int iIconID);
	
	void SelectAndOperate(int iExScene);
	void ToggleEnable();

	void WinodowMove(int ixFrom, int iyFrom, int ixTo, int iyTo);

	void SetSelection(int iExScene, CString sFilePath);

	BOOL ReHookWindowsHook();
	void ResetHotkey(int iScene);
	void Operate(int iScene);
	// ダイアログ データ
	enum { IDD = IDD_SAUTOMATION_DIALOG };
	
    NOTIFYICONDATA m_nIcon;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


	// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_sEditCompactMouseR;
	CString m_sEditCompactMouseC;
	CButton m_ButtonClose;
	CButton m_ButtonMinimize;

	afx_msg LRESULT OnDispStandby(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDispCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonCompactExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCompactButtonMinimize();
	afx_msg void OnBnClickedCompactButtonClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
