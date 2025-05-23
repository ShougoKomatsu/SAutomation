#include "stdafx.h"
#include "Variables.h"


ReturnValue Flow_WriteImage(CString sDir, int iScene, CStringArray* saData)
{


	ImgRGB* imgRGB=GetImgValuePointer(iScene, saData->GetAt(0));
	if(imgRGB == NULL){return RETURN_FAILED;}

	
	CString sFilePath;
	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(iScene, saData->GetAt(1)));
	if(sArg.GetLength()<4){return RETURN_FAILED;}
	if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg);sArg.Format(_T("%s\\%s"),sDir,sTemp);}
	sFilePath.Format(_T("%s"), sArg);


	BOOL bRet = WriteImage(imgRGB, sFilePath);
	if(bRet != TRUE){return RETURN_FAILED;}

	return RETURN_NORMAL;
}



/*
ReturnValue Flow_Threshold(int iScene, CStringArray* saData, CString* sReturnParam)
{
	
	ImgRGB* imgRGB=GetImgValuePointer(iScene, saData->GetAt(0));
	if(imgRGB == NULL){return RETURN_FAILED;}

	BYTE byMin=GetIntValue(iScene, saData->GetAt(1));
	BYTE byMax=GetIntValue(iScene, saData->GetAt(2));
	Object* obj=GetObjValuePointer(iScene, saData->GetAt(3));
	Threshold(imgRGB, byMin, byMax,obj);

		return RETURN_GOTO_BY_SWITCH;

	return RETURN_NORMAL;
}
*/