#include "stdafx.h"
#include "variables.h"
#include "perser.h"
#include "Common.h"
int g_iVar[MAX_THREAD][MAX_VARIABLES];
CString g_sVar[MAX_THREAD][MAX_VARIABLES];
ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];
Point g_point[MAX_THREAD][MAX_VARIABLES];

BOOL GetOperandSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("AddInt"))==0){*iCommandType=VARIABLE_ADD_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("SubInt"))==0){*iCommandType=VARIABLE_SUB_INT; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("MultInt"))==0){*iCommandType=VARIABLE_MULT_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("DivInt"))==0){*iCommandType=VARIABLE_DIV_INT; return TRUE;}
	if(sDataTrim.SpanIncluding(_T("0123456789")).CompareNoCase(sDataTrim)==0){*iCommandType = VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}

		if(sDataTrim.Right(1).CompareNoCase(_T("r"))==0){*iCommandType=VARIABLE_POINT_GET_R; return TRUE;}
		if(sDataTrim.Right(1).CompareNoCase(_T("c"))==0){*iCommandType=VARIABLE_POINT_GET_C; return TRUE;}

		return FALSE;
	}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("StrCombine"))==0){*iCommandType=VARIABLE_COMBINE_STR; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("Int2Str"))==0){*iCommandType=VARIABLE_INT2STR; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("NowDateTime"))==0){*iCommandType=VARIABLE_NOW_DATE_TIME; return TRUE;}
	*iCommandType=VARIABLE_STR;
	return TRUE;
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("CropImage"))==0){*iCommandType=VARIABLE_CROP_IMAGE; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("ScreenShot"))==0){*iCommandType=VARIABLE_SCREENSHOT; return TRUE;}
	if(sDataTrim.Right(4).CompareNoCase(_T(".bmp"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}
	return FALSE;
}

BOOL GetOperandDst(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}

		//		if(sDataTrim.Right(1).CompareNoCase(_T("r"))==0){*iCommandType=VARIABLE_POINT_R; return TRUE;}
		//		if(sDataTrim.Right(1).CompareNoCase(_T("c"))==0){*iCommandType=VARIABLE_POINT_C; return TRUE;}
		*iCommandType=VARIABLE_POINT; 
		return TRUE;
	}

	return FALSE;
}

//int GetValueInt(int iScene, CString sArg)
//{
//	if(sArg.GetLength()<0){return 0;}
//	if(sArg.Left(1).CompareNoCase(_T("v"))==0) {return GetIntValue(iScene, sArg);}
//	return _ttoi(sArg);
//}



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


const CString GetStrValue(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarStr"))!=0){return sArg;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarStr%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return g_sVar[iScene][iVarNameB1-1];}
	}

	return sArg;
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


ImgRGB* GetImgValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarImg"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarImg%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return &(g_imgRGB[iScene][iVarNameB1-1]);}
	}

	return NULL;
}

const ImgRGB* GetImgValuePointerConst(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarImg"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarImg%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return &(g_imgRGB[iScene][iVarNameB1-1]);}
	}

	return NULL;
}

Point* GetPointValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(8).CompareNoCase(_T("VarPoint"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarPoint%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return &(g_point[iScene][iVarNameB1-1]);}
	}

	return NULL;
}

Point GetPointValue(int iScene, CString sArg)
{
	if(sArg.Left(8).CompareNoCase(_T("VarPoint"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarPoint%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return (g_point[iScene][iVarNameB1-1]);}
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


BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);

	return (iInt1==iInt2);
}

ReturnValue Flow_IsIntEqual(int iScene, CStringArray* saData, CString* sReturnParam)
{
	if(IsIntEqual(iScene, saData->GetAt(0), saData->GetAt(1)))
	{
		sReturnParam->Format(_T("%s"), saData->GetAt(2));
		return RETURN_GOTO_BY_SWITCH;
	}

	return RETURN_NORMAL;
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
ReturnValue SetStrValue(CString* sDstPointer, int iScene, CString sDataLocal)
{
	CString sArg;
	int iOperandSrc;
	BOOL bRet = GetOperandDst(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iOperandSrc)
	{
	case VARIABLE_COMBINE_STR:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			sDstPointer->Format(_T("%s"), StrCombine(iScene, sArg1, sArg2)); 
			return RETURN_NORMAL;
		}
	case VARIABLE_STR:
		{
			sDstPointer->Format(_T("%s"),GetStrValue(iScene, sDataLocal));
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

			sDstPointer->Format(_T("%s"), Int2Str(iScene, sArg1, sArg2)); 
			return RETURN_NORMAL;
		}
	case VARIABLE_NOW_DATE_TIME:
		{
			CString sArg;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);

			sDstPointer->Format(_T("%s"), NowDateTime(sArg)); 
			return RETURN_NORMAL;
		}
	}
	return RETURN_FAILED;
}

