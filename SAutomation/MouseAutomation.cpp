#include "stdafx.h"
#include "MouseAutomation.h"

int g_iClickDulation = 50;

int MouseLDown(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, dwX, dwY, NULL, NULL);
	return 0;
}
int MouseLDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLDown(g_iC, g_iR);}
	else{return MouseLDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

int MouseRDown(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, dwX, dwY, NULL, NULL);
	return 0;
}

int MouseRDown(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRDown(g_iC, g_iR);}
	else{return MouseRDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

int MouseLUp(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, dwX, dwY, NULL, NULL);
	return 0;
}
int MouseLUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLUp(g_iC, g_iR);}
	else{return MouseLUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

int MouseRUp(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, dwX, dwY, NULL, NULL);
	return 0;
}
int MouseRUp(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRUp(g_iC, g_iR);}
	else{return MouseRUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

int MouseLClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseLDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseLUp(nX, nY);
}

int MouseLClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseLClick(g_iC, g_iR);}
	else{return MouseLClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}


int MoveMouseIncl(int iX, int iY)
{
	return MoveMouse(g_iC+iX, g_iR + iY);
}

int MoveMouseIncl(CStringArray* saData)
{
	return MoveMouseIncl(_ttoi(saData->GetAt(0)), _ttoi(saData->GetAt(1)));
}

int MouseRClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseRDown(nX, nY);
	Sleep(g_iClickDulation);
	return MouseRUp(nX, nY);
}

int MouseRClick(CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseRClick(g_iC, g_iR);}
	else{return MouseRClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}


int MoveMouse(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, dwX, dwY, NULL, NULL);
	return 0;
}

int MoveMouse(CStringArray* saData)
{
	return MoveMouse(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

int MouseVWheel(int iWheel)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL, 0, 0, iWheel, NULL);
	return 0;
}

int MouseVWheel(CStringArray* saData)
{
	return MouseVWheel(_ttoi(saData->GetAt(0)));
}


#include "ImgProc.h"

int MoveMouseToImage(CStringArray* saData)
{

	if(saData->GetCount()<5){return -1;}

	CString sModelFilePath;
	int iR0, iC0, iR1, iC1;

	sModelFilePath.Format(_T("%s"), saData->GetAt(0));

	iC0=_ttoi(saData->GetAt(1));
	iR0=_ttoi(saData->GetAt(2));
	iC1=_ttoi(saData->GetAt(3));
	iR1=_ttoi(saData->GetAt(4));


	ImgRGB imgModel;
	ImgRGB imgTarget;
	imgModel.Assign(sModelFilePath);


	ULONGLONG ullStartMilliSec;
	ullStartMilliSec = GetTickCount64();

	BOOL bRet;
	int iFoundR, iFoundC;

	Screenshot(&imgTarget);
	bRet = IsInRegion(&imgTarget, &imgModel, iR0, iC0, iR1, iC1, &iFoundR, &iFoundC);

	if(bRet != TRUE){return -1;}

	MoveMouse(iFoundC, iFoundR);

	return 0;
}
