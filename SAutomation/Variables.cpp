#include "stdafx.h"
#include "variables.h"
#include "perser.h"
#include "Common.h"
#include "MouseAutomation.h"
int g_iVar[MAX_THREAD][MAX_VARIABLES];
CString g_sVar[MAX_THREAD][MAX_VARIABLES];
ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];
Point g_point[MAX_THREAD][MAX_VARIABLES];

BOOL GetOperandStrSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("StrCombine"))==0){*iCommandType=VARIABLE_COMBINE_STR; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("Int2Str"))==0){*iCommandType=VARIABLE_INT2STR; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("NowDateTime"))==0){*iCommandType=VARIABLE_NOW_DATE_TIME; return TRUE;}
	*iCommandType=VARIABLE_STR;
	return TRUE;
}

BOOL GetOperandIntSrc(CString sDataLine, int* iCommandType)
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
		if(sDataTrim.GetLength() != 11){return FALSE;}
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}
		if(sDataTrim.Mid(9,1).Compare(_T(",")) != 0){return FALSE;}

		if(sDataTrim.Right(1).CompareNoCase(_T("r"))==0){*iCommandType=VARIABLE_POINT_GET_R; return TRUE;}
		if(sDataTrim.Right(1).CompareNoCase(_T("c"))==0){*iCommandType=VARIABLE_POINT_GET_C; return TRUE;}

		return FALSE;
	}

	return TRUE;
}

BOOL GetOperandImgSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.Left(9).CompareNoCase(_T("CropImage"))==0){*iCommandType=VARIABLE_CROP_IMAGE; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("ScreenShot"))==0){*iCommandType=VARIABLE_SCREENSHOT; return TRUE;}
	if(sDataTrim.Right(4).CompareNoCase(_T(".bmp"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}

	return TRUE;
}
BOOL GetOperandPointSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(5).CompareNoCase(_T("Point")) == 0)
	{
		if(sDataTrim.Mid(5,1).Compare(_T("("))!=0){return FALSE;}
		if(sDataTrim.Right(1).Compare(_T(")"))!=0){return FALSE;}
		*iCommandType=VARIABLE_POINT_DIRECT; 
		return TRUE;
	}
	if(sDataTrim.CompareNoCase(_T("MousePos"))==0){*iCommandType=VARIABLE_POINT_MOUSE_POS; return TRUE;}

	return RETURN_FAILED;
}

BOOL GetOperandDst(CString sDataLine, int* iCommandType, int* iSelfSrc)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0)
	{
		*iCommandType=VARIABLE_INT; 
		if(sDataTrim.Right(1).Compare(_T("+"))==0){*iSelfSrc=VARIABLE_SELF_SRC_ADD;}
		if(sDataTrim.Right(1).Compare(_T("-"))==0){*iSelfSrc=VARIABLE_SELF_SRC_SUB;}
		if(sDataTrim.Right(1).Compare(_T("*"))==0){*iSelfSrc=VARIABLE_SELF_SRC_MULT;}
		if(sDataTrim.Right(1).Compare(_T("/"))==0){*iSelfSrc=VARIABLE_SELF_SRC_DIV;}
		return TRUE;
	}
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
//	if(sArg.Left(1).CompareNoCase(_T("v"))==0) {return GetIntValuePointer(iScene, sArg);}
//	return _ttoi(sArg);
//}


/*
int GetIntValuePointer(int iScene, CString sArg)
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
*/

int* GetIntValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarInt"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarInt%d"), iVarNameB1);

		if(sArg.Right(1).Compare(_T("+"))==0){if(sArg.Left(sArg.GetLength()-1).CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}}
		if(sArg.Right(1).Compare(_T("-"))==0){if(sArg.Left(sArg.GetLength()-1).CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}}
		if(sArg.Right(1).Compare(_T("*"))==0){if(sArg.Left(sArg.GetLength()-1).CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}}
		if(sArg.Right(1).Compare(_T("/"))==0){if(sArg.Left(sArg.GetLength()-1).CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}}

		if(sArg.CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}
	}

	return NULL;
}

/*

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
*/
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

/*
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
*/
int IntAdd(int iScene, CString sArg1, CString sArg2)
{
	int* piSrc;
	int iSrc1;
	int iSrc2;
	
	piSrc = GetIntValuePointer(iScene, sArg1);
	if(piSrc==NULL){iSrc1=_ttoi(sArg1);}else{iSrc1=(*piSrc);}
	piSrc = GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc2=_ttoi(sArg2);}else{iSrc2=(*piSrc);}

	return iSrc1+iSrc2;
}

