#include "stdafx.h"
#include "variables.h"

#include "perser.h"
#include "Window.h"
#include "Variables_Int.h"

BOOL GetOperandIntSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(5).CompareNoCase(_T("Input"))==0){*iCommandType=VARIABLE_INPUT; return TRUE;}

	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("AddInt"))==0){*iCommandType=VARIABLE_ADD_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("SubInt"))==0){*iCommandType=VARIABLE_SUB_INT; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("MultInt"))==0){*iCommandType=VARIABLE_MULT_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("DivInt"))==0){*iCommandType=VARIABLE_DIV_INT; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("DlgItem"))==0){*iCommandType=VARIABLE_DLG_ITEM; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("ForegroundWindow"))==0){*iCommandType=VARIABLE_INT_FOREGROUND_WINDOW; return TRUE;}
	if(sDataTrim.SpanIncluding(_T("-0123456789")).CompareNoCase(sDataTrim)==0){*iCommandType = VARIABLE_INT; return TRUE;}
	
	if(sDataTrim.Right(3).CompareNoCase(_T("sec"))==0){*iCommandType=VARIABLE_STR2INT; return TRUE;}
	if(sDataTrim.Right(3).CompareNoCase(_T("min"))==0){*iCommandType=VARIABLE_STR2INT; return TRUE;}
	if(sDataTrim.Right(4).CompareNoCase(_T("hour"))==0){*iCommandType=VARIABLE_STR2INT; return TRUE;}
	if(sDataTrim.Right(3).CompareNoCase(_T("day"))==0){*iCommandType=VARIABLE_STR2INT; return TRUE;}

	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		if(sDataTrim.GetLength() != 11){return FALSE;}
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}
		if(sDataTrim.Mid(9,1).Compare(_T(".")) != 0){return FALSE;}

		if(sDataTrim.Right(1).CompareNoCase(_T("r"))==0){*iCommandType=VARIABLE_POINT_GET_R; return TRUE;}
		if(sDataTrim.Right(1).CompareNoCase(_T("c"))==0){*iCommandType=VARIABLE_POINT_GET_C; return TRUE;}

		return FALSE;
	}
	if(sDataTrim.Left(7).CompareNoCase(_T("VarRect"))==0)
	{
		if(sDataTrim.Mid(8,1).Compare(_T(".")) != 0){return FALSE;}
		if(sDataTrim.Right(5).CompareNoCase(_T("Width"))==0){*iCommandType=VARIABLE_RECT_WIDTH; return TRUE;}
		if(sDataTrim.Right(6).CompareNoCase(_T("Height"))==0){*iCommandType=VARIABLE_RECT_HEIGHT; return TRUE;}
		if(sDataTrim.Right(4).CompareNoCase(_T("Left"))==0){*iCommandType=VARIABLE_RECT_LEFT; return TRUE;}
		if(sDataTrim.Right(3).CompareNoCase(_T("TOP"))==0){*iCommandType=VARIABLE_RECT_TOP; return TRUE;}
		if(sDataTrim.Right(5).CompareNoCase(_T("Right"))==0){*iCommandType=VARIABLE_RECT_RIGHT; return TRUE;}
		if(sDataTrim.Right(6).CompareNoCase(_T("BOTTOM"))==0){*iCommandType=VARIABLE_RECT_BOTTOM; return TRUE;}

	}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0)
	{
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}
		if(sDataTrim.Mid(9,1).Compare(_T(".")) != 0){return FALSE;}

		if(sDataTrim.Right(5).CompareNoCase(_T("Width"))==0){*iCommandType=VARIABLE_IMG_WIDTH; return TRUE;}
		if(sDataTrim.Right(6).CompareNoCase(_T("Height"))==0){*iCommandType=VARIABLE_IMG_HEIGHT; return TRUE;}
		if((sDataTrim.Mid(10,6).Compare(_T("Value(")) == 0) && sDataTrim.Right(1).CompareNoCase(_T(")"))==0){*iCommandType = VARIABLE_IMG_VALUE; return TRUE;}
		return FALSE;
	}
	
	if(sDataTrim.Left(3).CompareNoCase(_T("Len"))==0){*iCommandType=VARIABLE_STR_LEN; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("Str2Int"))==0){*iCommandType=VARIABLE_STR2INT; return TRUE;}
	return FALSE;
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
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0){*iCommandType=VARIABLE_POINT; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("MousePos"))==0){*iCommandType=VARIABLE_POINT_MOUSE_POS; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("ObjectCenter"))==0){*iCommandType=VARIABLE_POINT_OBJECT_CENTER; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("SearchResult"))==0){*iCommandType=VARIABLE_POINT_SEARCH_RESULT; return TRUE;}
	if(sDataTrim.Left(18).CompareNoCase(_T("ForegroundWindowLU"))==0){*iCommandType=VARIABLE_POINT_FOREGROUND_WINDOW_LU; return TRUE;}
	if(sDataTrim.Left(18).CompareNoCase(_T("ForegroundWindowRD"))==0){*iCommandType=VARIABLE_POINT_FOREGROUND_WINDOW_RD; return TRUE;}

	return FALSE;
}

