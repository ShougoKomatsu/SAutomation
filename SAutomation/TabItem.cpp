// TabItem.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "TabItem.h"
#include "afxdialogex.h"
#include "Common.h"


// CTabItem ダイアログ

IMPLEMENT_DYNAMIC(CTabItem, CDialogEx)

CTabItem::CTabItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabItem::IDD, pParent)
{
	m_bReset=FALSE;
}

CTabItem::~CTabItem()
{
}

void CTabItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_TAB_EDIT_FILE_00, (m_sEditFileName[0]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_01, (m_sEditFileName[1]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_02, (m_sEditFileName[2]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_03, (m_sEditFileName[3]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_04, (m_sEditFileName[4]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_05, (m_sEditFileName[5]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_06, (m_sEditFileName[6]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_07, (m_sEditFileName[7]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_08, (m_sEditFileName[8]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_09, (m_sEditFileName[9]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_10, (m_sEditFileName[10]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_11, (m_sEditFileName[11]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_12, (m_sEditFileName[12]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_13, (m_sEditFileName[13]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_14, (m_sEditFileName[14]));
	DDX_Text(pDX, IDC_TAB_EDIT_FILE_15, (m_sEditFileName[15]));
	
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_00, (m_combo[0]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_01, (m_combo[1]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_02, (m_combo[2]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_03, (m_combo[3]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_04, (m_combo[4]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_05, (m_combo[5]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_06, (m_combo[6]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_07, (m_combo[7]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_08, (m_combo[8]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_09, (m_combo[9]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_10, (m_combo[10]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_11, (m_combo[11]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_12, (m_combo[12]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_13, (m_combo[13]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_14, (m_combo[14]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_KEY_15, (m_combo[15]));

	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_00, (m_comboUseCtrl[0]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_01, (m_comboUseCtrl[1]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_02, (m_comboUseCtrl[2]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_03, (m_comboUseCtrl[3]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_04, (m_comboUseCtrl[4]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_05, (m_comboUseCtrl[5]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_06, (m_comboUseCtrl[6]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_07, (m_comboUseCtrl[7]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_08, (m_comboUseCtrl[8]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_09, (m_comboUseCtrl[9]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_10, (m_comboUseCtrl[10]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_11, (m_comboUseCtrl[11]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_12, (m_comboUseCtrl[12]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_13, (m_comboUseCtrl[13]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_14, (m_comboUseCtrl[14]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_CTRL_15, (m_comboUseCtrl[15]));

	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_00, (m_comboUseShift[0]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_01, (m_comboUseShift[1]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_02, (m_comboUseShift[2]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_03, (m_comboUseShift[3]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_04, (m_comboUseShift[4]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_05, (m_comboUseShift[5]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_06, (m_comboUseShift[6]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_07, (m_comboUseShift[7]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_08, (m_comboUseShift[8]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_09, (m_comboUseShift[9]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_10, (m_comboUseShift[10]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_11, (m_comboUseShift[11]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_12, (m_comboUseShift[12]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_13, (m_comboUseShift[13]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_14, (m_comboUseShift[14]));
	DDX_Control(pDX, IDC_TAB_COMBO_HOTKEY_SHIFT_15, (m_comboUseShift[15]));

	if(m_bReset==FALSE)
	{
		for(int iScene=0; iScene<16; iScene++)
		{
			m_combo[iScene].ResetContent();
			m_comboUseCtrl[iScene].ResetContent();
			m_comboUseShift[iScene].ResetContent();
		}
		m_bReset=TRUE;
	}
}


BEGIN_MESSAGE_MAP(CTabItem, CDialogEx)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_00, &CTabItem::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_01, &CTabItem::OnBnClickedButton01)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_02, &CTabItem::OnBnClickedButton02)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_03, &CTabItem::OnBnClickedButton03)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_04, &CTabItem::OnBnClickedButton04)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_05, &CTabItem::OnBnClickedButton05)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_06, &CTabItem::OnBnClickedButton06)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_07, &CTabItem::OnBnClickedButton07)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_08, &CTabItem::OnBnClickedButton08)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_09, &CTabItem::OnBnClickedButton09)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_10, &CTabItem::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_11, &CTabItem::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_12, &CTabItem::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_13, &CTabItem::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_14, &CTabItem::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_TAB_BUTTON_SELECT_FILE_15, &CTabItem::OnBnClickedButton15)
	
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_00, &CTabItem::OnSelchangeCombo00)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_01, &CTabItem::OnSelchangeCombo01)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_02, &CTabItem::OnSelchangeCombo02)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_03, &CTabItem::OnSelchangeCombo03)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_04, &CTabItem::OnSelchangeCombo04)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_05, &CTabItem::OnSelchangeCombo05)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_06, &CTabItem::OnSelchangeCombo06)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_07, &CTabItem::OnSelchangeCombo07)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_08, &CTabItem::OnSelchangeCombo08)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_09, &CTabItem::OnSelchangeCombo09)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_10, &CTabItem::OnSelchangeCombo10)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_11, &CTabItem::OnSelchangeCombo11)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_12, &CTabItem::OnSelchangeCombo12)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_13, &CTabItem::OnSelchangeCombo13)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_14, &CTabItem::OnSelchangeCombo14)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_KEY_15, &CTabItem::OnSelchangeCombo15)

	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_00, &CTabItem::OnSelchangeComboCtrl00)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_01, &CTabItem::OnSelchangeComboCtrl01)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_02, &CTabItem::OnSelchangeComboCtrl02)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_03, &CTabItem::OnSelchangeComboCtrl03)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_04, &CTabItem::OnSelchangeComboCtrl04)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_05, &CTabItem::OnSelchangeComboCtrl05)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_06, &CTabItem::OnSelchangeComboCtrl06)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_07, &CTabItem::OnSelchangeComboCtrl07)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_08, &CTabItem::OnSelchangeComboCtrl08)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_09, &CTabItem::OnSelchangeComboCtrl09)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_10, &CTabItem::OnSelchangeComboCtrl10)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_11, &CTabItem::OnSelchangeComboCtrl11)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_12, &CTabItem::OnSelchangeComboCtrl12)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_13, &CTabItem::OnSelchangeComboCtrl13)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_14, &CTabItem::OnSelchangeComboCtrl14)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_CTRL_15, &CTabItem::OnSelchangeComboCtrl15)

	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_00, &CTabItem::OnSelchangeComboShift00)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_01, &CTabItem::OnSelchangeComboShift01)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_02, &CTabItem::OnSelchangeComboShift02)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_03, &CTabItem::OnSelchangeComboShift03)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_04, &CTabItem::OnSelchangeComboShift04)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_05, &CTabItem::OnSelchangeComboShift05)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_06, &CTabItem::OnSelchangeComboShift06)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_07, &CTabItem::OnSelchangeComboShift07)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_08, &CTabItem::OnSelchangeComboShift08)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_09, &CTabItem::OnSelchangeComboShift09)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_10, &CTabItem::OnSelchangeComboShift10)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_11, &CTabItem::OnSelchangeComboShift11)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_12, &CTabItem::OnSelchangeComboShift12)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_13, &CTabItem::OnSelchangeComboShift13)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_14, &CTabItem::OnSelchangeComboShift14)
	ON_CBN_SELCHANGE(IDC_TAB_COMBO_HOTKEY_SHIFT_15, &CTabItem::OnSelchangeComboShift15)
	
	/*
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_00, &CTabItem::OnBnClickedButtonOperate00)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_01, &CTabItem::OnBnClickedButtonOperate01)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_02, &CTabItem::OnBnClickedButtonOperate02)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_03, &CTabItem::OnBnClickedButtonOperate03)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_04, &CTabItem::OnBnClickedButtonOperate04)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_05, &CTabItem::OnBnClickedButtonOperate05)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_06, &CTabItem::OnBnClickedButtonOperate06)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_07, &CTabItem::OnBnClickedButtonOperate07)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_08, &CTabItem::OnBnClickedButtonOperate08)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_09, &CTabItem::OnBnClickedButtonOperate09)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_10, &CTabItem::OnBnClickedButtonOperate10)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_11, &CTabItem::OnBnClickedButtonOperate11)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_12, &CTabItem::OnBnClickedButtonOperate12)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_13, &CTabItem::OnBnClickedButtonOperate13)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_14, &CTabItem::OnBnClickedButtonOperate14)
	ON_BN_CLICKED(IDC_TAB_BUTTON_OPERATE_15, &CTabItem::OnBnClickedButtonOperate15)
	*/
