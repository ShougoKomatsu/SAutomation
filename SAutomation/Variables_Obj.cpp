#include "stdafx.h"
#include "variables.h"

#include "parser.h"
#include "Window.h"

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

	return FALSE;
}

Object* GetObjValuePointer(CString sDir, int iScene, CString sArg)
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
ReturnValue SetObjValue(CString sDir, int iScene, Object* objectDst, CString sData)
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
			objSrc=GetObjValuePointer(sDir, iScene, sArg);

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
			imgSrc=GetImgValuePointer(sDir, iScene, sArg0);

			BYTE byMin=GetIntValue(sDir, iScene, sArg1);
			BYTE byMax=GetIntValue(sDir, iScene, sArg2);

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
			objSrc=GetObjValuePointer(sDir, iScene, sArg0);

			int iPolicy=GetIntValue(sDir, iScene, sArg1);

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
			objSrc=GetObjValuePointer(sDir, iScene, sArg0);

			int iID=GetIntValue(sDir, iScene, sArg1);
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
			objSrc=GetObjValuePointer(sDir, iScene, sArg0);
			CString sFeature;
			sFeature.Format(_T("%s"), GetStrValue(sDir, iScene, sArg1));
			double dMin ,dMax;
			dMin=GetIntValue(sDir, iScene, sArg2);
			dMax=GetIntValue(sDir, iScene, sArg3);

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
			objSrc=GetObjValuePointer(sDir, iScene, sArg0);
			CString sMode;
			sMode.Format(_T("%s"), GetStrValue(sDir, iScene, sArg1));
			CString sAscDsc;
			sAscDsc.Format(_T("%s"), GetStrValue(sDir, iScene, sArg2));

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
			iC0=GetIntValue(sDir, iScene, sArg0);
			iR0=GetIntValue(sDir, iScene, sArg1);
			iC1=GetIntValue(sDir, iScene, sArg2);
			iR1=GetIntValue(sDir, iScene, sArg3);

			bRet = GenRectangle1(objectDst, iR0, iC0, iR1, iC1);
			if(bRet != TRUE){return RETURN_FAILED;}

			return RETURN_NORMAL;
		}
	}
	return RETURN_FAILED;
}