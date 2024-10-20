#include "stdafx.h"
#include "Variables.h"

ReturnValue Flow_WriteImage(int iScene, CStringArray* saData)
{


	ImgRGB* imgRGB=GetImgValuePointer(iScene, saData->GetAt(0));
	if(imgRGB == NULL){return RETURN_FAILED;}

	
	CString sFilePath;
	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(iScene, saData->GetAt(1)));
	if(sArg.GetLength()<4){return RETURN_FAILED;}
	if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg);sArg.Format(_T("%s\\%s"),g_sDir,sTemp);}
	sFilePath.Format(_T("%s"), sArg);


	BOOL bRet = WriteImage(imgRGB, sFilePath);
	if(bRet != TRUE){return RETURN_FAILED;}

	return RETURN_NORMAL;
}