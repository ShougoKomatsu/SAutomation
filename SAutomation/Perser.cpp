#include "stdafx.h"
#include "Perser.h"

#include "stdafx.h"
#include "MouseAutomation.h"

BOOL GetCommand(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(1).CompareNoCase(_T("'"))==0){*iCommandType=COMMAND_NOTING;return TRUE;}

	if(sDataTrim.GetLength()==1){*iCommandType = COMMAND_KEY_DOWN_UP; return TRUE;}
	

	if(sDataTrim.CompareNoCase(_T("Å©"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("<-"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("left"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("Å™"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("up"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("Å®"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("->"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("right"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("Å´"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("down"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}


	if(sDataTrim.CompareNoCase(_T("pageup"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("pagedown"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("home"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("end"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("printscreen"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	//-------------------------------------------------------
	if(sDataTrim.Left(10).CompareNoCase(_T("IsEqualInt"))==0){*iCommandType=COMMAND_ISEQUAL_INT; return TRUE;}
	if(sDataTrim.Left(13).CompareNoCase(_T("SwitchByInput"))==0){*iCommandType=COMMAND_SWITCH_BY_INPUT; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("goto"))==0){*iCommandType=COMMAND_GOTO;return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("exit"))==0){*iCommandType=COMMAND_EXIT;return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("onerror"))==0){*iCommandType=COMMAND_ERROR_TREAT;return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("lmouse click"))==0){*iCommandType=COMMAND_MOUSE_L_CLICK;  return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("lmouse down"))==0){*iCommandType=COMMAND_MOUSE_L_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("lmouse up"))==0){*iCommandType=COMMAND_MOUSE_L_UP; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("rmouse click"))==0){*iCommandType=COMMAND_MOUSE_R_CLICK;  return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("rmouse down"))==0){*iCommandType=COMMAND_MOUSE_R_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("rmouse up"))==0){*iCommandType=COMMAND_MOUSE_R_UP; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("mmouse click"))==0){*iCommandType=COMMAND_MOUSE_M_CLICK;  return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("mmouse down"))==0){*iCommandType=COMMAND_MOUSE_M_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("mmouse up"))==0){*iCommandType=COMMAND_MOUSE_M_UP; return TRUE;}


	if(sDataTrim.Left(11).CompareNoCase(_T("mouselclick"))==0){*iCommandType=COMMAND_MOUSE_L_CLICK;  return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("mouseldown"))==0){*iCommandType=COMMAND_MOUSE_L_DOWN; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("mouselup"))==0){*iCommandType=COMMAND_MOUSE_L_UP; return TRUE;}

	if(sDataTrim.Left(11).CompareNoCase(_T("mouserclick"))==0){*iCommandType=COMMAND_MOUSE_R_CLICK;  return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("mouserdown"))==0){*iCommandType=COMMAND_MOUSE_R_DOWN; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("mouserup"))==0){*iCommandType=COMMAND_MOUSE_R_UP; return TRUE;}

	if(sDataTrim.Left(11).CompareNoCase(_T("mousemclick"))==0){*iCommandType=COMMAND_MOUSE_M_CLICK;  return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("mousemdown"))==0){*iCommandType=COMMAND_MOUSE_M_DOWN; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("mousemup"))==0){*iCommandType=COMMAND_MOUSE_M_UP; return TRUE;}
	if(sDataTrim.Left(17).CompareNoCase(_T("setorigintowindow"))==0){*iCommandType=COMMAND_MOUSE_SET_ORIGIN_TO_WINDOW; return TRUE;}
	if(sDataTrim.Left(16).CompareNoCase(_T("setorigintoimage"))==0){*iCommandType=COMMAND_MOUSE_SET_ORIGIN_TO_IMAGE; return TRUE;}
	
	if(sDataTrim.Left(10).CompareNoCase(_T("screenshot"))==0){*iCommandType=COMMAND_SCREENSHOT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("WriteImage"))==0){*iCommandType=COMMAND_WRITE_IMAGE; return TRUE;}


	if(sDataTrim.Left(9).CompareNoCase(_T("waitimage"))==0){*iCommandType=COMMAND_WAIT_IMG; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("waitupdate"))==0){*iCommandType=COMMAND_WAIT_UPDATE; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("mouseposincl"))==0){*iCommandType=COMMAND_MOUSE_MOVE_INCL; return TRUE;}
	if(sDataTrim.Left(15).CompareNoCase(_T("mousepostoimage"))==0){*iCommandType=COMMAND_MOUSE_MOVE_TO_IMG; return TRUE;}
	if((sDataTrim.Left(8).CompareNoCase(_T("mousepos"))==0) && (sDataTrim.Left(11).CompareNoCase(_T("mouseposrel"))!=0)){*iCommandType=COMMAND_MOUSE_MOVE; return TRUE;}
	if(sDataTrim.Left(5).CompareNoCase(_T("wheel"))==0){*iCommandType=COMMAND_WHEEL; return TRUE;}
	if(sDataTrim.SpanIncluding(_T("0123456789")).CompareNoCase(sDataTrim)==0){*iCommandType = COMMAND_DELAY; return TRUE;}

	if(sDataTrim.Right(4).CompareNoCase(_T("down"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataTrim.Right(2).CompareNoCase(_T("up"))==0){*iCommandType=COMMAND_KEY_UP; return TRUE;}
	if((sDataTrim.Left(3).CompareNoCase(_T("run"))==0)){*iCommandType=COMMAND_RUN; return TRUE;}
	if((sDataTrim.Left(5).CompareNoCase(_T("input"))==0)){*iCommandType=COMMAND_INPUT; return TRUE;}

	if((sDataTrim.Left(4).CompareNoCase(_T("dim "))==0)){*iCommandType=COMMAND_DECRARE; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("WaitKey"))==0){*iCommandType=COMMAND_WAIT_KEY; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("wait"))==0){*iCommandType=COMMAND_WAIT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("windowsize"))==0){*iCommandType=COMMAND_WINDOW_SIZE; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("windowpos"))==0){*iCommandType=COMMAND_WINDOW_POS; return TRUE;}

	if(sDataTrim.Left(13).CompareNoCase(_T("windowforward"))==0){*iCommandType=COMMAND_WINDOW_FORWARD; return TRUE;}
	
	if(sDataTrim.Left(7).CompareNoCase(_T("keydown"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataTrim.Left(5).CompareNoCase(_T("keyup"))==0){*iCommandType=COMMAND_KEY_UP; return TRUE;}
	if(sDataTrim.Left(3).CompareNoCase(_T("key"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("MsgBox"))==0){*iCommandType=COMMAND_MESSAGEBOX; return TRUE;}

	//-------------------------------------------------------
	if(sDataTrim.CompareNoCase(_T("enter"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("return"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("space"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("backspace"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("jp"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("tab"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}

	if(sDataTrim.CompareNoCase(_T("maximize"))==0){*iCommandType=COMMAND_MAXIMIZE; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("minimize"))==0){*iCommandType=COMMAND_MINIMIZE; return TRUE;}
	
	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=COMMAND_VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=COMMAND_VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0){*iCommandType=COMMAND_VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0){*iCommandType=COMMAND_VARIABLE_POINT; return TRUE;}
	if(sDataTrim.GetLength()==2)
	{
		if(sDataTrim.CompareNoCase(_T("f1"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f2"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f3"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f4"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f5"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f6"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f7"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f8"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
		if(sDataTrim.CompareNoCase(_T("f9"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	}

	if(sDataTrim.GetLength()==3)
	{
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
	}
	
	if(sDataTrim.Left(3).CompareNoCase(_T("sub"))==0){*iCommandType=COMMAND_SUB; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("call"))==0){*iCommandType=COMMAND_CALL_SUB; return TRUE;}
	if(sDataTrim.Left(3).CompareNoCase(_T("end sub"))==0){*iCommandType=COMMAND_END_SUB; return TRUE;}

	if(sDataTrim.Right(1).CompareNoCase(_T(":"))==0){*iCommandType=COMMAND_LABEL; return TRUE;}
	//-------------------------------------------------------
	if((sDataTrim.Left(1).CompareNoCase(_T("<"))==0)&&(sDataTrim.Left(1).CompareNoCase(_T(">"))==0))
	{
		CString sRemaindRepeat;
		sRemaindRepeat.Format(_T("%s"), sDataTrim.Mid(1,sDataTrim.GetLength()-2));
		sRemaindRepeat.Trim(_T(" \t"));
		if(sRemaindRepeat.Left(1).CompareNoCase(_T("r"))==0)
		{
			int iRepeat;
			iRepeat = _ttoi(sRemaindRepeat.Right(sRemaindRepeat.GetLength()-1));
			if(iRepeat>=1)
			{
				*iCommandType = COMMAND_REPEAT;
				return TRUE;
			}
		}
		else{return FALSE;}
	}

	if((sDataTrim.Left(1).CompareNoCase(_T("<"))==0)&&(sDataTrim.Left(1).CompareNoCase(_T(">"))==0))
	{
		CString sRemaindRepeat;
		sRemaindRepeat.Format(_T("%s"), sDataTrim.Mid(1,sDataTrim.GetLength()-2));
		sRemaindRepeat.Trim(_T(" \t"));
		if(sRemaindRepeat.Left(2).CompareNoCase(_T("/r"))==0)
		{
			*iCommandType = COMMAND_REPEAT_END;
			return TRUE;
		}
		else{return FALSE;}
	}

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

	if(sInputTrim.Left(4).CompareNoCase(_T("wait"))!=0){return FALSE;}
	sRemind.Format(_T("%s"), sInputTrim.Right(sInputTrim.GetLength()-4));
	sRemind.Trim(_T(" \t"));
	saOut->RemoveAll();
	if(sRemind.Right(2).CompareNoCase(_T("on"))==0)
	{
		saOut->Add(sRemind.Left(sRemind.GetLength()-2).Trim(_T(" \t")));
		saOut->Add(_T("on"));
		return TRUE;
	}
	if(sRemind.Right(3).CompareNoCase(_T("off"))==0)
	{
		saOut->Add(sRemind.Left(sRemind.GetLength()-3).Trim(_T(" \t")));
		saOut->Add(_T("off"));
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

	if(sInputLower.CompareNoCase(_T("pagedown"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}
	if(sInputLower.CompareNoCase(_T("pageup"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}
	if(sInputLower.CompareNoCase(_T("up"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}
	if(sInputLower.CompareNoCase(_T("down"))==0){sOut->Format(_T("%s"), sInputLower);return TRUE;}

	if(sInputLower.Right(4).CompareNoCase(_T("down"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-5));}
	else if(sInputLower.Right(2).CompareNoCase(_T("up"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-2));}
	else{sRemind.Format(_T("%s"), sInput);}
	sRemind.Trim(_T(" \t"));

	sOut->Format(_T("%s"), sRemind);
	return TRUE;
}

ErrTreatValue GetErroTreat(CString sDataLine, CString* sLabel)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(7).CompareNoCase(_T("onerror"))!=0){return ERROR_TREAT_UNDEFINED;}
	CString sDataRemaind;
	sDataRemaind.Format(_T("%s"), sDataTrim.Right(sDataTrim.GetLength()-7));
	sDataRemaind.Trim(_T(" \t"));

	if(sDataRemaind.Left(4).CompareNoCase(_T("goto"))==0)
	{
		CString sTemp;
		sTemp.Format(_T("%s"), sDataRemaind.Right(sDataRemaind.GetLength()-4));
		sTemp.Trim(_T(" \t"));
		if(sTemp.GetAt(1)=='0'){return ERROR_TREAT_END;}

		sLabel->Format(_T("%s"), sTemp);
		return ERROR_TREAT_GOTO;
	}

	if(sDataRemaind.Left(11).CompareNoCase(_T("resume next"))==0){return ERROR_TREAT_RESUME;}


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
			return TRUE;
		}
		iStart=i+1;
		iTokenIndex++;
	}

	if(iTokenIndex==iIndexIn)
	{
		sToken->Format(_T("%s"), sInput.Mid(iStart, sInput.GetLength()-iStart));
		return TRUE;
	}
	return FALSE;
}

BOOL ExtractTokenInBracket(CString sInput, int iIndexIn, CString* sToken)
{
	int iOpenNum=0;
	int iCloseNum=0;
	for(int i=0; i<sInput.GetLength(); i++)
	{
		if(sInput.Mid(i,1).Compare(_T("("))==0){iOpenNum++;}
		if(sInput.Mid(i,1).Compare(_T(")"))==0){iCloseNum++;}
	}
	if(iOpenNum != iCloseNum){return FALSE;}
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

	if(sDataTrim.Left(4).CompareNoCase(_T("goto"))!=0){return FALSE;}
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
	case COMMAND_REPEAT:
		{
			CString sID;
			sID.Format(_T("%d"),(*iSceneData));
			saData->Add(sID);
			(*iSceneData)=(*iSceneData)+1;

			ExtractData(sDataLocal, _T("r"), &sArg, &sDataLocal);
			int iRepeat;
			CString sRepeat;
			iRepeat=_ttoi(sArg);
			sRepeat.Format(_T("%d"),iRepeat);
			saData->Add(sRepeat);
			return TRUE;
		}
	case COMMAND_MOUSE_L_DOWN:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_L_UP:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_R_DOWN:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_R_UP:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_M_DOWN:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_M_UP:
		{
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
	case COMMAND_MOUSE_L_CLICK:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_R_CLICK:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_MOUSE_M_CLICK:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()>0){saData->Add(sArg);}

			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
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
			if(sArg.GetLength()>2){if(sArg.GetAt(1)!=':'){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }}
			else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }
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
			if(sArg.GetLength()<=0)
			{
				saData->Add(sArg);
				saData->Add(_T("-1"));
			}
			else
			{
				ExtractTokenInBracket(sDataLocal,2,&sArg);
				saData->Add(sArg);
			}

			return TRUE;
		}
	case COMMAND_MAXIMIZE:{*iCommandType=iType; return TRUE;}
	case COMMAND_MINIMIZE:{*iCommandType=iType; return TRUE;}
	case COMMAND_WINDOW_FORWARD:
		{
			*iCommandType=iType;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
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
	case COMMAND_INPUT:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData->Add(sArg);
			*iCommandType = iType;
			return TRUE;
		}
	case COMMAND_WAIT_IMG:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>2){if(sArg.GetAt(1)!=':'){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }}
			else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }
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
			if(sArg.GetLength()>2){if(sArg.GetAt(1)!=':'){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }}
			else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }
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
	case COMMAND_VARIABLE_POINT:
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
	case COMMAND_ISEQUAL_INT:
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
	case COMMAND_SCREENSHOT:
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
	case COMMAND_WRITE_IMAGE:
		{
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()<7){return FALSE;}
			saData->Add(sArg);
			
			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()<4){return FALSE;}
			if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg);sArg.Format(_T("%s\\%s"),g_sDir,sTemp);}
			saData->Add(sArg);

			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			return TRUE;
		}
	}
	return FALSE;
}