#include "stdafx.h"
#include "variables.h"
#include "perser.h"

int g_iVar[MAX_THREAD][MAX_VARIABLES];
CString g_sVar[MAX_THREAD][MAX_VARIABLES];
ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];

BOOL GetCommandVariable(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=VARIABLE_INT; return TRUE;}

	if(sDataTrim.Left(6).CompareNoCase(_T("AddInt"))==0){*iCommandType=VARIABLE_ADD_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("SubInt"))==0){*iCommandType=VARIABLE_SUB_INT; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("MultInt"))==0){*iCommandType=VARIABLE_MULT_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("DivInt"))==0){*iCommandType=VARIABLE_DIV_INT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("StrCombine"))==0){*iCommandType=VARIABLE_COMBINE_STR; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("Int2Str"))==0){*iCommandType=VARIABLE_INT2STR; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("NowDateTime"))==0){*iCommandType=VARIABLE_NOW_DATE_TIME; return TRUE;}

	if(sDataTrim.SpanIncluding(_T("0123456789")).CompareNoCase(sDataTrim)==0){*iCommandType = VARIABLE_INT; return TRUE;}

	*iCommandType=VARIABLE_STR;
	return TRUE;
}


int GetIntValue(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarInt"))!=0){return _ttoi(sArg);}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarInt%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return g_iVar[iScene][iVarNameB1-1];}
	}

	return 0;
}

int* GetIntValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarInt"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarInt%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}
	}

	return NULL;
}


CString GetStrValue(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarStr"))!=0){return sArg;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarStr%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return g_sVar[iScene][iVarNameB1-1];}
	}

	return 0;
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



int IntAdd(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);

	return iInt1+iInt2;
}

int IntSub(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);

	return iInt1-iInt2;
}
int IntMult(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);

	return iInt1*iInt2;
}

int IntDiv(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);

	return iInt1/iInt2;
}

int IntAssign(int iScene, CString sArg, int iValue)
{
	(*GetIntValuePointer(iScene, sArg))=iValue;

	return 0;
}

BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);

	return (iInt1==iInt2);
}

int Flow_IsIntEqual(int iScene, CStringArray* saData, CString* sReturnParam)
{
	if(IsIntEqual(iScene, saData->GetAt(0), saData->GetAt(1)))
	{
		sReturnParam->Format(_T("%s"), saData->GetAt(2));
		return RETURN_GOTO_BY_SWITCH;
	}

	return RETURN_NORMAL;
}


int GetValueInt(int iScene, CString sArg)
{
	if(sArg.GetLength()<0){return 0;}
	if(sArg.Left(1).CompareNoCase(_T("v"))==0) {return GetIntValue(iScene, sArg);}
	return _ttoi(sArg);
}

void AssignInt(int iScene, CString sArg, int iInput)
{
	(*GetIntValuePointer(iScene, sArg))=iInput;
}

#define FORMAT_FLAG_MASK			(0x0000F000)
#define FORMAT_FLAG_NOTHING			(0x00000000)
#define FORMAT_FLAG_SPACE			(0x00001000)
#define FORMAT_FLAG_PLUS			(0x00002000)
#define FORMAT_FLAG_ZERO			(0x00003000)

#define FORMAT_MIN_FIELD_MASK		(0x000F0000)
#define FORMAT_MIN_FIELD_SHIFT		(16)

#define FORMAT_ACCURACY_MASK		(0x00F00000)
#define FORMAT_ACCURACY_SHIFT		(20)


#define FORMAT_QUALIFIER_MASK		(0x03000000)
#define FORMAT_QUALIFIER_NOTHING	(0x00000000)
#define FORMAT_QUALIFIER_HALF		(0x01000000)
#define FORMAT_QUALIFIER_LONG		(0x02000000)

#define FORMAT_FLAG_UNSIGNED		(0x04000000)

