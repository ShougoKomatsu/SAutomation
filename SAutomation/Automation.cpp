#include "stdafx.h"
#include "Automation.h"
#include "windows.h"
#include "Common.h"
#include "Variables.h"
#include "Window.h"

#include "ImgProc.h"
#include "Variables.h"
#include "InputDialog.h"




ReturnValue K_SleepWithoutHalt(LPVOID Suspend, DWORD SleepMilliSec)
{
	ULONGLONG ullStartMilliSec;
	ULONGLONG ullSuspendStartMilliSec;
	ULONGLONG ullSuspendedMilliSec;
	ullStartMilliSec = GetTickCount64();
	ullSuspendedMilliSec=0;
	while(GetTickCount64() < ullStartMilliSec+SleepMilliSec/g_dSpeedMult+ullSuspendedMilliSec)
	{
		if((*(int*)Suspend) == 0){Sleep(1);	continue;}
		ullSuspendStartMilliSec = GetTickCount64();

		while((*(int*)Suspend) == 1){Sleep(1);}

		ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;
		Sleep(1);
	}
	return RETURN_NORMAL;
}

ReturnValue K_SleepWithoutSuspend(LPVOID Halt, DWORD SleepMilliSec)
{
		ULONGLONG ullStartMilliSec;
		ullStartMilliSec = GetTickCount64();
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult)
		{
			if((*(int*)Halt) == 1){return RETURN_HALT;}
			Sleep(1);
		}
		return RETURN_NORMAL;
}

ReturnValue K_Sleep(LPVOID Halt, LPVOID Suspend, DWORD SleepMilliSec)
{
	if((Halt == NULL)&&(Suspend == NULL))	{Sleep(SleepMilliSec);return RETURN_NORMAL;}
	if(Halt == NULL)						{return K_SleepWithoutHalt(Suspend, SleepMilliSec);}
	if(Suspend == NULL)						{return K_SleepWithoutSuspend(Halt, SleepMilliSec);}

	ULONGLONG ullStartMilliSec;
	ULONGLONG ullSuspendStartMilliSec;
	ULONGLONG ullSuspendedMilliSec;
	ullStartMilliSec = GetTickCount64();
	ullSuspendedMilliSec=0;
	while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult+ullSuspendedMilliSec)
	{
		if((*(int*)Halt) == 1){return RETURN_HALT;}
		if((*(int*)Suspend) == 0){Sleep(1); continue;}

		ullSuspendStartMilliSec = GetTickCount64();
		while((*(int*)Suspend) == 1)
		{
			if((*(int*)Halt) == 1){return RETURN_HALT;}
			Sleep(1);
		}
		ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;

		Sleep(1);
	}


	return RETURN_NORMAL;
}


ReturnValue KeyDownAndUp(BYTE bySendKey)
{
	INPUT inputs[2] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;

	inputs[1].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=bySendKey;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2,inputs,sizeof(INPUT)); 
	return RETURN_NORMAL;
}

ReturnValue KeyDownAndUpUnicode(TCHAR tch)
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
	return RETURN_NORMAL;
}

ReturnValue KeyDownUnicode(TCHAR tch)
{
	INPUT input[1];
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = tch;
	input[0].ki.dwFlags = KEYEVENTF_UNICODE;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	SendInput(1, input, sizeof(INPUT));
	return RETURN_NORMAL;
}

ReturnValue KeyUpUnicode(TCHAR tch)
{
	INPUT input[1];

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = tch;
	input[0].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	SendInput(1, input, sizeof(INPUT));
	return RETURN_NORMAL;
}

ReturnValue KeyDown(BYTE bySendKey)
{
	INPUT inputs[1] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;

	SendInput(1,inputs,sizeof(INPUT)); 
	return RETURN_NORMAL;
}

ReturnValue KeyUp(BYTE bySendKey)
{
	INPUT inputs[1] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;
	inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1,inputs,sizeof(INPUT)); 
	return RETURN_NORMAL;
}

