#include "stdafx.h"
#include "variables.h"


#include "perser.h"
#include "Window.h"
#include "ClipBoard.h"
#include "Variables_Img.h"

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

BOOL GetOperandImgSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.CompareNoCase(_T("ClipBoard"))==0){*iCommandType=VARIABLE_CLIPBOARD; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("CropImage"))==0){*iCommandType=VARIABLE_CROP_IMAGE; return TRUE;}
	if(sDataTrim.Left(12).CompareNoCase(_T("ReduceDomain"))==0){*iCommandType=VARIABLE_IMG_REDUCE_DOMAIN; return TRUE;}
	if(sDataTrim.Left(26).CompareNoCase(_T("ScreenShotForeGroundWindow"))==0){*iCommandType=VARIABLE_SCREENSHOT_FOREGROUND_WINDOW; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("ScreenShot"))==0){*iCommandType=VARIABLE_SCREENSHOT; return TRUE;}
	if(sDataTrim.Left(10).CompareNoCase(_T("Decompose3"))==0){*iCommandType=VARIABLE_IMG_DECOMPOSE; return TRUE;}
	if(sDataTrim.Right(4).CompareNoCase(_T(".bmp"))==0){*iCommandType=VARIABLE_IMG; return TRUE;}
	if(sDataTrim.Left(9).CompareNoCase(_T("VarCamera"))==0){*iCommandType=VARIABLE_CAMERA_GRAB; return TRUE;}
	
	return FALSE;
}
ImgRGB* GetImgValuePointer(CString sDir, int iScene, CString sArg)
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

const ImgRGB* GetImgValuePointerConst(CString sDir, int iScene, CString sArg)
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

ReturnValue SetCameraValue(CString sDir, int iScene, Camera* cameraDst, CString sData)
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
ReturnValue SetImgValue(CString sDir, int iScene, ImgRGB* imgRGBDst, CString sData)
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
				sSrc.Format(_T("%s"),GetStrValue(sDir, iScene, sArg));

				pImgRGB->Assign(sSrc);
				return RETURN_NORMAL;
			}
			pImgRGB->Assign(GetImgValuePointerConst(sDir, iScene, sArg));
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


			ImgRGB* pImgRGBIn=GetImgValuePointer(sDir, iScene, sArg0);
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			int iSrc1=GetIntValue(sDir, iScene, sArg1);
			int iSrc2=GetIntValue(sDir, iScene, sArg2);
			int iSrc3=GetIntValue(sDir, iScene, sArg3);
			int iSrc4=GetIntValue(sDir, iScene, sArg4);

			CropImage(pImgRGBIn, pImgRGB, iSrc2, iSrc1, iSrc4,  iSrc3);
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


			ImgRGB* pImgRGBIn=GetImgValuePointer(sDir, iScene, sArg0);
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


			ImgRGB* pImgRGBIn=GetImgValuePointer(sDir, iScene, sArg0);
			if(pImgRGBIn == NULL){return RETURN_FAILED;}

			Object* objRegion=GetObjValuePointer(sDir, iScene, sArg1);
			if(objRegion == NULL){return RETURN_FAILED;}

			bRet = ReduceDomain(pImgRGBIn, objRegion, pImgRGB);
			if(bRet != TRUE){return RETURN_FAILED;}
			return RETURN_NORMAL;
		}
	case VARIABLE_CAMERA_GRAB:
		{

			Camera* pCamera;
			pCamera=GetCameraPointer(sDir, iScene,_T(""));

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
Camera* GetCameraPointer(CString sDir, int iScene, CString sArg)
{
	return &g_camera;
}
