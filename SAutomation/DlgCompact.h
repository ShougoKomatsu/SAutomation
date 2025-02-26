#pragma once
#include "afxwin.h"

#include "SAutomationDlg.h"

// CDlgCompact ダイアログ


class CDlgCompact : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCompact)

	BOOL m_bMoving;
	BOOL m_iX;
	BOOL m_iY;

	void WinodowMove(int ixFrom, int iyFrom, int ixTo, int iyTo);


public:
	BOOL m_bRunning;
	CBrush m_brRed;
	CBrush m_brGreen;
	CBrush m_brBlack;
	CDlgCompact(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDlgCompact();

	CSAutomationDlg* pParent; 

// ダイアログ データ
	enum { IDD = IDD_DIALOG_COMPACT };
BOOL ChangeIcon(int iIcon);

protected:
	HICON m_hIconStandby;
	HICON m_hIconRunning;
	HICON m_hIconMinimize;
	HICON m_hIconClose;
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
	CButton m_ButtonMinimize;
	afx_msg void OnBnClickedCompactButtonClose();
	CButton m_ButtonClose;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
