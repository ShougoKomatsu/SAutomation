#pragma once


// CSelectDlg �_�C�A���O

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CString m_sResultFileName;
	CString m_sSelectKeys[8];
	CString m_sSelectFiless[8];
	CSelectDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CSelectDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};
