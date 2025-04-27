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


void AssignInt(int iScene, CString sArg, int iInput)
{
	int* piDst;
	piDst = GetIntValuePointer(iScene, sArg);
	if(piDst==NULL){return;}
	*piDst=iInput;
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

			pPoint->Set((int)(dR[0]), (int)(dC[0]));

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