#include "stdafx.h"
#include "Automation.h"
#include "windows.h"
#include "Common.h"

#include "Window.h"

CString g_sDir;
int K_Sleep(LPVOID Halt, LPVOID Suspend, DWORD SleepMilliSec)
{
	if((Halt==NULL)&&(Suspend == NULL)){Sleep(SleepMilliSec);return 0;}



	if(Halt==NULL)
	{
		ULONGLONG ullStartMilliSec;
		ULONGLONG ullSuspendStartMilliSec;
		ULONGLONG ullSuspendedMilliSec;
		ullStartMilliSec = GetTickCount64();
		ullSuspendedMilliSec=0;
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult+ullSuspendedMilliSec)
		{
			if((*(int*)Suspend) == 1)
			{
				ullSuspendStartMilliSec = GetTickCount64();
				while((*(int*)Suspend) == 1)
				{
					Sleep(1);
				}
				ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;
			}
			Sleep(1);
		}
		return 0;
	}

	if(Suspend==NULL)
	{
		ULONGLONG ullStartMilliSec;
		ullStartMilliSec = GetTickCount64();
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult)
		{
			if((*(int*)Halt) == 1){return -1;}
			Sleep(1);
		}
		return 0;
	}

	ULONGLONG ullStartMilliSec;
	ULONGLONG ullSuspendStartMilliSec;
	ULONGLONG ullSuspendedMilliSec;
	ullStartMilliSec = GetTickCount64();
	ullSuspendedMilliSec=0;
	while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult+ullSuspendedMilliSec)
	{
		if((*(int*)Halt) == 1){return -1;}
		if((*(int*)Suspend) == 1)
		{
			ullSuspendStartMilliSec = GetTickCount64();
			while((*(int*)Suspend) == 1)
			{
				if((*(int*)Halt) == 1){return -1;}
				Sleep(1);
			}
			ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;
		}
		Sleep(1);
	}


	return 0;
}


int KeyDownAndUp(BYTE bySendKey)
{
	INPUT inputs[2] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;

	inputs[1].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=bySendKey;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2,inputs,sizeof(INPUT)); 
	return 0;
}

int KeyDownAndUpUnicode(TCHAR tch)
{
	INPUT input[2];
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = tch;
	input[0].ki.dwFlags = KEYEVENTF_UNICODE;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 0;
	input[1].ki.wScan = tch;
	input[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	input[1].ki.time = 0;
	input[1].ki.dwExtraInfo = 0;

	SendInput(2, input, sizeof(INPUT));
	return 0;
}

int KeyDownUnicode(TCHAR tch)
{
	INPUT input[1];
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = tch;
	input[0].ki.dwFlags = KEYEVENTF_UNICODE;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	SendInput(1, input, sizeof(INPUT));
	return 0;
}

int KeyUpUnicode(TCHAR tch)
{
	INPUT input[1];

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = tch;
	input[0].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	SendInput(1, input, sizeof(INPUT));
	return 0;
}

int KeyDown(BYTE bySendKey)
{
	INPUT inputs[1] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;

	SendInput(1,inputs,sizeof(INPUT)); 
	return 0;
}

int KeyUp(BYTE bySendKey)
{
	INPUT inputs[1] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;
	inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1,inputs,sizeof(INPUT)); 
	return 0;
}


