#pragma once
#include "afxwin.h"

#include "SAutomationDlg.h"

// CDlgCompact �_�C�A���O

class CDlgCompact : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCompact)

public:
	CDlgCompact(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CDlgCompact();

	CSAutomationDlg* pParent; 

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_COMPACT };
BOOL ChangeIcon(int iIcon);

protected:
	HICON m_hIconStandby;
	HICON m_hIconRunning;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
