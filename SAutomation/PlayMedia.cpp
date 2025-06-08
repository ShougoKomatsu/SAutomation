#include "stdafx.h"
#include "Common.h"
#include "Variables.h"
#include "mmsystem.h"

#pragma comment(lib, "winmm.lib")

ReturnValue PlaySound_my(CString sDir, int iScene, CStringArray* saData)
{
	BOOL bRet;
	CString sDataLocal;

	if(saData->GetCount()<=0)
	{
		bRet =PlaySound(NULL, NULL, 0 );
		if(bRet != TRUE){return RETURN_FAILED;}
		return RETURN_NORMAL;
	}
	sDataLocal.Format(_T("%s"), saData->GetAt(0));
	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(sDir, iScene, sDataLocal));
	if(sDataLocal.GetLength()<=0)
	{
		bRet =PlaySound(NULL, NULL, 0 );
		if(bRet != TRUE){return RETURN_FAILED;}
		return RETURN_NORMAL;
	}

	CString sSoundFilePath;
	bRet = GetSoundFilePath(sDir, sArg, &sSoundFilePath);
	if(bRet != TRUE){return RETURN_FAILED;}

	bRet =PlaySound(sSoundFilePath, NULL, SND_ALIAS| SND_ASYNC  );
	if(bRet != TRUE){return RETURN_FAILED;}


	return RETURN_NORMAL;
}