int IntSub(int iScene, CString sArg1, CString sArg2)
{
	int* piSrc;
	int iSrc1;
	int iSrc2;
	
	piSrc = GetIntValuePointer(iScene, sArg1);
	if(piSrc==NULL){iSrc1=_ttoi(sArg1);}else{iSrc1=(*piSrc);}
	piSrc = GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc2=_ttoi(sArg2);}else{iSrc2=(*piSrc);}

	return iSrc1-iSrc2;
}
int IntMult(int iScene, CString sArg1, CString sArg2)
{
	int* piSrc;
	int iSrc1;
	int iSrc2;
	
	piSrc = GetIntValuePointer(iScene, sArg1);
	if(piSrc==NULL){iSrc1=_ttoi(sArg1);}else{iSrc1=(*piSrc);}
	piSrc = GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc2=_ttoi(sArg2);}else{iSrc2=(*piSrc);}

	return iSrc1*iSrc2;
}

int IntDiv(int iScene, CString sArg1, CString sArg2)
{
	int* piSrc;
	int iSrc1;
	int iSrc2;
	
	piSrc = GetIntValuePointer(iScene, sArg1);
	if(piSrc==NULL){iSrc1=_ttoi(sArg1);}else{iSrc1=(*piSrc);}
	piSrc = GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc2=_ttoi(sArg2);}else{iSrc2=(*piSrc);}

	return iSrc1/iSrc2;
}


BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2)
{
	int* piSrc;
	int iSrc1;
	int iSrc2;
	
	piSrc = GetIntValuePointer(iScene, sArg1);
	if(piSrc==NULL){iSrc1=_ttoi(sArg1);}else{iSrc1=(*piSrc);}
	piSrc = GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc2=_ttoi(sArg2);}else{iSrc2=(*piSrc);}

	return (iSrc1==iSrc2);
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
	int* piDst;
	piDst = GetIntValuePointer(iScene, sArg);
	if(piDst==NULL){return;}
	*piDst=iInput;
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
	int* piSrc;
	int iSrc;
	piSrc = GetIntValuePointer(iScene, sArg);
	if(piSrc==NULL){iSrc=_ttoi(sArg);}else{ iSrc=(*piSrc);}

	CString sOut;

	int iFormat;
	PerseFormat(sFormat, &iFormat);
	switch(iFormat)
	{
	case FORMAT_SPECIFIER_DECIMAL+FORMAT_QUALIFIER_NOTHING+(0x00000000)+(0x00000000)+FORMAT_FLAG_NOTHING:
		{
			sOut.Format(_T("%d"), iSrc);
			break;
		}
	}

	return sOut;
}
int Str2Int(int iScene, CString sArg)
{
	CString sSrc;
	CString* psSrc;
	psSrc=GetStrValuePointer(iScene, sArg);
	if(psSrc==NULL){sSrc.Format(_T("%s"), sArg);}else{sSrc.Format(_T("%s"), *psSrc);}
	return _ttoi(sSrc);
}

const CString StrCombine(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc1, sSrc2;
	CString* psSrc;
	psSrc= GetStrValuePointer(iScene, sArg1);
	if(psSrc==NULL){sSrc1.Format(_T("%s"), sArg1);}else{sSrc1.Format(_T("%s"), *psSrc);}

	psSrc=GetStrValuePointer(iScene, sArg2);
	if(psSrc==NULL){sSrc2.Format(_T("%s"), sArg2);}else{sSrc2.Format(_T("%s"), *psSrc);}

	CString sTemp;
	sTemp.Format(_T("%s%s"),sSrc1,sSrc2);
	return sTemp;
}

const CString StrLeft(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc;
	CString* psSrc;
	psSrc=GetStrValuePointer(iScene, sArg1);
	if(psSrc==NULL){sSrc.Format(_T("%s"), sArg1);}else{sSrc.Format(_T("%s"), *psSrc);}

	int iSrc;
	int* piSrc=GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc=_ttoi(sArg2);}else{ iSrc=(*piSrc);}

	CString sTemp;
	sTemp.Format(_T("%"),sSrc.Left(iSrc));
	return sTemp;
}

const CString StrRight(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc;
	CString* psSrc;
	psSrc=GetStrValuePointer(iScene, sArg1);
	if(psSrc==NULL){sSrc.Format(_T("%s"), sArg1);}else{sSrc.Format(_T("%s"), *psSrc);}

	int iSrc;
	int* piSrc=GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc=_ttoi(sArg2); piSrc=&iSrc;}

	CString sTemp;
	sTemp.Format(_T("%"),sSrc.Right(*piSrc));
	return sTemp;
}

