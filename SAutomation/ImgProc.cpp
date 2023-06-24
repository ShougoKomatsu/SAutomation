#include "stdafx.h"
#include "ImgProc.h"

BOOL WriteImage(ImgRGB* imgRGB, CString sFilePath)
{
	BITMAPINFOHEADER bmih;
	BOOL bRet;
	
	CFile f;
	BITMAPFILEHEADER bmfh;
	ULONGLONG ullSize;
	ULONG ulSize;
	BYTE* byData;


	
	bRet = f.Open(_T("d:\\aaa.bmp"), CFile::modeRead);
	if(bRet != TRUE){return FALSE;}

	ullSize = f.SeekToEnd();
	if(ullSize>=ULONG_MAX){f.Close(); return FALSE;}

	ulSize = (ULONG)ullSize;
	f.SeekToBegin();
	byData = new BYTE[ulSize];
	f.Read(byData, ulSize);
	f.Close();

	
	for(int i=0; i<sizeof(bmfh); i++)
	{
		((BYTE*)&bmfh)[i]=byData[i];
	}
	if(bmfh.bfType != 0x4d42){return FALSE;}

	for(int i=0; i<sizeof(bmih); i++)
	{
		((BYTE*)&bmih)[i]=byData[sizeof(bmfh)+i];
	}

	int iBitSize;
	if(((imgRGB->iWidth*3)%4)==0)
	{
		iBitSize = (imgRGB->iWidth*3)*(imgRGB->iHeight);
	}
	else
	{
		iBitSize = ((imgRGB->iWidth*3)+(4-((imgRGB->iWidth*3)%4)))*(imgRGB->iHeight);
	}

	bmfh.bfType=0x4d42;
	bmfh.bfSize =  0x36+iBitSize;
	bmfh.bfOffBits = 0x36;
	bmfh.bfReserved1=0;
	bmfh.bfReserved2 = 0;

	bmih.biSize=0x00000028;
	bmih.biWidth	=imgRGB->iWidth;
	bmih.biHeight=imgRGB->iHeight;
	bmih.biPlanes=1;
	bmih.biBitCount=24;
	bmih.biCompression=0;
	bmih.biSizeImage	=iBitSize;
	bmih.biXPelsPerMeter	=0;
	bmih.biYPelsPerMeter	=0;
	bmih.biClrUsed	=0;
	bmih.biClrImportant		=0;


	bRet = f.Open(sFilePath, CFile::modeCreate|CFile::modeWrite);
	if(bRet != TRUE){return FALSE;}


	f.Write((BYTE*)&bmfh,sizeof(bmfh));
	f.Write((BYTE*)&bmih,sizeof(bmih));


	if(bmfh.bfType != 0x4d42){return FALSE;}

	BYTE* byOutBuf;

	byOutBuf = new BYTE[iBitSize];

	int iFiller;

	if(((imgRGB->iWidth*3)%4)==0)
	{
		iFiller = 0;
	}
	else
	{
		iFiller = (4-((imgRGB->iWidth*3)%4));
	}
	if(imgRGB->iChannel==CHANNEL_3_8)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFiller+0] = imgRGB->byImgB[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFiller+1] = imgRGB->byImgG[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFiller+2] = imgRGB->byImgR[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
			}
		}
	}

	if(imgRGB->iChannel==CHANNEL_1_24)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFiller+0] = imgRGB->byImgR[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+0];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFiller+1] = imgRGB->byImgR[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+1];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFiller+2] = imgRGB->byImgR[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+2];
			}
		}
	}


	f.Write((void*)(byOutBuf),iBitSize);
	f.Close();

	return TRUE;
}
BOOL Screenshot(ImgRGB* imgRGB)
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

	imgRGB->Set((rect.right-rect.left), (rect.bottom-rect.top), CHANNEL_1_24);
	GetDIBits(hMemDC, hBitmap, 0, rect.bottom, imgRGB->byImgR, (BITMAPINFO *)&bmpInfo, DIB_RGB_COLORS);


	ReleaseDC(hDesktop, hDC);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return TRUE;
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

BOOL ImgRGB::Assign(CString sFilePath)
{

	this->Init();

	BITMAPINFOHEADER bmih;
	CFileFind cf;
	BOOL bRet;
	
	CFile f;
	BITMAPFILEHEADER bmfh;
	ULONGLONG ullSize;
	ULONG ulSize;
	BYTE* byData;

	bRet = cf.FindFile(sFilePath);
	if(bRet != TRUE){cf.Close(); return FALSE;}
	cf.Close();

	bRet = f.Open(sFilePath, CFile::modeRead);
	if(bRet != TRUE){return FALSE;}

	ullSize = f.SeekToEnd();
	if(ullSize>=ULONG_MAX){f.Close(); return FALSE;}
	ulSize = (ULONG)ullSize;
	f.SeekToBegin();
	byData = new BYTE[ulSize];
	f.Read(byData, ulSize);
	f.Close();

	for(int i=0; i<sizeof(bmfh); i++)
	{
		((BYTE*)&bmfh)[i]=byData[i];
	}
	if(bmfh.bfType != 0x4d42){return FALSE;}

	for(int i=0; i<sizeof(bmih); i++)
	{
		((BYTE*)&bmih)[i]=byData[sizeof(bmfh)+i];
	}


	int iWidthLocal;
	int iHeightLocal;

	iWidthLocal = bmih.biWidth;
	if(bmih.biHeight<0){iHeightLocal=-1*(bmih.biHeight);}
	else{iHeightLocal=(bmih.biHeight);}

	this->Set(iWidthLocal, iHeightLocal, CHANNEL_3_8);

	ULONG ulOffset;
	ulOffset=bmfh.bfOffBits;
	int iFiller;

	iFiller = iWidth%4;

		for(int r=0; r<iHeightLocal; r++)
		{
			for(int c=0; c< iWidthLocal; c++)
			{
				(this->byImgB)[(this->iHeight - r -1) *this->iWidth+c]=byData[ulOffset +3*( r*iWidthLocal + c)+r*iFiller+0];
				(this->byImgG)[(this->iHeight - r -1) *this->iWidth+c]=byData[ulOffset +3*( r*iWidthLocal + c)+r*iFiller+1];
				(this->byImgR)[(this->iHeight - r -1) *this->iWidth+c]=byData[ulOffset +3*( r*iWidthLocal + c)+r*iFiller+2];
			}
		}

	delete [] byData;

	return TRUE;
}