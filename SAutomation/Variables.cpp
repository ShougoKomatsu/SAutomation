#include "stdafx.h"
#include "variables.h"
#include "perser.h"
#include "Common.h"
#include "MouseAutomation.h"
#include "InputDialog.h"
#include "ClipBoard.h"

#include "Window.h"
int g_iVar[MAX_THREAD][MAX_VARIABLES];
CString g_sVar[MAX_THREAD][MAX_VARIABLES];
ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];
Point g_point[MAX_THREAD][MAX_VARIABLES];
Object g_object[MAX_THREAD][MAX_VARIABLES];
Camera g_camera;

BOOL GetOperandObjSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));

	if(sDataTrim.Left(5).CompareNoCase(_T("VarObj"))==0){*iCommandType=VARIABLE_OBJECT; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("Threshold"))==0){*iCommandType=VARIABLE_OBJECT_THRESHLD; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("Connection"))==0){*iCommandType=VARIABLE_OBJECT_CONNECTION; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("SelectShape"))==0){*iCommandType=VARIABLE_OBJECT_SELECT_SHAPE; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("SelectObj"))==0){*iCommandType=VARIABLE_OBJECT_SELECT_OBJ; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("SortRegion"))==0){*iCommandType=VARIABLE_OBJECT_SORT_REGION; return TRUE;}
	if(sDataTrim.Left(13).CompareNoCase(_T("GenRectangle1"))==0){*iCommandType=VARIABLE_OBJECT_GEN_RECTANGLE1; return TRUE;}

	*iCommandType=VARIABLE_OBJECT;
	return TRUE;
}

BOOL GetOperandCameraSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.Left(9).CompareNoCase(_T("VarCamera"))==0){*iCommandType=VARIABLE_CAMERA; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("OpenCamera"))==0){*iCommandType=VARIABLE_CAMERA_OPEN; return TRUE;}
	if(sDataTrim.Left(11).CompareNoCase(_T("CloseCamera"))==0){*iCommandType=VARIABLE_CAMERA_CLOSE; return TRUE;}
	if(sDataTrim.Left(4).CompareNoCase(_T("Grab"))==0){*iCommandType=VARIABLE_CAMERA_GRAB; return TRUE;}

	*iCommandType=VARIABLE_CAMERA;
	return TRUE;
}

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
	if(sDataTrim.SpanIncluding(_T("-0123456789")).CompareNoCase(sDataTrim)==0){*iCommandType = VARIABLE_INT; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		if(sDataTrim.GetLength() != 11){return FALSE;}
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}
		if(sDataTrim.Mid(9,1).Compare(_T(".")) != 0){return FALSE;}

		if(sDataTrim.Right(1).CompareNoCase(_T("r"))==0){*iCommandType=VARIABLE_POINT_GET_R; return TRUE;}
		if(sDataTrim.Right(1).CompareNoCase(_T("c"))==0){*iCommandType=VARIABLE_POINT_GET_C; return TRUE;}

		return FALSE;
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

	return FALSE;
}