int GetKeyCode(CString sData, BOOL* bUnicode, TCHAR* tch, BYTE* byData)
{
	BYTE byDataLocal;
	byDataLocal = 0;
	*bUnicode = FALSE;
	*tch = 0;
	if(sData.CompareNoCase(_T("ctrl"))==0)
	{
		*byData= VK_CONTROL;
		return 0;
	}
	if(sData.CompareNoCase(_T("shift"))==0){*byData= VK_SHIFT;return 0;}
	if(sData.CompareNoCase(_T("alt"))==0){*byData= VK_MENU;return 0;}

	if(sData.CompareNoCase(_T("©"))==0){*byData= VK_LEFT;return 0;}
	if(sData.CompareNoCase(_T("ª"))==0){*byData= VK_UP;return 0;}
	if(sData.CompareNoCase(_T("¨"))==0){*byData= VK_RIGHT;return 0;}
	if(sData.CompareNoCase(_T("«"))==0){*byData= VK_DOWN;return 0;}


	if(sData.GetLength()==2)
	{
		if(sData.CompareNoCase(_T("f1"))==0){*byData = VK_F1;return 0;}
		if(sData.CompareNoCase(_T("f2"))==0){*byData = VK_F2;return 0;}
		if(sData.CompareNoCase(_T("f3"))==0){*byData = VK_F3;return 0;}
		if(sData.CompareNoCase(_T("f4"))==0){*byData = VK_F4;return 0;}
		if(sData.CompareNoCase(_T("f5"))==0){*byData = VK_F5;return 0;}
		if(sData.CompareNoCase(_T("f6"))==0){*byData = VK_F6;return 0;}
		if(sData.CompareNoCase(_T("f7"))==0){*byData = VK_F7;return 0;}
		if(sData.CompareNoCase(_T("f8"))==0){*byData = VK_F8;return 0;}
		if(sData.CompareNoCase(_T("f9"))==0){*byData = VK_F9;return 0;}
	}

	if(sData.GetLength()==3)
	{
		if(sData.CompareNoCase(_T("f10"))==0){*byData = VK_F10;return 0;}
		if(sData.CompareNoCase(_T("f11"))==0){*byData = VK_F11;return 0;}
		if(sData.CompareNoCase(_T("f12"))==0){*byData = VK_F12;return 0;}
		if(sData.CompareNoCase(_T("f13"))==0){*byData = VK_F13;return 0;}
		if(sData.CompareNoCase(_T("f14"))==0){*byData = VK_F14;return 0;}
		if(sData.CompareNoCase(_T("f15"))==0){*byData = VK_F15;return 0;}
		if(sData.CompareNoCase(_T("f16"))==0){*byData = VK_F16;return 0;}
		if(sData.CompareNoCase(_T("f17"))==0){*byData = VK_F17;return 0;}
		if(sData.CompareNoCase(_T("f18"))==0){*byData = VK_F18;return 0;}
		if(sData.CompareNoCase(_T("f19"))==0){*byData = VK_F19;return 0;}

		if(sData.CompareNoCase(_T("f20"))==0){*byData = VK_F20;return 0;}
		if(sData.CompareNoCase(_T("f21"))==0){*byData = VK_F21;return 0;}
		if(sData.CompareNoCase(_T("f22"))==0){*byData = VK_F22;return 0;}
		if(sData.CompareNoCase(_T("f23"))==0){*byData = VK_F23;return 0;}
		if(sData.CompareNoCase(_T("f24"))==0){*byData = VK_F24;return 0;}
	}

	if(sData.CompareNoCase(_T("lshift"))==0){*byData = VK_SHIFT;return 0;}
	if(sData.CompareNoCase(_T("rshift"))==0){*byData = VK_SHIFT;return 0;}
	if(sData.CompareNoCase(_T("lctrl"))==0){*byData = VK_CONTROL;return 0;}
	if(sData.CompareNoCase(_T("rctrl"))==0){*byData = VK_CONTROL;return 0;}
	if(sData.CompareNoCase(_T("lalt"))==0){*byData = VK_MENU;return 0;}
	if(sData.CompareNoCase(_T("ralt"))==0){*byData = VK_MENU;return 0;}

	if(sData.CompareNoCase(_T("tab"))==0){*byData = VK_TAB;return 0;}
	if(sData.CompareNoCase(_T("enter"))==0){*byData = VK_RETURN;return 0;}
	if(sData.CompareNoCase(_T("return"))==0){*byData = VK_RETURN;return 0;}
	if(sData.CompareNoCase(_T("space"))==0){*byData = VK_SPACE;return 0;}

	
	if(sData.GetLength()==1)
	{
		char cChar;
		cChar = sData.GetAt(0);
		if(('0'<=cChar)&&(cChar <= '9'))
		{
			*byData = sData.GetAt(0);
			*bUnicode = FALSE;
			return 0;
		}
		if(('A' <= cChar) &&(cChar <= 'Z'))
		{
			*byData = sData.GetAt(0);
			*bUnicode = FALSE;
			return 0;
		}
		if(('a' <= cChar) &&(cChar <= 'z'))
		{
			*byData = sData.GetAt(0)-'a'+'A';
			*bUnicode = FALSE;
			return 0;
		}
	}


	*bUnicode = TRUE;
	*byData = 0x00;
	*tch=sData.GetAt(0);
	return 0;
}

#include "ImgProc.h"

int WaitForImage(LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	int iWaitOn;

	int iTimeOut;
	int iContinue;

	if(saData->GetCount()<=6){return -1;}

	CString sModelFilePath;
	int iR0, iC0, iR1, iC1;

	sModelFilePath.Format(_T("%s"), saData->GetAt(0));

	iC0=_ttoi(saData->GetAt(1));
	iR0=_ttoi(saData->GetAt(2));
	iC1=_ttoi(saData->GetAt(3));
	iR1=_ttoi(saData->GetAt(4));

	if(saData->GetAt(5).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(5).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return -1;}


	iContinue = 0;
	if(saData->GetCount()==6){iTimeOut=-1;}
	else {iTimeOut = _ttoi(saData->GetAt(6));}


	if(saData->GetCount()>=8)
	{
		if(saData->GetAt(7).CompareNoCase(_T("continue"))==0){iContinue=1;}
	}



	ImgRGB imgModel;
	ImgRGB imgTarget;
	BOOL bRet;
	imgModel.Assign(sModelFilePath);

	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();

	int iFoundR, iFoundC;
	while(1)
	{
		Screenshot(&imgTarget);

		bRet = IsInRegion(&imgTarget, &imgModel, iR0, iC0, iR1, iC1, &iFoundR, &iFoundC);
		if(iWaitOn==1)
		{
			if(bRet == TRUE) {return 0;}
		}
		else
		{
			if(bRet == FALSE) {return 0;}
		}


		if(K_Sleep(Halt, Suspend, 1)<0){return -1;}
		if(iTimeOut>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+iTimeOut){if(iContinue==0){return -1;}else{return 0;}}
		}
	}

	return 0;
}