END_MESSAGE_MAP()

// CTabItem メッセージ ハンドラー

/*

void CTabItem::OnBnClickedButtonOperate00(){pParent->pParent->Operate(m_iSlot*16 + 0);}
void CTabItem::OnBnClickedButtonOperate01(){pParent->pParent->Operate(m_iSlot*16 + 1);}
void CTabItem::OnBnClickedButtonOperate02(){pParent->pParent->Operate(m_iSlot*16 + 2);}
void CTabItem::OnBnClickedButtonOperate03(){pParent->pParent->Operate(m_iSlot*16 + 3);}
void CTabItem::OnBnClickedButtonOperate04(){pParent->pParent->Operate(m_iSlot*16 + 4);}
void CTabItem::OnBnClickedButtonOperate05(){pParent->pParent->Operate(m_iSlot*16 + 5);}
void CTabItem::OnBnClickedButtonOperate06(){pParent->pParent->Operate(m_iSlot*16 + 6);}
void CTabItem::OnBnClickedButtonOperate07(){pParent->pParent->Operate(m_iSlot*16 + 7);}
void CTabItem::OnBnClickedButtonOperate08(){pParent->pParent->Operate(m_iSlot*16 + 8);}
void CTabItem::OnBnClickedButtonOperate09(){pParent->pParent->Operate(m_iSlot*16 + 9);}
void CTabItem::OnBnClickedButtonOperate10(){pParent->pParent->Operate(m_iSlot*16 + 10);}
void CTabItem::OnBnClickedButtonOperate11(){pParent->pParent->Operate(m_iSlot*16 + 11);}
void CTabItem::OnBnClickedButtonOperate12(){pParent->pParent->Operate(m_iSlot*16 + 12);}
void CTabItem::OnBnClickedButtonOperate13(){pParent->pParent->Operate(m_iSlot*16 + 13);}
void CTabItem::OnBnClickedButtonOperate14(){pParent->pParent->Operate(m_iSlot*16 + 14);}
void CTabItem::OnBnClickedButtonOperate15(){pParent->pParent->Operate(m_iSlot*16 + 15);}

*/