BOOL GetOperandImgSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.CompareNoCase(_T("ClipBoard"))==0){*iCommandType=VARIABLE_CLIPBOARD; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("CropImage"))==0){*iCommandType=VARIABLE_CROP_IMAGE; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("ReduceDomain"))==0){*iCommandType=VARIABLE_IMG_REDUCE_DOMAIN; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("ScreenShot"))==0){*iCommandType=VARIABLE_SCREENSHOT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("Decompose3"))==0){*iCommandType=VARIABLE_IMG_DECOMPOSE; return TRUE;}
	if(sDataTrim.Right(4).CompareNoCase(_T(".bmp"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("VarCamera"))==0){*iCommandType=VARIABLE_CAMERA_GRAB; return TRUE;}
	
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
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0){*iCommandType=VARIABLE_POINT; return TRUE;}
	if(sDataTrim.CompareNoCase(_T("MousePos"))==0){*iCommandType=VARIABLE_POINT_MOUSE_POS; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("ObjectCenter"))==0){*iCommandType=VARIABLE_POINT_OBJECT_CENTER; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("SearchResult"))==0){*iCommandType=VARIABLE_POINT_SEARCH_RESULT; return TRUE;}
	if(sDataTrim.Left(18).CompareNoCase(_T("ForegroundWindowLU"))==0){*iCommandType=VARIABLE_POINT_FOREGROUND_WINDOW_LU; return TRUE;}
	if(sDataTrim.Left(18).CompareNoCase(_T("ForegroundWindowRD"))==0){*iCommandType=VARIABLE_POINT_FOREGROUND_WINDOW_RD; return TRUE;}

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
	if(sDataTrim.Left(9).CompareNoCase(_T("VarCamera"))==0){*iCommandType=VARIABLE_CAMERA; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("ClipBoard"))==0){*iCommandType=VARIABLE_CLIPBOARD; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarObj"))==0){*iCommandType=VARIABLE_OBJECT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarStr"))==0){*iCommandType=VARIABLE_STR; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("VarImg"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		if(sDataTrim.Mid(8,1).SpanIncluding(_T("01234567")).Compare(sDataTrim.Mid(8,1))!=0){return FALSE;}

		if(sDataTrim.Right(1).CompareNoCase(_T("r"))==0){*iCommandType=VARIABLE_POINT_SET_R; return TRUE;}
		if(sDataTrim.Right(1).CompareNoCase(_T("c"))==0){*iCommandType=VARIABLE_POINT_SET_C; return TRUE;}
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


int GetIntValue(int iScene, CString sDataLocal)
{
	int iOperandSrc;
	BOOL bRet = GetOperandIntSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CString sArg;

	switch(iOperandSrc)
	{
	case VARIABLE_ADD_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntAdd(iScene, sArg1, sArg2);
		}
	case VARIABLE_SUB_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntSub(iScene, sArg1, sArg2);
		}
	case VARIABLE_MULT_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntMult(iScene, sArg1, sArg2);
		}
	case VARIABLE_DIV_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			return IntDiv(iScene, sArg1, sArg2);
		}
	case VARIABLE_INT:
		{
			int iSrc;
			int* piSrc;

			piSrc=GetIntValuePointer(iScene, sDataLocal);
			if(piSrc==NULL){iSrc=_ttoi(sDataLocal);}else{ iSrc=(*piSrc);LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);}

			return iSrc;
		}
	case VARIABLE_POINT_GET_R:
		{
			Point* pPointSrc = GetPointValuePointer(iScene, sDataLocal);
			if(pPointSrc==NULL){return 0;}
			LOG_OUTPUT_POINT(iScene, sDataLocal, pPointSrc);
			return pPointSrc->r;
		}
	case VARIABLE_POINT_GET_C:
		{
			Point* pPointSrc = GetPointValuePointer(iScene, sDataLocal);
			if(pPointSrc==NULL){return 0;}
			LOG_OUTPUT_POINT(iScene, sDataLocal, pPointSrc);
			return pPointSrc->c;
		}
	case VARIABLE_IMG_WIDTH:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			ImgRGB* pimgRGB = GetImgValuePointer(iScene, sArg);			
			if(pimgRGB == NULL){iSrc=0;} else{iSrc=pimgRGB->iWidth;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}
	case VARIABLE_IMG_HEIGHT:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);

			int iSrc;
			ImgRGB* pimgRGB = GetImgValuePointer(iScene, sArg);
			if(pimgRGB == NULL){iSrc=0;} else{iSrc=pimgRGB->iHeight;}
			LOG_OUTPUT_INT(iScene, sDataLocal, iSrc);

			return iSrc;
		}
	case VARIABLE_IMG_VALUE:
		{
			ExtractData(sDataLocal, _T("."), &sArg, &sDataLocal);
			ImgRGB* pimgRGB = GetImgValuePointer(iScene, sArg);
			if(pimgRGB == NULL){return 0;}

			int iTokenNum;
			CountTokenInBracket(sDataLocal, &iTokenNum);

			if(iTokenNum==3)
			{
				CString sR, sC;
				ExtractTokenInBracket(sDataLocal,0,&sC);
				ExtractTokenInBracket(sDataLocal,1,&sR);
				int iR, iC;
				iC=GetIntValue(iScene, sC);
				iR=GetIntValue(iScene, sR);

				CString sColorTemp;
				ExtractTokenInBracket(sDataLocal,2,&sColorTemp);
				CString sColor;
				sColor.Format(_T("%s"), GetStrValue(iScene, sColorTemp));

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
				iC1=GetIntValue(iScene, sArg);
				ExtractTokenInBracket(sDataLocal,1,&sArg);
				iR1=GetIntValue(iScene, sArg);
				ExtractTokenInBracket(sDataLocal,2,&sArg);
				iC2=GetIntValue(iScene, sArg);
				ExtractTokenInBracket(sDataLocal,3,&sArg);
				iR2=GetIntValue(iScene, sArg);

				CString sColorTemp;
				ExtractTokenInBracket(sDataLocal,4,&sColorTemp);
				CString sColor;
				sColor.Format(_T("%s"), GetStrValue(iScene, sColorTemp));

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
			return _ttoi(g_cInput.m_sReturnValue);
		}
	case VARIABLE_DLG_ITEM:
		{
			CString sText;
			int iRank;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			sText.Format(_T("%s"), GetStrValue(iScene,sArg));

			ExtractTokenInBracket(sDataLocal,1,&sArg);
			if(sArg.GetLength()<=0){iRank=0;}
			else{iRank=GetIntValue(iScene,sArg);}

			return GetDlgItem_My(sText, iRank);
		}
	default:
		{
			if(sDataLocal.SpanIncluding(_T("-0123456789")).CompareNoCase(sDataLocal)==0)
			{
				return _ttoi(sDataLocal);
			}
			return 0;
		}
	}
	return 0;
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
Object* GetObjValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarObj"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarObj%d"), iVarNameB1);
		if(sArg.CompareNoCase(sVarName)==0){return &(g_object[iScene][iVarNameB1-1]);}
	}

	return NULL;
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
		if(sArg.Left(sVarName.GetLength()).CompareNoCase(sVarName)==0){return &(g_imgRGB[iScene][iVarNameB1-1]);}
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
		if(sArg.Left(sVarName.GetLength()).CompareNoCase(sVarName)==0){return &(g_imgRGB[iScene][iVarNameB1-1]);}
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
		if(sArg.Left(sVarName.GetLength()).CompareNoCase(sVarName)==0){return &(g_point[iScene][iVarNameB1-1]);}
	}

	return NULL;
}
Camera* GetCameraPointer(int iScene, CString sArg)
{
	return &g_camera;
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
	int iSrc1=GetIntValue(iScene, sArg1);
	int iSrc2=GetIntValue(iScene, sArg2);

	return iSrc1+iSrc2;
}