BOOL GetOperandRectSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));


	if(sDataTrim.Left(7).CompareNoCase(_T("VarRect"))==0){*iCommandType=VARIABLE_RECT; return TRUE;}
	if(sDataTrim.Left(16).CompareNoCase(_T("ForegroundWindow"))==0){*iCommandType=VARIABLE_RECT_FOREGROUND_WINDOW; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("DlgItem"))==0){*iCommandType=VARIABLE_RECT_DLG_ITEM; return TRUE;}

	return FALSE;
}


int GetIntValue(CString sDir, int iScene, CString sDataLocal)
{
	int iOperandSrc;
	BOOL bRet = GetOperandIntSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return 0;}

	CString sArg;

	switch(iOperandSrc)
	{
	case VARIABLE_ADD_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntAdd(sDir, iScene, sArg1, sArg2);
		}
	case VARIABLE_SUB_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntSub(sDir, iScene, sArg1, sArg2);
		}
	case VARIABLE_MULT_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntMult(sDir, iScene, sArg1, sArg2);
		}
	case VARIABLE_DIV_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntDiv(sDir, iScene, sArg1, sArg2);
		}
	case VARIABLE_INT:
		{
			int iSrc;
			int* piSrc;

			piSrc=GetIntValuePointer(sDir, iScene, sDataLocal);
			if(piSrc==NULL){iSrc=_wtoi(sDataLocal);}else{ iSrc=(*piSrc);LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);}

			return iSrc;
		}
	case VARIABLE_POINT_GET_R:
		{
			Point pointSrc;
			bRet =  GetPointValue(sDir, iScene, sDataLocal, &pointSrc);
			if(bRet != TRUE){return 0;}

			return pointSrc.r;
		}
	case VARIABLE_POINT_GET_C:
		{
			Point pointSrc;
			bRet =  GetPointValue(sDir, iScene, sDataLocal, &pointSrc);
			if(bRet != TRUE){return 0;}

			return pointSrc.c;
		}
	case VARIABLE_IMG_WIDTH:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			ImgRGB* pimgRGB = GetImgValuePointer(sDir, iScene, sArg);			
			if(pimgRGB == NULL){iSrc=0;} else{iSrc=pimgRGB->iWidth;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}
	case VARIABLE_IMG_HEIGHT:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			ImgRGB* pimgRGB = GetImgValuePointer(sDir, iScene, sArg);
			if(pimgRGB == NULL){iSrc=0;} else{iSrc=pimgRGB->iHeight;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}
		
	case VARIABLE_RECT_WIDTH:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			CRect rect;
			bRet = GetRectValue(sDir, iScene, sArg, &rect);			
			if(bRet == FALSE){iSrc=0;} else{iSrc=rect.Width();}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}
	case VARIABLE_RECT_HEIGHT:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			CRect rect;
			bRet = GetRectValue(sDir, iScene, sArg, &rect);			
			if(bRet == FALSE){iSrc=0;} else{iSrc=rect.Height();}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}		
	case VARIABLE_RECT_LEFT:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			CRect rect;
			bRet = GetRectValue(sDir, iScene, sArg, &rect);			
			if(bRet == FALSE){iSrc=0;} else{iSrc=rect.left;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}		
	case VARIABLE_RECT_TOP:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			CRect rect;
			bRet = GetRectValue(sDir, iScene, sArg, &rect);			
			if(bRet == FALSE){iSrc=0;} else{iSrc=rect.top;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}		
	case VARIABLE_RECT_RIGHT:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			CRect rect;
			bRet = GetRectValue(sDir, iScene, sArg, &rect);			
			if(bRet == FALSE){iSrc=0;} else{iSrc=rect.right;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}		
	case VARIABLE_RECT_BOTTOM:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			CRect rect;
			bRet = GetRectValue(sDir, iScene, sArg, &rect);			
			if(bRet == FALSE){iSrc=0;} else{iSrc=rect.bottom;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}
	case VARIABLE_IMG_VALUE:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);
			ImgRGB* pimgRGB = GetImgValuePointer(sDir, iScene, sArg);
			if(pimgRGB == NULL){return 0;}

			int iTokenNum;
			CountTokenInBracket(sDataLocal, &iTokenNum);

			if(iTokenNum==3)
			{
				CString sR, sC;
				ExtractTokenInBracket(sDataLocal,0,&sC);
				ExtractTokenInBracket(sDataLocal,1,&sR);
				int iR, iC;
				iC=GetIntValue(sDir, iScene, sC);
				iR=GetIntValue(sDir, iScene, sR);

				CString sColorTemp;
				ExtractTokenInBracket(sDataLocal,2,&sColorTemp);
				CString sColor;
				sColor.Format(_T("%s"), GetStrValue(sDir, iScene, sColorTemp));

				int iValueR, iValueG, iValueB;
				GetValue(pimgRGB, iR, iC,&iValueR, &iValueG, &iValueB);
				if(sColor.CompareNoCase(_T("R"))==0){LOG_OUTPUT_INT(iScene, sDataLocal, iValueR);return iValueR;}
				if(sColor.CompareNoCase(_T("G"))==0){LOG_OUTPUT_INT(iScene, sDataLocal, iValueG);return iValueG;}
				if(sColor.CompareNoCase(_T("B"))==0){LOG_OUTPUT_INT(iScene, sDataLocal, iValueB);return iValueB;}
			}
			else if(iTokenNum==5)
			{
				CString sArg;
				int iC1;
				int iR1;
				int iC2;
				int iR2;
				ExtractTokenInBracket(sDataLocal,0,&sArg);
				iC1=GetIntValue(sDir, iScene, sArg);
				ExtractTokenInBracket(sDataLocal,1,&sArg);
				iR1=GetIntValue(sDir, iScene, sArg);
				ExtractTokenInBracket(sDataLocal,2,&sArg);
				iC2=GetIntValue(sDir, iScene, sArg);
				ExtractTokenInBracket(sDataLocal,3,&sArg);
				iR2=GetIntValue(sDir, iScene, sArg);

				CString sColorTemp;
				ExtractTokenInBracket(sDataLocal,4,&sColorTemp);
				CString sColor;
				sColor.Format(_T("%s"), GetStrValue(sDir, iScene, sColorTemp));

				double dValueR, dValueG, dValueB;
				GetValueInRegion(pimgRGB, iR1, iC1, iR2, iC2, &dValueR, &dValueG, &dValueB);
				int iValueR, iValueG, iValueB;
				iValueR=int(dValueR+0.5);
				iValueG=int(dValueG+0.5);
				iValueB=int(dValueB+0.5);
				if(sColor.CompareNoCase(_T("R"))==0){LOG_OUTPUT_INT(iScene, sDataLocal, iValueR);return iValueR;}
				if(sColor.CompareNoCase(_T("G"))==0){LOG_OUTPUT_INT(iScene, sDataLocal, iValueG);return iValueG;}
				if(sColor.CompareNoCase(_T("B"))==0){LOG_OUTPUT_INT(iScene, sDataLocal, iValueB);return iValueB;}
			}
			return 0;
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
			return _wtoi(g_cInput.m_sReturnValue);
		}
	case VARIABLE_DLG_ITEM:
		{
			CString sText;
			int iRank;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			sText.Format(_T("%s"), GetStrValue(sDir, iScene,sArg));

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()<=0){iRank=0;}
			else{iRank=GetIntValue(sDir, iScene,sArg);}

			return GetDlgItem_My(sText, iRank);
		}
	case VARIABLE_INT_FOREGROUND_WINDOW:
		{
			HWND hwnd = GetForegroundWindow();

			return (int)hwnd;
		}
	case VARIABLE_STR_LEN:
		{
			CString sText;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			sText.Format(_T("%s"), GetStrValue(sDir, iScene,sArg));
			
			return sText.GetLength();
		}
	case VARIABLE_STR2INT:
		{
			CString sText;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			CString sSrc;
			sSrc.Format(_T("%s"),GetStrValue(sDir, iScene, sArg));
			return ConvertStr2Int(sSrc);
		}
	default:
		{
			if(sDataLocal.SpanIncluding(_T("-0123456789")).CompareNoCase(sDataLocal)==0)
			{
				return _wtoi(sDataLocal);
			}
			return 0;
		}
	}
	return 0;
}

