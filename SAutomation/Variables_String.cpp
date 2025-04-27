#include "stdafx.h"
#include "variables.h"

#include "Window.h"
#include "perser.h"
#include "Variables_String.h"
#include "ClipBoard.h"

BOOL GetOperandStrSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0){*iCommandType = VARIABLE_IMG; return FALSE;}

	if(sDataTrim.Left(5).CompareNoCase(_T("Input"))==0){*iCommandType=VARIABLE_INPUT; return TRUE;}
	if(sDataTrim.Left(20).CompareNoCase(_T("ForegroundWindowName"))==0){*iCommandType=VARIABLE_FOREGROUND_WINDOW_NAME; return TRUE;}
	if(sDataTrim.Left(25).CompareNoCase(_T("ForegroundWindowClassName"))==0){*iCommandType=VARIABLE_FOREGROUND_WINDOW_CLASS_NAME; return TRUE;}
	
	if(sDataTrim.CompareNoCase(_T("ClipBoard"))==0){*iCommandType=VARIABLE_CLIPBOARD; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("ClipBoardFilePath"))==0){*iCommandType=VARIABLE_CLIPBOARD_FILE_PATH; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("ClipBoardFileName"))==0){*iCommandType=VARIABLE_CLIPBOARD_FILE_NAME; return TRUE;}

	if(sDataTrim.Left(25).CompareNoCase(_T("ClipBoardFileCreationTime"))==0){*iCommandType=VARIABLE_CLIPBOARD_FILE_CREATIONTIME; return TRUE;}
	if(sDataTrim.Left(26).CompareNoCase(_T("ClipBoardFileLastWriteTime"))==0){*iCommandType=VARIABLE_CLIPBOARD_FILE_LASTWRITETIME; return TRUE;}
	if(sDataTrim.Left(27).CompareNoCase(_T("ClipBoardFileLastAccessTime"))==0){*iCommandType=VARIABLE_CLIPBOARD_FILE_LASTACCESSTIME; return TRUE;}

	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("StrCombine"))==0){*iCommandType=VARIABLE_COMBINE_STR; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("Int2Str"))==0){*iCommandType=VARIABLE_INT2STR; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("NowDateTime"))==0){*iCommandType=VARIABLE_NOW_DATE_TIME; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("Left"))==0){*iCommandType=VARIABLE_STR_LEFT; return TRUE;}
	if(sDataTrim.Left(5).CompareNoCase(_T("Right"))==0){*iCommandType=VARIABLE_STR_RIGHT; return TRUE;}
	if(sDataTrim.Left(3).CompareNoCase(_T("Mid"))==0){*iCommandType=VARIABLE_STR_MID; return TRUE;}
	*iCommandType=VARIABLE_STR;
	return TRUE;
}

