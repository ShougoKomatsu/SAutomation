#pragma once
#include "afxwin.h"

#include "SAutomationDlg.h"

// CDlgCompact ダイアログ

class CDlgCompact : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCompact)

public:
	CDlgCompact(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDlgCompact();

	CSAutomationDlg* pParent; 

// ダイアログ データ
	enum { IDD = IDD_DIALOG_COMPACT };
BOOL ChangeIcon(int iIcon);

protected:
	HICON m_hIconStandby;
	HICON m_hIconRunning;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnDispStandby(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonCompactExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sEditCompactMouseR;
	CString m_sEditCompactMouseC;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCompactButtonMinimize();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
