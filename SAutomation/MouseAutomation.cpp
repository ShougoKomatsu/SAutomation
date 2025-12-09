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
ReturnValue MouseDownAbs(MouseButton mouseButton, UINT nX, UINT nY)	
{
	switch(mouseButton)
	{
	case MOUSE_L_BUTTON:{	return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, nX, nY);}
	case MOUSE_R_BUTTON:{	return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, nX, nY);}
	case MOUSE_M_BUTTON:{	return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN, nX, nY);}
	}
	return RETURN_FAILED;
}
ReturnValue MouseUpAbs(MouseButton mouseButton, UINT nX, UINT nY)
{
	switch(mouseButton)
	{
	case MOUSE_L_BUTTON:{	return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, nX, nY);}
	case MOUSE_R_BUTTON:{	return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, nX, nY);}
	case MOUSE_M_BUTTON:{	return MouseEvent(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP, nX, nY);}
	}
	return RETURN_FAILED;
}


ReturnValue MoveMouse(UINT nX, UINT nY){return MoveMouseAbs(nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseDown(MouseButton mouseButton, UINT nX, UINT nY){return MouseDownAbs(mouseButton, nX + g_iOriginC, nY + g_iOriginR);}
ReturnValue MouseUp(MouseButton mouseButton, UINT nX, UINT nY){return MouseUpAbs(mouseButton, nX + g_iOriginC, nY + g_iOriginR);}


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


ReturnValue MouseDown(MouseButton mouseButton, CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseDown(mouseButton, g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseDown(mouseButton, point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseDown(mouseButton, iSrc1, iSrc2);
}



ReturnValue MouseUp(MouseButton mouseButton, CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseUp(mouseButton, g_iC, g_iR);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseUp(mouseButton, point.c, point.r);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseUp(mouseButton, iSrc1, iSrc2);
}


ReturnValue MouseClick(MouseButton mouseButton,  UINT nX, UINT nY, int iClickDulation)
{
	MoveMouse(nX, nY);
	MouseDown(mouseButton, nX, nY);

	Sleep(iClickDulation);
	MouseUp(mouseButton, nX, nY);
	return RETURN_FAILED;
}

ReturnValue MouseDragAndDrop(MouseButton mouseButton, UINT nXFrom, UINT nYFrom,UINT nXTo, UINT nYTo, int iClickTimeMilliSec, int iDragTimeMilliSec)
{
	MoveMouse(nXFrom, nYFrom);
	MouseDown(mouseButton, nXFrom, nYFrom);
	Sleep(iClickTimeMilliSec);

	MoveMouse(nXTo, nYTo);
	Sleep(iDragTimeMilliSec);
	MouseUp(mouseButton, nXTo, nYTo); 
	return RETURN_NORMAL;
}

ReturnValue MouseDragAndDrop(MouseButton mouseButton, CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()<2){return RETURN_FAILED;}
	int iXFrom, iYFrom, iXTo, iYTo;
	int iNextArgIndex=0;

	if(saData->GetAt(iNextArgIndex).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(iNextArgIndex),_T(","),&sArg,&sDummy);iNextArgIndex++;
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet != TRUE){return RETURN_FAILED;}
		iXFrom=point.c;
		iYFrom=point.r;
	}
	else
	{
		iXFrom=GetIntValue(sDir, iScene, saData->GetAt(iNextArgIndex));iNextArgIndex++;
		iYFrom=GetIntValue(sDir, iScene, saData->GetAt(iNextArgIndex));iNextArgIndex++;
	}

	if(saData->GetCount()<=iNextArgIndex){return RETURN_FAILED;}
	if(saData->GetAt(iNextArgIndex).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(iNextArgIndex),_T(","),&sArg,&sDummy);iNextArgIndex++;
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet != TRUE){return RETURN_FAILED;}
		iXTo=point.c;
		iYTo=point.r;
	}
	else
	{
		iXTo=GetIntValue(sDir, iScene, saData->GetAt(iNextArgIndex));iNextArgIndex++;
		if(saData->GetCount()<=iNextArgIndex){return RETURN_FAILED;}
		iYTo=GetIntValue(sDir, iScene, saData->GetAt(iNextArgIndex));iNextArgIndex++;
	}
	int iClickTimeMilliSec;
	int iDragTimeMilliSec;

	if(saData->GetCount()<=iNextArgIndex){iClickTimeMilliSec=50;}
	else
	{
		iClickTimeMilliSec=GetIntValue(sDir, iScene, saData->GetAt(iNextArgIndex));iNextArgIndex++;
		if(iClickTimeMilliSec<=0){iClickTimeMilliSec=50;}
	}

	if(saData->GetCount()<=iNextArgIndex){iDragTimeMilliSec=50;}
	else
	{
		iDragTimeMilliSec=GetIntValue(sDir, iScene, saData->GetAt(iNextArgIndex));iNextArgIndex++;
		if(iDragTimeMilliSec<=0){iDragTimeMilliSec=50;}
	}
	return MouseDragAndDrop(mouseButton, iXFrom, iYFrom, iXTo, iYTo, iClickTimeMilliSec,  iDragTimeMilliSec);
}


