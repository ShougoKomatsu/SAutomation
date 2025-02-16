// TabItem.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "TabItem.h"
#include "afxdialogex.h"


// CTabItem ダイアログ

IMPLEMENT_DYNAMIC(CTabItem, CDialogEx)

CTabItem::CTabItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabItem::IDD, pParent)
{

}

CTabItem::~CTabItem()
{
}

void CTabItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_FILE_00, (m_sEditFileName[0]));
	DDX_Text(pDX, IDC_EDIT_FILE_01, (m_sEditFileName[1]));
	DDX_Text(pDX, IDC_EDIT_FILE_02, (m_sEditFileName[2]));
	DDX_Text(pDX, IDC_EDIT_FILE_03, (m_sEditFileName[3]));
	DDX_Text(pDX, IDC_EDIT_FILE_04, (m_sEditFileName[4]));
	DDX_Text(pDX, IDC_EDIT_FILE_05, (m_sEditFileName[5]));
	DDX_Text(pDX, IDC_EDIT_FILE_06, (m_sEditFileName[6]));
	DDX_Text(pDX, IDC_EDIT_FILE_07, (m_sEditFileName[7]));
	DDX_Text(pDX, IDC_EDIT_FILE_08, (m_sEditFileName[8]));
	DDX_Text(pDX, IDC_EDIT_FILE_09, (m_sEditFileName[9]));
	DDX_Text(pDX, IDC_EDIT_FILE_10, (m_sEditFileName[10]));
	DDX_Text(pDX, IDC_EDIT_FILE_11, (m_sEditFileName[11]));
	DDX_Text(pDX, IDC_EDIT_FILE_12, (m_sEditFileName[12]));
	DDX_Text(pDX, IDC_EDIT_FILE_13, (m_sEditFileName[13]));
	DDX_Text(pDX, IDC_EDIT_FILE_14, (m_sEditFileName[14]));
	DDX_Text(pDX, IDC_EDIT_FILE_15, (m_sEditFileName[15]));

	DDX_Text(pDX, IDC_EDIT_STATUS_00, (m_sEditStatus[0]));
	DDX_Text(pDX, IDC_EDIT_STATUS_01, (m_sEditStatus[1]));
	DDX_Text(pDX, IDC_EDIT_STATUS_02, (m_sEditStatus[2]));
	DDX_Text(pDX, IDC_EDIT_STATUS_03, (m_sEditStatus[3]));
	DDX_Text(pDX, IDC_EDIT_STATUS_04, (m_sEditStatus[4]));
	DDX_Text(pDX, IDC_EDIT_STATUS_05, (m_sEditStatus[5]));
	DDX_Text(pDX, IDC_EDIT_STATUS_06, (m_sEditStatus[6]));
	DDX_Text(pDX, IDC_EDIT_STATUS_07, (m_sEditStatus[7]));
	DDX_Text(pDX, IDC_EDIT_STATUS_08, (m_sEditStatus[8]));
	DDX_Text(pDX, IDC_EDIT_STATUS_09, (m_sEditStatus[9]));
	DDX_Text(pDX, IDC_EDIT_STATUS_10, (m_sEditStatus[10]));
	DDX_Text(pDX, IDC_EDIT_STATUS_11, (m_sEditStatus[11]));
	DDX_Text(pDX, IDC_EDIT_STATUS_12, (m_sEditStatus[12]));
	DDX_Text(pDX, IDC_EDIT_STATUS_13, (m_sEditStatus[13]));
	DDX_Text(pDX, IDC_EDIT_STATUS_14, (m_sEditStatus[14]));
	DDX_Text(pDX, IDC_EDIT_STATUS_15, (m_sEditStatus[15]));

	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_00, (m_combo[0]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_01, (m_combo[1]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_02, (m_combo[2]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_03, (m_combo[3]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_04, (m_combo[4]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_05, (m_combo[5]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_06, (m_combo[6]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_07, (m_combo[7]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_08, (m_combo[8]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_09, (m_combo[9]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_10, (m_combo[10]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_11, (m_combo[11]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_12, (m_combo[12]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_13, (m_combo[13]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_14, (m_combo[14]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_KEY_15, (m_combo[15]));

	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_00, (m_comboUseCtrl[0]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_01, (m_comboUseCtrl[1]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_02, (m_comboUseCtrl[2]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_03, (m_comboUseCtrl[3]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_04, (m_comboUseCtrl[4]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_05, (m_comboUseCtrl[5]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_06, (m_comboUseCtrl[6]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_07, (m_comboUseCtrl[7]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_08, (m_comboUseCtrl[8]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_09, (m_comboUseCtrl[9]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_10, (m_comboUseCtrl[10]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_11, (m_comboUseCtrl[11]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_12, (m_comboUseCtrl[12]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_13, (m_comboUseCtrl[13]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_14, (m_comboUseCtrl[14]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_CTRL_15, (m_comboUseCtrl[15]));

	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_00, (m_comboUseShift[0]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_01, (m_comboUseShift[1]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_02, (m_comboUseShift[2]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_03, (m_comboUseShift[3]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_04, (m_comboUseShift[4]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_05, (m_comboUseShift[5]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_06, (m_comboUseShift[6]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_07, (m_comboUseShift[7]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_08, (m_comboUseShift[8]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_09, (m_comboUseShift[9]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_10, (m_comboUseShift[10]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_11, (m_comboUseShift[11]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_12, (m_comboUseShift[12]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_13, (m_comboUseShift[13]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_14, (m_comboUseShift[14]));
	DDX_Control(pDX, IDC_COMBO_HOTKEY_SHIFT_15, (m_comboUseShift[15]));
}


BEGIN_MESSAGE_MAP(CTabItem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_00, &CTabItem::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_01, &CTabItem::OnBnClickedButton01)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_02, &CTabItem::OnBnClickedButton02)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_03, &CTabItem::OnBnClickedButton03)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_04, &CTabItem::OnBnClickedButton04)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_05, &CTabItem::OnBnClickedButton05)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_06, &CTabItem::OnBnClickedButton06)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_07, &CTabItem::OnBnClickedButton07)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_08, &CTabItem::OnBnClickedButton08)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_09, &CTabItem::OnBnClickedButton09)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_10, &CTabItem::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_11, &CTabItem::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_12, &CTabItem::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_13, &CTabItem::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_14, &CTabItem::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_15, &CTabItem::OnBnClickedButton15)

	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_00, &CTabItem::OnSelchangeCombo00)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_01, &CTabItem::OnSelchangeCombo01)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_02, &CTabItem::OnSelchangeCombo02)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_03, &CTabItem::OnSelchangeCombo03)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_04, &CTabItem::OnSelchangeCombo04)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_05, &CTabItem::OnSelchangeCombo05)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_06, &CTabItem::OnSelchangeCombo06)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_07, &CTabItem::OnSelchangeCombo07)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_08, &CTabItem::OnSelchangeCombo08)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_09, &CTabItem::OnSelchangeCombo09)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_10, &CTabItem::OnSelchangeCombo10)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_11, &CTabItem::OnSelchangeCombo11)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_12, &CTabItem::OnSelchangeCombo12)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_13, &CTabItem::OnSelchangeCombo13)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_14, &CTabItem::OnSelchangeCombo14)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_KEY_15, &CTabItem::OnSelchangeCombo15)

	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_00, &CTabItem::OnSelchangeComboCtrl00)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_01, &CTabItem::OnSelchangeComboCtrl01)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_02, &CTabItem::OnSelchangeComboCtrl02)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_03, &CTabItem::OnSelchangeComboCtrl03)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_04, &CTabItem::OnSelchangeComboCtrl04)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_05, &CTabItem::OnSelchangeComboCtrl05)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_06, &CTabItem::OnSelchangeComboCtrl06)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_07, &CTabItem::OnSelchangeComboCtrl07)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_08, &CTabItem::OnSelchangeComboCtrl08)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_09, &CTabItem::OnSelchangeComboCtrl09)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_10, &CTabItem::OnSelchangeComboCtrl10)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_11, &CTabItem::OnSelchangeComboCtrl11)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_12, &CTabItem::OnSelchangeComboCtrl12)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_13, &CTabItem::OnSelchangeComboCtrl13)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_14, &CTabItem::OnSelchangeComboCtrl14)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_CTRL_15, &CTabItem::OnSelchangeComboCtrl15)

	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_00, &CTabItem::OnSelchangeComboShift00)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_01, &CTabItem::OnSelchangeComboShift01)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_02, &CTabItem::OnSelchangeComboShift02)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_03, &CTabItem::OnSelchangeComboShift03)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_04, &CTabItem::OnSelchangeComboShift04)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_05, &CTabItem::OnSelchangeComboShift05)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_06, &CTabItem::OnSelchangeComboShift06)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_07, &CTabItem::OnSelchangeComboShift07)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_08, &CTabItem::OnSelchangeComboShift08)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_09, &CTabItem::OnSelchangeComboShift09)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_10, &CTabItem::OnSelchangeComboShift10)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_11, &CTabItem::OnSelchangeComboShift11)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_12, &CTabItem::OnSelchangeComboShift12)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_13, &CTabItem::OnSelchangeComboShift13)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_14, &CTabItem::OnSelchangeComboShift14)
	ON_CBN_SELCHANGE(IDC_COMBO_HOTKEY_SHIFT_15, &CTabItem::OnSelchangeComboShift15)

	ON_BN_CLICKED(IDC_BUTTON_OPERATE_00, &CTabItem::OnBnClickedButtonOperate00)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_01, &CTabItem::OnBnClickedButtonOperate01)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_02, &CTabItem::OnBnClickedButtonOperate02)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_03, &CTabItem::OnBnClickedButtonOperate03)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_04, &CTabItem::OnBnClickedButtonOperate04)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_05, &CTabItem::OnBnClickedButtonOperate05)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_06, &CTabItem::OnBnClickedButtonOperate06)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_07, &CTabItem::OnBnClickedButtonOperate07)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_08, &CTabItem::OnBnClickedButtonOperate08)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_09, &CTabItem::OnBnClickedButtonOperate09)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_10, &CTabItem::OnBnClickedButtonOperate10)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_11, &CTabItem::OnBnClickedButtonOperate11)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_12, &CTabItem::OnBnClickedButtonOperate12)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_13, &CTabItem::OnBnClickedButtonOperate13)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_14, &CTabItem::OnBnClickedButtonOperate14)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_15, &CTabItem::OnBnClickedButtonOperate15)
