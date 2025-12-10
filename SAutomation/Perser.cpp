#include "stdafx.h"
#include "Perser.h"

#include "Automation.h"
#include "stdafx.h"
#include "MouseAutomation.h"




BOOL GetCommand(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(1).CompareNoCase(_T("'"))==0){*iCommandType=COMMAND_NOTING;return TRUE;}
	if(sDataTrim.Left(2).CompareNoCase(_T("//"))==0){*iCommandType=COMMAND_NOTING;return TRUE;}

	if(sDataTrim.GetLength()==1){*iCommandType = COMMAND_KEY_DOWN_UP; return TRUE;}
	
	if(sDataTrim.Right(1).CompareNoCase(_T(":"))==0){*iCommandType=COMMAND_LABEL; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("Å©"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("<-"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Left"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Å™"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Up"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Å®"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("->"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Right"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Å´"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Down"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("PageUp"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("PageDown"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Home"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("End"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("PrintScreen"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	
	if(sDataTrim.CompareNoCase(_T("Enter"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Return"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Space"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("BackSpace"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Jp"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Tab"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("f1"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f2"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f3"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f4"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f5"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f6"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f7"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f8"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f9"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f10"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f11"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f12"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f13"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f14"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f15"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f16"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f17"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f18"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f19"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f20"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f21"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f22"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f23"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("f24"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	//-------------------------------------------------------

	if(sDataTrim.CompareNoCase(_T("Maximize"))==0){*iCommandType=COMMAND_MAXIMIZE; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("Minimize"))==0){*iCommandType=COMMAND_MINIMIZE; return TRUE;}
	if(sDataTrim.Left(18).CompareNoCase(_T("SetWindowAttribute"))==0){*iCommandType=COMMAND_SET_WINDOW_ATTRIBUTE; return TRUE;}
	//-------------------------------------------------------

	if(sDataTrim.SpanIncluding(_T("0123456789")).Compare(sDataTrim)==0){*iCommandType = COMMAND_DELAY; return TRUE;}
	if(sDataTrim.Right(3).CompareNoCase(_T("sec"))==0){CString sDataTrimTemp; sDataTrim.Format(_T("%s"),sDataTrim.Left(sDataTrim.GetLength()-3)); if(sDataTrimTemp.SpanIncluding(_T("0123456789")).Compare(sDataTrimTemp)==0){*iCommandType = COMMAND_DELAY; return TRUE;}}
	if(sDataTrim.Right(3).CompareNoCase(_T("min"))==0){CString sDataTrimTemp; sDataTrim.Format(_T("%s"),sDataTrim.Left(sDataTrim.GetLength()-3)); if(sDataTrimTemp.SpanIncluding(_T("0123456789")).Compare(sDataTrimTemp)==0){*iCommandType = COMMAND_DELAY; return TRUE;}}
	if(sDataTrim.Right(4).CompareNoCase(_T("hour"))==0){CString sDataTrimTemp; sDataTrim.Format(_T("%s"),sDataTrim.Left(sDataTrim.GetLength()-4)); if(sDataTrimTemp.SpanIncluding(_T("0123456789")).Compare(sDataTrimTemp)==0){*iCommandType = COMMAND_DELAY; return TRUE;}}
	if(sDataTrim.Right(3).CompareNoCase(_T("day"))==0){CString sDataTrimTemp; sDataTrim.Format(_T("%s"),sDataTrim.Left(sDataTrim.GetLength()-3)); if(sDataTrimTemp.SpanIncluding(_T("0123456789")).Compare(sDataTrimTemp)==0){*iCommandType = COMMAND_DELAY; return TRUE;}}

	//-------------------------------------------------------
	if(sDataTrim.Left(12).CompareNoCase(_T("LMouse Click"))==0){*iCommandType=COMMAND_MOUSE_L_CLICK;  return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("LMouse Down"))==0){*iCommandType=COMMAND_MOUSE_L_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("LMouse Up"))==0){*iCommandType=COMMAND_MOUSE_L_UP; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("RMouse Click"))==0){*iCommandType=COMMAND_MOUSE_R_CLICK;  return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("RMouse Down"))==0){*iCommandType=COMMAND_MOUSE_R_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("RMouse Up"))==0){*iCommandType=COMMAND_MOUSE_R_UP; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("MMouse Click"))==0){*iCommandType=COMMAND_MOUSE_M_CLICK;  return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("MMouse Down"))==0){*iCommandType=COMMAND_MOUSE_M_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("MMouse Up"))==0){*iCommandType=COMMAND_MOUSE_M_UP; return TRUE;}

	
	if(sDataTrim.Left(16).CompareNoCase(_T("MouseLClickImage"))==0){*iCommandType=COMMAND_MOUSE_L_CLICK_IMG; return TRUE;}
	if(sDataTrim.Left(16).CompareNoCase(_T("MouseRClickImage"))==0){*iCommandType=COMMAND_MOUSE_R_CLICK_IMG; return TRUE;}
	if(sDataTrim.Left(16).CompareNoCase(_T("MouseMClickImage"))==0){*iCommandType=COMMAND_MOUSE_M_CLICK_IMG; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("MouseLClick"))==0){*iCommandType=COMMAND_MOUSE_L_CLICK;  return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("MouseLDown"))==0){*iCommandType=COMMAND_MOUSE_L_DOWN; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("MouseLUp"))==0){*iCommandType=COMMAND_MOUSE_L_UP; return TRUE;}
	if(sDataTrim.Left(17).CompareNoCase(_T("MouseLRepeatClick"))==0){*iCommandType=COMMAND_MOUSE_L_REPEATCLICK; return TRUE;}
	if(sDataTrim.Left(17).CompareNoCase(_T("MouseRRepeatClick"))==0){*iCommandType=COMMAND_MOUSE_R_REPEATCLICK; return TRUE;}
	if(sDataTrim.Left(17).CompareNoCase(_T("MouseMRepeatClick"))==0){*iCommandType=COMMAND_MOUSE_M_REPEATCLICK; return TRUE;}
		
	if(sDataTrim.Left(11).CompareNoCase(_T("MouseRClick"))==0){*iCommandType=COMMAND_MOUSE_R_CLICK;  return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("MouseRDown"))==0){*iCommandType=COMMAND_MOUSE_R_DOWN; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("MouseRUp"))==0){*iCommandType=COMMAND_MOUSE_R_UP; return TRUE;}

	if(sDataTrim.Left(11).CompareNoCase(_T("MouseMClick"))==0){*iCommandType=COMMAND_MOUSE_M_CLICK;  return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("MouseMDown"))==0){*iCommandType=COMMAND_MOUSE_M_DOWN; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("MouseMUp"))==0){*iCommandType=COMMAND_MOUSE_M_UP; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("MousePosIncl"))==0){*iCommandType=COMMAND_MOUSE_MOVE_INCL; return TRUE;}
	if(sDataTrim.Left(15).CompareNoCase(_T("MousePosToimage"))==0){*iCommandType=COMMAND_MOUSE_MOVE_TO_IMG; return TRUE;}
	if(sDataTrim.Left(14).CompareNoCase(_T("MousePosToItem"))==0){*iCommandType=COMMAND_MOUSE_MOVE_TO_ITEM; return TRUE;}
	if((sDataTrim.Left(8).CompareNoCase(_T("MousePos"))==0) && (sDataTrim.Left(11).CompareNoCase(_T("MousePosRel"))!=0)){*iCommandType=COMMAND_MOUSE_MOVE; return TRUE;}

	
	if(sDataTrim.Left(17).CompareNoCase(_T("MouseLDragAndDrop"))==0){*iCommandType=COMMAND_MOUSE_L_DRAG_AND_DROP; return TRUE;}
	if(sDataTrim.Left(17).CompareNoCase(_T("MouseRDragAndDrop"))==0){*iCommandType=COMMAND_MOUSE_R_DRAG_AND_DROP; return TRUE;}
	if(sDataTrim.Left(17).CompareNoCase(_T("MouseMDragAndDrop"))==0){*iCommandType=COMMAND_MOUSE_M_DRAG_AND_DROP; return TRUE;}


	if(sDataTrim.Left(5).CompareNoCase(_T("Wheel"))==0){*iCommandType=COMMAND_WHEEL; return TRUE;}

	if(sDataTrim.Left(17).CompareNoCase(_T("SetOriginToWindow"))==0){*iCommandType=COMMAND_MOUSE_SET_ORIGIN_TO_WINDOW; return TRUE;}
	if(sDataTrim.Left(16).CompareNoCase(_T("SetOriginToImage"))==0){*iCommandType=COMMAND_MOUSE_SET_ORIGIN_TO_IMAGE; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("PlaySound"))==0){*iCommandType=COMMAND_PLAY_SOUND; return TRUE;}

	//-------------------------------------------------------

	if(sDataTrim.Left(26).CompareNoCase(_T("ScreenShotForeGroundWindow"))==0){*iCommandType=COMMAND_SCREENSHOT_FOREGROUND_WINDOW; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("ScreenShot"))==0){*iCommandType=COMMAND_SCREENSHOT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("WriteImage"))==0){*iCommandType=COMMAND_WRITE_IMAGE; return TRUE;}


	if(sDataTrim.Left(9).CompareNoCase(_T("WaitImage"))==0){*iCommandType=COMMAND_WAIT_IMG; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("WaitColor"))==0){*iCommandType=COMMAND_WAIT_COLOR; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("WaitUpdate"))==0){*iCommandType=COMMAND_WAIT_UPDATE; return TRUE;}


	if(sDataTrim.Right(4).CompareNoCase(_T("Down"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataTrim.Right(2).CompareNoCase(_T("Up"))==0){*iCommandType=COMMAND_KEY_UP; return TRUE;}

	if((sDataTrim.Left(3).CompareNoCase(_T("Run"))==0)){*iCommandType=COMMAND_RUN; return TRUE;}
	if((sDataTrim.Left(4).CompareNoCase(_T("Kill"))==0)){*iCommandType=COMMAND_KILL; return TRUE;}
	if((sDataTrim.Left(5).CompareNoCase(_T("Input"))==0)){*iCommandType=COMMAND_OUTPUT_KEY; return TRUE;}
	if((sDataTrim.Left(9).CompareNoCase(_T("OutputKey"))==0)){*iCommandType=COMMAND_OUTPUT_KEY; return TRUE;}

	if(sDataTrim.Left(7).CompareNoCase(_T("WaitKey"))==0){*iCommandType=COMMAND_WAIT_KEY; return TRUE;}
	if(sDataTrim.Left(13).CompareNoCase(_T("WaitEitherKey"))==0){*iCommandType=COMMAND_WAIT_EITHER_KEY; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("Wait"))==0){*iCommandType=COMMAND_WAIT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("WindowSize"))==0){*iCommandType=COMMAND_WINDOW_SIZE; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("WindowPos"))==0){*iCommandType=COMMAND_WINDOW_POS; return TRUE;}

	if(sDataTrim.Left(13).CompareNoCase(_T("WindowForward"))==0){*iCommandType=COMMAND_WINDOW_FORWARD; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("SendMessage"))==0){*iCommandType=COMMAND_SEND_MESSAGE; return TRUE;}
	
	if(sDataTrim.Left(7).CompareNoCase(_T("KeyDown"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataTrim.Left(5).CompareNoCase(_T("KeyUp"))==0){*iCommandType=COMMAND_KEY_UP; return TRUE;}
	if(sDataTrim.Left(3).CompareNoCase(_T("Key"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("MsgBox"))==0){*iCommandType=COMMAND_MESSAGEBOX; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("ListDlgItems"))==0){*iCommandType=COMMAND_LIST_DLG_ITEMS; return TRUE;}
	
	//-------------------------------------------------------
	
	if(sDataTrim.Left(11).CompareNoCase(_T("CloseCamera"))==0){*iCommandType=COMMAND_VARIABLE_CAMERA_CLOSE; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("ClipBoard"))==0){*iCommandType=COMMAND_VARIABLE_CLIPBOARD; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("VarCamera"))==0){*iCommandType=COMMAND_VARIABLE_CAMERA; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=COMMAND_VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=COMMAND_VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0){*iCommandType=COMMAND_VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarObj"))==0){*iCommandType=COMMAND_VARIABLE_OBJ; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0){*iCommandType=COMMAND_VARIABLE_POINT; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("VarRect"))==0){*iCommandType=COMMAND_VARIABLE_RECT; return TRUE;}

	if(sDataTrim.Left(7).CompareNoCase(_T("Compare"))==0){*iCommandType=COMMAND_COMPARE; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("AreEqualInt"))==0){*iCommandType=COMMAND_AREEQUAL_INT; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("AreEqualStr"))==0){*iCommandType=COMMAND_AREEQUAL_STR; return TRUE;}
	if(sDataTrim.Left(13).CompareNoCase(_T("SwitchByInput"))==0){*iCommandType=COMMAND_SWITCH_BY_INPUT; return TRUE;}

	//-------------------------------------------------------

	if(sDataTrim.Left(4).CompareNoCase(_T("GoTo"))==0){*iCommandType=COMMAND_GOTO;return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("Exit"))==0){*iCommandType=COMMAND_EXIT;return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("OnError"))==0){*iCommandType=COMMAND_ERROR_TREAT;return TRUE;}
	if(sDataTrim.Left(3).CompareNoCase(_T("Sub"))==0){*iCommandType=COMMAND_SUB; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("Call"))==0){*iCommandType=COMMAND_CALL_SUB; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("End Sub"))==0){*iCommandType=COMMAND_END_SUB; return TRUE;}


	return FALSE;
}