ReturnValue GetInput(CStringArray* saData, CString* sReturnParam)
{
	g_cInput.m_saParam.Copy(*saData);
	g_cInput.m_bInputMulti=TRUE;
	g_cInput.DoModal();
	sReturnParam->Format(_T("%s"), g_cInput.m_sResultLabel);
	return RETURN_GOTO_BY_SWITCH;
}

ReturnValue GetKeyCode(CString sData, BOOL* bUnicode, TCHAR* tch, BYTE* byData)
{
	BYTE byDataLocal;
	byDataLocal = 0;
	*bUnicode = FALSE;
	*tch = 0;
	if(sData.CompareNoCase(_T("ctrl"))==0)
	{
		*byData= VK_CONTROL;
		return RETURN_NORMAL;
	}
	if(sData.CompareNoCase(_T("shift"))==0){*byData= VK_SHIFT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("alt"))==0){*byData= VK_MENU;return RETURN_NORMAL;}

	if(sData.CompareNoCase(_T("Å©"))==0){*byData= VK_LEFT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("<-"))==0){*byData= VK_LEFT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("left"))==0){*byData= VK_LEFT;return RETURN_NORMAL;}

	if(sData.CompareNoCase(_T("Å™"))==0){*byData= VK_UP;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("up"))==0){*byData= VK_UP;return RETURN_NORMAL;}

	if(sData.CompareNoCase(_T("Å®"))==0){*byData= VK_RIGHT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("->"))==0){*byData= VK_RIGHT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("right"))==0){*byData= VK_RIGHT;return RETURN_NORMAL;}

	if(sData.CompareNoCase(_T("Å´"))==0){*byData= VK_DOWN;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("down"))==0){*byData= VK_DOWN;return RETURN_NORMAL;}


	if(sData.GetLength()==2)
	{
		if(sData.CompareNoCase(_T("f1"))==0){*byData = VK_F1;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f2"))==0){*byData = VK_F2;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f3"))==0){*byData = VK_F3;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f4"))==0){*byData = VK_F4;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f5"))==0){*byData = VK_F5;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f6"))==0){*byData = VK_F6;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f7"))==0){*byData = VK_F7;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f8"))==0){*byData = VK_F8;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f9"))==0){*byData = VK_F9;return RETURN_NORMAL;}
	}

	if(sData.GetLength()==3)
	{
		if(sData.CompareNoCase(_T("f10"))==0){*byData = VK_F10;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f11"))==0){*byData = VK_F11;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f12"))==0){*byData = VK_F12;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f13"))==0){*byData = VK_F13;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f14"))==0){*byData = VK_F14;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f15"))==0){*byData = VK_F15;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f16"))==0){*byData = VK_F16;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f17"))==0){*byData = VK_F17;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f18"))==0){*byData = VK_F18;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f19"))==0){*byData = VK_F19;return RETURN_NORMAL;}

		if(sData.CompareNoCase(_T("f20"))==0){*byData = VK_F20;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f21"))==0){*byData = VK_F21;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f22"))==0){*byData = VK_F22;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f23"))==0){*byData = VK_F23;return RETURN_NORMAL;}
		if(sData.CompareNoCase(_T("f24"))==0){*byData = VK_F24;return RETURN_NORMAL;}
	}

	if(sData.CompareNoCase(_T("lshift"))==0){*byData = VK_SHIFT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("rshift"))==0){*byData = VK_SHIFT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("lctrl"))==0){*byData = VK_CONTROL;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("rctrl"))==0){*byData = VK_CONTROL;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("lalt"))==0){*byData = VK_MENU;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("ralt"))==0){*byData = VK_MENU;return RETURN_NORMAL;}

	if(sData.CompareNoCase(_T("tab"))==0){*byData = VK_TAB;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("enter"))==0){*byData = VK_RETURN;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("return"))==0){*byData = VK_RETURN;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("space"))==0){*byData = VK_SPACE;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("backspace"))==0){*byData = VK_BACK;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("jp"))==0){*byData = 0xf3;return RETURN_NORMAL;}

	if(sData.CompareNoCase(_T("pageup"))==0){*byData = VK_PRIOR;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("pagedown"))==0){*byData = VK_NEXT;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("home"))==0){*byData = VK_HOME;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("end"))==0){*byData = VK_END;return RETURN_NORMAL;}
	if(sData.CompareNoCase(_T("printscreen"))==0){*byData = VK_SNAPSHOT;return RETURN_NORMAL;}

	
	if(sData.GetLength()==1)
	{
		char cChar;
		cChar = sData.GetAt(0);
		if(('0'<=cChar)&&(cChar <= '9'))
		{
			*byData = sData.GetAt(0);
			*bUnicode = FALSE;
			return RETURN_NORMAL;
		}
		if(('A' <= cChar) &&(cChar <= 'Z'))
		{
			*byData = sData.GetAt(0);
			*bUnicode = FALSE;
			return RETURN_NORMAL;
		}
		if(('a' <= cChar) &&(cChar <= 'z'))
		{
			*byData = sData.GetAt(0)-'a'+'A';
			*bUnicode = FALSE;
			return RETURN_NORMAL;
		}
	}


	*bUnicode = TRUE;
	*byData = 0x00;
	*tch=sData.GetAt(0);
	return RETURN_NORMAL;
}