const CString StrMid(int iScene, CString sArg1, CString sArg2, CString sArg3)
{
	CString sSrc;
	CString* psSrc;
	psSrc=GetStrValuePointer(iScene, sArg1);
	if(psSrc==NULL){sSrc.Format(_T("%s"), sArg1);}else{sSrc.Format(_T("%s"), *psSrc);}

	int iSrc1, iSrc2;
	int* piSrc;
	piSrc=GetIntValuePointer(iScene, sArg2);
	if(piSrc==NULL){iSrc1=_ttoi(sArg2);}else{ iSrc1=(*piSrc);}

	piSrc=GetIntValuePointer(iScene, sArg3);
	if(piSrc==NULL){iSrc2=_ttoi(sArg3); }else{ iSrc2=(*piSrc);}

	CString sTemp;
	sTemp.Format(_T("%"),sSrc.Mid(iSrc1, iSrc2));
	return sTemp;
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
	BOOL bRet = GetOperandStrSrc(sDataLocal, &iOperandSrc);
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
			CString* psSrc;
			CString sSrc;
			psSrc=GetStrValuePointer(iScene, sDataLocal);
			if(psSrc==NULL){sSrc.Format(_T("%s"),sDataLocal);}else{sSrc.Format(_T("%s"),*psSrc);}
			sDstPointer->Format(_T("%s"),sSrc);
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

ReturnValue SetIntValue(int* iDstPointer, int iScene, CString sDataLocal, int iSelfSrc)
{	
	int iOperandSrc;
	BOOL bRet = GetOperandIntSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CString sArg;
	int iSrcValue;

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

			iSrcValue=IntAdd(iScene, sArg1, sArg2);
			break;
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

			iSrcValue=IntSub(iScene, sArg1, sArg2);
			break;
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
			
			iSrcValue=IntMult(iScene, sArg1, sArg2);
			break;
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
			
			iSrcValue=IntDiv(iScene, sArg1, sArg2);
			break;
		}
	case VARIABLE_INT:
		{
			int iSrc;
			int* piSrc;

			piSrc=GetIntValuePointer(iScene, sDataLocal);
				if(piSrc==NULL){iSrc=_ttoi(sArg);}else{ iSrc=(*piSrc);}

			iSrcValue=iSrc;
			break;
		}
	case VARIABLE_POINT_GET_R:
		{
			Point* pPointSrc = GetPointValuePointer(iScene, sDataLocal);
			iSrcValue=pPointSrc->r;
			break;
		}
	case VARIABLE_POINT_GET_C:
		{
			Point* pPointSrc = GetPointValuePointer(iScene, sDataLocal);
			iSrcValue=pPointSrc->c;
			break;
		}
	case VARIABLE_IMG_WIDTH:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			ImgRGB* pimgRGB = GetImgValuePointer(iScene, sArg);
			if(pimgRGB == NULL){return RETURN_FAILED;}
			
			iSrcValue=pimgRGB->iWidth;
			break;
		}
	case VARIABLE_IMG_HEIGHT:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			ImgRGB* pimgRGB = GetImgValuePointer(iScene, sArg);
			if(pimgRGB == NULL){return RETURN_FAILED;}
			
			iSrcValue=pimgRGB->iHeight;
			break;
		}
	default:
		{
			if(sDataLocal.SpanIncluding(_T("0123456789")).CompareNoCase(sDataLocal)==0)
			{
				iSrcValue=_ttoi(sDataLocal);
				break;
			}
			return RETURN_FAILED;
		}
	}

	int iTemp=(*iDstPointer); 
	switch(iSelfSrc)
	{
	case VARIABLE_SELF_SRC_NONE:{(*iDstPointer)=iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_ADD:{(*iDstPointer)=iTemp+iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_SUB:{(*iDstPointer)=iTemp-iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_MULT:{(*iDstPointer)=iTemp*iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_DIV:{(*iDstPointer)=iTemp/iSrcValue; return RETURN_NORMAL;}
	}

	return RETURN_FAILED;
}
ReturnValue SetImgValue(ImgRGB* imgRGBDst, int iScene, CString sData)
{

	CStringArray saData;
	saData.RemoveAll();
	CString sArg;
	CString sDataLocal;

	ExtractData(sData, _T("("), &sArg, &sDataLocal);

	int iOperandSrc;
	BOOL bRet = GetOperandImgSrc(sArg, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}


	ImgRGB* pImgRGB=imgRGBDst;


	switch(iOperandSrc)
	{
	case VARIABLE_IMG:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}

			if(sArg.Left(6).CompareNoCase(_T("VarImg"))!=0)
			{
				CString sSrc;
				CString* psSrc=GetStrValuePointer(iScene, sArg);
			if(psSrc==NULL){sSrc.Format(_T("%s"),sArg);}else{sSrc.Format(_T("%s"),*psSrc);}

				pImgRGB->Assign(sSrc);
				return RETURN_NORMAL;
			}
			pImgRGB->Assign(GetImgValuePointerConst(iScene, sArg));
			return RETURN_NORMAL;
		}
	case VARIABLE_SCREENSHOT:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}

			Screenshot(pImgRGB);
			return RETURN_NORMAL;
		}
	case VARIABLE_CROP_IMAGE:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}


			ExtractData(sData, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData.Add(sArg);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData.Add(sArg);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData.Add(sArg);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData.Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData.Add(sArg);
			if(saData.GetCount()<4){return RETURN_FAILED;}

			ImgRGB* pImgRGBIn=(GetImgValuePointer(iScene, saData.GetAt(0)));
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			int iSrc1, iSrc2, iSrc3, iSrc4;
			int* piSrc;
			piSrc=GetIntValuePointer(iScene, saData.GetAt(1));
			if(piSrc==NULL){iSrc1=_ttoi( saData.GetAt(1)); }else{iSrc1=(*piSrc);}

			piSrc=GetIntValuePointer(iScene, saData.GetAt(2));
			if(piSrc==NULL){iSrc2=_ttoi( saData.GetAt(2));} else{iSrc2=(*piSrc);}

			piSrc=GetIntValuePointer(iScene, saData.GetAt(3));
			if(piSrc==NULL){iSrc3=_ttoi( saData.GetAt(3)); }else{iSrc3=(*piSrc);}

			piSrc=GetIntValuePointer(iScene, saData.GetAt(4));
			if(piSrc==NULL){iSrc4=_ttoi( saData.GetAt(4)); }else{iSrc4=(*piSrc);}

			CropImage(pImgRGBIn, pImgRGB, iSrc1, iSrc2, iSrc3, iSrc4 );
			return RETURN_NORMAL;
		}
	}

	return RETURN_FAILED;
}

