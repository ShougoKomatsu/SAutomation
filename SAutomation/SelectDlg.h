#pragma once
#include "Common.h"

// CSelectDlg �_�C�A���O

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CString m_sResultFileName;
	DWORD m_dwHotKeys[MAX_SELECTION];
	CString m_sSelectKeys[MAX_SELECTION];
	CString m_sSelectFiles[MAX_SELECTION];
	CSelectDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CSelectDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