ReturnValue WaitForUpdate(int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	
	int iWaitOn;

	int iTimeOutMillisec;
	int iTickMillisec;
	if(saData->GetCount()<=5){return RETURN_FAILED;}

	int iR0, iC0, iR1, iC1;

	iTickMillisec = GetIntValue(iScene, saData->GetAt(0));
	iC0=GetIntValue(iScene, saData->GetAt(1));
	iR0=GetIntValue(iScene, saData->GetAt(2));
	iC1=GetIntValue(iScene, saData->GetAt(3));
	iR1=GetIntValue(iScene, saData->GetAt(4));

	CString sArg;
	sArg.Format(_T("%s"),GetStrValue(iScene, saData->GetAt(5)));
	if(sArg.CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(sArg.CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}

	iTimeOutMillisec = GetIntValue(iScene, saData->GetAt(6));
	if(iTimeOutMillisec==6){iTimeOutMillisec=-1;}


	ImgRGB imgModelCropped;
	ImgRGB imgModel;
	ImgRGB imgTarget;
	BOOL bRet;

	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();
	int iFoundR, iFoundC;
	BOOL bFirstTime;
	bFirstTime=TRUE;
	Screenshot(&imgModel);
	ReturnValue iRet;
	iRet = K_Sleep(Halt, Suspend, iTickMillisec);
	if(iRet<0){return iRet;}
	while(1)
	{
		Screenshot(&imgTarget);
		if(bFirstTime==TRUE){CropImage(&imgModel, &imgModelCropped, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC);}

		bRet = IsInRegion(&imgTarget, &imgModelCropped, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, &iFoundR, &iFoundC);
		if((iWaitOn == 1) && (bRet == FALSE)) {return RETURN_NORMAL;}
		if((iWaitOn == 0) && (bRet == TRUE)) {return RETURN_NORMAL;}

		CropImage(&imgTarget, &imgModelCropped, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC);
		iRet=K_Sleep(Halt, Suspend, iTickMillisec);
		if(iRet<0){return iRet;}
		if(iTimeOutMillisec>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+(iTimeOutMillisec/g_dSpeedMult))
			{
				return RETURN_FAILED;
			}
		}
	}

	return RETURN_NORMAL;

}

