#include "stdafx.h"
#include "Automation.h"
#include "windows.h"
#include "Common.h"
#include "Variables.h"
#include "Window.h"

#include "ImgProc.h"
#include "Variables.h"
#include "InputDialog.h"
#include "PlayMedia.h"



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

ReturnValue KeyDownAndUpUnicode(wchar_t tch)
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

ReturnValue KeyDownUnicode(wchar_t tch)
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

ReturnValue KeyUpUnicode(wchar_t tch)
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

ReturnValue GetKeyCode(CString sData, BOOL* bUnicode, wchar_t* tch, BYTE* byData)
{
	*bUnicode = FALSE;
	*tch = 0;
	*byData = 0x00;

	DWORD dwRet= GetVKeyCode(sData);
	if(dwRet >0)
	{
		*byData= (BYTE)(dwRet);
		return RETURN_NORMAL;
	}

	*bUnicode = TRUE;
	*byData = 0x00;
	*tch=sData.GetAt(0);
	return RETURN_NORMAL;
}


ReturnValue WaitForUpdate(CString sDir, int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	
	int iWaitOn;

	int iTimeOutMilliSec;
	int iTickMillisec;
	if(saData->GetCount()<=2){return RETURN_FAILED;}
	
	BOOL bRet;

	int iR0, iC0, iR1, iC1;
	int iParamOffset;
	bRet = GetRectData(sDir, iScene, saData, 1, &iR0, &iC0, &iR1, &iC1, &iParamOffset);



	iTickMillisec = GetIntValue(sDir, iScene, saData->GetAt(0));
	

	if(saData->GetAt(iParamOffset+0).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(iParamOffset+0).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}


	if(saData->GetCount()<=iParamOffset+1){iTimeOutMilliSec=-1;}
	else {iTimeOutMilliSec = GetIntValue(sDir, iScene, saData->GetAt(iParamOffset+1));}
	


	ImgRGB imgModelCropped;
	ImgRGB imgModel;
	ImgRGB imgTarget;

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

ReturnValue WaitForImage(CString sDir, int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	int iWaitOn;

	int iTimeOutMilliSec;
	int icount=saData->GetCount();
	BOOL bRet;
	if(saData->GetCount()<3){return RETURN_FAILED;}


	int iR0, iC0, iR1, iC1;
	int iParamOffset;
	bRet = GetRectData(sDir, iScene, saData, 1, &iR0, &iC0, &iR1, &iC1, &iParamOffset);


	CString sModelFilePath;
	
	CString sModel;
	sModel.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	GetModelFilePath(sDir, sModel, &sModelFilePath);


	if(saData->GetAt(iParamOffset+0).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(iParamOffset+0).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}


	if(saData->GetCount()<=iParamOffset+1){iTimeOutMilliSec=-1;}
	else {iTimeOutMilliSec = GetIntValue(sDir, iScene, saData->GetAt(iParamOffset+1));}
	
	


	ImgRGB imgModel;
	ImgRGB imgTarget;
	ImgRGB imgMask;

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

ReturnValue WaitForColor(CString sDir, int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{
	int iWaitOn;

	int iTimeOutMilliSec;
	
	CString sArg;
	CString sColor;
	sColor.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));

	if((sColor.CompareNoCase(_T("R"))!=0) && (sColor.CompareNoCase(_T("G"))!=0) && (sColor.CompareNoCase(_T("B"))!=0)){return RETURN_FAILED;}

	int iLower;
	iLower = GetIntValue(sDir, iScene, saData->GetAt(1));
	int iUpper;
	iUpper = GetIntValue(sDir, iScene, saData->GetAt(2));

	int iR0, iC0, iR1, iC1;
	BOOL bRet;
	Point point;
	CRect rect;

	BOOL bRegion;
	BOOL bSpecified=FALSE;
	int iParamOffset;
	if(bSpecified==FALSE)
	{
		bRet =  GetPointValue(sDir, iScene, saData->GetAt(3), &point);
		if(bRet == TRUE)
		{
			bSpecified=TRUE;
			bRegion = FALSE;
			iParamOffset=4;
			iC0 = point.c;
			iR0 = point.r;
		}
	}

	if(bSpecified==FALSE)
	{
		bRet =  GetRectValue(sDir, iScene, saData->GetAt(3), &rect);
		if(bRet == TRUE)
		{
			bSpecified=TRUE;
			bRegion = TRUE;
			iParamOffset=4;
			iC0 = rect.left;
			iR0 = rect.top;
			iC1 = rect.right;
			iR1 = rect.bottom;
		}
	}

	if(bSpecified==FALSE)
	{

		if((saData->GetCount()==8) || (saData->GetCount()==9)){bRegion = TRUE;}
		else if((saData->GetCount()==6) || (saData->GetCount()==7)){bRegion = FALSE;}
		else{return RETURN_FAILED;}
		
		if(bRegion == TRUE)
		{
			bSpecified=TRUE;
			iC0 = GetIntValue(sDir, iScene, saData->GetAt(3));
			iR0 = GetIntValue(sDir, iScene, saData->GetAt(4));
			iC1 = GetIntValue(sDir, iScene, saData->GetAt(5));
			iR1 = GetIntValue(sDir, iScene, saData->GetAt(6));
			iParamOffset=7;
		}
		else
		{
			bSpecified=TRUE;
			iC0 = GetIntValue(sDir, iScene, saData->GetAt(3));
			iR0 = GetIntValue(sDir, iScene, saData->GetAt(4));
			iParamOffset=5;
		}
	}

	
	if(saData->GetCount()<iParamOffset+0){return RETURN_FAILED;}

	if(saData->GetAt(iParamOffset+0).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(iParamOffset+0).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}


	if(saData->GetCount()==iParamOffset+0){iTimeOutMilliSec=-1;}
	else {iTimeOutMilliSec = GetIntValue(sDir, iScene, saData->GetAt(iParamOffset+1));}

	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();
	ImgRGB imgTarget;
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


ReturnValue WaitForKey(CString sDir, int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{

	int iWaitOn;

	BYTE byKey;
	BOOL bUnicode;
	wchar_t tch;
	ReturnValue iRet;
	int iTimeOutMillisec;
	
	iRet = GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &byKey);
	if(iRet < 0){return iRet;}

	if(saData->GetAt(1).CompareNoCase(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(1).CompareNoCase(_T("off"))==0){iWaitOn=0;}
	else{return RETURN_FAILED;}

	if(saData->GetCount()>=3)
	{
		iTimeOutMillisec = GetIntValue(sDir, iScene, saData->GetAt(2));
	}
	else
	{
		iTimeOutMillisec=-1;
	}

	if(bUnicode == TRUE)
	{
		if(('0'<=tch) && (tch<='9')){byKey = (BYTE)(tch);}
		if(('a'<=tch) && (tch<='z')){byKey = (BYTE)(tch);}
		if(('A'<=tch) && (tch<='Z')){byKey = (BYTE)(tch-'A'+'a');}
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
	wchar_t tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyDownAndUpUnicode(tch);}

	return KeyDownAndUp(bySendKey);
}


ReturnValue KeyDown(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	wchar_t tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyDownUnicode(tch);}

	return KeyDown(bySendKey);
}



ReturnValue KeyUp(CStringArray* saData)
{
	BYTE bySendKey;
	BOOL bUnicode;
	wchar_t tch;

	GetKeyCode(saData->GetAt(0), &bUnicode, &tch, &bySendKey);
	if(bUnicode == TRUE){return KeyUpUnicode(tch);}

	return KeyUp(bySendKey);
}
ReturnValue ScreenShot(CString sDir, int iScene, CStringArray* saCommands)
{
	ImgRGB imgRGB;
	Screenshot(&imgRGB);

	CString sSrc;
	sSrc.Format(_T("%s"),GetStrValue(sDir, iScene, saCommands->GetAt(0)));

	BOOL bRet=WriteImage(&imgRGB, sSrc);
	if(bRet !=TRUE){return RETURN_FAILED;}
	return RETURN_NORMAL;
}

ReturnValue ScreenShotForegroundWindow(CString sDir, int iScene, CStringArray* saCommands)
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
	sSrc.Format(_T("%s"),GetStrValue(sDir, iScene, saCommands->GetAt(0)));

	BOOL bRet=WriteImage(&imgRGBCropped, sSrc);
	if(bRet !=TRUE){return RETURN_FAILED;}
	return RETURN_NORMAL;
}

ReturnValue OperateCommand(CString sDir, int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine, CString* sReturnParam)
{
	int iCommandType=COMMAND_UNDEFINED;
	BOOL bRet;
	CStringArray saData;
	bRet = PerseCommand(iSceneData, sDataLine, &iCommandType, &saData, sDir);
	if(iCommandType == COMMAND_NOTING){return RETURN_NORMAL;}
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iCommandType)
	{
	case COMMAND_DELAY:
		{
			int iSrc=GetIntValue(sDir, *iSceneData, saData.GetAt(0));
			return K_Sleep(Halt, Suspend, iSrc);
		}
	case COMMAND_MOUSE_L_DOWN:{MoveMouse(sDir, *iSceneData, &saData);return MouseLDown(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_R_DOWN:{MoveMouse(sDir, *iSceneData, &saData);return MouseRDown(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_M_DOWN:{MoveMouse(sDir, *iSceneData, &saData);return MouseMDown(sDir, *iSceneData, &saData);}

	case COMMAND_MOUSE_L_UP:{MoveMouse(sDir, *iSceneData, &saData);return MouseLUp(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_R_UP:{MoveMouse(sDir, *iSceneData, &saData);return MouseRUp(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_M_UP:{MoveMouse(sDir, *iSceneData, &saData);return MouseMUp(sDir, *iSceneData, &saData);}

	case COMMAND_MOUSE_L_CLICK:{return MouseLClick(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_R_CLICK:{return MouseRClick(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_M_CLICK:{return MouseMClick(sDir, *iSceneData, &saData);}
							   
	case COMMAND_MOUSE_SET_ORIGIN_TO_WINDOW:{return MouseSetOriginToWindow(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_SET_ORIGIN_TO_IMAGE:{return MouseSetOriginToImage(sDir, *iSceneData, &saData);}


	case COMMAND_MOUSE_MOVE:{return MoveMouse(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_MOVE_INCL:{return MoveMouseIncl(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_MOVE_TO_IMG:{return MoveMouseToImage(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_L_CLICK_IMG:{return MouseLClickImage(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_MOVE_TO_ITEM:{return MoveMouseToItem(sDir, *iSceneData, &saData);}
	case COMMAND_MOUSE_L_REPEATCLICK:{return MouseLRepeatClick(sDir, *iSceneData, &saData,Halt, Suspend);}

	case COMMAND_WHEEL:{return MouseVWheel(sDir, *iSceneData, &saData);}


	case COMMAND_KEY_DOWN_UP:{return KeyDownAndUp(&saData);}
	case COMMAND_KEY_DOWN:{return KeyDown(&saData);}
	case COMMAND_KEY_UP:{return KeyUp(&saData);}

	case COMMAND_WAIT:{return WaitForKey(sDir, *iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_KEY:{return WaitForKey(sDir, *iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_EITHER_KEY:{return WaitForEitherKeyOn(sDir, *iSceneData, Halt, Suspend, &saData, sReturnParam);}
	case COMMAND_WAIT_IMG:{return WaitForImage(sDir,  *iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_COLOR:{return WaitForColor(sDir, *iSceneData, Halt, Suspend, &saData);}
	case COMMAND_WAIT_UPDATE:{return WaitForUpdate(sDir, *iSceneData, Halt, Suspend, &saData);}
	case COMMAND_PLAY_SOUND:{
		return PlaySound_my(sDir, *iSceneData, &saData);
							}
	case COMMAND_MAXIMIZE:{return Maximize();}
	case COMMAND_MINIMIZE:{return Minimize();}
	case COMMAND_SET_WINDOW_ATTRIBUTE:{return SetWindowAttribute(sDir, *iSceneData, &saData);}
	case COMMAND_WINDOW_FORWARD:{return SetWindowForward(sDir, *iSceneData, &saData);}
	case COMMAND_SEND_MESSAGE:{return SendMessage_My(sDir, *iSceneData, &saData);}
	case COMMAND_WINDOW_SIZE:{return WindowSize(sDir, *iSceneData, &saData);}
	case COMMAND_WINDOW_POS:{return WindowPos(sDir, *iSceneData, &saData);}
	case COMMAND_RUN:{return RunExe(saData.GetAt(0));}
	case COMMAND_KILL:{return KillExe(sDir, *iSceneData, &saData);}
	case COMMAND_OUTPUT_KEY:{return OutputKeys(sDir, *iSceneData, saData.GetAt(0));}
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
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_STR:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_IMG:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_OBJ:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_POINT:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_RECT:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_CLIPBOARD:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_CAMERA:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_VARIABLE_CAMERA_CLOSE:
		{
			return Flow_Assign(sDir, *iSceneData, &saData);
		}
	case COMMAND_AREEQUAL_STR:
		{
			return Flow_AreStrEqual(sDir, *iSceneData, &saData, sReturnParam);
		}
	case COMMAND_COMPARE:
		{
			return Flow_Compare(sDir, *iSceneData, &saData, sReturnParam);
		}
	case COMMAND_SCREENSHOT:
		{
			return ScreenShot(sDir, *iSceneData, &saData);
		}
	case COMMAND_SCREENSHOT_FOREGROUND_WINDOW:
		{
			return ScreenShotForegroundWindow(sDir, *iSceneData, &saData);
		}
	case COMMAND_WRITE_IMAGE:
		{
			return Flow_WriteImage(sDir, *iSceneData, &saData);
		}
	case COMMAND_MESSAGEBOX:
		{
			return MessageBox_My(sDir, *iSceneData, &saData);
		}
	case COMMAND_LIST_DLG_ITEMS:
		{
			return ListDlgItems();
		}
	default:{return RETURN_FAILED;}
	}
	return RETURN_FAILED;
}
#include "Variables_String.h"
ReturnValue OutputKeys(CString sDir, int iScene, CString sInputWithDblQuart)
{
	CString sValue;
	sValue.Format(_T("%s"),GetStrValue(sDir, iScene, sInputWithDblQuart));

	int iPosL;
	int iPosR;
	for(int i=0; i<sValue.GetLength(); i++)
	{
		if(sValue.GetAt(i)==' '){continue;}
		if(sValue.GetAt(i)=='\t'){continue;}
		if(sValue.GetAt(i)=='@'){continue;}
		if(sValue.GetAt(i)=='\"'){iPosL=i+1;break;}
		iPosL=0; break;
	}
	for(int i=sValue.GetLength()-1; i>=0; i--)
	{
		if(sValue.GetAt(i)==' '){continue;}
		if(sValue.GetAt(i)=='\t'){continue;}
		if(sValue.GetAt(i)=='@'){continue;}
		if(sValue.GetAt(i)=='\"'){iPosR=i-1;break;}
		iPosR=sValue.GetLength()-1; break;
	}
	if(iPosL>iPosR)
	{
		return RETURN_FAILED;
	}
	for(int i=iPosL; i<=iPosR; i++)
	{
		KeyDownAndUpUnicode(sValue.GetAt(i));
		/*
		if((sValue.GetAt(i)<=' ') && ( '~'<= sValue.GetAt(i)))
		{
		KeyDownUnicode(sValue.GetAt(i));
		KeyUpUnicode(sValue.GetAt(i));
		}
		else
		{
		KeyDownUnicode(sValue.GetAt(i));
		KeyUpUnicode(sValue.GetAt(i));
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
		sTemp.Format(_T("%c"),sValue.GetAt(i));
		saData.Add(sTemp);
	KeyDownAndUp(&saData);
	*/
	}

	return RETURN_NORMAL;
}

ReturnValue WaitForEitherKeyOn(CString sDir, int iScene, LPVOID Halt, LPVOID Suspend, CStringArray* saData, CString* sReturnParam)
{
	BOOL bUnicode;
	wchar_t tch;
	ReturnValue iRet;
	int iTimeOutMillisec;
	BYTE* byKeys;
	CString* sLabels;
	
	int iLength=saData->GetCount();
	if((iLength%2) != 1){return RETURN_FAILED;}
	if(iLength<3){return RETURN_FAILED;}

	int iKeynum=(iLength-1)/2;
	byKeys=new BYTE[iKeynum];
	if(byKeys == NULL){return RETURN_FAILED;}
	sLabels=new CString[iKeynum];
	if(sLabels == NULL){SAFE_DELETE(byKeys); return RETURN_FAILED;}

	iTimeOutMillisec = GetIntValue(sDir, iScene, saData->GetAt(0));
	for(int i=0; i<iKeynum; i++)
	{
		iRet = GetKeyCode(saData->GetAt(2*i+1), &bUnicode, &tch, &(byKeys[i]));
		sLabels[i].Format(_T("%s"),saData->GetAt(2*i+2));
		if(iRet < 0)
		{ 
			SAFE_DELETE(byKeys);
			SAFE_DELETE(sLabels);
			return iRet;
		}
		if(bUnicode == TRUE)
		{
			if(('0'<=tch) && (tch<='9')){byKeys[i] = (BYTE)(tch);}
			if(('a'<=tch) && (tch<='z')){byKeys[i] = (BYTE)(tch);}
			if(('A'<=tch) && (tch<='Z')){byKeys[i] = (BYTE)(tch-'A'+'a');}
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
				
				SAFE_DELETE(byKeys);
				SAFE_DELETE(sLabels);
				return RETURN_GOTO_BY_SWITCH;
			}
		}
		iRet = K_Sleep(Halt, Suspend, 1);
		if(iRet <0)
		{
			SAFE_DELETE(byKeys);
			SAFE_DELETE(sLabels);
			return iRet;
		}

		if(iTimeOutMillisec>=0)
		{
			if(GetTickCount64()>ullStartMilliSec+(iTimeOutMillisec/g_dSpeedMult))
			{
				SAFE_DELETE(byKeys);
				SAFE_DELETE(sLabels);
				return RETURN_FAILED;
			}
		}
	}
	SAFE_DELETE(byKeys);
	SAFE_DELETE(sLabels);
	return RETURN_FAILED;
}
