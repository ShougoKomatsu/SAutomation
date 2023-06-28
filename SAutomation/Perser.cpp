#include "stdafx.h"
#include "Perser.h"

#include "stdafx.h"
#include "MouseAutomation.h"

BOOL GetCommand(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" ")).Trim(_T("\t")));

	if(sDataTrim.GetLength()==1){*iCommandType = COMMAND_KEY_DOWN_UP; return TRUE;}

	//-------------------------------------------------------
	if(sDataTrim.Left(4).CompareNoCase(_T("goto"))==0){*iCommandType=COMMAND_GOTO;return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("exit"))==0){*iCommandType=COMMAND_EXIT;return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("onerror"))==0){*iCommandType=COMMAND_ERROR_TREAT;return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("lmouse click"))==0){*iCommandType=COMMAND_MOUSE_L_CLICK; 		return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("lmouse down"))==0){*iCommandType=COMMAND_MOUSE_L_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("lmouse up"))==0){*iCommandType=COMMAND_MOUSE_L_UP; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("rmouse click"))==0){*iCommandType=COMMAND_MOUSE_R_CLICK; 		return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("rmouse down"))==0){*iCommandType=COMMAND_MOUSE_R_DOWN; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("rmouse up"))==0){*iCommandType=COMMAND_MOUSE_R_UP; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("waitimage"))==0){*iCommandType=COMMAND_WAIT_IMG; return TRUE;}

	if(sDataTrim.Left(12).CompareNoCase(_T("mouseposincl"))==0){*iCommandType=COMMAND_MOUSE_MOVE_INCL; return TRUE;}
	if(sDataTrim.Left(15).CompareNoCase(_T("mousepostoimage"))==0){*iCommandType=COMMAND_MOUSE_MOVE_TO_IMG; return TRUE;}
	if((sDataTrim.Left(8).CompareNoCase(_T("mousepos"))==0) && (sDataTrim.Left(11).CompareNoCase(_T("mouseposrel"))!=0)){*iCommandType=COMMAND_MOUSE_MOVE; return TRUE;}
	if(sDataTrim.Left(5).CompareNoCase(_T("wheel"))==0){*iCommandType=COMMAND_WHEEL; return TRUE;}
	if(sDataTrim.SpanIncluding(_T("0123456789")).CompareNoCase(sDataTrim)==0){*iCommandType = COMMAND_DELAY; return TRUE;}

	if(sDataTrim.Right(4).CompareNoCase(_T("down"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataTrim.Right(2).CompareNoCase(_T("up"))==0){*iCommandType=COMMAND_KEY_UP; return TRUE;}
	if((sDataTrim.Left(3).CompareNoCase(_T("run"))==0)){*iCommandType=COMMAND_RUN; return TRUE;}

	if((sDataTrim.Left(4).CompareNoCase(_T("dim "))==0)){*iCommandType=COMMAND_DECRARE; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("wait"))==0){*iCommandType=COMMAND_WAIT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("windowsize"))==0){*iCommandType=COMMAND_WINDOW_SIZE; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("windowpos"))==0){*iCommandType=COMMAND_WINDOW_POS; return TRUE;}

	if(sDataTrim.Left(13).CompareNoCase(_T("windowforward"))==0){*iCommandType=COMMAND_WINDOW_FORWARD; return TRUE;}

	//-------------------------------------------------------
	if(sDataTrim.CompareNoCase(_T("enter"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("return"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("space"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("tab"))==0){*iCommandType=COMMAND_KEY_DOWN_UP; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("maximize"))==0){*iCommandType=COMMAND_MAXIMIZE; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("minimize"))==0){*iCommandType=COMMAND_MINIMIZE; return TRUE;}

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

	if(sDataTrim.Right(1).CompareNoCase(_T(":"))==0){*iCommandType=COMMAND_LABEL; return TRUE;}
	//-------------------------------------------------------
	if((sDataTrim.Left(1).CompareNoCase(_T("<"))==0)&&(sDataTrim.Left(1).CompareNoCase(_T(">"))==0))
	{
		CString sRemaindRepeat;
		sRemaindRepeat.Format(_T("%s"), sDataTrim.Mid(1,sDataTrim.GetLength()-2));
		sRemaindRepeat.Trim(_T(" ")).Trim(_T("\t"));
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
		sRemaindRepeat.Trim(_T(" ")).Trim(_T("\t"));
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
		sOut->Format(_T("%s"),sInputLocal.Trim(_T(" ")).Trim(_T("\t")));
		sRemin->Format(_T(""));
	}
	else
	{
		sOut->Format(_T("%s"),sInputLocal.Left(iIndex).Trim(_T(" ")).Trim(_T("\t")));
		sRemin->Format(_T("%s"),sInputLocal.Right(sInputLocal.GetLength()-iIndex-1).Trim(_T(" ")).Trim(_T("\t")));
	}
	return TRUE;
}

