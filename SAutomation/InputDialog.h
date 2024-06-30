#pragma once
#include "stdafx.h"
#include "resource.h"
// CInputDialog2 �_�C�A���O

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
		CStringArray m_saParam;
	
	CString m_sMessage;
	int m_iTimeOutMilliSec;
	BYTE* m_byKey;
	int m_iKeyNum;
	CString* m_sLabel;
	CString m_sResultLabel;

	BOOL PerseParameter();
	CInputDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CInputDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};

