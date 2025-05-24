#include "stdafx.h"
#include "MouseAutomation.h"
#include "Window.h"
#include "ImgProc.h"
#include "Variables.h"


ReturnValue MouseVWheel(int iWheel)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL, 0, 0, iWheel, NULL);
	return RETURN_NORMAL;
}

ReturnValue MouseVWheel(CString sDir, int iScene, CStringArray* saData)
{
	int iSrc=GetIntValue(sDir, iScene, saData->GetAt(0));
	return MouseVWheel(iSrc);
}



ReturnValue MouseEvent(UINT uiEvent, UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(uiEvent, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}

ReturnValue MoveMouseAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, nX, nY);}
ReturnValue MouseLDownAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, nX, nY);}
ReturnValue MouseRDownAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, nX, nY);}
ReturnValue MouseMDownAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN, nX, nY);}
ReturnValue MouseLUpAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, nX, nY);}
ReturnValue MouseRUpAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, nX, nY);}
ReturnValue MouseMUpAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP, nX, nY);}


ReturnValue MoveMouse(UINT nX, UINT nY){return MoveMouseAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseLDown(UINT nX, UINT nY){return MouseLDownAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseRDown(UINT nX, UINT nY){return MouseRDownAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseMDown(UINT nX, UINT nY){return MouseMDownAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseLUp(UINT nX, UINT nY){return MouseLUpAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseRUp(UINT nX, UINT nY){return MouseRUpAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseMUp(UINT nX, UINT nY){return MouseMUpAbs(nX + g_iOriginC, nY + g_iOriginR);}


ReturnValue MoveMouse(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==1)
	{
		if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))!=0)
		{
			return RETURN_FAILED;
		}

		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MoveMouse(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));

	return MoveMouse(iSrc1, iSrc2);
}


ReturnValue MouseLDown(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLDown(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseLDown(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseLDown(iSrc1, iSrc2);
}
ReturnValue MouseRDown(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRDown(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseRDown(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseRDown(iSrc1, iSrc2);
}

ReturnValue MouseMDown(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMDown(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseMDown(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseMDown(iSrc1, iSrc2);
}




ReturnValue MouseLUp(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLUp(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseLUp(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseLUp(iSrc1, iSrc2);
}

ReturnValue MouseRUp(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRUp(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseRUp(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseRUp(iSrc1, iSrc2);
}

ReturnValue MouseMUp(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMUp(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseMUp(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseMUp(iSrc1, iSrc2);
}



ReturnValue MouseLClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseLDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseLUp(nX, nY);
}
ReturnValue MouseRClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseRDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseRUp(nX, nY);
}
ReturnValue MouseMClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseMDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseMUp(nX, nY);
}





ReturnValue MouseLClick(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLClick(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseLClick(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseLClick(iSrc1, iSrc2);
}
ReturnValue MouseRClick(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRClick(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseRClick(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseRClick(iSrc1, iSrc2);
}

ReturnValue MouseMClick(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMClick(g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseMClick(point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseMClick(iSrc1, iSrc2);
}


ReturnValue MoveMouseIncl(int iX, int iY)
{
	return MoveMouse(g_iC+iX, g_iR+iY);
}

ReturnValue MoveMouseIncl(CString sDir, int iScene, CStringArray* saData)
{
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MoveMouseIncl(iSrc1, iSrc2);
}




ReturnValue MouseSetOriginToWindow(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetAt(0).Compare(_T("Desktop"))==0)
	{
		ChangeMouseOrigin(0, 0);
		return RETURN_NORMAL;
	}

	RECT rect;
	BOOL bRet;
	bRet = GetWindowRectByName(saData->GetAt(0),&rect);
	if(bRet!=TRUE)
	{
		ChangeMouseOrigin(0, 0);
		return RETURN_FAILED;
	}

	ChangeMouseOrigin(rect.left, rect.top);
	return RETURN_NORMAL;
}

ReturnValue MouseSetOriginToImage(CString sDir, int iScene, CStringArray* saData)
{
	BOOL bRet;
	if(saData->GetCount()<2){return RETURN_FAILED;}

	int iR0, iC0, iR1, iC1;
	if(saData->GetCount()==2)
	{
		CRect rect;
		bRet = GetRectValue(sDir, iScene,  saData->GetAt(1), &rect);
		if(bRet != TRUE){return RETURN_FAILED;}

		iC0=rect.left;
		iR0=rect.top;
		iC1=rect.right;
		iR1=rect.bottom;
	}
	if(saData->GetCount()==5)
	{
		iC0=GetIntValue(sDir, iScene, saData->GetAt(1));
		iR0=GetIntValue(sDir, iScene, saData->GetAt(2));
		iC1=GetIntValue(sDir, iScene, saData->GetAt(3));
		iR1=GetIntValue(sDir, iScene, saData->GetAt(4));
	}




	CString sModelFilePath;

	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	if(sArg.GetLength()>2){if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Model\\%s"), sDir,sTemp); }}
	else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Model\\%s"), sDir,sTemp); }
	sModelFilePath.Format(_T("%s"), sArg);



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
	if(bRet != TRUE){return RETURN_FAILED;}

	ChangeMouseOrigin(iFoundC, iFoundR);
	return RETURN_NORMAL;
}


ReturnValue MoveMouseToItem(CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()<=0){return RETURN_FAILED;}
	
	int iItem = GetIntValue(sDir, iScene, saData->GetAt(0));
	CRect rect;
	GetWindowRect_My(iItem,&rect);

	
	MoveMouseAbs((rect.left+rect.right)/2, (rect.top+rect.bottom)/2);

	return RETURN_NORMAL;

}




ReturnValue MoveMouseToImage(CString sDir, int iScene, CStringArray* saData)
{
	
	BOOL bRet;
	if(saData->GetCount()<2){return RETURN_FAILED;}

	int iR0, iC0, iR1, iC1;
	if(saData->GetCount()==2)
	{
		CRect rect;
		bRet = GetRectValue(sDir, iScene,  saData->GetAt(1), &rect);
		if(bRet != TRUE){return RETURN_FAILED;}

		iC0=rect.left;
		iR0=rect.top;
		iC1=rect.right;
		iR1=rect.bottom;
	}
	if(saData->GetCount()==5)
	{
		iC0=GetIntValue(sDir, iScene, saData->GetAt(1));
		iR0=GetIntValue(sDir, iScene, saData->GetAt(2));
		iC1=GetIntValue(sDir, iScene, saData->GetAt(3));
		iR1=GetIntValue(sDir, iScene, saData->GetAt(4));
	}

	CString sModelFilePath;
	
	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	if(sArg.GetLength()>2){if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Model\\%s"), sDir,sTemp); }}
	else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Model\\%s"), sDir,sTemp); }
	sModelFilePath.Format(_T("%s"), sArg);

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

	MoveMouseAbs(iFoundC, iFoundR);

	return RETURN_NORMAL;
}

ReturnValue MouseLClickImage(CString sDir, int iScene, CStringArray* saData)
{
	BOOL bRet;
	if(saData->GetCount()<2){return RETURN_FAILED;}

	int iR0, iC0, iR1, iC1;
	if(saData->GetCount()==2)
	{
		CRect rect;
		bRet = GetRectValue(sDir, iScene,  saData->GetAt(1), &rect);
		if(bRet != TRUE){return RETURN_FAILED;}

		iC0=rect.left;
		iR0=rect.top;
		iC1=rect.right;
		iR1=rect.bottom;
	}
	if(saData->GetCount()==5)
	{
		iC0=GetIntValue(sDir, iScene, saData->GetAt(1));
		iR0=GetIntValue(sDir, iScene, saData->GetAt(2));
		iC1=GetIntValue(sDir, iScene, saData->GetAt(3));
		iR1=GetIntValue(sDir, iScene, saData->GetAt(4));
	}

	CString sModelFilePath;
	
	CString sArg;
	sArg.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	if(sArg.GetLength()>2){if(sArg.Mid(1,1).Compare(_T(":")) != 0){CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Model\\%s"), sDir,sTemp); }}
	else{CString sTemp; sTemp.Format(_T("%s"), sArg); sArg.Format(_T("%s\\Model\\%s"), sDir,sTemp); }
	sModelFilePath.Format(_T("%s"), sArg);


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

	MoveMouseAbs(iFoundC, iFoundR);
	MouseLDownAbs(iFoundC, iFoundR);
	Sleep(g_iClickDulation);
	return MouseLUpAbs(iFoundC, iFoundR);

	return RETURN_NORMAL;
}


void ChangeMouseOrigin(UINT uiX, UINT uiY)
{
	int iRNowAbs=g_iR+g_iOriginR;
	int iCNowAbs=g_iC+g_iOriginC;
	g_iOriginC = uiX;
	g_iOriginR = uiY;
	g_iR=iRNowAbs-g_iOriginR;
	g_iC=iCNowAbs-g_iOriginC;
}
