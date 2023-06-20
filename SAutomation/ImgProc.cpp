#include "stdafx.h"
#include "ImgProc.h"


void test()
{
	HWND hDesktop = GetDesktopWindow();
	RECT rect;
	GetWindowRect(hDesktop, &rect);


	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = rect.right;
	bmpInfo.bmiHeader.biHeight = -rect.bottom;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;


	LPDWORD lpPixel;
	HDC hDC = GetDC(hDesktop);
	HBITMAP hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
	HDC hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC, hBitmap);


	BitBlt(hMemDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);

	ImgRGB imgRGB;
	imgRGB.Set((rect.right-rect.left+1), (rect.bottom-rect.top+1), CHANNEL_1_24);
	GetDIBits(hMemDC, hBitmap, 0, rect.bottom, imgRGB.byImgR, (BITMAPINFO *)&bmpInfo, DIB_RGB_COLORS);


	ReleaseDC(hDesktop, hDC);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return ;
}

BOOL IsInRegion(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1)
{
	int iModelHeight;
	int iModelWidth;

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}

	
	iModelHeight = imgModel->iHeight;
	iModelWidth = imgModel->iWidth;

	int iScanHeight;
	int iScanWidth;
	iScanHeight = iR1-iR0-iModelHeight + 2;
	iScanWidth = iC1-iC0-iModelWidth + 2;

	if(iScanHeight<=0){return FALSE;}
	if(iScanWidth<=0){return FALSE;}
	
	BOOL bFound;

	if((imgTarget->iChannel==CHANNEL_3_8) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR=iR0; iTargetR<iR0+iScanHeight; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iC0 + iScanWidth; iTargetC++)
			{
				bFound = TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						if(imgTarget->byImgR[(iTargetR + r)*imgTarget->iWidth+(iTargetC+c)] != (imgModel->byImgR[(r)*imgModel->iWidth+(c)])){bFound = FALSE; break;}
						if(imgTarget->byImgG[(iTargetR + r)*imgTarget->iWidth+(iTargetC+c)] != (imgModel->byImgG[(r)*imgModel->iWidth+(c)])){bFound = FALSE; break;}
						if(imgTarget->byImgB[(iTargetR + r)*imgTarget->iWidth+(iTargetC+c)] != (imgModel->byImgB[(r)*imgModel->iWidth+(c)])){bFound = FALSE; break;}
					}
					if(bFound == FALSE){break;}
				}
				if(bFound == TRUE){return TRUE;}
				break;
			}
		}
	}
	
	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_1_24))
	{
		for(int iTargetR=iR0; iTargetR<iR0+iScanHeight; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iC0 + iScanWidth; iTargetC++)
			{
				bFound = TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						if(imgTarget->byImgR[3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c))+0] != (imgModel->byImgR[3*((r)*imgModel->iWidth+(c))+0])){bFound = FALSE; break;}
						if(imgTarget->byImgR[3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c))+1] != (imgModel->byImgR[3*((r)*imgModel->iWidth+(c))+1])){bFound = FALSE; break;}
						if(imgTarget->byImgR[3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c))+2] != (imgModel->byImgR[3*((r)*imgModel->iWidth+(c))+2])){bFound = FALSE; break;}
					}
					if(bFound == FALSE){break;}
				}
				if(bFound == TRUE){return TRUE;}
				break;
			}
		}
	}
	
	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR=iR0; iTargetR<iR0+iScanHeight; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iC0 + iScanWidth; iTargetC++)
			{
				bFound = TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						if(imgTarget->byImgR[3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c))+0] != (imgModel->byImgR[(r)*imgModel->iWidth+(c)])){bFound = FALSE; break;}
						if(imgTarget->byImgR[3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c))+1] != (imgModel->byImgG[(r)*imgModel->iWidth+(c)])){bFound = FALSE; break;}
						if(imgTarget->byImgR[3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c))+2] != (imgModel->byImgB[(r)*imgModel->iWidth+(c)])){bFound = FALSE; break;}
					}
					if(bFound == FALSE){break;}
				}
				if(bFound == TRUE){return TRUE;}
				break;
			}
		}
	}

	return FALSE;
}

BOOL Assign(CString sFilePath)
{
	BITMAPINFOHEADER bmih;
	CFileFind cf;
	BOOL bRet;

	bRet = cf.FindFile(sFilePath);
	if(bRet != TRUE){return FALSE;}




	return TRUE;
}