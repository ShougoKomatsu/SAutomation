#pragma once
#include "TabItem.h"
//#include "SAutomationDlg.h"
// CSettingDlg ダイアログ
class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)
public:
	CSettingDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSettingDlg();
	CString m_sDir;
	CTabItem m_tabItem;
//	BOOL ChangeIcon(int iIcon);
	HICON m_hIconStandby;
	HICON m_hIconRunning;
	CString m_sTargetWindowName;
	CComboBox m_comboEnable;
	CComboBox m_comboLogLevel;

	CString m_sEditSpeed;
	CSliderCtrl m_sliderSpeed;
	CTabCtrl m_tab;

	BOOL m_bNotModified;
	AutomationInfo m_Automation;
	void SetTitleNotChanged(BOOL bTF);

	BOOL UpdateAutomationInfo(AutomationInfo* autoInfo);
	void GetLogLavel(AutomationInfo* autoInfo);
	CString m_sEditMousePosC;
	CString m_sEditMousePosR;
	CComboBox m_comboWindowName;
	//	CSAutomationDlg* pParent;
	void WindowNameRefresh();
	void RefreshTargetWindowPos();
	// ダイアログ データ
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton0OpenFolder();
	afx_msg void OnKillfocusEditSpeed();
	afx_msg void OnCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton0WindowNameRefresh();
	afx_msg void OnSelchangeCombo0Enable();
	afx_msg void OnBnClickedCheckEnableHotkey();
	afx_msg void OnSelchangeWindowName();
	afx_msg void OnBnClickedSave();
	afx_msg void OnTcnSelchangeTabOperation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonOpenCompact();
//	afx_msg LRESULT OnDispStandby(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedCheckAutoMinimize();
	afx_msg void OnBnClickedCheckLog();
	afx_msg void OnSelchangeComboLogLevel();
	afx_msg void OnBnClickedCheckTasktray();
};