#define FORMAT_SPECIFIER_MASK		 (0xF0000000)
#define FORMAT_SPECIFIER_DECIMAL	 (0x10000000)
#define FORMAT_SPECIFIER_SMALL_HEX	 (0x20000000)
#define FORMAT_SPECIFIER_CAPITAL_HEX (0x30000000)


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

	if(sFormat.Mid(iNextChar,1).SpanIncluding(_T("123456789")).Compare(sFormat.Mid(1,1))==0)
	{
		int iDigit=1;
		iNextChar++;
		while(sFormat.Mid(iNextChar,1).SpanIncluding(_T("0123456789")).Compare(sFormat.Mid(1,1))==0)
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
		if(sFormat.Mid(iNextChar,1).SpanIncluding(_T("123456789")).Compare(sFormat.Mid(1,1))==0)
		{
			int iDigit=1;
			iNextChar++;
			while(sFormat.Mid(iNextChar,1).SpanIncluding(_T("0123456789")).Compare(sFormat.Mid(1,1))==0)
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

#define FORMATO (_T("%d"))
const CString Int2Str(int iScene, CString sArg, CString sFormat)
{
	int iTemp;
	iTemp = GetIntValue(iScene, sArg);
	CString sOut;

	int iFormat;
	PerseFormat(sFormat, &iFormat);
	switch(iFormat)
	{
	case FORMAT_SPECIFIER_DECIMAL+FORMAT_QUALIFIER_NOTHING+(0x00000000)+(0x00000000)+FORMAT_FLAG_NOTHING:
		{
			sOut.Format(_T("%d"), iTemp);
			break;
		}
	}
	
	return sOut;
}
int Str2Int(int iScene, CString sArg)
{
	CString sTemp;
	sTemp.Format(_T("%s"), GetStrValue(iScene, sArg));
	return _ttoi(sTemp);
}

const CString StrCombine(int iScene, CString sArg1, CString sArg2)
{
	CString sTemp;
	sTemp.Format(_T("%s%s"), GetStrValue(iScene, sArg1),GetStrValue(iScene, sArg2));
	return sTemp;
}

const CString StrLeft(int iScene, CString sArg1, CString sArg2)
{
	CString sTemp;
	sTemp.Format(_T("%s"), GetStrValue(iScene, sArg1));
	return sTemp.Left(GetIntValue(iScene, sArg2));
}

const CString StrRight(int iScene, CString sArg1, CString sArg2)
{
	CString sTemp;
	sTemp.Format(_T("%s"), GetStrValue(iScene, sArg1));
	return sTemp.Right(GetIntValue(iScene, sArg2));
}

const CString StrMid(int iScene, CString sArg1, CString sArg2, CString sArg3)
{
	CString sTemp;
	sTemp.Format(_T("%s"), GetStrValue(iScene, sArg1));
	return sTemp.Mid(GetIntValue(iScene, sArg2),GetIntValue(iScene, sArg3));
}
const CString NowDateTime(CString sArg)
{
	CString sOut;

	SYSTEMTIME st;
	GetLocalTime(&st);

	int iPlace=0;
	sOut.Format(_T(""));
	while(iPlace<=sArg.GetLength())
	{
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("Y"))==0)
		{
			if(sArg.Mid(iPlace,4).CompareNoCase(_T("YYYY"))==0){CString sTemp; sTemp.Format(_T("%d"),st.wYear); sOut+=sTemp; iPlace+=4;}
			else if(sArg.Mid(iPlace,2).CompareNoCase(_T("YY"))==0){CString sTemp; sTemp.Format(_T("%d"),(st.wYear%100)); sOut+=sTemp;iPlace+=2;}
			else{return _T("");}
			continue;
		}
		if(sArg.Mid(iPlace,1).Compare(_T("M"))==0)
		{
			if(sArg.Mid(iPlace,2).Compare(_T("MM"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wMonth); sOut+=sTemp; iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wMonth); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("D"))==0)
		{
			if(sArg.Mid(iPlace,2).CompareNoCase(_T("dd"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wDay); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wDay); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("h"))==0)
		{
			if(sArg.Mid(iPlace,2).CompareNoCase(_T("hh"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wHour); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wHour); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).Compare(_T("m"))==0)
		{
			if(sArg.Mid(iPlace,2).Compare(_T("mm"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wMinute); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wMinute); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("s"))==0)
		{
			if(sArg.Mid(iPlace,2).CompareNoCase(_T("ss"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wSecond); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wSecond); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		sOut+=sArg.Mid(iPlace,1);
		iPlace++;
	}
	return sOut;
}
int Flow_Assign(int iScene, CStringArray* saData)
{
	int iCommandType;

	BOOL bRet;
	CString sArg;
	CString sDataLocal;
	sDataLocal.Format(_T("%s"), saData->GetAt(1));
	GetCommandVariable(sDataLocal, &iCommandType);
	switch(iCommandType)
	{
	case VARIABLE_ADD_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntAdd(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_SUB_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntSub(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_MULT_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntMult(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_DIV_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntDiv(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_INT:
		{
			int iTemp=GetIntValue(iScene, sDataLocal);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_COMBINE_STR:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			(*GetStrValuePointer(iScene, saData->GetAt(0))).Format(_T("%s"), StrCombine(iScene, sArg1, sArg2)); 
			return RETURN_NORMAL;
		}
	case VARIABLE_STR:
		{
			(*GetStrValuePointer(iScene, saData->GetAt(0))).Format(_T("%s"),GetStrValue(iScene, sDataLocal));
			return RETURN_NORMAL;
		}
	case VARIABLE_INT2STR:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			(*GetStrValuePointer(iScene, saData->GetAt(0))).Format(_T("%s"), Int2Str(iScene, sArg1, sArg2)); 
			return RETURN_NORMAL;
		}
	case VARIABLE_NOW_DATE_TIME:
		{
			CString sArg;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);

			(*GetStrValuePointer(iScene, saData->GetAt(0))).Format(_T("%s"), NowDateTime(sArg)); 
			return RETURN_NORMAL;
		}
	default:
		{
			if(sDataLocal.SpanIncluding(_T("0123456789")).CompareNoCase(sDataLocal)==0)
			{
				(*GetIntValuePointer(iScene, saData->GetAt(0)))=_ttoi(sDataLocal);
				return RETURN_NORMAL;
			}
			return RETURN_FAILED;
		}

	}
	return RETURN_FAILED;
}