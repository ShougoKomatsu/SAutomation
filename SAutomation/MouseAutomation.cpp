#include "stdafx.h"
#include "MouseAutomation.h"
#include "Window.h"
#include "ImgProc.h"
int g_iClickDulation = 50;


int MouseVWheel(int iWheel)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL, 0, 0, iWheel, NULL);
	return RETURN_NORMAL;
}

int MouseVWheel(CStringArray* saData)
{
	return MouseVWheel(_ttoi(saData->GetAt(0)));
}



int MouseEvent(UINT uiEvent, UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(uiEvent, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}

int MoveMouseAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, nX, nY);}
int MouseLDownAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, nX, nY);}
int MouseRDownAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, nX, nY);}
int MouseMDownAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN, nX, nY);}
int MouseLUpAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, nX, nY);}
int MouseRUpAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, nX, nY);}
int MouseMUpAbs(UINT nX, UINT nY)	{return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP, nX, nY);}


int MoveMouse(UINT nX, UINT nY){return MoveMouseAbs(nX + g_iOriginC, nY + g_iOriginR);}
int MouseLDown(UINT nX, UINT nY){return MouseLDownAbs(nX + g_iOriginC, nY + g_iOriginR);}
int MouseRDown(UINT nX, UINT nY){return MouseRDownAbs(nX + g_iOriginC, nY + g_iOriginR);}
int MouseMDown(UINT nX, UINT nY){return MouseMDownAbs(nX + g_iOriginC, nY + g_iOriginR);}
int MouseLUp(UINT nX, UINT nY){return MouseLUpAbs(nX + g_iOriginC, nY + g_iOriginR);}
int MouseRUp(UINT nX, UINT nY){return MouseRUpAbs(nX + g_iOriginC, nY + g_iOriginR);}
int MouseMUp(UINT nX, UINT nY){return MouseMUpAbs(nX + g_iOriginC, nY + g_iOriginR);}


int MoveMouse(CStringArray* saData)
{
	return MoveMouse(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}


int MouseLDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLDown(g_iC, g_iR);}
	return MouseLDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}
int MouseRDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRDown(g_iC, g_iR);}
	return MouseRDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

int MouseMDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMDown(g_iC, g_iR);}
	return MouseMDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}




int MouseLUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLUp(g_iC, g_iR);}
	return MouseLUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

int MouseRUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRUp(g_iC, g_iR);}
	return MouseRUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

int MouseMUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMUp(g_iC, g_iR);}
	return MouseMUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}



int MouseLClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseLDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseLUp(nX, nY);
}
int MouseRClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseRDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseRUp(nX, nY);
}
int MouseMClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseMDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseMUp(nX, nY);
}





int MouseLClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLClick(g_iC, g_iR);}
	return MouseLClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}
int MouseRClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRClick(g_iC, g_iR);}
	return MouseRClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

int MouseMClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMClick(g_iC, g_iR);}
	return MouseMClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}


int MoveMouseIncl(int iX, int iY)
{
	return MoveMouse(g_iC+iX, g_iR+iY);
}

int MoveMouseIncl(CStringArray* saData)
{
	return MoveMouseIncl(_ttoi(saData->GetAt(0)), _ttoi(saData->GetAt(1)));
}




int MouseSetOriginToWindow(CStringArray* saData)
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

int MouseSetOriginToImage(CStringArray* saData)
{
	int iWaitOn;

	int iTimeOut;

	if(saData->GetCount()<=4){return RETURN_FAILED;}

	CString sModelFilePath;
	int iR0, iC0, iR1, iC1;

	sModelFilePath.Format(_T("%s"), saData->GetAt(0));

	iC0=_ttoi(saData->GetAt(1));
	iR0=_ttoi(saData->GetAt(2));
	iC1=_ttoi(saData->GetAt(3));
	iR1=_ttoi(saData->GetAt(4));



	ImgRGB imgModel;
	ImgRGB imgTarget;
	ImgRGB imgMask;

	BOOL bRet;
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



int MoveMouseToImage(CStringArray* saData)
{

	if(saData->GetCount()<5){return RETURN_FAILED;}
	
	BOOL bRet;
	CString sModelFilePath;
	int iR0, iC0, iR1, iC1;

	sModelFilePath.Format(_T("%s"), saData->GetAt(0));

	iC0=_ttoi(saData->GetAt(1));
	iR0=_ttoi(saData->GetAt(2));
	iC1=_ttoi(saData->GetAt(3));
	iR1=_ttoi(saData->GetAt(4));


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
//	FindModel(&imgTarget, &imgModel, iR0+g_iOriginR, iC0+g_iOriginC, iR1+g_iOriginR, iC1+g_iOriginC, &iFoundR, &iFoundC);

	if(bRet != TRUE){return RETURN_FAILED;}

	MoveMouseAbs(iFoundC, iFoundR);

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