const CString GetStrValue(int iScene, CString sDataLocal)
{
	CString sOut;
	CString sArg;
	int iOperandSrc;
	BOOL bRet = GetOperandStrSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return sOut;}

	switch(iOperandSrc)
	{
	case VARIABLE_COMBINE_STR:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			sOut.Format(_T("%s"), StrCombine(iScene, sArg1, sArg2)); 
			return sOut;
		}
	case VARIABLE_STR:
		{
			CString* psSrc;
			CString sSrc;
			psSrc=GetStrValuePointer(iScene, sDataLocal);
			if(psSrc==NULL){sSrc.Format(_T("%s"),sDataLocal);}else{sSrc.Format(_T("%s"),*psSrc);}
			sOut.Format(_T("%s"),sSrc);
			LOG_OUTPUT_STR(iScene, sDataLocal, sSrc);
			return sOut;
		}
	case VARIABLE_INT2STR:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			sOut.Format(_T("%s"), Int2Str(iScene, sArg1, sArg2)); 
			return sOut;
		}
	case VARIABLE_NOW_DATE_TIME:
		{
			CString sArg;
			ExtractTokenInBracket(sDataLocal,0,&sArg);

			sOut.Format(_T("%s"), NowDateTime(sArg)); 
			LOG_OUTPUT_STR(iScene, sDataLocal, sOut);
			return sOut;
		}
	case VARIABLE_INPUT:
		{
			CStringArray saData;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			saData.Add(sArg);
			saData.Add(_T("-1"));
			g_cInput.m_bInputMulti=TRUE;
			g_cInput.m_saParam.Copy(saData);
			g_cInput.DoModal();
			return g_cInput.m_sReturnValue;
		}
	case VARIABLE_FOREGROUND_WINDOW_NAME:
		{
			return GetForegroundWindowName();
		}
	case VARIABLE_FOREGROUND_WINDOW_CLASS_NAME:
		{
			return GetForegroundWindowClassName();
		}
	case VARIABLE_STR_LEFT:
		{
			CString sArg1;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			sArg1.Format(_T("%s"), GetStrValue(iScene, sArg1));
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,1,&sArg2);
			int iArg2;
			iArg2 = GetIntValue(iScene, sArg2);
			return sArg1.Left(iArg2);
		}
	case VARIABLE_STR_RIGHT:
		{
			CString sArg1;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			sArg1.Format(_T("%s"), GetStrValue(iScene, sArg1));
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,1,&sArg2);
			int iArg2;
			iArg2 = GetIntValue(iScene, sArg2);
			return sArg1.Right(iArg2);
		}
	case VARIABLE_STR_MID:
		{
			CString sArg1;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			sArg1.Format(_T("%s"), GetStrValue(iScene, sArg1));
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,1,&sArg2);
			CString sArg3;
			ExtractTokenInBracket(sDataLocal,2,&sArg3);
			int iArg2;
			iArg2 = GetIntValue(iScene, sArg2);
			int iArg3;
			iArg3 = GetIntValue(iScene, sArg3);
			return sArg1.Mid(iArg2, iArg3);
		}
	case VARIABLE_CLIPBOARD:
		{
			return CopyFromClipBoardStr();
		}
	case VARIABLE_CLIPBOARD_FILE_PATH:
		{
			return CopyFromClipBoardFilePath();
		}
	case VARIABLE_CLIPBOARD_FILE_NAME:
		{
			CString sArg=CopyFromClipBoardFilePath();
			if(sArg.GetLength()<=0){return _T("");}

			CString sFileName;
			GetFileName(sArg, &sFileName);
			return sFileName;
		}
	case VARIABLE_CLIPBOARD_FILE_CREATIONTIME:
		{
			CString sFilePath=CopyFromClipBoardFilePath();
			if(sFilePath.GetLength()<=0){return _T("");}

			CTime ctTime;
			bRet = GetFileProperty(sFilePath, &ctTime,NULL, NULL);
			SYSTEMTIME sysTime;

			ctTime.GetAsSystemTime(sysTime);
			CString sArg;
			bRet = ExtractTokenInBracket(sDataLocal,0,&sArg);

			return  ConvertTimeToString(sysTime, sArg);
		}
	case VARIABLE_CLIPBOARD_FILE_LASTACCESSTIME:
		{
			CString sFilePath=CopyFromClipBoardFilePath();
			if(sFilePath.GetLength()<=0){return _T("");}

			CTime ctTime;
			bRet = GetFileProperty(sFilePath, NULL, &ctTime, NULL);
			SYSTEMTIME sysTime;

			ctTime.GetAsSystemTime(sysTime);
			CString sArg;
			bRet = ExtractTokenInBracket(sDataLocal,0,&sArg);

			return  ConvertTimeToString(sysTime, sArg);
		}
	case VARIABLE_CLIPBOARD_FILE_LASTWRITETIME:
		{
			CString sFilePath=CopyFromClipBoardFilePath();
			if(sFilePath.GetLength()<=0){return _T("");}

			CTime ctTime;
			bRet = GetFileProperty(sFilePath, NULL, NULL, &ctTime);
			SYSTEMTIME sysTime;

			ctTime.GetAsSystemTime(sysTime);
			CString sArg;
			bRet = ExtractTokenInBracket(sDataLocal,0,&sArg);

			return  ConvertTimeToString(sysTime, sArg);
		}
	default :
		{
			sOut.Format(_T("%s"),sDataLocal); 
			return sOut;

		}
	}
	return sOut;
}

CString* GetStrValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarStr"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarStr%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return &(g_sVar[iScene][iVarNameB1-1]);}
	}

	return NULL;
}


const CString StrCombine(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc1, sSrc2;

	sSrc1.Format(_T("%s"),GetStrValue(iScene, sArg1));
	sSrc2.Format(_T("%s"),GetStrValue(iScene, sArg2));

	CString sTemp;
	sTemp.Format(_T("%s%s"),sSrc1,sSrc2);
	return sTemp;
}

const CString StrLeft(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc;
	sSrc.Format(_T("%s"),GetStrValue(iScene, sArg1));

	int iSrc=GetIntValue(iScene, sArg2);

	CString sTemp;
	sTemp.Format(_T("%"),sSrc.Left(iSrc));
	return sTemp;
}

const CString StrRight(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc;
	sSrc.Format(_T("%s"),GetStrValue(iScene, sArg1));

	int iSrc=GetIntValue(iScene, sArg2);

	CString sTemp;
	sTemp.Format(_T("%"),sSrc.Right(iSrc));
	return sTemp;
}

const CString StrMid(int iScene, CString sArg1, CString sArg2, CString sArg3)
{
	CString sSrc;
	sSrc.Format(_T("%s"),GetStrValue(iScene, sArg1));

	int iSrc1=GetIntValue(iScene, sArg2);
	int iSrc2=GetIntValue(iScene, sArg3);

	CString sTemp;
	sTemp.Format(_T("%"),sSrc.Mid(iSrc1, iSrc2));
	return sTemp;
}