int WaitForKey(LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{

	int iWaitOn;

	BYTE byKey;
	BOOL bUnicode;
	TCHAR tch;
	int iRet;
	iRet = GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &byKey);
	if(iRet < 0){return iRet;}

	if(saData->GetAt(1).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(1).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return -1;}


	if(bUnicode == TRUE)
	{
		if(('0'<=tch) && (tch<='9')){byKey = tch;}
		if(('a'<=tch) && (tch<='z')){byKey = tch;}
		if(('A'<=tch) && (tch<='Z')){byKey = tch-'A'+'a';}
	}

	short shKey;
	while(1)
	{
		shKey = GetAsyncKeyState (byKey);
		if(iWaitOn==1)
		{
			if((shKey<0)) {return 0;}

		}
		else
		{
			if((shKey>=0)) {return 0;}
		}


		if(K_Sleep(Halt, Suspend, 1)<0){return -1;}
	}
	return 0;
}

int KeyDownAndUp(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	TCHAR tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyDownAndUpUnicode(tch);}

	return KeyDownAndUp(bySendKey);
}


int KeyDown(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	TCHAR tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyDownUnicode(tch);}

	return KeyDown(bySendKey);
}



int KeyUp(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	TCHAR tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyUpUnicode(tch);}

	return KeyUp(bySendKey);
}
int FilndLabel(CStringArray* saCommands, CString sLabel)
{
	CString sCommand;
	for(int i=0; i<saCommands->GetCount(); i++)
	{
		sCommand.Format(_T("%s"), saCommands->GetAt(i));
		sCommand.Trim(_T(" ")).Trim(_T("\t"));

		if(sCommand.GetLength()!=sLabel.GetLength()+1){continue;}
		if(sCommand.GetAt(sLabel.GetLength())!=':'){continue;}

		if(sCommand.Left(sLabel.GetLength()).CompareNoCase(sLabel)==0){return i;}
	}
	return -1;
}

int OperateCommand(int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine)
{
	int iCommandType=COMMAND_UNDEFINED;
	BOOL bRet;
	CStringArray saData;
	bRet = PerseCommand(iSceneData, sDataLine, &iCommandType, &saData, g_sDir);
	if(iCommandType == COMMAND_NOTING){return 0;}
	if(bRet != TRUE){return -1;}

	switch(iCommandType)
	{
	case COMMAND_DELAY:{return K_Sleep(Halt, Suspend, _ttoi(saData.GetAt(0)));}

	case COMMAND_MOUSE_L_DOWN:{MoveMouse(&saData);return MouseLDown(&saData);}
	case COMMAND_MOUSE_R_DOWN:{MoveMouse(&saData);return MouseRDown(&saData);}

	case COMMAND_MOUSE_L_UP:{MoveMouse(&saData);return MouseLUp(&saData);}
	case COMMAND_MOUSE_R_UP:{MoveMouse(&saData);return MouseRUp(&saData);}

	case COMMAND_MOUSE_L_CLICK:{return MouseLClick(&saData);}
	case COMMAND_MOUSE_R_CLICK:{return MouseRClick(&saData);}

	case COMMAND_MOUSE_MOVE:{return MoveMouse(&saData);}
	case COMMAND_MOUSE_MOVE_INCL:{return MoveMouseIncl(&saData);}
	case COMMAND_MOUSE_MOVE_TO_IMG:{return MoveMouseToImage(&saData);}

	case COMMAND_WHEEL:{return MouseVWheel(&saData);}


	case COMMAND_KEY_DOWN_UP:{return KeyDownAndUp(&saData);}
	case COMMAND_KEY_DOWN:{return KeyDown(&saData);}
	case COMMAND_KEY_UP:{return KeyUp(&saData);}

	case COMMAND_WAIT:{return WaitForKey(Halt, Suspend, &saData);}
	case COMMAND_WAIT_IMG:{return WaitForImage(Halt, Suspend, &saData);}
	case COMMAND_MAXIMIZE:{return Maximize();}
	case COMMAND_MINIMIZE:{return Minimize();}
	case COMMAND_WINDOW_FORWARD:{return SetWindowForward(saData.GetAt(0));}
	case COMMAND_WINDOW_SIZE:{return WindowSize(&saData);}
	case COMMAND_WINDOW_POS:{return WindowPos(&saData);}
	case COMMAND_RUN:{return RunExe(saData.GetAt(0));}
	case COMMAND_NOTING:{return 0;}
	default:{return -1;}
	}
	return -1;
}