int ConvertStr2Int(CString sSrc)
{
	if(sSrc.Right(3).CompareNoCase(_T("sec"))==0){return(_wtoi(sSrc.Left(sSrc.GetLength()-3)) *1000);}
	if(sSrc.Right(3).CompareNoCase(_T("min"))==0){return(_wtoi(sSrc.Left(sSrc.GetLength()-3)) *1000*60);}
	if(sSrc.Right(4).CompareNoCase(_T("hour"))==0){return(_wtoi(sSrc.Left(sSrc.GetLength()-4)) *1000*60*60);}
	if(sSrc.Right(3).CompareNoCase(_T("day"))==0){return(_wtoi(sSrc.Left(sSrc.GetLength()-3)) *1000*60*60*24);}
	return _wtoi(sSrc);
}



int* GetIntValuePointer(CString sDir, int iScene, CString sArg)
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

CRect* GetRectValuePointer(CString sDir, int iScene, CString sArg)
{
	if(sArg.Left(7).CompareNoCase(_T("VarRect"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarRect%d"), iVarNameB1);
		if(sArg.Left(sVarName.GetLength()).CompareNoCase(sVarName)==0){return &(g_rect[iScene][iVarNameB1-1]);}
	}

	return NULL;
}

BOOL GetRectValue(CString sDir, int iScene, CString sArg, CRect* rectOutput)
{
	int iOperandSrc;
	rectOutput->SetRect(0,0,0,0);
	BOOL bRet = GetOperandRectSrc(sArg, &iOperandSrc);
	if(bRet != TRUE){return FALSE;}


	switch(iOperandSrc)
	{
	case VARIABLE_RECT:
		{
			CRect* pRect;
			pRect = GetRectValuePointer(sDir, iScene, sArg);
			rectOutput->CopyRect(pRect);
			return TRUE;
		}
	case VARIABLE_RECT_FOREGROUND_WINDOW:
		{
			int iLeft;
			int iTop; 
			int iWidth;
			int iHeight;
			BOOL bRet = GetForegroundWindowPos(&iLeft, &iTop, &iWidth,  &iHeight);
			rectOutput->SetRect( iLeft, iTop, iLeft+iWidth-1, iTop+iHeight-1);
			return TRUE;
		}
	case VARIABLE_RECT_DLG_ITEM:
		{

			CString sText;
			int iRank;
			CString sArgID;
			CString sArgRank;
			ExtractTokenInBracket(sArg,0,&sArgID);

			if(sArgID.Left(6).CompareNoCase(_T("VarInt"))==0)
			{
				int iItem = GetIntValue(sDir, iScene, sArgID);
				GetWindowRect_My(iItem,rectOutput);
				return TRUE;
			}

			sText.Format(_T("%s"), GetStrValue(sDir, iScene,sArgID));

			ExtractTokenInBracket(sArgID,1,&sArgRank);
			if(sArg.GetLength()<=0){iRank=0;}
			else{iRank=GetIntValue(sDir, iScene,sArg);}
			int iItem = GetDlgItem_My(sText, iRank);

			GetWindowRect_My(iItem,rectOutput);
			return TRUE;
		}
	default:
		{
		}
	}

	return FALSE;
}




int IntAdd(CString sDir, int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(sDir, iScene, sArg1);
	int iSrc2=GetIntValue(sDir, iScene, sArg2);

	return iSrc1+iSrc2;
}

int IntSub(CString sDir, int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(sDir, iScene, sArg1);
	int iSrc2=GetIntValue(sDir, iScene, sArg2);

	return iSrc1-iSrc2;
}
int IntMult(CString sDir, int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(sDir, iScene, sArg1);
	int iSrc2=GetIntValue(sDir, iScene, sArg2);

	return iSrc1*iSrc2;
}

int IntDiv(CString sDir, int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(sDir, iScene, sArg1);
	int iSrc2=GetIntValue(sDir, iScene, sArg2);

	return iSrc1/iSrc2;
}


ReturnValue SetIntValue(CString sDir, int iScene, int* iDstPointer, CString sDataLocal, int iSelfSrc)
{	
	int iOperandSrc;
	BOOL bRet = GetOperandIntSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CString sArg;
	int iSrcValue=GetIntValue(sDir, iScene, sDataLocal);

	switch(iSelfSrc)
	{
	case VARIABLE_SELF_SRC_NONE:{(*iDstPointer) = iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_ADD:{(*iDstPointer) += iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_SUB:{(*iDstPointer) -= iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_MULT:{(*iDstPointer) *= iSrcValue; return RETURN_NORMAL;}
	case VARIABLE_SELF_SRC_DIV:{(*iDstPointer) /= iSrcValue; return RETURN_NORMAL;}
	}

	return RETURN_FAILED;
}



BOOL GetPointValue(CString sDir, int iScene, CString sDataLocal, Point* pPoint)
{
	int iOperandSrc;
	BOOL bRet;
	bRet = GetOperandPointSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return FALSE;}

	switch(iOperandSrc)
	{
	case VARIABLE_POINT:
		{
			Point* pPointSrc=(GetPointValuePointer(sDir, iScene, sDataLocal));
			if(pPointSrc == NULL){return RETURN_FAILED;}

			pPoint->Set( pPointSrc->c,pPointSrc->r);
			return TRUE;
		}
	case VARIABLE_POINT_DIRECT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			int iSrc1=GetIntValue(sDir, iScene, sArg1);
			int iSrc2=GetIntValue(sDir, iScene, sArg2);

			pPoint->Set(iSrc1, iSrc2);
			return TRUE;
		}
	case VARIABLE_POINT_MOUSE_POS:
		{

			pPoint->Set(g_iC,g_iR);

			return TRUE;
		}
	case VARIABLE_POINT_OBJECT_CENTER:
		{

			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			Object* objSrc;
			objSrc=GetObjValuePointer(sDir, iScene, sArg1);
			int iLength;
			iLength=objSrc->m_uiMaxLabel+1;
			double* dA;
			double* dR;
			double* dC;
			dA=new double[iLength];
			dR=new double[iLength];
			dC=new double[iLength];


			AreaCenter(objSrc, dA, dR, dC, iLength);

			pPoint->Set((int)(dR[0]), (int)(dC[0]));

			SAFE_DELETE(dA);
			SAFE_DELETE(dR);
			SAFE_DELETE(dC);
			return TRUE;
		}
	case VARIABLE_POINT_FOREGROUND_WINDOW_LU:
		{
			int iLeft;
			int iTop; 
			int iWidth;
			int iHeight;
			BOOL bRet = GetForegroundWindowPos(&iLeft, &iTop, &iWidth,  &iHeight);
			pPoint->Set(iLeft,iTop);
			return TRUE;
		}
	case VARIABLE_POINT_FOREGROUND_WINDOW_RD:
		{
			int iLeft;
			int iTop; 
			int iWidth;
			int iHeight;
			BOOL bRet = GetForegroundWindowPos(&iLeft, &iTop, &iWidth,  &iHeight);
			pPoint->Set(iLeft+iWidth-1,iTop+iHeight-1);
			return TRUE;
		}
	case VARIABLE_POINT_SEARCH_RESULT:
		{

			BOOL bRet;
			CString sModelFilePath;
			int iR0, iC0, iR1, iC1;

			CString sArg;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			CString sModel;
			sModel.Format(_T("%s"), GetStrValue(sDir, iScene, sArg));
			GetModelFilePath(sDir, sModel, &sModelFilePath);

			CString sC0, sR0, sC1, sR1;
			ExtractTokenInBracket(sDataLocal,1,&sC0);
			ExtractTokenInBracket(sDataLocal,2,&sR0);
			ExtractTokenInBracket(sDataLocal,3,&sC1);
			ExtractTokenInBracket(sDataLocal,4,&sR1);

			iC0=GetIntValue(sDir, iScene, sC0);
			iR0=GetIntValue(sDir, iScene, sR0);
			iC1=GetIntValue(sDir, iScene, sC1);
			iR1=GetIntValue(sDir, iScene, sR1);

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

			Screenshot(&imgTarget);
			if(bUseMask==TRUE)
			{
				bRet = IsInRegionMask(&imgTarget, &imgModel, &imgMask, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, &iFoundR, &iFoundC);
			}
			else
			{
				bRet = IsInRegion(&imgTarget, &imgModel, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, &iFoundR, &iFoundC);
			}
			//	bRet = FindModelPyramid(&imgTarget, &imgModel, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, 80, &iFoundR, &iFoundC);

			if(bRet != TRUE){return FALSE;}
			pPoint->Set(iFoundC, iFoundR);


			return TRUE;
		}
	}
	return FALSE;
}




Point* GetPointValuePointer(CString sDir, int iScene, CString sArg)
{
	if(sArg.Left(8).CompareNoCase(_T("VarPoint"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarPoint%d"), iVarNameB1);
		if(sArg.Left(sVarName.GetLength()).CompareNoCase(sVarName)==0){return &(g_point[iScene][iVarNameB1-1]);}
	}

	return NULL;
}

ReturnValue SetRectValue(CString sDir, int iScene, CRect* pRect, CString sDataLocal)
{
	int iOperandSrc;
	BOOL bRet;
	bRet = GetOperandRectSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CRect rectSrc;
	bRet = (GetRectValue(sDir, iScene, sDataLocal, &rectSrc));
	if(bRet != TRUE){return RETURN_FAILED;}

	pRect->CopyRect(&rectSrc);
	return RETURN_NORMAL;

}

ReturnValue SetPointValue(CString sDir, int iScene, Point* pPoint, CString sDataLocal)
{
	int iOperandSrc;
	BOOL bRet;
	bRet = GetOperandPointSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	Point pointSrc;
	bRet = (GetPointValue(sDir, iScene, sDataLocal, &pointSrc));
	if(bRet != TRUE){return RETURN_FAILED;}

	pPoint->Set(pointSrc.c, pointSrc.r);
	return RETURN_NORMAL;
}