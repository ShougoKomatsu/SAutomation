// SelectDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "SelectDlg.h"
#include "afxdialogex.h"


// CSelectDlg ダイアログ

IMPLEMENT_DYNAMIC(CSelectDlg, CDialogEx)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelectDlg::IDD, pParent)
{

}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
END_MESSAGE_MAP()


// CSelectDlg メッセージ ハンドラー


BOOL CSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	for(int iSelection=0;iSelection<MAX_SELECTION; iSelection++)
	{

		if(m_sSelectKeys[iSelection].GetLength()>0)
		{

			if(m_sSelectFiles[iSelection].GetLength()>0)
			{
				((CButton*)GetDlgItem(IDC_STATIC_SELECT_KEY_1+iSelection))->SetWindowText(m_sSelectKeys[iSelection]);
				((CButton*)GetDlgItem(IDC_STATIC_SELECT_FILENAME_1+iSelection))->SetWindowText(m_sSelectFiles[iSelection]);
				CString sTemp;
				sTemp.Format(_T("%c"),m_sSelectKeys[iSelection].GetAt(0));
				sTemp.MakeLower();
				m_dwHotKeys[iSelection] = char(sTemp.GetAt(0))-'a'+0x41;
			}
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


BOOL CSelectDlg::PreTranslateMessage(MSG* pMsg)
{

	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		{
			for(int iSelection=0; iSelection<MAX_SELECTION; iSelection++)
			{
				if(pMsg->wParam==m_dwHotKeys[iSelection] )
				{
					m_sResultFileName.Format(_T("%s"), m_sSelectFiles[iSelection]);
					CDialog::OnOK();
				}
			}
					m_sResultFileName.Format(_T(""));
			CDialog::OnCancel();
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