void CTabItem::OnBnClickedButton00(){FileSelect(m_iSlot, 0); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton01(){FileSelect(m_iSlot, 1); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton02(){FileSelect(m_iSlot, 2); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton03(){FileSelect(m_iSlot, 3); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton04(){FileSelect(m_iSlot, 4); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton05(){FileSelect(m_iSlot, 5); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton06(){FileSelect(m_iSlot, 6); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton07(){FileSelect(m_iSlot, 7); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton08(){FileSelect(m_iSlot, 8); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton09(){FileSelect(m_iSlot, 9); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton10(){FileSelect(m_iSlot, 10); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton11(){FileSelect(m_iSlot, 11); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton12(){FileSelect(m_iSlot, 12); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton13(){FileSelect(m_iSlot, 13); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton14(){FileSelect(m_iSlot, 14); RefleshDialog(m_iSlot);}
void CTabItem::OnBnClickedButton15(){FileSelect(m_iSlot, 15); RefleshDialog(m_iSlot);}

void CTabItem::OnSelchangeCombo00(){UpdateHotkey(m_iSlot, 0);}
void CTabItem::OnSelchangeCombo01(){UpdateHotkey(m_iSlot, 1);}
void CTabItem::OnSelchangeCombo02(){UpdateHotkey(m_iSlot, 2);}
void CTabItem::OnSelchangeCombo03(){UpdateHotkey(m_iSlot, 3);}
void CTabItem::OnSelchangeCombo04(){UpdateHotkey(m_iSlot, 4);}
void CTabItem::OnSelchangeCombo05(){UpdateHotkey(m_iSlot, 5);}
void CTabItem::OnSelchangeCombo06(){UpdateHotkey(m_iSlot, 6);}
void CTabItem::OnSelchangeCombo07(){UpdateHotkey(m_iSlot, 7);}
void CTabItem::OnSelchangeCombo08(){UpdateHotkey(m_iSlot, 8);}
void CTabItem::OnSelchangeCombo09(){UpdateHotkey(m_iSlot, 9);}
void CTabItem::OnSelchangeCombo10(){UpdateHotkey(m_iSlot, 10);}
void CTabItem::OnSelchangeCombo11(){UpdateHotkey(m_iSlot, 11);}
void CTabItem::OnSelchangeCombo12(){UpdateHotkey(m_iSlot, 12);}
void CTabItem::OnSelchangeCombo13(){UpdateHotkey(m_iSlot, 13);}
void CTabItem::OnSelchangeCombo14(){UpdateHotkey(m_iSlot, 14);}
void CTabItem::OnSelchangeCombo15(){UpdateHotkey(m_iSlot, 15);}

void CTabItem::OnSelchangeComboCtrl00(){UpdateHotkey(m_iSlot, 0);}
void CTabItem::OnSelchangeComboCtrl01(){UpdateHotkey(m_iSlot, 1);}
void CTabItem::OnSelchangeComboCtrl02(){UpdateHotkey(m_iSlot, 2);}
void CTabItem::OnSelchangeComboCtrl03(){UpdateHotkey(m_iSlot, 3);}
void CTabItem::OnSelchangeComboCtrl04(){UpdateHotkey(m_iSlot, 4);}
void CTabItem::OnSelchangeComboCtrl05(){UpdateHotkey(m_iSlot, 5);}
void CTabItem::OnSelchangeComboCtrl06(){UpdateHotkey(m_iSlot, 6);}
void CTabItem::OnSelchangeComboCtrl07(){UpdateHotkey(m_iSlot, 7);}
void CTabItem::OnSelchangeComboCtrl08(){UpdateHotkey(m_iSlot, 8);}
void CTabItem::OnSelchangeComboCtrl09(){UpdateHotkey(m_iSlot, 9);}
void CTabItem::OnSelchangeComboCtrl10(){UpdateHotkey(m_iSlot, 10);}
void CTabItem::OnSelchangeComboCtrl11(){UpdateHotkey(m_iSlot, 11);}
void CTabItem::OnSelchangeComboCtrl12(){UpdateHotkey(m_iSlot, 12);}
void CTabItem::OnSelchangeComboCtrl13(){UpdateHotkey(m_iSlot, 13);}
void CTabItem::OnSelchangeComboCtrl14(){UpdateHotkey(m_iSlot, 14);}
void CTabItem::OnSelchangeComboCtrl15(){UpdateHotkey(m_iSlot, 15);}

void CTabItem::OnSelchangeComboShift00(){UpdateHotkey(m_iSlot, 0);}
void CTabItem::OnSelchangeComboShift01(){UpdateHotkey(m_iSlot, 1);}
void CTabItem::OnSelchangeComboShift02(){UpdateHotkey(m_iSlot, 2);}
void CTabItem::OnSelchangeComboShift03(){UpdateHotkey(m_iSlot, 3);}
void CTabItem::OnSelchangeComboShift04(){UpdateHotkey(m_iSlot, 4);}
void CTabItem::OnSelchangeComboShift05(){UpdateHotkey(m_iSlot, 5);}
void CTabItem::OnSelchangeComboShift06(){UpdateHotkey(m_iSlot, 6);}
void CTabItem::OnSelchangeComboShift07(){UpdateHotkey(m_iSlot, 7);}
void CTabItem::OnSelchangeComboShift08(){UpdateHotkey(m_iSlot, 8);}
void CTabItem::OnSelchangeComboShift09(){UpdateHotkey(m_iSlot, 9);}
void CTabItem::OnSelchangeComboShift10(){UpdateHotkey(m_iSlot, 10);}
void CTabItem::OnSelchangeComboShift11(){UpdateHotkey(m_iSlot, 11);}
void CTabItem::OnSelchangeComboShift12(){UpdateHotkey(m_iSlot, 12);}
void CTabItem::OnSelchangeComboShift13(){UpdateHotkey(m_iSlot, 13);}
void CTabItem::OnSelchangeComboShift14(){UpdateHotkey(m_iSlot, 14);}
void CTabItem::OnSelchangeComboShift15(){UpdateHotkey(m_iSlot, 15);}

BOOL CTabItem::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN){return TRUE;}
		if(pMsg->wParam == VK_ESCAPE){return TRUE;}
		if(pMsg->wParam == VK_SPACE){return TRUE;}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTabItem::RefleshDialog(int iSlot)
{
	if(iSlot<4)
	{
		for(int iScene=0; iScene<16; iScene++)
		{
			((CButton*)GetDlgItem(IDC_TAB_EDIT_FILE_00+iScene))->ShowWindow(SW_SHOW);
		}

		for(int iScene=0; iScene<16; iScene++)
		{
			m_sEditFileName[iScene].Format(_T("%s"),m_autoInfo->m_OpeInfo[iSlot*16 + iScene].sFileName);

			SetComboItem(&m_combo[iScene],m_autoInfo->m_OpeInfo[iSlot*16 + iScene].sHotkey);
			SetComboItemShift(&m_comboUseCtrl[iScene], &(m_autoInfo->m_OpeInfo[iSlot*16 + iScene]));
			SetComboItemCtrl(&m_comboUseShift[iScene], &(m_autoInfo->m_OpeInfo[iSlot*16 + iScene]));

			CString sScene;
			sScene.Format(_T("%d"),iSlot*16 + iScene);
			((CButton*)GetDlgItem(IDC_TAB_STATIC_EX0+iScene))->SetWindowText(sScene);
		}
	}
	else
	{
		for(int iScene=0; iScene<16; iScene++)
		{
			((CButton*)GetDlgItem(IDC_TAB_EDIT_FILE_00+iScene))->ShowWindow(SW_HIDE);
		}

		for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++)
		{
			m_sEditFileName[iExScene].Format(_T("%s"),m_autoInfo->m_OpeInfo[iSlot*16 + iExScene].sFileName);

			SetComboItem(&m_combo[iExScene],m_autoInfo->m_OpeInfo[iSlot*16 + iExScene].sHotkey);
			SetComboItemShift(&m_comboUseCtrl[iExScene], &(m_autoInfo->m_OpeInfo[iSlot*16 + iExScene]));
			SetComboItemCtrl(&m_comboUseShift[iExScene], &(m_autoInfo->m_OpeInfo[iSlot*16 + iExScene]));

			CString sScene;
			sScene.Format(_T("Ex%d"),iExScene);
			((CButton*)GetDlgItem(IDC_TAB_STATIC_EX0+iExScene))->SetWindowText(sScene);
		}
	}


	UpdateData(FALSE);
}
void CTabItem::FileSelect(int iSlot, int iScene)
{
	if(iSlot<4)
	{
		CString sMacroFolderPath;
		sMacroFolderPath.Format(_T("%s\\Macro"),m_autoInfo->m_sDir);

		CFileDialog cf(TRUE);
		cf.m_ofn.lpstrInitialDir = sMacroFolderPath;
		if(cf.DoModal()!=IDOK){ return;}
		m_autoInfo->m_OpeInfo[iSlot*16 + iScene].sFileName.Format(_T("%s"), cf.GetFileName());
	}
	else
	{

		m_cDlgSelect.m_iModeOperate=0;
		for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
		{
			m_cDlgSelect.m_sSelectKeys[iSelect].Format(_T("%s"), m_autoInfo->m_sSelectKeys[iScene][iSelect]);
			m_cDlgSelect.m_sSelectFiles[iSelect].Format(_T("%s"), m_autoInfo->m_sSelectFiles[iScene][iSelect]);
		}
		int iRet = m_cDlgSelect.DoModal();
		if(iRet == IDOK)
		{
			for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
			{
				m_autoInfo->m_sSelectFiles[iScene][iSelect].Format(_T("%s"),m_cDlgSelect.m_sSelectFiles[iSelect]);
				m_autoInfo->m_sSelectKeys[iScene][iSelect].Format(_T("%s"),m_cDlgSelect.m_sSelectKeys[iSelect]);
			}
		}
	}
	*pbNotModified = m_autoInfo->IsSameAs(&g_Automation);
	SetTitleNotChanged( *pbNotModified);
}

void CTabItem::UpdateHotkey(int iSlot, int iScene)
{
	UpdateData(TRUE);

	TCHAR tch[8];
	if(m_combo[iScene].GetCurSel()<0)
	{
		*pbNotModified = m_autoInfo->IsSameAs(&g_Automation);
		SetTitleNotChanged(*pbNotModified);
		UpdateData(FALSE);
		return;
	}
	m_combo[iScene].GetLBText(m_combo[iScene].GetCurSel(),tch);

	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].sHotkey.Format(_T("%s"),tch);
	if(wcscmp(tch,_T(" "))==0)
	{
		*pbNotModified = m_autoInfo->IsSameAs(&g_Automation);
		SetTitleNotChanged(*pbNotModified);
		UpdateData(FALSE);return;
	}

	DWORD dwHotKey;
	if(_tcslen(tch)>=2)
	{
		if(_tcsicmp(tch,_T("F1"))==0){dwHotKey = VK_F1;}
		if(_tcsicmp(tch,_T("F2"))==0){dwHotKey = VK_F2;}
		if(_tcsicmp(tch,_T("F3"))==0){dwHotKey = VK_F3;}
		if(_tcsicmp(tch,_T("F4"))==0){dwHotKey = VK_F4;}
		if(_tcsicmp(tch,_T("F5"))==0){dwHotKey = VK_F5;}
		if(_tcsicmp(tch,_T("F6"))==0){dwHotKey = VK_F6;}
		if(_tcsicmp(tch,_T("F7"))==0){dwHotKey = VK_F7;}
		if(_tcsicmp(tch,_T("F8"))==0){dwHotKey = VK_F8;}
		if(_tcsicmp(tch,_T("F9"))==0){dwHotKey = VK_F9;}
		if(_tcsicmp(tch,_T("F10"))==0){dwHotKey = VK_F10;}
		if(_tcsicmp(tch,_T("F11"))==0){dwHotKey = VK_F11;}
		if(_tcsicmp(tch,_T("F12"))==0){dwHotKey = VK_F12;}
		if(_tcsicmp(tch,_T("Insert"))==0){dwHotKey = VK_INSERT;}


	}
	else
	{
		if((tch[0]>='a') && (tch[0]<='z')){dwHotKey = char(tch[0])-'a'+0x41;}
		if((tch[0]>='0') && (tch[0]<='9')){dwHotKey = char(tch[0])-'0'+0x30;}
	}
	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].dwHotKey = dwHotKey;

	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].sHotkey.Format(_T("%s"),tch);

	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseShift=FALSE;
	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseCtrl=FALSE;
	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseAlt=FALSE;
	m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseWin=FALSE;

	if(m_comboUseCtrl[iScene].GetCurSel()<0){}
	else
	{
		m_comboUseCtrl[iScene].GetLBText(m_comboUseCtrl[iScene].GetCurSel(),tch);
		if(wcscmp(tch,_T("Ctrl"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseCtrl=TRUE;}
		if(wcscmp(tch,_T("Shift"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseShift=TRUE;}
		if(wcscmp(tch,_T("Alt"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseAlt=TRUE;}
		if(wcscmp(tch,_T("Win"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseWin=TRUE;}
	}

	if(m_comboUseShift[iScene].GetCurSel()<0){}
	else
	{
		m_comboUseShift[iScene].GetLBText(m_comboUseShift[iScene].GetCurSel(),tch);
		if(wcscmp(tch,_T("Ctrl"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseCtrl=TRUE;}
		if(wcscmp(tch,_T("Shift"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseShift=TRUE;}
		if(wcscmp(tch,_T("Alt"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseAlt=TRUE;}
		if(wcscmp(tch,_T("Win"))==0){m_autoInfo->m_OpeInfo[iSlot*16 + iScene].bUseWin=TRUE;}
	}
	
	*pbNotModified = m_autoInfo->IsSameAs(&g_Automation);
	SetTitleNotChanged(*pbNotModified);
	UpdateData(FALSE);

}
void CTabItem::SetTitleNotChanged(BOOL bTF)
{
	if(bTF==FALSE)
	{
		pParentWnd->SetWindowText(_T("SAutomation *"));
	}
	else
	{
		pParentWnd->SetWindowText(_T("SAutomation"));
	}
}