ReturnValue WaitForImage(int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	int iWaitOn;

	int iTimeOutMilliSec;

	if(saData->GetCount()<=6){return RETURN_FAILED;}

	CString sModelFilePath;
	int iR0, iC0, iR1, iC1;
	
	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(iScene, saData->GetAt(0)));
	if(sArg.GetLength()>2){if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), g_sDir,sTemp); }}
	else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), g_sDir,sTemp); }
	sModelFilePath.Format(_T("%s"), sArg);

	iC0 = GetIntValue(iScene, saData->GetAt(1));
	iR0 = GetIntValue(iScene, saData->GetAt(2));
	iC1 = GetIntValue(iScene, saData->GetAt(3));
	iR1 = GetIntValue(iScene, saData->GetAt(4));

	if(saData->GetAt(5).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(5).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}


	if(saData->GetCount()==6){iTimeOutMilliSec=-1;}
	else {iTimeOutMilliSec = GetIntValue(iScene, saData->GetAt(6));}
	
	


	ImgRGB imgModel;
	ImgRGB imgTarget;
	ImgRGB imgMask;

	BOOL bRet;
	imgModel.Assign(sModelFilePath);
	CString sMaskFilePath;
	sMaskFilePath.Format(_T("%s"), sModelFilePath);
	sMaskFilePath.Insert(sModelFilePath.GetLength()-4,_T("_mask"));
	BOOL bUseMask;
	bRet = imgMask.Assign(sMaskFilePath);
	if(bRet == TRUE){bUseMask = TRUE;}else{bUseMask = FALSE;}

	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();

	int iFoundR, iFoundC;
	while(1)
	{
		Screenshot(&imgTarget);

		if(bUseMask==TRUE)
		{
			bRet = IsInRegionMask(&imgTarget, &imgModel, &imgMask, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, &iFoundR, &iFoundC);
		}
		else
		{
			bRet = IsInRegion(&imgTarget, &imgModel, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, &iFoundR, &iFoundC);
		}
		
		if((iWaitOn == 1) && (bRet == TRUE)) {return RETURN_NORMAL;}
		if((iWaitOn == 0) && (bRet == FALSE)) {return RETURN_NORMAL;}


		ReturnValue iRet=K_Sleep(Halt, Suspend, 1);
		if(iRet<0){return iRet;}
		if(iTimeOutMilliSec>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+(iTimeOutMilliSec/g_dSpeedMult))
			{
				return RETURN_FAILED;
			}
		}
	}

	return RETURN_NORMAL;
}

ReturnValue WaitForColor(int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	int iWaitOn;

	int iTimeOutMilliSec;

	BOOL bRegion;
	if((saData->GetCount()==8) || (saData->GetCount()==9)){bRegion = TRUE;}
	else if((saData->GetCount()==6) || (saData->GetCount()==7)){bRegion = FALSE;}
	else{return RETURN_FAILED;}

	CString sModelFilePath;
	int iR0, iC0, iR1, iC1;

	CString sArg;
	CString sColor;
	sColor.Format(_T("%s"), GetStrValue(iScene, saData->GetAt(0)));
	
	if((sColor.CompareNoCase(_T("R"))!=0) && (sColor.CompareNoCase(_T("G"))!=0) && (sColor.CompareNoCase(_T("B"))!=0)){return RETURN_FAILED;}

	int iLower;
	iLower = GetIntValue(iScene, saData->GetAt(1));
	int iUpper;
	iUpper = GetIntValue(iScene, saData->GetAt(2));



	if(bRegion == TRUE)
	{
		iC0 = GetIntValue(iScene, saData->GetAt(3));
		iR0 = GetIntValue(iScene, saData->GetAt(4));
		iC1 = GetIntValue(iScene, saData->GetAt(5));
		iR1 = GetIntValue(iScene, saData->GetAt(6));

		if(saData->GetAt(7).CompareNoCase(_T("on"))==0){iWaitOn=1;}
		else if(saData->GetAt(7).CompareNoCase(_T("off"))==0){iWaitOn=0;}
		else{return RETURN_FAILED;}


		if(saData->GetCount()==8){iTimeOutMilliSec=-1;}
		else {iTimeOutMilliSec = GetIntValue(iScene, saData->GetAt(8));}
	}
	else
	{
		iC0 = GetIntValue(iScene, saData->GetAt(3));
		iR0 = GetIntValue(iScene, saData->GetAt(4));

		if(saData->GetAt(5).CompareNoCase(_T("on"))==0){iWaitOn=1;}
		else if(saData->GetAt(5).CompareNoCase(_T("off"))==0){iWaitOn=0;}
		else{return RETURN_FAILED;}


		if(saData->GetCount()==6){iTimeOutMilliSec=-1;}
		else {iTimeOutMilliSec = GetIntValue(iScene, saData->GetAt(6));}
	}

	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();
	ImgRGB imgTarget;
	BOOL bRet;
	while(1)
	{
		Screenshot(&imgTarget);

		double dValueR, dValueG, dValueB;
		BOOL bColorBeing;

		if(bRegion == TRUE)
		{
			bRet = GetValueInRegion(&imgTarget,iR0, iC0, iR1, iC1, &dValueR, &dValueG, &dValueB);
		}
		else
		{
			int iValueR, iValueG, iValueB;
			bRet = GetValue(&imgTarget,iR0, iC0, &iValueR, &iValueG, &iValueB);	
			dValueR=iValueR;
			dValueG=iValueG;
			dValueB=iValueB;
		}
		if(sColor.CompareNoCase(_T("R"))==0){if((iLower <= dValueR) && (dValueR<=iUpper)){bColorBeing = TRUE;}else{bColorBeing = FALSE;}}
		if(sColor.CompareNoCase(_T("G"))==0){if((iLower <= dValueG) && (dValueG<=iUpper)){bColorBeing = TRUE;}else{bColorBeing = FALSE;}}
		if(sColor.CompareNoCase(_T("B"))==0){if((iLower <= dValueB) && (dValueB<=iUpper)){bColorBeing = TRUE;}else{bColorBeing = FALSE;}}

		if((iWaitOn == 1) && (bColorBeing == TRUE)) {return RETURN_NORMAL;}
		if((iWaitOn == 0) && (bColorBeing == FALSE)) {return RETURN_NORMAL;}

		ReturnValue iRet=K_Sleep(Halt, Suspend, 1);
		if(iRet<0){return iRet;}
		if(iTimeOutMilliSec>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+(iTimeOutMilliSec/g_dSpeedMult))
			{
				return RETURN_FAILED;
			}
		}
	}

	return RETURN_NORMAL;
}