const CString NowDateTime(CString sArg)
{
	CString sOut;

	SYSTEMTIME st;
	GetLocalTime(&st);
	
	return ConvertTimeToString(st, sArg);
}
ReturnValue SetStrValue(CString* sDstPointer, int iScene, CString sDataLocal)
{
	CString sArg;
	int iOperandSrc;
	BOOL bRet = GetOperandStrSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CString sStrVal;
	sStrVal.Format(_T("%s"),GetStrValue(iScene,sDataLocal));

	switch(iOperandSrc)
	{
	case VARIABLE_COMBINE_STR:{break;}
	case VARIABLE_STR:{break;}
	case VARIABLE_INT2STR:{break;}
	case VARIABLE_NOW_DATE_TIME:{break;}
	case VARIABLE_INPUT:{break;}
	case VARIABLE_FOREGROUND_WINDOW_NAME:{break;}
	case VARIABLE_FOREGROUND_WINDOW_CLASS_NAME:{break;}
	case VARIABLE_STR_LEFT:{break;}
	case VARIABLE_STR_RIGHT:{break;}
	case VARIABLE_STR_MID:{break;}
	case VARIABLE_CLIPBOARD:{break;}
	case VARIABLE_CLIPBOARD_FILE_PATH:{if(sStrVal.GetLength()<=0){return RETURN_FAILED;} break;}
	case VARIABLE_CLIPBOARD_FILE_NAME:{if(sStrVal.GetLength()<=0){return RETURN_FAILED;} break;}
	case VARIABLE_CLIPBOARD_FILE_CREATIONTIME:{if(sStrVal.GetLength()<=0){return RETURN_FAILED;} break;}
	case VARIABLE_CLIPBOARD_FILE_LASTACCESSTIME:{if(sStrVal.GetLength()<=0){return RETURN_FAILED;} break;}
	case VARIABLE_CLIPBOARD_FILE_LASTWRITETIME:{if(sStrVal.GetLength()<=0){return RETURN_FAILED;} break;}
	default:
		{
			return RETURN_FAILED;
		}
	}
	sDstPointer->Format(_T("%s"), sStrVal); 
	return RETURN_NORMAL;
}



BOOL PerseFormat(CString sFormat, int* iFormatOut)
{
	int iNextChar;

	if(sFormat.Left(1).Compare(_T("%"))!=0){return FALSE;}
	iNextChar = 1;

	//フラグ - + 0
	//最小フィールド幅
	//.精度
	//修飾子　h, l
	//変換指定子 d, u x, X
	(*iFormatOut)=0;
	int iFormat=0;
	if(sFormat.Mid(iNextChar,1).Compare(_T("-"))==0)
	{
		iFormat+=FORMAT_FLAG_SPACE;
		iNextChar++;
	}
	else if(sFormat.Mid(iNextChar,1).Compare(_T("+"))==0)
	{
		iFormat+=FORMAT_FLAG_PLUS;
		iNextChar++;
	}
	else if(sFormat.Mid(iNextChar,1).Compare(_T("0"))==0)
	{
		iFormat+=FORMAT_FLAG_ZERO;
		iNextChar++;
	}

	if(sFormat.Mid(iNextChar,1).SpanIncluding(_T("123456789")).Compare(sFormat.Mid(iNextChar,1))==0)
	{
		int iDigit=1;
		iNextChar++;
		while(sFormat.Mid(iNextChar,1).SpanIncluding(_T("0123456789")).Compare(sFormat.Mid(iNextChar,1))==0)
		{
			iDigit++;
			iNextChar++;
		}
		if(iDigit>=15){iDigit=15;}
		iFormat+=(iDigit<<FORMAT_MIN_FIELD_SHIFT);
	}

	BOOL bAccuracy=FALSE;
	if(sFormat.Mid(iNextChar,1).Compare(_T("."))==0)
	{
		bAccuracy=TRUE;
		iNextChar++;
	}

	if(bAccuracy==TRUE)
	{
		if(sFormat.Mid(iNextChar,1).SpanIncluding(_T("123456789")).Compare(sFormat.Mid(iNextChar,1))==0)
		{
			int iDigit=1;
			iNextChar++;
			while(sFormat.Mid(iNextChar,1).SpanIncluding(_T("0123456789")).Compare(sFormat.Mid(iNextChar,1))==0)
			{
				iDigit++;
				iNextChar++;
			}
			if(iDigit>=15){iDigit=15;}
			iFormat+=(iDigit<<FORMAT_ACCURACY_SHIFT);
		}
	}

	if(sFormat.Mid(iNextChar,1).Compare(_T("u"))==0)
	{
		iFormat+=FORMAT_FLAG_UNSIGNED;
	}

	if(sFormat.Mid(iNextChar,1).Compare(_T("x"))==0)
	{
		iFormat+=FORMAT_SPECIFIER_SMALL_HEX;
	}
	else if(sFormat.Mid(iNextChar,1).Compare(_T("X"))==0)
	{
		iFormat+=FORMAT_SPECIFIER_CAPITAL_HEX;
	}
	else if(sFormat.Mid(iNextChar,1).CompareNoCase(_T("d"))==0)
	{
		iFormat+=FORMAT_SPECIFIER_DECIMAL;
	}
	else if(sFormat.Mid(iNextChar,1).CompareNoCase(_T("f"))==0)
	{
		return FALSE;
	}
	else if(sFormat.Mid(iNextChar,1).CompareNoCase(_T("e"))==0)
	{
		return FALSE;
	}
	else
	{
		return FALSE;
	}
	(*iFormatOut)=iFormat;
	return TRUE;
}