END_MESSAGE_MAP()


// CTabItem メッセージ ハンドラー

void CTabItem::OnBnClickedButton00(){FileSelect(0); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton01(){FileSelect(1); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton02(){FileSelect(2); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton03(){FileSelect(3); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton04(){FileSelect(4); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton05(){FileSelect(5); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton06(){FileSelect(6); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton07(){FileSelect(7); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton08(){FileSelect(8); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton09(){FileSelect(9); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton10(){FileSelect(10); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton11(){FileSelect(11); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton12(){FileSelect(12); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton13(){FileSelect(13); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton14(){FileSelect(14); RefleshDialog(); pParent->SaveSettings();}
void CTabItem::OnBnClickedButton15(){FileSelect(15); RefleshDialog(); pParent->SaveSettings();}

void CTabItem::OnSelchangeCombo00(){UpdateHotkey(0); pParent->ResetHotkey(0);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo01(){UpdateHotkey(1); pParent->ResetHotkey(1);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo02(){UpdateHotkey(2); pParent->ResetHotkey(2);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo03(){UpdateHotkey(3); pParent->ResetHotkey(3);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo04(){UpdateHotkey(4); pParent->ResetHotkey(4);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo05(){UpdateHotkey(5); pParent->ResetHotkey(5);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo06(){UpdateHotkey(6); pParent->ResetHotkey(6);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo07(){UpdateHotkey(7); pParent->ResetHotkey(7);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo08(){UpdateHotkey(8); pParent->ResetHotkey(8);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo09(){UpdateHotkey(9); pParent->ResetHotkey(9);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo10(){UpdateHotkey(10); pParent->ResetHotkey(10);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo11(){UpdateHotkey(11); pParent->ResetHotkey(11);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo12(){UpdateHotkey(12); pParent->ResetHotkey(12);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo13(){UpdateHotkey(13); pParent->ResetHotkey(13);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo14(){UpdateHotkey(14); pParent->ResetHotkey(14);pParent->SaveSettings();}
void CTabItem::OnSelchangeCombo15(){UpdateHotkey(15); pParent->ResetHotkey(15);pParent->SaveSettings();}

void CTabItem::OnSelchangeComboCtrl00(){UpdateHotkey(0); pParent->ResetHotkey(0);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl01(){UpdateHotkey(1); pParent->ResetHotkey(1);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl02(){UpdateHotkey(2); pParent->ResetHotkey(2);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl03(){UpdateHotkey(3); pParent->ResetHotkey(3);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl04(){UpdateHotkey(4); pParent->ResetHotkey(4);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl05(){UpdateHotkey(5); pParent->ResetHotkey(5);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl06(){UpdateHotkey(6); pParent->ResetHotkey(6);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl07(){UpdateHotkey(7); pParent->ResetHotkey(7);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl08(){UpdateHotkey(8); pParent->ResetHotkey(8);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl09(){UpdateHotkey(9); pParent->ResetHotkey(9);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl10(){UpdateHotkey(10); pParent->ResetHotkey(10);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl11(){UpdateHotkey(11); pParent->ResetHotkey(11);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl12(){UpdateHotkey(12); pParent->ResetHotkey(12);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl13(){UpdateHotkey(13); pParent->ResetHotkey(13);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl14(){UpdateHotkey(14); pParent->ResetHotkey(14);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboCtrl15(){UpdateHotkey(15); pParent->ResetHotkey(15);pParent->SaveSettings();}

void CTabItem::OnSelchangeComboShift00(){UpdateHotkey(0); pParent->ResetHotkey(0);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift01(){UpdateHotkey(1); pParent->ResetHotkey(1);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift02(){UpdateHotkey(2); pParent->ResetHotkey(2);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift03(){UpdateHotkey(3); pParent->ResetHotkey(3);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift04(){UpdateHotkey(4); pParent->ResetHotkey(4);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift05(){UpdateHotkey(5); pParent->ResetHotkey(5);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift06(){UpdateHotkey(6); pParent->ResetHotkey(6);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift07(){UpdateHotkey(7); pParent->ResetHotkey(7);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift08(){UpdateHotkey(8); pParent->ResetHotkey(8);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift09(){UpdateHotkey(9); pParent->ResetHotkey(9);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift10(){UpdateHotkey(10); pParent->ResetHotkey(10);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift11(){UpdateHotkey(11); pParent->ResetHotkey(11);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift12(){UpdateHotkey(12); pParent->ResetHotkey(12);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift13(){UpdateHotkey(13); pParent->ResetHotkey(13);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift14(){UpdateHotkey(14); pParent->ResetHotkey(14);pParent->SaveSettings();}
void CTabItem::OnSelchangeComboShift15(){UpdateHotkey(15); pParent->ResetHotkey(15);pParent->SaveSettings();}

void CTabItem::OnBnClickedButtonOperate00(){pParent->Operate(m_iSlot*16 + 0);}
void CTabItem::OnBnClickedButtonOperate01(){pParent->Operate(m_iSlot*16 + 1);}
void CTabItem::OnBnClickedButtonOperate02(){pParent->Operate(m_iSlot*16 + 2);}
void CTabItem::OnBnClickedButtonOperate03(){pParent->Operate(m_iSlot*16 + 3);}
void CTabItem::OnBnClickedButtonOperate04(){pParent->Operate(m_iSlot*16 + 4);}
void CTabItem::OnBnClickedButtonOperate05(){pParent->Operate(m_iSlot*16 + 5);}
void CTabItem::OnBnClickedButtonOperate06(){pParent->Operate(m_iSlot*16 + 6);}
void CTabItem::OnBnClickedButtonOperate07(){pParent->Operate(m_iSlot*16 + 7);}
void CTabItem::OnBnClickedButtonOperate08(){pParent->Operate(m_iSlot*16 + 8);}
void CTabItem::OnBnClickedButtonOperate09(){pParent->Operate(m_iSlot*16 + 9);}
void CTabItem::OnBnClickedButtonOperate10(){pParent->Operate(m_iSlot*16 + 10);}
void CTabItem::OnBnClickedButtonOperate11(){pParent->Operate(m_iSlot*16 + 11);}
void CTabItem::OnBnClickedButtonOperate12(){pParent->Operate(m_iSlot*16 + 12);}
void CTabItem::OnBnClickedButtonOperate13(){pParent->Operate(m_iSlot*16 + 13);}
void CTabItem::OnBnClickedButtonOperate14(){pParent->Operate(m_iSlot*16 + 14);}
void CTabItem::OnBnClickedButtonOperate15(){pParent->Operate(m_iSlot*16 + 15);}


void CTabItem::RefleshDialog()
{
	for(int iScene=0; iScene<16; iScene++)
	{
		m_sEditFileName[iScene].Format(_T("%s"),pParent->m_OpeInfo[m_iSlot*16 + iScene].sFileName);

		SetComboItem(&m_combo[iScene],pParent->m_OpeInfo[m_iSlot*16 + iScene].sHotkey);
		SetComboItemShift(&m_comboUseCtrl[iScene], &(pParent->m_OpeInfo[m_iSlot*16 + iScene]));
		SetComboItemCtrl(&m_comboUseShift[iScene], &(pParent->m_OpeInfo[m_iSlot*16 + iScene]));

		CString sScene;
		sScene.Format(_T("%d"),m_iSlot*16 + iScene);
		((CButton*)GetDlgItem(IDC_STATIC_EX0+iScene))->SetWindowText(sScene);
	}

	UpdateData(FALSE);
}
void CTabItem::FileSelect(int iScene)
{
	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),pParent->m_sDir);

	CFileDialog cf(TRUE);
	cf.m_ofn.lpstrInitialDir = sMacroFolderPath;
	if(cf.DoModal()!=IDOK){ return;}
	pParent->m_OpeInfo[m_iSlot*16 + iScene].sFileName.Format(_T("%s"), cf.GetFileName());
}

void CTabItem::UpdateHotkey(int iScene)
{
	UpdateData(TRUE);

	TCHAR tch[8];
	if(m_combo[iScene].GetCurSel()<0){return;}
	m_combo[iScene].GetLBText(m_combo[iScene].GetCurSel(),tch);
	if(wcscmp(tch,_T(" "))==0){return;}
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
		pParent->m_OpeInfo[m_iSlot*16 + iScene].dwHotKey = dwHotKey;

	pParent->m_OpeInfo[m_iSlot*16 + iScene].sHotkey.Format(_T("%s"),tch);

	pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseShift=FALSE;
	pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseCtrl=FALSE;
	pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseAlt=FALSE;
	pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseWin=FALSE;

	if(m_comboUseCtrl[iScene].GetCurSel()<0){}
	else
	{
		m_comboUseCtrl[iScene].GetLBText(m_comboUseCtrl[iScene].GetCurSel(),tch);
		if(wcscmp(tch,_T("Ctrl"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseCtrl=TRUE;}
		if(wcscmp(tch,_T("Shift"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseShift=TRUE;}
		if(wcscmp(tch,_T("Alt"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseAlt=TRUE;}
		if(wcscmp(tch,_T("Win"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseWin=TRUE;}
	}

	if(m_comboUseShift[iScene].GetCurSel()<0){}
	else
	{
		m_comboUseShift[iScene].GetLBText(m_comboUseShift[iScene].GetCurSel(),tch);
		if(wcscmp(tch,_T("Ctrl"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseCtrl=TRUE;}
		if(wcscmp(tch,_T("Shift"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseShift=TRUE;}
		if(wcscmp(tch,_T("Alt"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseAlt=TRUE;}
		if(wcscmp(tch,_T("Win"))==0){pParent->m_OpeInfo[m_iSlot*16 + iScene].bUseWin=TRUE;}
	}
	UpdateData(FALSE);

}


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
