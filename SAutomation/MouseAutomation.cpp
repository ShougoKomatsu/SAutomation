#include "stdafx.h"
#include "MouseAutomation.h"
#include "Window.h"
#include "ImgProc.h"
int g_iClickDulation = 50;

int MouseLDownAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}
int MouseLDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLDownAbs(g_iC, g_iR);}
	else{return MouseLDownAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);}
}

int MouseRDownAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}

int MouseRDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRDownAbs(g_iC+g_iC_Origin, g_iR+g_iR_Origin);}
	else{return MouseRDownAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);}
}

int MouseMDownAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}

int MouseMDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMDownAbs(g_iC+g_iC_Origin, g_iR+g_iR_Origin);}
	else{return MouseMDownAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);}
}




int MouseLUpAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}
int MouseLUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLUp(g_iC+g_iC_Origin, g_iR+g_iR_Origin);}
	else{return MouseLUpAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);}
}

int MouseRUpAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}
int MouseRUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRUpAbs(g_iC+g_iC_Origin, g_iR+g_iR_Origin);}
	else{return MouseRUpAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);}
}

int MouseMUpAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}
int MouseMUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMUpAbs(g_iC+g_iC_Origin, g_iR+g_iR_Origin);}
	else{return MouseMUpAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);}
}




int MouseLClickAbs(UINT nX, UINT nY)
{
	MoveMouseAbs(nX, nY);
	MouseLDownAbs(nX, nY);
	Sleep(g_iClickDulation);
	return MouseLUpAbs(nX, nY);
}

int MouseLClick(UINT nX, UINT nY)
{
	return MouseLClickAbs(nX+g_iC_Origin, nY+g_iR_Origin);
}


int MouseLClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLClickAbs(g_iC, g_iR);}
	else{return MouseLClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}


int MoveMouseIncl(int iX, int iY)
{
	return MoveMouse(g_iC+g_iC_Origin+iX, g_iR + g_iR_Origin+iY);
}

int MoveMouseIncl(CStringArray* saData)
{
	return MoveMouseIncl(_ttoi(saData->GetAt(0)), _ttoi(saData->GetAt(1)));
}

int MouseRClickAbs(UINT nX, UINT nY)
{
	MoveMouseAbs(nX, nY);
	MouseRDownAbs(nX, nY);
	Sleep(g_iClickDulation);
	return MouseRUpAbs(nX, nY);
}

int MouseRClick(UINT nX, UINT nY)
{
	return MouseRClickAbs(nX+g_iC_Origin, nY+g_iR_Origin);
}

int MouseRClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRClickAbs(g_iC, g_iR);}
	else{return MouseRClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

int MouseMClickAbs(UINT nX, UINT nY)
{
	MoveMouseAbs(nX, nY);
	MouseMDownAbs(nX, nY);
	Sleep(g_iClickDulation);
	return MouseMUpAbs(nX, nY);
}

int MouseMClick(UINT nX, UINT nY)
{
	return MouseMClickAbs(nX+g_iC_Origin, nY+g_iR_Origin);
}
int MouseMClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseMClickAbs(g_iC, g_iR);}
	else{return MouseMClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

int MouseSetOriginToWindow(CStringArray* saData)
{
	int iRNowAbs=g_iR+g_iR_Origin;
	int iCNowAbs=g_iC+g_iC_Origin;
	if(saData->GetAt(0).Compare(_T("Desktop"))==0)
	{
		g_iR=iRNowAbs;
		g_iC=iCNowAbs;
		g_iR_Origin=0; 
		g_iC_Origin=0;
		return RETURN_NORMAL;
	}

	RECT rect;
	BOOL bRet;
	bRet = GetWindowRectByName(saData->GetAt(0),&rect);
	if(bRet!=TRUE)
	{
		g_iR=iRNowAbs;
		g_iC=iCNowAbs;
		g_iR_Origin = 0;
		g_iC_Origin = 0;
		return RETURN_FAILED;
	}
	g_iC_Origin = rect.left;
	g_iR_Origin = rect.top;
	g_iR=iRNowAbs-g_iR_Origin;
	g_iC=iCNowAbs-g_iC_Origin;
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
		bRet = IsInRegionMask(&imgTarget, &imgModel, &imgMask, iR0+g_iR_Origin, iC0+g_iC_Origin, iR1+g_iR_Origin, iC1+g_iC_Origin, &iFoundR, &iFoundC);
	}
	else
	{
		bRet = IsInRegion(&imgTarget, &imgModel, iR0+g_iR_Origin, iC0+g_iC_Origin, iR1+g_iR_Origin, iC1+g_iC_Origin, &iFoundR, &iFoundC);
	}
	if(bRet != TRUE){return RETURN_FAILED;}


	
	int iRNowAbs=g_iR+g_iR_Origin;
	int iCNowAbs=g_iC+g_iC_Origin;
	g_iC_Origin = iFoundC;
	g_iR_Origin = iFoundR;
	g_iR=iRNowAbs-g_iR_Origin;
	g_iC=iCNowAbs-g_iC_Origin;
	return RETURN_NORMAL;
}


int MoveMouseAbs(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, dwX, dwY, NULL, NULL);
	return RETURN_NORMAL;
}

int MoveMouse(CStringArray* saData)
{
	return MoveMouseAbs(_ttoi(saData->GetAt(0))+g_iC_Origin,_ttoi(saData->GetAt(1))+g_iR_Origin);
}

int MouseVWheel(int iWheel)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL, 0, 0, iWheel, NULL);
	return RETURN_NORMAL;
}

int MouseVWheel(CStringArray* saData)
{
	return MouseVWheel(_ttoi(saData->GetAt(0)));
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
		bRet = IsInRegionMask(&imgTarget, &imgModel, &imgMask, iR0+g_iR_Origin, iC0+g_iC_Origin, iR1+g_iR_Origin, iC1+g_iC_Origin, &iFoundR, &iFoundC);
	}
	else
	{
		bRet = IsInRegion(&imgTarget, &imgModel, iR0+g_iR_Origin, iC0+g_iC_Origin, iR1+g_iR_Origin, iC1+g_iC_Origin, &iFoundR, &iFoundC);
	}
	FindModel(&imgTarget, &imgModel, iR0+g_iR_Origin, iC0+g_iC_Origin, iR1+g_iR_Origin, iC1+g_iC_Origin, &iFoundR, &iFoundC);

	if(bRet != TRUE){return RETURN_FAILED;}

	MoveMouse(iFoundC, iFoundR);

	return RETURN_NORMAL;
}
