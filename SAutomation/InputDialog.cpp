// InputDialog2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "InputDialog.h"
#include "afxdialogex.h"
#include "Automation.h"

// CInputDialog ダイアログ

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputDialog::IDD, pParent)
	, m_sReturnValue(_T(""))
{
	m_sLabel = NULL;
	m_byKey=NULL;
	m_iKeyNum=0;
}

CInputDialog::~CInputDialog()
{
	if(m_byKey != NULL){SAFE_DELETE(m_byKey);}
	if(m_sLabel != NULL){SAFE_DELETE(m_sLabel);}
	m_iKeyNum = 0;
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_EDIT1, m_sReturnValue);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
END_MESSAGE_MAP()


// CInputDialog メッセージ ハンドラーbr


BOOL CInputDialog::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYUP)
	{
		if(m_bInputMulti==FALSE)
		{
		for(int i=0; i<m_iKeyNum; i++)
		{
			if(pMsg->wParam == m_byKey[i])
			{
				m_sResultLabel.Format(_T("%s"), m_sLabel[i]);
			}
		}
		OnOK();
		}

	}

	if(pMsg->wParam==VK_RETURN)
	{
		UpdateData(TRUE);
		OnOK();
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
BOOL CInputDialog::PerseParameter()
{

	m_iKeyNum = (m_saParam.GetCount()-2)/2;
	m_byKey = new BYTE[m_iKeyNum];
	m_sLabel = new CString[m_iKeyNum];
	m_sMessage.Format(_T("%s"), m_saParam.GetAt(0));
	m_iTimeOutMilliSec = _wtoi(m_saParam.GetAt(1));
	for(int i=0; i<m_iKeyNum; i++)
	{
		wchar_t tch;
		BOOL bUnicode;
		m_sLabel[i].Format(_T("%s"), m_saParam.GetAt(2+i*2));
		GetKeyCode(m_saParam.GetAt(2+i*2+1),&bUnicode, &tch, &(m_byKey[i]));
	}
	return TRUE;
}






BOOL CInputDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(m_bInputMulti==TRUE)
	{
		m_sReturnValue.Format(_T(""));
		UpdateData(FALSE);
		SetWindowText(_T("Input"));
		((CButton*)GetDlgItem(IDC_INPUT_EDIT1))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_INPUT_EDIT1))->SetFocus();
		((CButton*)GetDlgItem(IDC_INPUT_STATIC_INSTRUCTION))->SetWindowText(m_saParam.GetAt(0));
		((CButton*)GetDlgItem(IDC_INPUT_STATIC_MESSAGE))->SetWindowText(_T(""));
		return TRUE;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_INPUT_EDIT1))->ShowWindow(SW_HIDE);
	}
	BOOL bRet;
	bRet = PerseParameter();
	if(bRet != TRUE){m_sLabel[0].Format(_T("")); return FALSE;}
	m_sResultLabel.Format(_T("%s"), m_sLabel[0]);
	SetWindowText(_T("SwitchByInput"));

	((CButton*)GetDlgItem(IDC_INPUT_STATIC_MESSAGE))->SetWindowText(m_sMessage);
	CString sInstruction;
	sInstruction=_T("");
	for(int i=0; i<m_iKeyNum-1; i++)
	{
		CString sTemp;
		sTemp.Format(_T("%c: %s\n"), m_byKey[i], m_sLabel[i]);
		sInstruction.Append(sTemp);
	}
	CString sTemp;
	sTemp.Format(_T("%c: %s\n"), m_byKey[m_iKeyNum-1], m_sLabel[m_iKeyNum-1]);
	sInstruction.Append(sTemp);

	((CButton*)GetDlgItem(IDC_INPUT_STATIC_MESSAGE))->SetWindowText(m_sMessage);
	CRect rect;
	CRect rectParent;
	GetWindowRect(&rectParent);

	((CButton*)GetDlgItem(IDC_INPUT_STATIC_INSTRUCTION))->GetWindowRect(&rect);
	CRect rect2;
	rect2.SetRect(rect.left, rect.top, rect.left+rect.Width(), rect.top+13*m_iKeyNum);
	((CButton*)GetDlgItem(IDC_INPUT_STATIC_INSTRUCTION))->MoveWindow(rect2);

	rect2.SetRect(rectParent.left, rectParent.top, rectParent.left+rectParent.Width(), rectParent.top+130+13*m_iKeyNum);
	MoveWindow(rect2);
	((CButton*)GetDlgItem(IDC_INPUT_STATIC_INSTRUCTION))->SetWindowText(sInstruction);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