BOOL ExtractData(const CString sInput, const CString sDelim, CString* sOut, CString* sRemin)
{
	int iIndex;
	CString sInputLocal;
	sInputLocal.Format(_T("%s"), sInput);
	iIndex=sInputLocal.Find(sDelim);
	if(iIndex<0)
	{
		sOut->Format(_T("%s"),sInputLocal.Trim(_T(" \t")));
		sRemin->Format(_T(""));
	}
	else
	{
		sOut->Format(_T("%s"),sInputLocal.Left(iIndex).Trim(_T(" \t")));
		sRemin->Format(_T("%s"),sInputLocal.Right(sInputLocal.GetLength()-iIndex-1).Trim(_T(" \t")));
	}
	return TRUE;
}

BOOL GetWaitParameter(CString sInput, CStringArray* saOut)
{
	CString sRemind;

	CString sInputTrim;
	sInputTrim.Format(_T("%s"), sInput);
	sInputTrim.Trim(_T(" \t"));

	if(sInputTrim.Left(4).CompareNoCase(_T("Wait"))!=0){return FALSE;}
	sRemind.Format(_T("%s"), sInputTrim.Right(sInputTrim.GetLength()-4));
	sRemind.Trim(_T(" \t"));
	saOut->RemoveAll();
	if(sRemind.Right(2).CompareNoCase(_T("On"))==0)
	{
		saOut->Add(sRemind.Left(sRemind.GetLength()-2).Trim(_T(" \t")));
		saOut->Add(_T("On"));
		return TRUE;
	}
	if(sRemind.Right(3).CompareNoCase(_T("Off"))==0)
	{
		saOut->Add(sRemind.Left(sRemind.GetLength()-3).Trim(_T(" \t")));
		saOut->Add(_T("Off"));
		return TRUE;
	}

	return FALSE;
}
BOOL GetKeyType(CString sInput, CString* sOut)
{
	CString sRemind;
	CString sInputLower;
	sInputLower.Format(_T("%s"), sInput);
	sInputLower.Trim(_T(" \t"));

	if(sInputLower.CompareNoCase(_T("PageDown"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}
	if(sInputLower.CompareNoCase(_T("PageUp"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}
	if(sInputLower.CompareNoCase(_T("Up"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}
	if(sInputLower.CompareNoCase(_T("Down"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}

	if(sInputLower.Right(4).CompareNoCase(_T("Down"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-5));}
	else if(sInputLower.Right(2).CompareNoCase(_T("Up"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-2));}
	else{sRemind.Format(_T("%s"), sInput);}
	sRemind.Trim(_T(" \t"));

	sOut->Format(_T("%s"), sRemind);
	return TRUE;
}

ErrTreatValue GetErroTreat(CString sDataLine, CString* sLabel)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(7).CompareNoCase(_T("OnError"))!=0){return ERROR_TREAT_UNDEFINED;}
	CString sDataRemaind;
	sDataRemaind.Format(_T("%s"), sDataTrim.Right(sDataTrim.GetLength()-7));
	sDataRemaind.Trim(_T(" \t"));

	if(sDataRemaind.Left(4).CompareNoCase(_T("GoTo"))==0)
	{
		CString sTemp;
		sTemp.Format(_T("%s"), sDataRemaind.Right(sDataRemaind.GetLength()-4));
		sTemp.Trim(_T(" \t"));
		if(sTemp.GetAt(1)=='0'){return ERROR_TREAT_END;}

		sLabel->Format(_T("%s"), sTemp);
		return ERROR_TREAT_GOTO;
	}

	if(sDataRemaind.Left(11).CompareNoCase(_T("Resume Next"))==0){return ERROR_TREAT_RESUME;}


	return ERROR_TREAT_UNDEFINED;
}

BOOL ExtractToken(CString sInput, int iIndexIn, CString* sToken)
{
	int iOpenNum=0;
	int iCloseNum=0;
	for(int i=0; i<sInput.GetLength(); i++)
	{
		if(sInput.Mid(i,1).Compare(_T("("))==0){iOpenNum++;}
		if(sInput.Mid(i,1).Compare(_T(")"))==0){iCloseNum++;}
	}
	if(iOpenNum != iCloseNum){return FALSE;}
	
	int iStart=0;
	int iTokenIndex=0;
	for(int i=0; i<sInput.GetLength(); i++)
	{
		if(sInput.Mid(i,1).Compare(_T("("))==0){iOpenNum++;}
		if(sInput.Mid(i,1).Compare(_T(")"))==0){iCloseNum++;}

		if(iOpenNum!=iCloseNum){continue;}
		if(sInput.Mid(i,1).Compare(_T(","))!=0){continue;}

		if(iTokenIndex==iIndexIn)
		{
			sToken->Format(_T("%s"), sInput.Mid(iStart, i-iStart));
			sToken->Trim(_T(" \t"));
			return TRUE;
		}
		iStart=i+1;
		iTokenIndex++;
	}

	if(iTokenIndex==iIndexIn)
	{
		sToken->Format(_T("%s"), sInput.Mid(iStart, sInput.GetLength()-iStart));
		sToken->Trim(_T(" \t"));
		return TRUE;
	}
	return FALSE;
}

BOOL ExtractTokenInBracket(CString sInput, int iIndexIn, CString* sToken)
{
	int iOpenNum=0;
	int iCloseNum=0;
	sToken->Format(_T(""));
	for(int i=0; i<sInput.GetLength(); i++)
	{
		if(sInput.Mid(i,1).Compare(_T("("))==0){iOpenNum++;}
		if(sInput.Mid(i,1).Compare(_T(")"))==0){iCloseNum++;}
	}
	if(iOpenNum != iCloseNum){return FALSE;}
	//if((iOpenNum==0)&&(iIndexIn==0)){sToken->Format(_T("%s"),sInput); return TRUE;}
	if(iOpenNum==0){sToken->Format(_T("")); return TRUE;}

	int iStart;
	int iEnd;
	iStart=0;
	for(int i=0; i<sInput.GetLength(); i++)
	{
		if(sInput.Mid(i,1).Compare(_T("("))==0){iStart=i;break;}
	}
	iEnd = sInput.GetLength()-1;
	for(int i=sInput.GetLength()-1; i>=0; i--)
	{
		if(sInput.Mid(i,1).Compare(_T(")"))==0){iEnd=i;break;}
	}

	return  ExtractToken(sInput.Mid(iStart+1,iEnd-iStart-1), iIndexIn, sToken);

}

BOOL PerseLabelFromGotoStatement(CString sData, CString* sLabel)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"), sData.Trim(_T(" \t")));

	if(sDataTrim.Left(4).CompareNoCase(_T("GoTo"))!=0){return FALSE;}
	CString sDataRemaind;
	sDataRemaind.Format(_T("%s"),sDataTrim.Right(sDataTrim.GetLength()-4));

	sDataRemaind.Trim(_T(" \t"));

	sLabel->Format(_T("%s"), sDataRemaind);

	return TRUE;
}
BOOL CountArgsInTheParameter(CString sParameter, int* iCount)
{
	int iStart;
	iStart=0;
	int iFound;
	if(sParameter.GetLength()<=0){*iCount=0; return TRUE;}
	int iCountLocal=1;

	while(1)
	{
		iFound = sParameter.Find(_T(","), iStart);
		if(iFound <0){break;}

		iCountLocal++;
		iStart=iFound+1;
	}
	
	*iCount = iCountLocal;
	return TRUE;
}
BOOL CountToken(CString sParameter, int* iCount)
{
	if(sParameter.GetLength()<=0){*iCount=0; return TRUE;}
	int i=0;
	CString sDummy;
	BOOL bRet;
	while(1)
	{
		bRet = ExtractToken(sParameter,i,&sDummy);
		if(bRet != TRUE){break;}
		i++;
	}
	
	*iCount = i;
	return TRUE;
}
BOOL CountTokenInBracket(CString sParameter, int* iCount)
{
	if(sParameter.GetLength()<=0){*iCount=0; return TRUE;}

	BOOL bBracketExist=FALSE;
	for(int i=0; i<sParameter.GetLength(); i++)
	{
		if(sParameter.Mid(i,1).Compare(_T("("))==0){bBracketExist=TRUE; break;}
	}
	if(bBracketExist==FALSE){*iCount=0; return TRUE;}


	int i=0;
	CString sDummy;
	BOOL bRet;
	while(1)
	{
		bRet = ExtractTokenInBracket(sParameter,i,&sDummy);
		if(bRet != TRUE){break;}
		i++;
	}
	
	*iCount = i;
	return TRUE;
}
BOOL PerseCommand(int* iSceneData, CString sDataLine, int* iCommandType, CStringArray* saData, CString sDir)
{
	int iType;
	BOOL bRet;
	bRet = GetCommand(sDataLine, &iType);
	if(bRet == FALSE){*iCommandType = COMMAND_NOTING; return FALSE;}

	CString sDataLocal;
	sDataLocal.Format(_T("%s"), sDataLine.Trim(_T(" \t")));

	CString sName;
	CString sArg;
	CString sRemain;
	saData->RemoveAll();

	switch(iType)
	{
	case COMMAND_NOTING:{*iCommandType = COMMAND_NOTING; return TRUE;}
	case COMMAND_MOUSE_L_DOWN:
	case COMMAND_MOUSE_R_DOWN:
	case COMMAND_MOUSE_M_DOWN:
	case COMMAND_MOUSE_L_UP:
	case COMMAND_MOUSE_R_UP:
	case COMMAND_MOUSE_M_UP:
	case COMMAND_MOUSE_L_CLICK:
	case COMMAND_MOUSE_R_CLICK:
	case COMMAND_MOUSE_M_CLICK:
		{
			int iCount;
			CountTokenInBracket(sDataLocal,&iCount);
			if(iCount==1)
			{
				ExtractTokenInBracket(sDataLocal,0,&sArg);
				if((sArg.GetLength()==9)&&(sArg.Left(8).CompareNoCase(_T("VarPoint"))==0)&&((sArg.Right(1).SpanIncluding(_T("01234567")).Compare(sArg.Right(1))==0)))
				{	CString sTemp;sTemp.Format(_T("%s.c"),sArg);saData->Add(sTemp);sTemp.Format(_T("%s.r"),sArg);saData->Add(sTemp);*iCommandType = iType;return TRUE;}
				return FALSE;
			}

			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_MOVE:
		{
			int iCount;
			CountTokenInBracket(sDataLocal,&iCount);
			if(iCount==1)
			{
				ExtractTokenInBracket(sDataLocal,0,&sArg);
				if((sArg.GetLength()==9)&&(sArg.Left(8).CompareNoCase(_T("VarPoint"))==0)&&((sArg.Right(1).SpanIncluding(_T("01234567")).Compare(sArg.Right(1))==0)))
				{	CString sTemp;sTemp.Format(_T("%s.c"),sArg);saData->Add(sTemp);sTemp.Format(_T("%s.r"),sArg);saData->Add(sTemp);*iCommandType = iType;return TRUE;}
				return FALSE;
			}

			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_MOVE_INCL:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WHEEL:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){*iCommandType=iType; saData->Add(sArg); return TRUE;}


			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_SET_ORIGIN_TO_WINDOW:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_SET_ORIGIN_TO_IMAGE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_DELAY:
		{
			saData->Add(sDataLocal);
			*iCommandType=iType;
			return TRUE;
		}
	case COMMAND_KEY_DOWN_UP:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){*iCommandType=iType; saData->Add(sArg); return TRUE;}


			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;

			return TRUE;
		}
	case COMMAND_KEY_DOWN:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){*iCommandType=iType; saData->Add(sArg); return TRUE;}

			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
			return TRUE;
		}
	case COMMAND_KEY_UP:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){*iCommandType=iType; saData->Add(sArg); return TRUE;}

			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
			return TRUE;
		}
	case COMMAND_WAIT:
		{
			GetWaitParameter(sDataLocal, saData);
			*iCommandType=iType;
			return TRUE;
		}
	case COMMAND_WAIT_KEY:
		{
			*iCommandType=iType;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			saData->Add(sArg);

			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()<=0)
			{
				saData->Add(_T("-1"));
			}
			else
			{
				ExtractTokenInBracket(sDataLocal,2,&sArg);
				saData->Add(sArg);
			}

			return TRUE;
		}
	case COMMAND_WAIT_EITHER_KEY:
		{
			*iCommandType=iType;

			int iCount;
			CountTokenInBracket(sDataLocal,&iCount);
			if( (iCount%2) != 1){return FALSE;}
			if( iCount < 3){return FALSE;}

			for(int i=0; i<iCount; i++)
			{
				ExtractTokenInBracket(sDataLocal,i,&sArg);
				saData->Add(sArg);
			}
			return TRUE;
		}
	case COMMAND_MAXIMIZE:{*iCommandType=iType; return TRUE;}
	case COMMAND_MINIMIZE:{*iCommandType=iType; return TRUE;}
	case COMMAND_SET_WINDOW_ATTRIBUTE:
		{
			*iCommandType=iType;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			return TRUE;
		}
	case COMMAND_PLAY_SOUND:
		{
			*iCommandType=iType;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			return TRUE;
		}
	case COMMAND_WINDOW_FORWARD:
		{
			*iCommandType=iType;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			return TRUE;
		}
	case COMMAND_SEND_MESSAGE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WINDOW_SIZE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WINDOW_POS:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_RUN:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_KILL:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_OUTPUT_KEY:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WAIT_IMG:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,5,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,6,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WAIT_COLOR:
		{
			int iArgCount;
			bRet = CountTokenInBracket(sDataLocal, &iArgCount);
			if((iArgCount != 6) && (iArgCount != 7) && (iArgCount != 8) && (iArgCount != 9)){return FALSE;}
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,5,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,6,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,7,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,8,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WAIT_UPDATE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,5,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,6,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_MOVE_TO_IMG:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_L_CLICK_IMG:
	case COMMAND_MOUSE_R_CLICK_IMG:
	case COMMAND_MOUSE_M_CLICK_IMG:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_L_REPEATCLICK:
	case COMMAND_MOUSE_R_REPEATCLICK:
	case COMMAND_MOUSE_M_REPEATCLICK:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_L_DRAG_AND_DROP:
	case COMMAND_MOUSE_R_DRAG_AND_DROP:
	case COMMAND_MOUSE_M_DRAG_AND_DROP:
		{
			int iArgCount;
			bRet = CountTokenInBracket(sDataLocal, &iArgCount);
			if(iArgCount<2){return FALSE;}
			*iCommandType = iType;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if(iArgCount<3){return TRUE;}
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if(iArgCount<4){return TRUE;}
			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			if(iArgCount<5){return TRUE;}
			ExtractTokenInBracket(sDataLocal,4,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if(iArgCount<6){return TRUE;}
			ExtractTokenInBracket(sDataLocal,5,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			return TRUE;
		}
	case COMMAND_MOUSE_MOVE_TO_ITEM:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_INT:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_STR:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_IMG:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_OBJ:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_POINT:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_RECT:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_CLIPBOARD:
		{
			if(sDataLocal.Find(_T("="))<0){return FALSE;}
			
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			saData->Add(sDataLocal);

			*iCommandType = iType;
			return TRUE;
		}

	case COMMAND_EXIT:{*iCommandType = iType;return TRUE;}
	case COMMAND_LABEL:{*iCommandType = iType;return TRUE;}

	case COMMAND_SUB:{*iCommandType = iType;return TRUE;}
	case COMMAND_END_SUB:{*iCommandType = iType;return TRUE;}
	case COMMAND_CALL_SUB:
		{
			saData->Add(sDataLocal.Right(sDataLocal.GetLength()-4).Trim(_T(" \t")));
			*iCommandType = iType;return TRUE;
		}
	case COMMAND_ERROR_TREAT:{*iCommandType = iType;return TRUE;}
	case COMMAND_GOTO:{*iCommandType = iType;return TRUE;}
	case COMMAND_SWITCH_BY_INPUT:
		{

			CString sParameter;
			int iArgCount;
			bRet = CountTokenInBracket(sDataLocal, &iArgCount);
			if(bRet != TRUE){return FALSE;}
			if(iArgCount<6){return FALSE;}
			if((iArgCount%2)!=0){return FALSE;}
		
			for(int i=0; i<iArgCount-1; i++)
			{
				ExtractTokenInBracket(sDataLocal,0,&sArg);
				if(sArg.GetLength()<=0){return FALSE;}
				saData->Add(sArg);
			}
			
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_AREEQUAL_INT:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			saData->Add(_T("="));

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = COMMAND_COMPARE;
			return TRUE;
		}
	case COMMAND_AREEQUAL_STR:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_COMPARE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			
			ExtractTokenInBracket(sDataLocal,2,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,3,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_SCREENSHOT:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_SCREENSHOT_FOREGROUND_WINDOW:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MESSAGEBOX:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_LIST_DLG_ITEMS:
		{
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WRITE_IMAGE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()<7){return FALSE;}
			saData->Add(sArg);
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()<4){return FALSE;}
			saData->Add(sArg);

			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_CAMERA:
		{
			CString sDataLocalTemp;
			sDataLocalTemp.Format(_T("%s"),sDataLocal);
			ExtractData(sDataLocal, _T("="), &sArg, &sDataLocal);
			saData->Add(sArg);
			CString sArg1;
			ExtractData(sDataLocal, _T("("), &sArg1, &sDataLocal);
			CString sArg2;
			ExtractTokenInBracket(sDataLocalTemp,0,&sArg2);
			sArg.Format(_T("(%s,%s)"),sArg1,sArg2);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_VARIABLE_CAMERA_CLOSE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			sArg.Format(_T("(CloseCamera)"));
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	}
	return FALSE;
}