#include "stdafx.h"
#include "variables.h"

#include "ClipBoard.h"

#include "Variables_String.h"
#include "Variables_Int.h"
#include "Variables_Img.h"
#include "Variables_Obj.h"

int g_iVar[MAX_THREAD][MAX_VARIABLES];
CString g_sVar[MAX_THREAD][MAX_VARIABLES];
ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];
Point g_point[MAX_THREAD][MAX_VARIABLES];
Object g_object[MAX_THREAD][MAX_VARIABLES];
CRect g_rect[MAX_THREAD][MAX_VARIABLES];
ByteVector g_bytes[MAX_THREAD][MAX_VARIABLES];
Camera g_camera;


int GetOperandType(CString sDataLine)
{
	int iCommandType;
	BOOL bRet;
	bRet = GetOperandIntSrc(sDataLine, &iCommandType);
	if(bRet == TRUE){return VARIABLE_INT;}

	bRet = GetOperandImgSrc(sDataLine, &iCommandType);
	if(bRet == TRUE){return VARIABLE_IMG;}

	bRet = GetOperandObjSrc(sDataLine, &iCommandType);
	if(bRet == TRUE){return VARIABLE_OBJECT;}

	bRet = GetOperandPointSrc(sDataLine, &iCommandType);
	if(bRet == TRUE){return VARIABLE_POINT;}

	bRet = GetOperandRectSrc(sDataLine, &iCommandType);
	if(bRet == TRUE){return VARIABLE_RECT;}

	bRet = GetOperandStrSrc(sDataLine, &iCommandType);
	if(bRet == TRUE){return VARIABLE_STR;}
	return VARIABLE_UNDEFINED;
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
	if(sDataTrim.Left(7).CompareNoCase(_T("VarRect"))==0){*iCommandType=VARIABLE_RECT; return TRUE;}
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


BOOL IsStrEqual(CString sDir, int iScene, CString sArg1, CString sArg2)
{
	CString sSrc1;
	CString sSrc2;

	sSrc1.Format(_T("%s"), GetStrValue(sDir, iScene, sArg1));
	sSrc2.Format(_T("%s"), GetStrValue(sDir, iScene, sArg2));

	if(sSrc1.Compare(sSrc2)==0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL IsIntEqual(CString sDir, int iScene, CString sArg1, CString sArg2)
{
	int iSrc1=GetIntValue(sDir, iScene, sArg1);
	int iSrc2=GetIntValue(sDir, iScene, sArg2);

	return (iSrc1==iSrc2);
}




ReturnValue Flow_AreStrEqual(CString sDir, int iScene, CStringArray* saData, CString* sReturnParam)
{
	if(IsStrEqual(sDir, iScene, saData->GetAt(0), saData->GetAt(1)))
	{
		sReturnParam->Format(_T("%s"), saData->GetAt(2));
		return RETURN_GOTO_BY_SWITCH;
	}

	return RETURN_NORMAL;
}

ReturnValue Flow_Compare(CString sDir, int iScene, CStringArray* saData, CString* sReturnParam)
{

	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene,  saData->GetAt(2));
	CString sOperator;
	sOperator.Format(_T("%s"),saData->GetAt(1));

	if((sOperator.Compare(_T("="))==0) || (sOperator.Compare(_T("=="))==0))
	{
		if (iSrc1==iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(sOperator.Compare(_T(">"))==0)
	{
		if (iSrc1>iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(sOperator.Compare(_T(">="))==0)
	{
		if (iSrc1>=iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(sOperator.Compare(_T("<"))==0)
	{
		if (iSrc1<iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if(sOperator.Compare(_T("<="))==0)
	{
		if (iSrc1<=iSrc2)
		{
			sReturnParam->Format(_T("%s"), saData->GetAt(3));
			return RETURN_GOTO_BY_SWITCH;
		}
		return RETURN_NORMAL;
	}

	if((sOperator.Compare(_T("<>"))==0) || (sOperator.Compare(_T("!="))==0))
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


ReturnValue Flow_Assign(CString sDir, int iScene, CStringArray* saData)
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
			Point* pPointDst = GetPointValuePointer(sDir, iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetIntValue(sDir, iScene, &(pPointDst->r), saData->GetAt(1),iSelfSrc);
		}
	case VARIABLE_POINT_SET_C:
		{
			Point* pPointDst = GetPointValuePointer(sDir, iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetIntValue(sDir, iScene, &(pPointDst->c), saData->GetAt(1),iSelfSrc);
		}
	case VARIABLE_INT:
		{
			int* piDst = GetIntValuePointer(sDir, iScene, saData->GetAt(0));
			if(piDst == NULL){return RETURN_FAILED;}
			return SetIntValue(sDir, iScene, piDst, saData->GetAt(1),iSelfSrc);
		}
	case VARIABLE_STR:
		{
			CString* psDst=GetStrValuePointer(sDir, iScene, saData->GetAt(0));
			if(psDst == NULL){return RETURN_FAILED;}
			return SetStrValue(sDir, iScene, psDst, saData->GetAt(1));
		}
	case VARIABLE_IMG:
		{
			ImgRGB* pImgRGBDst = GetImgValuePointer(sDir, iScene, saData->GetAt(0));
			if(pImgRGBDst == NULL){return RETURN_FAILED;}
			return SetImgValue(sDir, iScene, pImgRGBDst, saData->GetAt(1));
		}
	case VARIABLE_OBJECT:
		{
			Object* pObjDst = GetObjValuePointer(sDir, iScene, saData->GetAt(0));
			if(pObjDst == NULL){return RETURN_FAILED;}
			return SetObjValue(sDir, iScene, pObjDst, saData->GetAt(1));
		}
	case VARIABLE_POINT:
		{
			Point* pPointDst = GetPointValuePointer(sDir, iScene, saData->GetAt(0));
			if(pPointDst == NULL){return RETURN_FAILED;}
			return SetPointValue(sDir, iScene, pPointDst, saData->GetAt(1));
		}
	case VARIABLE_RECT:
		{
			CRect* pRectDst = GetRectValuePointer(sDir, iScene, saData->GetAt(0));
			if(pRectDst == NULL){return RETURN_FAILED;}
			return SetRectValue(sDir, iScene, pRectDst, saData->GetAt(1));
		}
	case VARIABLE_CAMERA:
		{
			Camera* pCamera = GetCameraPointer(sDir, iScene, saData->GetAt(0));
			if(pCamera == NULL){return RETURN_FAILED;}
			return SetCameraValue(sDir, iScene, pCamera, saData->GetAt(1));
		}
	case VARIABLE_CLIPBOARD:
		{
			int iCmmandType;
			bRet = GetOperandStrSrc(saData->GetAt(1),&iCmmandType);
			if(bRet == TRUE)
			{
				CString sValue;
				sValue.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(1)));

				bRet = CopyToClipBoardStr(sValue);
				if(bRet != TRUE){return RETURN_FAILED;}
				return RETURN_NORMAL;
			}

			bRet = GetOperandImgSrc(saData->GetAt(1),&iCmmandType);
			if(bRet == TRUE)
			{
				ImgRGB* pImgRGBSrc = GetImgValuePointer(sDir, iScene, saData->GetAt(1));
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

ReturnValue MessageBox_My(CString sDir, int iScene, CStringArray* saData)
{

	CString sMes;
	BOOL bRet;
	int iCommandType;
	bRet = GetOperandIntSrc(saData->GetAt(0), &iCommandType);
	if(bRet == TRUE)
	{
		int iSrc=GetIntValue(sDir, iScene, saData->GetAt(0));

		sMes.Format(_T("%d"),iSrc);
		AfxMessageBox(sMes);
		return RETURN_NORMAL;
	}
	bRet = GetOperandPointSrc(saData->GetAt(0), &iCommandType);
	if(bRet == TRUE)
	{
		CString sData;
		sData.Format(_T("%s.r"),saData->GetAt(0));
		int iSrcR=GetIntValue(sDir, iScene, sData);
		sData.Format(_T("%s.c"),saData->GetAt(0));
		int iSrcC=GetIntValue(sDir, iScene, sData);

		sMes.Format(_T("(%d, %d)"),iSrcC, iSrcR);
		AfxMessageBox(sMes);
		return RETURN_NORMAL;
	}
	bRet = GetOperandRectSrc(saData->GetAt(0), &iCommandType);
	if(bRet == TRUE)
	{
		CString sData;
		sData.Format(_T("%s.top"),saData->GetAt(0));
		int iSrcR1=GetIntValue(sDir, iScene, sData);
		sData.Format(_T("%s.left"),saData->GetAt(0));
		int iSrcC1=GetIntValue(sDir, iScene, sData);
		sData.Format(_T("%s.bottom"),saData->GetAt(0));
		int iSrcR2=GetIntValue(sDir, iScene, sData);
		sData.Format(_T("%s.right"),saData->GetAt(0));
		int iSrcC2=GetIntValue(sDir, iScene, sData);

		sMes.Format(_T("(%d, %d) - (%d, %d)"),iSrcC1, iSrcR1, iSrcC2, iSrcR2);
		AfxMessageBox(sMes);
		return RETURN_NORMAL;
	}
	bRet = GetOperandStrSrc(saData->GetAt(0), &iCommandType);
	if(bRet == TRUE)
	{
		CString sSrc;
		sSrc.Format(_T("%s"),GetStrValue(sDir, iScene, saData->GetAt(0)));
		AfxMessageBox(sSrc);
		return RETURN_NORMAL;
	}

	return RETURN_FAILED;
}

BOOL GetRectData(CString sDir, int iScene, CStringArray* saData, int iStartIndex, int* iR0, int* iC0, int* iR1, int* iC1, int* iNextIndex)
{
	BOOL bRet;

	CRect rect;
	if(saData->GetCount()<=iStartIndex+0){return FALSE;}
	bRet =  GetRectValue(sDir, iScene, saData->GetAt(iStartIndex), &rect);
	if(bRet == TRUE)
	{
		*iC0 = rect.left;
		*iR0 = rect.top;
		*iC1 = rect.right;
		*iR1 = rect.bottom;
		*iNextIndex=iStartIndex+1;
		return TRUE;
	}
	
	if(saData->GetCount()<=iStartIndex+3){return FALSE;}
	*iC0=GetIntValue(sDir, iScene, saData->GetAt(iStartIndex+0));
	*iR0=GetIntValue(sDir, iScene, saData->GetAt(iStartIndex+1));
	*iC1=GetIntValue(sDir, iScene, saData->GetAt(iStartIndex+2));
	*iR1=GetIntValue(sDir, iScene, saData->GetAt(iStartIndex+3));
	*iNextIndex=iStartIndex+4;
	return TRUE;

}

