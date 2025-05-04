#pragma once
#include "Common.h"
#include "SelectDlg.h"
// CTabItem ダイアログ

class CTabItem : public CDialogEx
{
	DECLARE_DYNAMIC(CTabItem)
	
public:
	CTabItem(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CTabItem();
	BOOL m_bReset;
	int m_iSlot;
	CString m_sDir;

	CSelectDlg m_cDlgSelect;
	AutomationInfo* m_autoInfo;
	CWnd* pParentWnd;
	BOOL* pbNotModified;
	void SetTitleNotChanged(BOOL bTF);
	void RefleshDialog(int iSlot);
	void UpdateData_My(BOOL bTF){UpdateData(bTF);}
	void FileSelect(int iSlot, int iScene);
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
	
	void CTabItem::UpdateHotkey(int iSlot, int iScene);

	/*
	class CSettingDlg* pParent;
	
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
	*/

// ダイアログ データ
	enum { IDD = IDD_DIALOG_TAB_ITEMS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_sEditFileName[MAX_NORMAL_THREAD];
	CComboBox m_combo[MAX_NORMAL_THREAD];
	CComboBox m_comboUseCtrl[MAX_NORMAL_THREAD];
	CComboBox m_comboUseShift[MAX_NORMAL_THREAD];

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedTabCheckDisableHalt00();
	afx_msg void OnBnClickedTabCheckDisableHalt01();
	afx_msg void OnBnClickedTabCheckDisableHalt02();
	afx_msg void OnBnClickedTabCheckDisableHalt03();
	afx_msg void OnBnClickedTabCheckDisableHalt04();
	afx_msg void OnBnClickedTabCheckDisableHalt05();
	afx_msg void OnBnClickedTabCheckDisableHalt06();
	afx_msg void OnBnClickedTabCheckDisableHalt07();
	afx_msg void OnBnClickedTabCheckDisableHalt08();
	afx_msg void OnBnClickedTabCheckDisableHalt09();
	afx_msg void OnBnClickedTabCheckDisableHalt10();
	afx_msg void OnBnClickedTabCheckDisableHalt11();
	afx_msg void OnBnClickedTabCheckDisableHalt12();
	afx_msg void OnBnClickedTabCheckDisableHalt13();
	afx_msg void OnBnClickedTabCheckDisableHalt14();
	afx_msg void OnBnClickedTabCheckDisableHalt15();
};