int IntSub(int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(iScene, sArg1);
	int iSrc2=GetIntValue(iScene, sArg2);

	return iSrc1-iSrc2;
}
int IntMult(int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(iScene, sArg1);
	int iSrc2=GetIntValue(iScene, sArg2);

	return iSrc1*iSrc2;
}

int IntDiv(int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(iScene, sArg1);
	int iSrc2=GetIntValue(iScene, sArg2);

	return iSrc1/iSrc2;
}


BOOL IsStrEqual(int iScene, CString sArg1, CString sArg2)
{
	CString sSrc1;
	CString sSrc2;

	sSrc1.Format(_T("%s"), GetStrValue(iScene, sArg1));
	sSrc2.Format(_T("%s"), GetStrValue(iScene, sArg2));

	if(sSrc1.Compare(sSrc2)==0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(iScene, sArg1);
	int iSrc2=GetIntValue(iScene, sArg2);

	return (iSrc1==iSrc2);
}




ReturnValue Flow_AreStrEqual(int iScene, CStringArray* saData, CString* sReturnParam)
{
	if(IsStrEqual(iScene, saData->GetAt(0), saData->GetAt(1)))
	{
		sReturnParam->Format(_T("%s"), saData->GetAt(2));
		return RETURN_GOTO_BY_SWITCH;
	}

	return RETURN_NORMAL;
}

ReturnValue Flow_AreIntEqual(int iScene, CStringArray* saData, CString* sReturnParam)
{
	if(IsIntEqual(iScene, saData->GetAt(0), saData->GetAt(1)))
	{
		sReturnParam->Format(_T("%s"), saData->GetAt(2));
		return RETURN_GOTO_BY_SWITCH;
	}

	return RETURN_NORMAL;
}

ReturnValue Flow_Compare(int iScene, CStringArray* saData, CString* sReturnParam)
{

	int iSrc1=GetIntValue(iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(iScene,  saData->GetAt(2));


	if((saData->GetAt(1).Compare(_T("="))==0) || (saData->GetAt(1).Compare(_T("=="))==0))
	{
		if (iSrc1==iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(saData->GetAt(1).Compare(_T(">"))==0)
	{
		if (iSrc1>iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(saData->GetAt(1).Compare(_T(">="))==0)
	{
		if (iSrc1>=iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(saData->GetAt(1).Compare(_T("<="))==0)
	{
		if (iSrc1<=iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(saData->GetAt(1).Compare(_T("<="))==0)
	{
		if (iSrc1<=iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if((saData->GetAt(1).Compare(_T("<>"))==0) || (saData->GetAt(1).Compare(_T("!="))==0))
	{
		if (iSrc1!=iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	return RETURN_FAILED;
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

#define FORMATO (_T("%d"))
const CString Int2Str(int iScene, CString sArg, CString sFormat)
{
	int iSrc=GetIntValue(iScene, sArg);
	LOG_OUTPUT_STR(iScene, _T("Format"), sFormat);

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
	sSrc.Format(_T("%s"),GetStrValue(iScene, sArg));
	return _ttoi(sSrc);
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

ReturnValue SetIntValue(int* iDstPointer, int iScene, CString sDataLocal, int iSelfSrc)
{	
	int iOperandSrc;
	BOOL bRet = GetOperandIntSrc(sDataLocal, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	CString sArg;
	int iSrcValue=GetIntValue(iScene, sDataLocal);

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

ReturnValue SetCameraValue(Camera* cameraDst, int iScene, CString sData)
{
	CString sArg;
	CString sDummy;
	ExtractTokenInBracket(sData,0, &sArg);

	int iOperandSrc;
	BOOL bRet = GetOperandCameraSrc(sArg, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iOperandSrc)
	{
	case VARIABLE_CAMERA_OPEN:
		{
			bRet = ExtractTokenInBracket(sData,1,&sArg);
			cameraDst->OpenCamera(sArg);
			ImgRGB imgDummy;
			Sleep(1000);
//			cameraDst->GrabImage(&imgDummy);
			return RETURN_NORMAL;
		}
		
	case VARIABLE_CAMERA_CLOSE:
		{
			cameraDst->CloseCamera();
			return RETURN_NORMAL;	
		}
	}
	return RETURN_FAILED;
}
ReturnValue SetObjValue(Object* objectDst, int iScene, CString sData)
{
	CString sArg;
	CString sDummy;
	ExtractData(sData, _T("("), &sArg, &sDummy);

	int iOperandSrc;
	BOOL bRet = GetOperandObjSrc(sArg, &iOperandSrc);
	if(bRet != TRUE){return RETURN_FAILED;}

	switch(iOperandSrc)
	{
	case VARIABLE_OBJECT:
		{
			Object* objSrc;
			bRet = ExtractTokenInBracket(sData,0,&sArg);
			objSrc=GetObjValuePointer(iScene, sArg);

			objectDst->Copy(objSrc);
			return RETURN_NORMAL;
		}
	case VARIABLE_OBJECT_THRESHLD:
		{
			Object objSrc;

			CString sArg0;
			CString sArg1;
			CString sArg2;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			bRet = ExtractTokenInBracket(sData,2,&sArg2);

			ImgRGB* imgSrc;
			imgSrc=GetImgValuePointer(iScene, sArg0);

			BYTE byMin=GetIntValue(iScene, sArg1);
			BYTE byMax=GetIntValue(iScene, sArg2);

			Threshold(imgSrc, byMin, byMax, &objSrc);

			objectDst->Copy(&objSrc);
			return RETURN_NORMAL;
		}
	case VARIABLE_OBJECT_CONNECTION:
		{
			CString sArg0;
			CString sArg1;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			bRet = ExtractTokenInBracket(sData,1,&sArg1);

			Object* objSrc;
			objSrc=GetObjValuePointer(iScene, sArg0);

			int iPolicy=GetIntValue(iScene, sArg1);

			Connection(objSrc, objectDst, iPolicy);

			return RETURN_NORMAL;
		}
	case VARIABLE_OBJECT_SELECT_OBJ:
		{
			CString sArg0;
			CString sArg1;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			bRet = ExtractTokenInBracket(sData,1,&sArg1);

			Object* objSrc;
			objSrc=GetObjValuePointer(iScene, sArg0);

			int iID=GetIntValue(iScene, sArg1);
			SelectObj(objSrc, iID, objectDst);

			return RETURN_NORMAL;
		}
	case VARIABLE_OBJECT_SELECT_SHAPE:
		{
			CString sArg0;
			CString sArg1;
			CString sArg2;
			CString sArg3;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			bRet = ExtractTokenInBracket(sData,2,&sArg2);
			bRet = ExtractTokenInBracket(sData,3,&sArg3);

			Object* objSrc;
			objSrc=GetObjValuePointer(iScene, sArg0);
			CString sFeature;
			sFeature.Format(_T("%s"), GetStrValue(iScene, sArg1));
			double dMin ,dMax;
			dMin=GetIntValue(iScene, sArg2);
			dMax=GetIntValue(iScene, sArg3);

			SelectShape(objSrc, objectDst,sFeature, dMin, dMax);

			return RETURN_NORMAL;
		}
	case VARIABLE_OBJECT_SORT_REGION:
		{
			CString sArg0;
			CString sArg1;
			CString sArg2;
			CString sArg3;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			bRet = ExtractTokenInBracket(sData,2,&sArg2);

			Object* objSrc;
			objSrc=GetObjValuePointer(iScene, sArg0);
			CString sMode;
			sMode.Format(_T("%s"), GetStrValue(iScene, sArg1));
			CString sAscDsc;
			sAscDsc.Format(_T("%s"), GetStrValue(iScene, sArg2));

			SortRegion(objSrc, sMode, sAscDsc, objectDst);

			return RETURN_NORMAL;
		}
	case VARIABLE_OBJECT_GEN_RECTANGLE1:
		{
			CString sArg0;
			CString sArg1;
			CString sArg2;
			CString sArg3;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			bRet = ExtractTokenInBracket(sData,2,&sArg2);
			bRet = ExtractTokenInBracket(sData,3,&sArg3);

			int iR0, iR1, iC0, iC1;
			iC0=GetIntValue(iScene, sArg0);
			iR0=GetIntValue(iScene, sArg1);
			iC1=GetIntValue(iScene, sArg2);
			iR1=GetIntValue(iScene, sArg3);

			bRet = GenRectangle1(objectDst, iR0, iC0, iR1, iC1);
			if(bRet != TRUE){return RETURN_FAILED;}

			return RETURN_NORMAL;
		}
	}
	return RETURN_FAILED;
}
ReturnValue SetImgValue(ImgRGB* imgRGBDst, int iScene, CString sData)
{

	CString sArg;
	CString sDummy;
	ExtractData(sData, _T("("), &sArg, &sDummy);

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
				sSrc.Format(_T("%s"),GetStrValuePointer(iScene, sArg));

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
	case VARIABLE_SCREENSHOT_FOREGROUND_WINDOW:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}
			ImgRGB imgRGB;
			ImgRGB imgRGBCropped;;
			Screenshot(&imgRGB);
			int iLeft;
			int iTop;
			int iWidth;
			int iHeight;

			bRet = GetForegroundWindowPos(&iLeft, &iTop, &iWidth, &iHeight);
			if(bRet != TRUE){return RETURN_FAILED;}

			bRet = CropImage(&imgRGB, &imgRGBCropped, iTop, iLeft, iTop+iHeight-1, iLeft+iWidth-1);
			if(bRet != TRUE){return RETURN_FAILED;}

			pImgRGB->Assign(&imgRGBCropped);

			return RETURN_NORMAL;
		}
	case VARIABLE_CROP_IMAGE:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}


			CString sArg0;
			CString sArg1;
			CString sArg2;
			CString sArg3;
			CString sArg4;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			if(bRet != TRUE){return RETURN_FAILED;} 
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			if(bRet != TRUE){return RETURN_FAILED;} 
			bRet = ExtractTokenInBracket(sData,2,&sArg2);
			if(bRet != TRUE){return RETURN_FAILED;} 
			bRet = ExtractTokenInBracket(sData,3,&sArg3);
			if(bRet != TRUE){return RETURN_FAILED;} 
			bRet = ExtractTokenInBracket(sData,4,&sArg4);
			if(bRet != TRUE){return RETURN_FAILED;} 


			ImgRGB* pImgRGBIn=GetImgValuePointer(iScene, sArg0);
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			int iSrc1=GetIntValue(iScene, sArg1);
			int iSrc2=GetIntValue(iScene, sArg2);
			int iSrc3=GetIntValue(iScene, sArg3);
			int iSrc4=GetIntValue(iScene, sArg4);

			CropImage(pImgRGBIn, pImgRGB, iSrc1, iSrc2, iSrc3, iSrc4 );
			return RETURN_NORMAL;
		}
	case VARIABLE_IMG_DECOMPOSE:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}


			CString sArg0;
			CString sArg1;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			if(bRet != TRUE){return RETURN_FAILED;} 
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			if(bRet != TRUE){return RETURN_FAILED;} 


			ImgRGB* pImgRGBIn=GetImgValuePointer(iScene, sArg0);
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			ImgRGB imgR, imgG, imgB;
			Decompose3(pImgRGBIn, &imgR, &imgG, &imgB);

			if(sArg1.CompareNoCase(_T("R"))==0){pImgRGB->Assign(&imgR);return RETURN_NORMAL;}
			if(sArg1.CompareNoCase(_T("G"))==0){pImgRGB->Assign(&imgG);return RETURN_NORMAL;}
			if(sArg1.CompareNoCase(_T("B"))==0){pImgRGB->Assign(&imgB);return RETURN_NORMAL;}

			return RETURN_FAILED;
		}
	case VARIABLE_IMG_REDUCE_DOMAIN:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}


			CString sArg0;
			CString sArg1;
			bRet = ExtractTokenInBracket(sData,0,&sArg0);
			if(bRet != TRUE){return RETURN_FAILED;} 
			bRet = ExtractTokenInBracket(sData,1,&sArg1);
			if(bRet != TRUE){return RETURN_FAILED;} 


			ImgRGB* pImgRGBIn=GetImgValuePointer(iScene, sArg0);
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			Object* objRegion=GetObjValuePointer(iScene, sArg1);
			if(objRegion == NULL){return RETURN_FAILED;}

			bRet = ReduceDomain(pImgRGBIn, objRegion, pImgRGB);
			if(bRet != TRUE){return RETURN_FAILED;}
			return RETURN_NORMAL;
		}
	case VARIABLE_CAMERA_GRAB:
		{

			Camera* pCamera;
			pCamera=GetCameraPointer(iScene,_T(""));

			g_camera.GrabImage(pImgRGB);
			return RETURN_NORMAL;
		}
	case VARIABLE_CLIPBOARD:
		{
			if(pImgRGB == NULL){return RETURN_FAILED;}
			bRet = CopyFromClipBoardImg(pImgRGB);
			if(bRet != TRUE){return RETURN_FAILED;}
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

			pPoint->Set( pPointSrc->c,pPointSrc->r);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_DIRECT:
		{
			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			int iSrc1=GetIntValue(iScene, sArg1);
			int iSrc2=GetIntValue(iScene, sArg2);

			pPoint->Set(iSrc1, iSrc2);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_MOUSE_POS:
		{

			pPoint->Set(g_iC,g_iR);

			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_OBJECT_CENTER:
		{

			CString sArg1;
			CString sArg2;
			ExtractTokenInBracket(sDataLocal,0,&sArg1);
			ExtractTokenInBracket(sDataLocal,1,&sArg2);

			Object* objSrc;
			objSrc=GetObjValuePointer(iScene, sArg1);
			int iLength;
			iLength=objSrc->m_uiMaxLabel+1;
			double* dA;
			double* dR;
			double* dC;
			dA=new double[iLength];
			dR=new double[iLength];
			dC=new double[iLength];


			AreaCenter(objSrc, dA, dR, dC, iLength);

			pPoint->Set(dR[0], dC[0]);

			SAFE_DELETE(dA);
			SAFE_DELETE(dR);
			SAFE_DELETE(dC);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_FOREGROUND_WINDOW_LU:
		{
			int iLeft;
			int iTop; 
			int iWidth;
			int iHeight;
			BOOL bRet = GetForegroundWindowPos(&iLeft, &iTop, &iWidth,  &iHeight);
			pPoint->Set(iLeft,iTop);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_FOREGROUND_WINDOW_RD:
		{
			int iLeft;
			int iTop; 
			int iWidth;
			int iHeight;
			BOOL bRet = GetForegroundWindowPos(&iLeft, &iTop, &iWidth,  &iHeight);
			pPoint->Set(iLeft+iWidth-1,iTop+iHeight-1);
			return RETURN_NORMAL;
		}
	case VARIABLE_POINT_SEARCH_RESULT:
		{

			BOOL bRet;
			CString sModelFilePath;
			int iR0, iC0, iR1, iC1;

			CString sArg;
			ExtractTokenInBracket(sDataLocal,0,&sArg);
			if(sArg.GetLength()>2){if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), g_sDir,sTemp); }}
			else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Macro\\Model\\%s"), g_sDir,sTemp); }
			sModelFilePath.Format(_T("%s"), sArg);

			CString sC0, sR0, sC1, sR1;
			ExtractTokenInBracket(sDataLocal,1,&sC0);
			ExtractTokenInBracket(sDataLocal,2,&sR0);
			ExtractTokenInBracket(sDataLocal,3,&sC1);
			ExtractTokenInBracket(sDataLocal,4,&sR1);

			iC0=GetIntValue(iScene, sC0);
			iR0=GetIntValue(iScene, sR0);
			iC1=GetIntValue(iScene, sC1);
			iR1=GetIntValue(iScene, sR1);

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

			if(bRet != TRUE){return RETURN_FAILED;}
			pPoint->Set(iFoundC, iFoundR);


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
	case VARIABLE_OBJECT:
		{
			Object* pObjDst = GetObjValuePointer(iScene, saData->GetAt(0));
			if(pObjDst == NULL){return RETURN_FAILED;}
			return SetObjValue(pObjDst,iScene, saData->GetAt(1));
		}
	case VARIABLE_POINT:
		{
			Point* pPointDst = GetPointValuePointer(iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetPointValue(pPointDst, iScene, saData->GetAt(1));
		}
	case VARIABLE_CAMERA:
		{
			Camera* pCamera = GetCameraPointer(iScene, saData->GetAt(0));
			if(pCamera == NULL){return RETURN_FAILED;}
			return SetCameraValue(pCamera, iScene, saData->GetAt(1));
		}
	case VARIABLE_CLIPBOARD:
		{
			int iCmmandType;
			bRet = GetOperandStrSrc(saData->GetAt(1),&iCmmandType);
			if(bRet == TRUE)
			{
				CString sValue;
				sValue.Format(_T("%s"), GetStrValue(iScene, saData->GetAt(1)));

				bRet = CopyToClipBoardStr(sValue);
				if(bRet != TRUE){return RETURN_FAILED;}
				return RETURN_NORMAL;
			}

			bRet = GetOperandImgSrc(saData->GetAt(1),&iCmmandType);
			if(bRet == TRUE)
			{
				ImgRGB* pImgRGBSrc = GetImgValuePointer(iScene, saData->GetAt(1));
				if(pImgRGBSrc == NULL){return RETURN_FAILED;}

				bRet = CopyToClipBoardImg(pImgRGBSrc);
				if(bRet != TRUE){return RETURN_FAILED;}
				return RETURN_NORMAL;
			}


			return RETURN_FAILED;
		}
	default:{return RETURN_FAILED;}
	}

	return RETURN_FAILED;
}

ReturnValue MessageBox_My(int iScene, CStringArray* saData)
{

	CString sMes;
	BOOL bRet;
	int iCommandType;
	bRet = GetOperandIntSrc(saData->GetAt(0), &iCommandType);
	if(bRet == TRUE)
	{
		int iSrc=GetIntValue(iScene, saData->GetAt(0));

		sMes.Format(_T("%d"),iSrc);
		AfxMessageBox(sMes);
		return RETURN_NORMAL;
	}

	bRet = GetOperandStrSrc(saData->GetAt(0), &iCommandType);
	if(bRet == TRUE)
	{
		CString sSrc;
		sSrc.Format(_T("%s"),GetStrValue(iScene, saData->GetAt(0)));
		AfxMessageBox(sSrc);
		return RETURN_NORMAL;
	}

	return RETURN_FAILED;
}