ReturnValue SetIntValue(int* iDstPointer, int iScene, CString sDataLocal)
{	
	int iOperandSrc;
	BOOL bRet = GetOperandDst(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CString sArg;
	switch(iOperandSrc)
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

			(*iDstPointer)=IntAdd(iScene, sArg1, sArg2);
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

			(*iDstPointer)=IntSub(iScene, sArg1, sArg2);
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

			(*iDstPointer)=IntMult(iScene, sArg1, sArg2);
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

			(*iDstPointer)=IntDiv(iScene, sArg1, sArg2);
			return RETURN_NORMAL;
		}
	case VARIABLE_INT:
		{
			(*iDstPointer)=GetIntValue(iScene, sDataLocal);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_GET_R:
		{
			Point pointTemp = GetPointValue(iScene, sDataLocal);
			(*iDstPointer)=pointTemp.r;
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_GET_C:
		{
			Point pointTemp = GetPointValue(iScene, sDataLocal);
			(*iDstPointer)=pointTemp.c;
			return RETURN_NORMAL;
		}
	default:
		{
			if(sDataLocal.SpanIncluding(_T("0123456789")).CompareNoCase(sDataLocal)==0)
			{
				(*iDstPointer)=_ttoi(sDataLocal);
				return RETURN_NORMAL;
			}
			return RETURN_FAILED;
		}
	}
	return RETURN_FAILED;
}
ReturnValue SetImgValue(ImgRGB* imgRGBDst, int iScene, CStringArray* saDataLocal)
{

	
	int iOperandSrc;
	BOOL bRet = GetOperandDst(saDataLocal->GetAt(0), &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	ImgRGB* pImgRGB=imgRGBDst;

	CString sArg;

	switch(iOperandSrc)
	{
	case VARIABLE_IMG:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}

			if(saDataLocal->GetAt(0).Left(6).CompareNoCase(_T("VarImg"))!=0)
			{
				pImgRGB->Assign(GetStrValue(iScene, saDataLocal->GetAt(0)));
				return RETURN_NORMAL;
			}
			pImgRGB->Assign(GetImgValuePointerConst(iScene, saDataLocal->GetAt(0)));
			return RETURN_NORMAL;
		}
	case VARIABLE_SCREENSHOT:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}

			Screenshot(pImgRGB);
		}
	case VARIABLE_CROP_IMAGE:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}

			ImgRGB* pImgRGBIn=(GetImgValuePointer(iScene, saDataLocal->GetAt(0)));
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			CropImage(pImgRGBIn, pImgRGB, GetIntValue(iScene, saDataLocal->GetAt(1)) , GetIntValue(iScene, saDataLocal->GetAt(2)), GetIntValue(iScene, saDataLocal->GetAt(3)), GetIntValue(iScene, saDataLocal->GetAt(4)));
		}
	}

	return RETURN_FAILED;
}
ReturnValue Flow_Assign(int iScene, CStringArray* saData)
{
	int iOperandFrom;

	BOOL bRet;
	CString sArg;
	CString sDataLocal;
	sDataLocal.Format(_T("%s"), saData->GetAt(1));
	int iOperandDst;
	bRet = GetOperandDst(saData->GetAt(0),&iOperandDst);
	if(bRet != TRUE){return RETURN_FAILED;}

	int iOperandSrc;
	bRet = GetOperandDst(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}
	switch(iOperandDst)
	{
	case VARIABLE_POINT_SET_R:
		{
			return SetIntValue(&((GetPointValuePointer(iScene, saData->GetAt(0)))->r), iScene, sDataLocal);
		}
	case VARIABLE_POINT_SET_C:
		{
			return SetIntValue(&((GetPointValuePointer(iScene, saData->GetAt(0)))->c), iScene, sDataLocal);
		}
	case VARIABLE_INT:
		{
			return SetIntValue((GetIntValuePointer(iScene, saData->GetAt(0))), iScene, sDataLocal);
		}
	case VARIABLE_STR:
		{
			return SetStrValue(GetStrValuePointer(iScene, saData->GetAt(0)),iScene, sDataLocal);
		}
	case VARIABLE_IMG:
		{
			CStringArray saDataLocal;
			for(int i=1; saData->GetCount(); i++){saDataLocal.Add(saData->GetAt(i));}
			return SetImgValue(GetImgValuePointer(iScene, saData->GetAt(0)),iScene, &saDataLocal);
		}
	case VARIABLE_POINT:
		{

			switch(iOperandSrc)
			{
			case VARIABLE_POINT:
				{
					Point* pPoint=(GetPointValuePointer(iScene, saData->GetAt(0)));
					if(pPoint == NULL){return RETURN_FAILED;}

					pPoint=(GetPointValuePointer(iScene, saData->GetAt(1)));
					if(pPoint == NULL){return RETURN_FAILED;}

					(GetPointValuePointer(iScene, saData->GetAt(0)))->Set(pPoint->r, pPoint->c);
				}
			}
			return RETURN_FAILED;
		}

	}

	return RETURN_FAILED;
}