ReturnValue SetPointValue(Point* pPoint, int iScene, CString sDataLocal)
{
	int iOperandSrc;
	BOOL bRet;
	bRet = GetOperandPointSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iOperandSrc)
	{
	case VARIABLE_POINT:
		{
			Point* pPointSrc=(GetPointValuePointer(iScene, sDataLocal));
			if(pPointSrc == NULL){return RETURN_FAILED;}

			pPoint->Set(pPointSrc->r, pPointSrc->c);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_DIRECT:
		{
			CString sArg;
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg1, &sDataLocal);
			ExtractData(sDataLocal, _T(")"), &sArg2, &sDataLocal);

			int iSrc1, iSrc2;
			int* piSrc;
			piSrc=GetIntValuePointer(iScene, sArg1);
			if(piSrc==NULL){iSrc1=_ttoi(sArg1);}else{iSrc1=(*piSrc);}
			piSrc=GetIntValuePointer(iScene, sArg2);
			if(piSrc==NULL){iSrc2=_ttoi(sArg2);}else{iSrc2=(*piSrc);}
			pPoint->Set(iSrc1, iSrc2);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_MOUSE_POS:
		{

			pPoint->Set(g_iR, g_iC);

			return RETURN_NORMAL;
		}
	}
	return RETURN_FAILED;
}
ReturnValue Flow_Assign(int iScene, CStringArray* saData)
{
	BOOL bRet;
	int iOperandDst = VARIABLE_UNDEFINED;
	int iSelfSrc=VARIABLE_SELF_SRC_NONE;
	bRet = GetOperandDst(saData->GetAt(0),&iOperandDst, &iSelfSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iOperandDst)
	{
	case VARIABLE_POINT_SET_R:
		{
			Point* pPointDst = GetPointValuePointer(iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetIntValue(&(pPointDst->r), iScene, saData->GetAt(1),iSelfSrc);
		}
	case VARIABLE_POINT_SET_C:
		{
			Point* pPointDst = GetPointValuePointer(iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetIntValue(&(pPointDst->c), iScene, saData->GetAt(1),iSelfSrc);
		}
	case VARIABLE_INT:
		{
			int* piDst = GetIntValuePointer(iScene, saData->GetAt(0));
			if(piDst == NULL){return RETURN_FAILED;}
			return SetIntValue(piDst, iScene, saData->GetAt(1),iSelfSrc);
		}
	case VARIABLE_STR:
		{
			CString* psDst=GetStrValuePointer(iScene, saData->GetAt(0));
			if(psDst == NULL){return RETURN_FAILED;}
			return SetStrValue(psDst,iScene, saData->GetAt(1));
		}
	case VARIABLE_IMG:
		{
			ImgRGB* pImgRGBDst = GetImgValuePointer(iScene, saData->GetAt(0));
			if(pImgRGBDst == NULL){return RETURN_FAILED;}
			return SetImgValue(pImgRGBDst,iScene, saData->GetAt(1));
		}
	case VARIABLE_POINT:
		{
			Point* pPointDst = GetPointValuePointer(iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetPointValue(pPointDst, iScene, saData->GetAt(1));
		}
	default:{return RETURN_FAILED;}
	}

	return RETURN_FAILED;
}