BOOL GetWaitParameter(CString sInput, CStringArray* saOut)
{
	CString sRemind;

	CString sInputTrim;
	sInputTrim.Format(_T("%s"), sInput);
	sInputTrim.Trim(_T(" ")).Trim(_T("\t"));

	if(sInputTrim.Left(4).CompareNoCase(_T("wait"))!=0){return FALSE;}
	sRemind.Format(_T("%s"), sInputTrim.Right(sInputTrim.GetLength()-4));
	sRemind.Trim(_T(" ")).Trim(_T("\t"));
	saOut->RemoveAll();
	if(sRemind.Right(2).CompareNoCase(_T("on"))==0)
	{
		saOut->Add(sRemind.Left(sRemind.GetLength()-2).Trim(_T(" ")).Trim(_T("\t")));
		saOut->Add(_T("on"));
		return TRUE;
	}
	if(sRemind.Right(3).CompareNoCase(_T("off"))==0)
	{
		saOut->Add(sRemind.Left(sRemind.GetLength()-3).Trim(_T(" ")).Trim(_T("\t")));
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
	sInputLower.Trim(_T(" ")).Trim(_T("\t"));
	if(sInputLower.Right(4).CompareNoCase(_T("down"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-5));}
	else if(sInputLower.Right(2).CompareNoCase(_T("up"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-2));}
	else{sRemind.Format(_T("%s"), sInput);}
	sRemind.Trim(_T(" ")).Trim(_T("\t"));

	sOut->Format(_T("%s"), sRemind);
	return TRUE;
}

int GetErroTreat(CString sDataLine, CString* sLabel)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" ")).Trim(_T("\t")));

	if(sDataTrim.Left(7).CompareNoCase(_T("onerror"))!=0){return ERROR_TREAT_UNDEFINED;}
	CString sDataRemaind;
	sDataRemaind.Format(_T("%s"), sDataTrim.Right(sDataTrim.GetLength()-7));
	sDataRemaind.Trim(_T(" ")).Trim(_T("\t"));

	if(sDataRemaind.Left(4).CompareNoCase(_T("goto"))==0)
	{
		CString sTemp;
		sTemp.Format(_T("%s"), sDataRemaind.Right(sDataRemaind.GetLength()-4));
		sTemp.Trim(_T(" ")).Trim(_T("\t"));
		if(sTemp.GetAt(1)=='0'){return ERROR_TREAT_END;}
		
		sLabel->Format(_T("%s"), sTemp);
		return ERROR_TREAT_GOTO;
	}

	if(sDataRemaind.Left(11).CompareNoCase(_T("resume next"))==0){return ERROR_TREAT_RESUME;}


	return ERROR_TREAT_UNDEFINED;
}

int SearchLable(CStringArray* saData, CString sLabel)
{
	for(int i=0; i<saData->GetCount(); i++)
	{
		CString sTemp;
		sTemp.Format(_T("%s"), saData->GetAt(i));
		sTemp.Trim(_T(" ")).Trim(_T("\t"));
		CString sTrim;
		sTrim.Format(_T("%s"), sTemp.Left(sTemp.GetLength()-1));
		sTrim.Trim(_T(" ")).Trim(_T("\t"));
		if(sTrim.CompareNoCase(sLabel)==0){return i;}
	}
	return -1;
}
BOOL PerseLabelFromGotoStatement(CString sData, CString* sLabel)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"), sData.Trim(_T(" ")).Trim(_T("\t")));

	if(sDataTrim.Left(4).CompareNoCase(_T("goto"))!=0){return FALSE;}
	CString sDataRemaind;
	sDataRemaind.Format(_T("%s"),sDataTrim.Right(sDataTrim.GetLength()-4));

	sDataRemaind.Trim(_T(" ")).Trim(_T("\t"));

	sLabel->Format(_T("%s"), sDataRemaind);

	return TRUE;
}

