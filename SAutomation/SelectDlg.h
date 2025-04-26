#pragma once
#include "Common.h"

// CSelectDlg ダイアログ

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CString m_sResultFileName;
	DWORD m_dwHotKeys[MAX_SELECTION];
	CString m_sSelectKeys[MAX_SELECTION];
	CString m_sSelectFiles[MAX_SELECTION];
	CSelectDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSelectDlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
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
};