ReturnValue WaitForKey(int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{

	int iWaitOn;

	BYTE byKey;
	BOOL bUnicode;
	TCHAR tch;
	ReturnValue iRet;
	int iTimeOutMillisec;
	
	iRet = GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &byKey);
	if(iRet < 0){return iRet;}

	if(saData->GetAt(1).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(1).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}

	if(saData->GetCount()>=3)
	{
		iTimeOutMillisec = GetIntValue(iScene, saData->GetAt(2));
	}
	else
	{
		iTimeOutMillisec=-1;
	}

	if(bUnicode == TRUE)
	{
		if(('0'<=tch) && (tch<='9')){byKey = tch;}
		if(('a'<=tch) && (tch<='z')){byKey = tch;}
		if(('A'<=tch) && (tch<='Z')){byKey = tch-'A'+'a';}
	}

	short shKey;
	
	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();

	while(1)
	{
		shKey = GetAsyncKeyState (byKey);
		if((iWaitOn == 1) && (shKey<0)) {return RETURN_NORMAL;}
		if((iWaitOn == 0) && (shKey>=0)) {return RETURN_NORMAL;}
		
		iRet = K_Sleep(Halt, Suspend, 1);
		if(iRet <0){return iRet;}
		
		if(iTimeOutMillisec>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+(iTimeOutMillisec/g_dSpeedMult))
			{
				return RETURN_FAILED;
			}
		}
	}
	return RETURN_NORMAL;
}

ReturnValue KeyDownAndUp(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	TCHAR tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyDownAndUpUnicode(tch);}

	return KeyDownAndUp(bySendKey);
}


ReturnValue KeyDown(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	TCHAR tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyDownUnicode(tch);}

	return KeyDown(bySendKey);
}



ReturnValue KeyUp(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	TCHAR tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyUpUnicode(tch);}

	return KeyUp(bySendKey);
}
ReturnValue ScreenShot(int iScene, CStringArray* saCommands)
{
	ImgRGB imgRGB;
	Screenshot(&imgRGB);

	CString sSrc;
	sSrc.Format(_T("%s"),GetStrValue(iScene, saCommands->GetAt(0)));

	BOOL bRet=WriteImage(&imgRGB, sSrc);
	if(bRet !=TRUE){return RETURN_FAILED;}
	return RETURN_NORMAL;
}