BOOL PerseCommand(int* iSceneData, CString sDataLine, int* iCommandType, CStringArray* saData, CString sDir)
{
	int iType;
	BOOL bRet;
	bRet = GetCommand(sDataLine, &iType);
	if(bRet == FALSE){*iCommandType = COMMAND_NOTING; return FALSE;}

	CString sDataLocal;
	sDataLocal.Format(_T("%s"), sDataLine.Trim(_T(" ")).Trim(_T("\t")));

	CString sName;
	CString sArg;
	CString sRemain;
	saData->RemoveAll();
	switch(iType)
	{
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
		}
	case COMMAND_MOUSE_L_DOWN:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			break;
		}

	case COMMAND_MOUSE_L_UP:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			break;
		}
		
	case COMMAND_MOUSE_R_DOWN:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			break;
		}

	case COMMAND_MOUSE_R_UP:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			break;
		}
	case COMMAND_MOUSE_MOVE:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData->Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}
	case COMMAND_MOUSE_MOVE_INCL:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData->Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}
	case COMMAND_WHEEL:
		{
			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}
	case COMMAND_MOUSE_L_CLICK:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			break;
		}
		
	case COMMAND_MOUSE_R_CLICK:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount()!=0) && (saData->GetCount()!=2)){return FALSE;}
			*iCommandType = iType;
			break;
		}

	case COMMAND_DELAY:
		{
			saData->Add(sDataLocal);
			*iCommandType=iType;
			break;
		}
	case COMMAND_KEY_DOWN_UP:
		{
			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
			break;
		}
	case COMMAND_KEY_DOWN:
		{
			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
			break;
		}

	case COMMAND_KEY_UP:
		{
			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
			break;
		}
	case COMMAND_WAIT:
		{
			GetWaitParameter(sDataLocal, saData);
			*iCommandType=iType;
			break;
		}
	case COMMAND_MAXIMIZE:
		{
			*iCommandType=iType;
			break;
		}
	case COMMAND_MINIMIZE:
		{
			*iCommandType=iType;
			break;
		}
	case COMMAND_WINDOW_FORWARD:
		{
			*iCommandType=iType;
			ExtractData(sDataLine, _T(" "), &sArg, &sDataLocal);
			saData->Add(sDataLocal);
			break;
		}
	case COMMAND_WINDOW_SIZE:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			break;
		}
	case COMMAND_WINDOW_POS:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			if((saData->GetCount())!=2){return FALSE;}
			*iCommandType = iType;
			break;
		}
	case COMMAND_RUN:
		{
			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			saData->Add(sDataLocal);
			*iCommandType = iType;
			break;
		}
		
	case COMMAND_WAIT_IMG:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			
			if(sArg.GetLength()>2){if(sArg.GetAt(1)!=':'){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }}
			else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }

			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			break;
		}
		
	case COMMAND_MOUSE_MOVE_TO_IMG:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);

			if(sArg.GetLength()>2){if(sArg.GetAt(1)!=':'){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }}
			else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), sDir,sTemp); }

			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){saData->Add(sArg);}
			*iCommandType = iType;
			break;
		}
	case COMMAND_EXIT:
		{
			*iCommandType = iType;
			break;
		}
	case COMMAND_LABEL:
		{
//			ExtractData(sDataLocal, _T(":"), &sArg, &sDataLocal);
//			sArg.Trim(_T(" ")).Trim(_T("\t"));
//			if(sArg.GetLength()<0){return FALSE;}
			*iCommandType = iType;
			break;
		}
	case COMMAND_ERROR_TREAT:
		{
//			ExtractData(sDataLocal, _T("onerror"), &sArg, &sDataLocal);
//			sArg.Trim(_T(" ")).Trim(_T("\t"));
//			if(sArg.GetLength()<0){return FALSE;}
			*iCommandType = iType;
			break;
		}
	case COMMAND_GOTO:
		{
					*iCommandType = iType;
			break;
		}
	}

	return TRUE;
}