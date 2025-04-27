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
Camera g_camera;




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
