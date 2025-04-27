#pragma once
#include "Common.h"

// CSelectDlg ダイアログ

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	BOOL m_bReset;
	CString m_sDir;
	CString m_sResultFileName;
	DWORD m_dwHotKeys[MAX_SELECTION];
	CString m_sSelectKeys[MAX_SELECTION];
	CString m_sSelectFiles[MAX_SELECTION];
	CSelectDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSelectDlg();
	int m_iModeOperate;
// ダイアログ データ
	enum { IDD = IDD_DIALOG_SELECT };
	
void FileSelect(int iSelect);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo[MAX_SELECTION];
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSelectKey1();
	afx_msg void OnBnClickedButtonSelectKey2();
	afx_msg void OnBnClickedButtonSelectKey3();
	afx_msg void OnBnClickedButtonSelectKey4();
	afx_msg void OnBnClickedButtonSelectKey5();
	afx_msg void OnBnClickedButtonSelectKey6();
	afx_msg void OnBnClickedButtonSelectKey7();
	afx_msg void OnBnClickedButtonSelectKey8();
	afx_msg void OnCbnSelchangeSelectCombo1();
	afx_msg void OnCbnSelchangeSelectCombo2();
	afx_msg void OnCbnSelchangeSelectCombo3();
	afx_msg void OnCbnSelchangeSelectCombo4();
	afx_msg void OnCbnSelchangeSelectCombo5();
	afx_msg void OnCbnSelchangeSelectCombo6();
	afx_msg void OnCbnSelchangeSelectCombo7();
	afx_msg void OnCbnSelchangeSelectCombo8();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSelectionFile1();
	afx_msg void OnBnClickedButtonSelectionFile2();
	afx_msg void OnBnClickedButtonSelectionFile3();
	afx_msg void OnBnClickedButtonSelectionFile4();
	afx_msg void OnBnClickedButtonSelectionFile5();
	afx_msg void OnBnClickedButtonSelectionFile6();
	afx_msg void OnBnClickedButtonSelectionFile7();
	afx_msg void OnBnClickedButtonSelectionFile8();
};