ReturnValue ScreenShotForegroundWindow(int iScene, CStringArray* saCommands)
{
	ImgRGB imgRGB;
	ImgRGB imgRGBCropped;
	Screenshot(&imgRGB);
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	GetForegroundWindowPos(&iLeft, &iTop, &iWidth, &iHeight);
	CropImage(&imgRGB, &imgRGBCropped, iTop, iLeft, iTop+iHeight-1, iLeft+iWidth-1);
	CString sSrc;
	sSrc.Format(_T("%s"),GetStrValue(iScene, saCommands->GetAt(0)));

	BOOL bRet=WriteImage(&imgRGBCropped, sSrc);
	if(bRet !=TRUE){return RETURN_FAILED;}
	return RETURN_NORMAL;
}

ReturnValue OperateCommand(int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine, CString* sReturnParam)
{
	int iCommandType=COMMAND_UNDEFINED;
	BOOL bRet;
	CStringArray saData;
	bRet = PerseCommand(iSceneData, sDataLine, &iCommandType, &saData, g_sDir);
	if(iCommandType == COMMAND_NOTING){return RETURN_NORMAL;}
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iCommandType)
	{
	case COMMAND_DELAY:
		{
			int iSrc=GetIntValue(*iSceneData, saData.GetAt(0));
			return K_Sleep(Halt, Suspend, iSrc);
		}
	case COMMAND_MOUSE_L_DOWN:{MoveMouse(*iSceneData, &saData);return MouseLDown(*iSceneData, &saData);}
	case COMMAND_MOUSE_R_DOWN:{MoveMouse(*iSceneData, &saData);return MouseRDown(*iSceneData, &saData);}
	case COMMAND_MOUSE_M_DOWN:{MoveMouse(*iSceneData, &saData);return MouseMDown(*iSceneData, &saData);}

	case COMMAND_MOUSE_L_UP:{MoveMouse(*iSceneData, &saData);return MouseLUp(*iSceneData, &saData);}
	case COMMAND_MOUSE_R_UP:{MoveMouse(*iSceneData, &saData);return MouseRUp(*iSceneData, &saData);}
	case COMMAND_MOUSE_M_UP:{MoveMouse(*iSceneData, &saData);return MouseMUp(*iSceneData, &saData);}

	case COMMAND_MOUSE_L_CLICK:{return MouseLClick(*iSceneData, &saData);}
	case COMMAND_MOUSE_R_CLICK:{return MouseRClick(*iSceneData, &saData);}
	case COMMAND_MOUSE_M_CLICK:{return MouseMClick(*iSceneData, &saData);}
							   
	case COMMAND_MOUSE_SET_ORIGIN_TO_WINDOW:{return MouseSetOriginToWindow(*iSceneData, &saData);}
	case COMMAND_MOUSE_SET_ORIGIN_TO_IMAGE:{return MouseSetOriginToImage(*iSceneData, &saData);}


	case COMMAND_MOUSE_MOVE:{return MoveMouse(*iSceneData, &saData);}
	case COMMAND_MOUSE_MOVE_INCL:{return MoveMouseIncl(*iSceneData, &saData);}
	case COMMAND_MOUSE_MOVE_TO_IMG:{return MoveMouseToImage(*iSceneData, &saData);}
	case COMMAND_MOUSE_L_CLICK_IMG:{return MouseLClickImage(*iSceneData, &saData);}
	case COMMAND_MOUSE_MOVE_TO_ITEM:{return MoveMouseToItem(*iSceneData, &saData);}

	case COMMAND_WHEEL:{return MouseVWheel(*iSceneData, &saData);}


	case COMMAND_KEY_DOWN_UP:{return KeyDownAndUp(&saData);}
	case COMMAND_KEY_DOWN:{return KeyDown(&saData);}
	case COMMAND_KEY_UP:{return KeyUp(&saData);}

	case COMMAND_WAIT:{return WaitForKey(*iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_KEY:{return WaitForKey(*iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_EITHER_KEY:{return WaitForEitherKeyOn(*iSceneData, Halt, Suspend, &saData, sReturnParam);}
	case COMMAND_WAIT_IMG:{return WaitForImage(*iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_COLOR:{return WaitForColor(*iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_UPDATE:{return WaitForUpdate(*iSceneData, Halt, Suspend, &saData);}
	case COMMAND_MAXIMIZE:{return Maximize();}
	case COMMAND_MINIMIZE:{return Minimize();}
	case COMMAND_WINDOW_FORWARD:{return SetWindowForward(saData.GetAt(0));}
	case COMMAND_WINDOW_SIZE:{return WindowSize(*iSceneData, &saData);}
	case COMMAND_WINDOW_POS:{return WindowPos(*iSceneData, &saData);}
	case COMMAND_RUN:{return RunExe(saData.GetAt(0));}
	case COMMAND_INPUT:{return Input(saData.GetAt(0));}
	case COMMAND_NOTING:{return RETURN_NORMAL;}
	case COMMAND_EXIT:{return RETURN_END;}
	case COMMAND_LABEL:{return RETURN_LABEL;}
	case COMMAND_SUB:{return RETURN_SUB;}
	case COMMAND_CALL_SUB:
		{
			CString sData;
			sData.Format(_T("%s"),saData.GetAt(0));
			sReturnParam->Format(_T("%s"),sData.Trim(_T(" \t")));
			return RETURN_CALL_SUB;
		}
	case COMMAND_END_SUB:{return RETURN_END_SUB;}
	case COMMAND_GOTO:{return RETURN_GOTO;}
	case COMMAND_ERROR_TREAT:{return RETURN_ERROR_TREAT;}
	case COMMAND_SWITCH_BY_INPUT:
		{
			return  GetInput(&saData, sReturnParam);
		}
	case COMMAND_VARIABLE_INT:
		{
			return Flow_Assign(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_STR:
		{
			return Flow_Assign(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_IMG:
		{
			return Flow_Assign(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_OBJ:
		{
			return Flow_Assign(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_POINT:
		{
			return Flow_Assign(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_CLIPBOARD:
		{
			return Flow_Assign(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_CAMERA:
		{
			return Flow_OpenCamera(*iSceneData, &saData);
		}
	case COMMAND_VARIABLE_CAMERA_CLOSE:
		{
			return Flow_CloseCamera(*iSceneData, &saData);
		}
	case COMMAND_AREEQUAL_INT:
		{
			return Flow_AreIntEqual(*iSceneData, &saData, sReturnParam);
		}
	case COMMAND_AREEQUAL_STR:
		{
			return Flow_AreStrEqual(*iSceneData, &saData, sReturnParam);
		}
	case COMMAND_COMPARE:
		{
			return Flow_Compare(*iSceneData, &saData, sReturnParam);
		}
	case COMMAND_SCREENSHOT:
		{
			return ScreenShot(*iSceneData, &saData);
		}
	case COMMAND_SCREENSHOT_FOREGROUND_WINDOW:
		{
			return ScreenShotForegroundWindow(*iSceneData, &saData);
		}
	case COMMAND_WRITE_IMAGE:
		{
			return Flow_WriteImage(*iSceneData, &saData);
		}
	case COMMAND_MESSAGEBOX:
		{
			return MessageBox_My(*iSceneData, &saData);
		}
	case COMMAND_LIST_DLG_ITEMS:
		{
			return ListDlgItems();
		}
	default:{return RETURN_FAILED;}
	}
	return RETURN_FAILED;
}
ReturnValue Input(CString sInputWithDblQuart)
{
	int iPosL;
	int iPosR;
	for(int i=0; i<sInputWithDblQuart.GetLength(); i++)
	{
		if(sInputWithDblQuart.GetAt(i)==' '){continue;}
		if(sInputWithDblQuart.GetAt(i)=='\t'){continue;}
		if(sInputWithDblQuart.GetAt(i)=='Å@'){continue;}
		if(sInputWithDblQuart.GetAt(i)=='\"'){iPosL=i+1;break;}
		iPosL=0; break;
	}
	for(int i=sInputWithDblQuart.GetLength()-1; i>=0; i--)
	{
		if(sInputWithDblQuart.GetAt(i)==' '){continue;}
		if(sInputWithDblQuart.GetAt(i)=='\t'){continue;}
		if(sInputWithDblQuart.GetAt(i)=='Å@'){continue;}
		if(sInputWithDblQuart.GetAt(i)=='\"'){iPosR=i-1;break;}
		iPosR=sInputWithDblQuart.GetLength()-1; break;
	}
	if(iPosL==iPosR)
	{
		return RETURN_FAILED;
	}
	for(int i=iPosL; i<=iPosR; i++)
	{
		KeyDownAndUpUnicode(sInputWithDblQuart.GetAt(i));
		/*
		if((sInputWithDblQuart.GetAt(i)<=' ') && ( '~'<= sInputWithDblQuart.GetAt(i)))
		{
		KeyDownUnicode(sInputWithDblQuart.GetAt(i));
		KeyUpUnicode(sInputWithDblQuart.GetAt(i));
		}
		else
		{
		KeyDownUnicode(sInputWithDblQuart.GetAt(i));
		KeyUpUnicode(sInputWithDblQuart.GetAt(i));
			CString sTemp;
		CStringArray saData;
		sTemp.Format(_T("enter"));
		saData.Add(sTemp);
	KeyDownAndUp(&saData);


		}
		*/
		/*
		CStringArray saData;
		CString sTemp;
		sTemp.Format(_T("%c"),sInputWithDblQuart.GetAt(i));
		saData.Add(sTemp);
	KeyDownAndUp(&saData);
	*/
	}

	return RETURN_NORMAL;
}

ReturnValue WaitForEitherKeyOn(int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData, CString* sReturnParam)
{

	int iWaitOn;

	BOOL bUnicode;
	TCHAR tch;
	ReturnValue iRet;
	int iTimeOutMillisec;
	BYTE* byKeys;
	CString* sLabels;
	
	int iLength=saData->GetCount();
	if((iLength%2) != 1){return RETURN_FAILED;}
	if(iLength<3){return RETURN_FAILED;}

	int iKeynum=(iLength-1)/2;
	byKeys=new BYTE[iKeynum];
	sLabels=new CString[iKeynum];

	iTimeOutMillisec = GetIntValue(iScene, saData->GetAt(0));
	for(int i=0; i<iKeynum; i++)
	{
		iRet = GetKeyCode(saData->GetAt(2*i+1), &bUnicode, &tch, &(byKeys[i]));
		sLabels[i].Format(_T("%s"),saData->GetAt(2*i+2));
		if(iRet < 0)
		{ 
			delete [] byKeys;
			delete [] sLabels;
			return iRet;
		}
		if(bUnicode == TRUE)
		{
			if(('0'<=tch) && (tch<='9')){byKeys[i] = tch;}
			if(('a'<=tch) && (tch<='z')){byKeys[i] = tch;}
			if(('A'<=tch) && (tch<='Z')){byKeys[i] = tch-'A'+'a';}
		}
	}




	short shKey;

	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();

	while(1)
	{
		for(int i=0; i<iKeynum; i++)
		{
			shKey = GetAsyncKeyState (byKeys[i]);
			if(shKey<0) 
			{
				sReturnParam->Format(_T("%s"), sLabels[i]);

				delete [] byKeys;
				delete [] sLabels;
				return RETURN_GOTO_BY_SWITCH;
			}
		}
		iRet = K_Sleep(Halt, Suspend, 1);
		if(iRet <0)
		{
			delete [] byKeys;
			delete [] sLabels;
			return iRet;
		}

		if(iTimeOutMillisec>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+(iTimeOutMillisec/g_dSpeedMult))
			{
				delete [] byKeys;
				delete [] sLabels;
				return RETURN_FAILED;
			}
		}
	}
	delete [] byKeys;
	delete [] sLabels;
	return RETURN_FAILED;
}