ReturnValue MouseClick(MouseButton mouseButton, CString sDir, int iScene, CStringArray* saData)
{
	if(saData->GetCount()==0){return MouseClick(mouseButton, g_iC, g_iR, g_iClickDulation);}
	if(saData->GetAt(0).Left(8).CompareNoCase(_T("VarPoint"))==0)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		Point point;
		BOOL bRet = GetPointValue(sDir, iScene, sArg, &point);
		if(bRet==FALSE){return RETURN_FAILED;}
		return MouseClick(mouseButton, point.c, point.r, g_iClickDulation);
	}
	int iSrc1=GetIntValue(sDir, iScene, saData->GetAt(0));
	int iSrc2=GetIntValue(sDir, iScene, saData->GetAt(1));
	return MouseClick(mouseButton, iSrc1, iSrc2, g_iClickDulation);
}

ReturnValue MouseRepeatClick(MouseButton mouseButton, CString sDir, int iScene, CStringArray* saData,LPVOID Halt, LPVOID Suspend)
{
	int iTimeMillisec;
	if(saData->GetCount()==0){iTimeMillisec=-1;}
	if(saData->GetCount()>=1)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(0),_T(")"),&sArg,&sDummy);
		iTimeMillisec= GetIntValue(sDir, iScene, sArg);
	}

	int iClickDulation=g_iClickDulation;
	if(saData->GetCount()>=2)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(1),_T(")"),&sArg,&sDummy);
		iClickDulation= GetIntValue(sDir, iScene, sArg);
	}
	int iClickSleep = 1;
	if(saData->GetCount()>=3)
	{
		CString sArg, sDummy;
		ExtractData(saData->GetAt(2),_T(")"),&sArg,&sDummy);
		iClickSleep = GetIntValue(sDir, iScene, sArg);
	}

	ULONGLONG ullStartMilliSec;
	ULONGLONG ullSuspendStartMilliSec;
	ULONGLONG ullSuspendedMilliSec;
	ullStartMilliSec = GetTickCount64();
	ullSuspendedMilliSec=0;

	MouseClick(mouseButton, g_iC, g_iR, iClickDulation);
	Sleep(iClickSleep);
	while(1)
	{
		if(iTimeMillisec>=0)
		{
			if(GetTickCount64()>=ullStartMilliSec+iTimeMillisec/g_dSpeedMult+ullSuspendedMilliSec){break;}
		}

		MouseClick(mouseButton, g_iC, g_iR, iClickDulation);
		if(Halt != NULL){if((*(int*)Halt) == 1){return RETURN_HALT;}}
		if(Suspend != NULL)
		{
			if((*(int*)Suspend) == 1)
			{
				ullSuspendStartMilliSec = GetTickCount64();
				while((*(int*)Suspend) == 1)
				{
					if((*(int*)Halt) == 1){return RETURN_HALT;}
					Sleep(1);
				}
				ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;
				continue;
			}
		}
		Sleep(iClickSleep);
	}
	return RETURN_NORMAL;
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
	int iNextIndex;
	bRet = GetRectData(sDir, iScene, saData, 1, &iR0, &iC0, &iR1, &iC1, &iNextIndex);

	CString sModelFilePath;

	CString sModel;
	sModel.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	GetModelFilePath(sDir, sModel, &sModelFilePath);



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
	int iNextIndex;
	bRet = GetRectData(sDir, iScene, saData, 1, &iR0, &iC0, &iR1, &iC1, &iNextIndex);


	CString sModelFilePath;
	
	CString sModel;
	sModel.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	GetModelFilePath(sDir, sModel, &sModelFilePath);

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

ReturnValue MouseClickImage(MouseButton mouseButton, CString sDir, int iScene, CStringArray* saData)
{
	BOOL bRet;
	if(saData->GetCount()<2){return RETURN_FAILED;}

	int iR0, iC0, iR1, iC1;
	int iNextIndex;
	bRet = GetRectData(sDir, iScene, saData, 1, &iR0, &iC0, &iR1, &iC1, &iNextIndex);

	CString sModelFilePath;
	
	CString sModel;
	sModel.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
	GetModelFilePath(sDir, sModel, &sModelFilePath);


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
	MouseDownAbs(mouseButton, iFoundC, iFoundR);
	Sleep(g_iClickDulation);
	return MouseUpAbs(mouseButton, iFoundC, iFoundR);

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
