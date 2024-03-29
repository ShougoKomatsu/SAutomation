#include "stdafx.h"
#include "ImgProc.h"

BOOL WriteImage(ImgRGB* imgRGB, CString sFilePath)
{
	BITMAPINFOHEADER bmih;
	BOOL bRet;
	
	CFile f;
	BITMAPFILEHEADER bmfh;


	
	int iFillerSize;

	if(((imgRGB->iWidth*3)%4)==0)
	{
		iFillerSize = 0;
	}
	else
	{
		iFillerSize = (4-((imgRGB->iWidth*3)%4));
	}


	int iBitSize;

	iBitSize = ((imgRGB->iWidth*3)+iFillerSize)*(imgRGB->iHeight);

	bmfh.bfType=0x4d42;
	bmfh.bfSize =  0x36+iBitSize;
	bmfh.bfOffBits = 0x36;
	bmfh.bfReserved1=0;
	bmfh.bfReserved2 = 0;

	bmih.biSize=0x00000028;
	bmih.biWidth=imgRGB->iWidth;
	bmih.biHeight=imgRGB->iHeight;
	bmih.biPlanes=1;
	bmih.biBitCount=24;
	bmih.biCompression=0;
	bmih.biSizeImage=iBitSize;
	bmih.biXPelsPerMeter=0;
	bmih.biYPelsPerMeter=0;
	bmih.biClrUsed=0;
	bmih.biClrImportant	=0;


	bRet = f.Open(sFilePath, CFile::modeCreate|CFile::modeWrite);
	if(bRet != TRUE){return FALSE;}


	f.Write((BYTE*)&bmfh,sizeof(bmfh));
	f.Write((BYTE*)&bmih,sizeof(bmih));
	

	BYTE* byOutBuf;

	byOutBuf = new BYTE[iBitSize];

	if(imgRGB->iChannel==CHANNEL_3_8)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+0] = imgRGB->byImgB[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+1] = imgRGB->byImgG[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+2] = imgRGB->byImgR[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
			}
		}
	}

	if(imgRGB->iChannel==CHANNEL_1_24)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+0] = imgRGB->byImgR[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+0];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+1] = imgRGB->byImgR[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+1];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+2] = imgRGB->byImgR[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+2];
			}
		}
	}


	f.Write((void*)(byOutBuf),iBitSize);
	f.Close();
	delete [] byOutBuf;

	return TRUE;
}
BOOL CropImage(ImgRGB* imgRGBin, ImgRGB* imgRGBout, int iR0, int iC0, int iR1, int iC1)
{
	if(imgRGBin==NULL){return FALSE;}
	if(imgRGBout==NULL){return FALSE;}
	if(iR0>iR1){return FALSE;}
	if(iC0>iC1){return FALSE;}
	if(iR0<0){return FALSE;}
	if(iC0<0){return FALSE;}
	if(iR1>=imgRGBin->iHeight){return FALSE;}
	if(iC1>=imgRGBin->iWidth){return FALSE;}

	if(imgRGBin==imgRGBout)
	{
		//
	}
	else
	{
		imgRGBout->Init();
		imgRGBout->Set(iC1-iC0+1, iR1-iR0+1, imgRGBin->iChannel);
		if(imgRGBin->iChannel==CHANNEL_1_24)
		{

			for(int r=iR0; r<=iR1; r++)
			{for(int c=iC0; c<=iC1; c++)
			{
				imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0))+0]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+0];
				imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0))+1]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+1];
				imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0))+2]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+2];
			}}
		}
		if(imgRGBin->iChannel==CHANNEL_3_8)
		{
			for(int r=iR0; r<=iR1; r++)
			{for(int c=iC0; c<=iC1; c++)
			{
				imgRGBout->byImgB[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgB[r*imgRGBin->iWidth+c];
				imgRGBout->byImgG[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgG[r*imgRGBin->iWidth+c];
				imgRGBout->byImgR[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
			}}
		}
		if(imgRGBin->iChannel==CHANNEL_1_8)
		{
			for(int r=iR0; r<=iR1; r++)
			{for(int c=iC0; c<=iC1; c++)
			{
				imgRGBout->byImgR[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
			}}
		}


	}
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

	int iWidth;
	int iHeight;
	iWidth = (rect.right-rect.left);
	iHeight = (rect.bottom-rect.top);

	imgRGB->Set(iWidth, iHeight, CHANNEL_1_24);

	int iFillerSize;

	if((iWidth%4)==0)
	{
		iFillerSize = 0;
	}
	else
	{
		iFillerSize = 4-(iWidth*3)%4;
	}

	int iBitSize;
	iBitSize = ((iWidth*3)+iFillerSize)*iHeight;
	
	BYTE* byDataTemp;
	byDataTemp = new BYTE[iBitSize];

	GetDIBits(hMemDC, hBitmap, 0, rect.bottom, byDataTemp, (BITMAPINFO *)&bmpInfo, DIB_RGB_COLORS);
	for(int r=0; r<iHeight; r++)
	{
		for(int c=0; c<iWidth; c++)
		{
			imgRGB->byImgR[3*(r*iWidth+c)+0] = byDataTemp[3*(r*iWidth+c) + r*iFillerSize +0];
			imgRGB->byImgR[3*(r*iWidth+c)+1] = byDataTemp[3*(r*iWidth+c) + r*iFillerSize +1];
			imgRGB->byImgR[3*(r*iWidth+c)+2] = byDataTemp[3*(r*iWidth+c) + r*iFillerSize +2];
		}
	}
	delete [] byDataTemp;


	ReleaseDC(hDesktop, hDC);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return TRUE;
}

BOOL IsInRegion(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC)
{
	int iModelHeight;
	int iModelWidth;

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}

	
	iModelHeight = imgModel->iHeight;
	iModelWidth = imgModel->iWidth;


	int iR1Local;
	int iC1Local;

	iR1Local = iR1;
	iC1Local = iC1;

	if(iR1Local>=imgTarget->iHeight){iR1Local = imgTarget->iHeight-1;}
	if(iC1Local>=imgTarget->iWidth){iC1Local = imgTarget->iWidth-1;}

	int iScanHeight;
	int iScanWidth;
	iScanHeight = iR1Local-iR0-iModelHeight + 2;
	iScanWidth = iC1Local-iC0-iModelWidth + 2;

	if(iScanHeight<=0){return FALSE;}
	if(iScanWidth<=0){return FALSE;}
	
	BOOL bFound;
	int iREnd, iCEnd;

	iREnd = iR0+iScanHeight;
	iCEnd = iC0+iScanWidth;

	int iPtrTarget;
	int iPtrModel;
	
	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR = iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC = iC0; iTargetC<iCEnd; iTargetC++)
			{
				bFound = TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = (r)*imgModel->iWidth+(c);
						if(imgTarget->byImgR[iPtrTarget + 0] != (imgModel->byImgB[iPtrModel])){bFound = FALSE; break;}
						if(imgTarget->byImgR[iPtrTarget + 1] != (imgModel->byImgG[iPtrModel])){bFound = FALSE; break;}
						if(imgTarget->byImgR[iPtrTarget + 2] != (imgModel->byImgR[iPtrModel])){bFound = FALSE; break;}
					}
					if(bFound == FALSE){break;}
				}
				if(bFound == TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC; 
				
				return TRUE;}
			}
		}
	}

	if((imgTarget->iChannel==CHANNEL_3_8) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR=iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iCEnd; iTargetC++)
			{
				bFound = TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = (iTargetR + r)*imgTarget->iWidth+(iTargetC+c);
						iPtrModel = (r)*imgModel->iWidth+(c);
						if(imgTarget->byImgR[iPtrTarget] != (imgModel->byImgR[iPtrModel])){bFound = FALSE; break;}
						if(imgTarget->byImgG[iPtrTarget] != (imgModel->byImgG[iPtrModel])){bFound = FALSE; break;}
						if(imgTarget->byImgB[iPtrTarget] != (imgModel->byImgB[iPtrModel])){bFound = FALSE; break;}
					}
					if(bFound == FALSE){break;}
				}
				if(bFound == TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC; return TRUE;}
				break;
			}
		}
	}
	
	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_1_24))
	{
		for(int iTargetR=iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iCEnd; iTargetC++)
			{
				bFound = TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = 3*((r)*imgModel->iWidth+(c));
						if(imgTarget->byImgR[iPtrTarget+0] != (imgModel->byImgR[iPtrModel + 0])){bFound = FALSE; break;}
						if(imgTarget->byImgR[iPtrTarget+1] != (imgModel->byImgR[iPtrModel + 1])){bFound = FALSE; break;}
						if(imgTarget->byImgR[iPtrTarget+2] != (imgModel->byImgR[iPtrModel + 2])){bFound = FALSE; break;}
					}
					if(bFound == FALSE){break;}
				}
				if(bFound == TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC; return TRUE;}
				break;
			}
		}
	}
	

	return FALSE;
}


inline BYTE bySubAbs(BYTE by1, BYTE by2)
{
	if(by1>=by2){return by1-by2;}
	return by2-by1;
}

BOOL CropImage2(ImgRGB* imgRGBin, ImgRGB* imgRGBout, int iR0, int iC0, int iR1, int iC1)
{
	if(imgRGBin==NULL){return FALSE;}
	if(imgRGBout==NULL){return FALSE;}
	if(iR0>iR1){return FALSE;}
	if(iC0>iC1){return FALSE;}
	if(iR0<0){return FALSE;}
	if(iC0<0){return FALSE;}
	if(iR1>=imgRGBin->iHeight){return FALSE;}
	if(iC1>=imgRGBin->iWidth){return FALSE;}

	if(imgRGBin==imgRGBout)
	{
		//
	}
	else
	{
		imgRGBout->Init();
		int iWidthP1;
		int iHeightP1;
		if(((iC1-iC0+1)%2)==0){iWidthP1=0;}else{iWidthP1=1;}
		if(((iR1-iR0+1)%2)==0){iHeightP1=0;}else{iHeightP1=1;}

		imgRGBout->Set(iC1-iC0+1+iWidthP1, iR1-iR0+1+iHeightP1, imgRGBin->iChannel);
		if(imgRGBin->iChannel==CHANNEL_1_24)
		{

			for(int r=iR0; r<=iR1; r++)
			{
				for(int c=iC0; c<=iC1; c++)
				{
					imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0))+0]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+0];
					imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0))+1]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+1];
					imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0))+2]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+2];
				}
				if(iWidthP1==1)
				{
					int c=iC1;
					imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0+1))+0]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+0];
					imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0+1))+1]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+1];
					imgRGBout->byImgR[3*((r-iR0)*imgRGBout->iWidth+(c-iC0+1))+2]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+2];
				}
			}
			if(iHeightP1==1)
			{
				int r=iR1;
				for(int c=iC0; c<=iC1; c++)
				{
					imgRGBout->byImgR[3*((r+1-iR0)*imgRGBout->iWidth+(c-iC0))+0]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+0];
					imgRGBout->byImgR[3*((r+1-iR0)*imgRGBout->iWidth+(c-iC0))+1]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+1];
					imgRGBout->byImgR[3*((r+1-iR0)*imgRGBout->iWidth+(c-iC0))+2]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+2];
				}
				if(iWidthP1==1)
				{
					int c=iC1;
					imgRGBout->byImgR[3*((r+1-iR0)*imgRGBout->iWidth+(c-iC0+1))+0]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+0];
					imgRGBout->byImgR[3*((r+1-iR0)*imgRGBout->iWidth+(c-iC0+1))+1]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+1];
					imgRGBout->byImgR[3*((r+1-iR0)*imgRGBout->iWidth+(c-iC0+1))+2]=imgRGBin->byImgR[3*(r*imgRGBin->iWidth+c)+2];
				}
			}
		}
		if(imgRGBin->iChannel==CHANNEL_3_8)
		{
			for(int r=iR0; r<=iR1; r++)
			{
				for(int c=iC0; c<=iC1; c++)
				{
					imgRGBout->byImgB[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgB[r*imgRGBin->iWidth+c];
					imgRGBout->byImgG[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgG[r*imgRGBin->iWidth+c];
					imgRGBout->byImgR[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];

				}
				if(iWidthP1==1)
				{
					int c=iC1;
					imgRGBout->byImgB[(r-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgB[r*imgRGBin->iWidth+c];
					imgRGBout->byImgG[(r-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgG[r*imgRGBin->iWidth+c];
					imgRGBout->byImgR[(r-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
				}
			}
			if(iHeightP1==1)
			{
				int r=iR1;
				for(int c=iC0; c<=iC1; c++)
				{
					imgRGBout->byImgB[(r+1-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgB[r*imgRGBin->iWidth+c];
					imgRGBout->byImgG[(r+1-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgG[r*imgRGBin->iWidth+c];
					imgRGBout->byImgR[(r+1-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];

				}
				if(iWidthP1==1)
				{
					int c=iC1;
					imgRGBout->byImgB[(r+1-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgB[r*imgRGBin->iWidth+c];
					imgRGBout->byImgG[(r+1-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgG[r*imgRGBin->iWidth+c];
					imgRGBout->byImgR[(r+1-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
				}
			}
		}
		if(imgRGBin->iChannel==CHANNEL_1_8)
		{
			for(int r=iR0; r<=iR1; r++)
			{
				for(int c=iC0; c<=iC1; c++)
				{
					imgRGBout->byImgR[(r-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];

				}
				if(iWidthP1==1)
				{
					int c=iC1;
					imgRGBout->byImgR[(r-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
				}
			}
			if(iHeightP1==1)
			{
				int r=iR1;
				for(int c=iC0; c<=iC1; c++)
				{
					imgRGBout->byImgR[(r+1-iR0)*imgRGBout->iWidth+(c-iC0)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
				}	
				if(iWidthP1==1)
				{
					int c=iC1;
					imgRGBout->byImgR[(r+1-iR0)*imgRGBout->iWidth+(c-iC0+1)]=imgRGBin->byImgR[r*imgRGBin->iWidth+c];
				}
			}
		}


	}
	return TRUE;
}

BOOL CreatePyramid(ImgRGB* imgIn, ImgRGB* imgOut)
{
	if(imgIn == NULL){return FALSE;}
	if(imgOut == NULL){return FALSE;}
	if(imgIn == imgOut){return FALSE;}

	int iWidthOriginal=imgIn->iWidth;
	int iHeightOriginal=imgIn->iHeight;
	int iWidthNew;
	int iHeightNew;
	if((iWidthOriginal%2)!=0){return FALSE;}
	if((iHeightOriginal%2)!=0){return FALSE;}

	iHeightNew=iHeightOriginal>>1;
	iWidthNew=iWidthOriginal>>1;

	imgOut->Set(iWidthNew, iHeightNew, imgIn->iChannel);
	UINT uiData;
	if(imgIn->iChannel==CHANNEL_1_24)
	{
		for(int r=0; r<iHeightNew; r++)
		{for(int c=0; c<iWidthNew; c++)
		{
			uiData = imgIn->byImgR[3*(((2*r+0)*iWidthOriginal)+(2*c+0))+0]
			+imgIn->byImgR[3*(((2*r+0)*iWidthOriginal)+(2*c+1))+0]
			+imgIn->byImgR[3*(((2*r+1)*iWidthOriginal)+(2*c+0))+0]
			+imgIn->byImgR[3*(((2*r+1)*iWidthOriginal)+(2*c+1))+0];
			imgOut->byImgR[3*(r*iWidthNew+c)+0]=uiData>>2;

			uiData = imgIn->byImgR[3*(((2*r+0)*iWidthOriginal)+(2*c+0))+1]
			+imgIn->byImgR[3*(((2*r+0)*iWidthOriginal)+(2*c+1))+1]
			+imgIn->byImgR[3*(((2*r+1)*iWidthOriginal)+(2*c+0))+1]
			+imgIn->byImgR[3*(((2*r+1)*iWidthOriginal)+(2*c+1))+1];
			imgOut->byImgR[3*(r*iWidthNew+c)+1]=uiData>>2;

			uiData = imgIn->byImgR[3*(((2*r+0)*iWidthOriginal)+(2*c+0))+2]
			+imgIn->byImgR[3*(((2*r+0)*iWidthOriginal)+(2*c+1))+2]
			+imgIn->byImgR[3*(((2*r+1)*iWidthOriginal)+(2*c+0))+2]
			+imgIn->byImgR[3*(((2*r+1)*iWidthOriginal)+(2*c+1))+2];
			imgOut->byImgR[3*(r*iWidthNew+c)+2]=uiData>>2;
		}}
	}
	return TRUE;
}


BOOL FindModel(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC)
{
	int iModelHeight;
	int iModelWidth;

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}

	
	iModelHeight = imgModel->iHeight;
	iModelWidth = imgModel->iWidth;

	UINT* uiMap;
	int iMapW;
	int iMapH;
	iMapW=(iC1-iC0+1)-imgModel->iWidth+1;
	iMapH=(iR1-iR0+1)-imgModel->iHeight+1;
	if(iMapW<=0){return FALSE;}
	if(iMapH<=0){return FALSE;}
	uiMap = new UINT[iMapW*iMapH];
	int iR1Local;
	int iC1Local;

	iR1Local = iR1;
	iC1Local = iC1;

	if(iR1Local>=imgTarget->iHeight){iR1Local = imgTarget->iHeight-1;}
	if(iC1Local>=imgTarget->iWidth){iC1Local = imgTarget->iWidth-1;}

	int iScanHeight;
	int iScanWidth;
	iScanHeight = iR1Local-iR0-iModelHeight + 2;
	iScanWidth = iC1Local-iC0-iModelWidth + 2;

	if(iScanHeight<=0){return FALSE;}
	if(iScanWidth<=0){return FALSE;}
	
	BOOL bFound;
	int iREnd, iCEnd;

	iREnd = iR0+iScanHeight;
	iCEnd = iC0+iScanWidth;

	int iPtrTarget;
	int iPtrModel;

	memset(uiMap,0,iMapW*iMapH);
	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iMapR=0; iMapR<iMapH; iMapR++)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{

				int iTargetR=iR0+iMapR;
				int iTargetC=iC0+iMapC;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						if(iTargetR + r>=imgTarget->iHeight){uiMap[iMapR*iMapW+iMapC]+=255*3;break;}
						if(iTargetC + c>=imgTarget->iWidth){uiMap[iMapR*iMapW+iMapC]+=255*3;break;}
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = (r)*imgModel->iWidth+(c);

						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 0] , (imgModel->byImgB[iPtrModel]));
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgG[iPtrModel]));
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 3] , (imgModel->byImgR[iPtrModel]));

					}
				}
			}
		}
		int iScoreMax;
		iScoreMax=0;
		int iMaxR;
		int iMaxC;


		iMaxR=-1;
		iMaxC=-1;
		for(int iMapR=0; iMapR<iMapH; iMapR++)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{
				if(uiMap[iMapR*iMapW+iMapC]>iScoreMax){iScoreMax=uiMap[iMapR*iMapW+iMapC]; iMaxR=iMapR; iMaxC=iMapC;}

			}
		}
		(*iFoundR)=iMaxR+iR0;
		(*iFoundC)=iMaxC+iC0;
		return TRUE;
	}
	return FALSE;
}
BOOL FindModelPylamid(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, double dThreshPercent, int* iFoundR0, int* iFoundC0, int* iFoundR1, int* iFoundC1)
{

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}
	if(dThreshPercent<0){return FALSE;}
	if(dThreshPercent>1){dThreshPercent=1;}
	ImgRGB imgTargetTemp;
	ImgRGB imgModelTemp;

	CropImage2(imgTarget, &imgTargetTemp, iR0, iC0, iR1, iC1);
	CropImage2(imgModel, &imgModelTemp, 0, 0, imgModel->iHeight-1, imgModel->iWidth-1);

	
	int iModelHeight;
	int iModelWidth;
	iModelHeight = imgModelTemp.iHeight;
	iModelWidth = imgModelTemp.iWidth;

	UINT uiThresh;

	uiThresh=UINT(dThreshPercent*255*iModelHeight*iModelWidth);
	UINT* uiMap;
	int iMapW;
	int iMapH;
	iMapW=imgTargetTemp.iWidth-imgModelTemp.iWidth+1;
	iMapH=imgTargetTemp.iHeight-imgModelTemp.iHeight+1;
	if(iMapW<=0){return FALSE;}
	if(iMapH<=0){return FALSE;}
	uiMap = new UINT[iMapW*iMapH];
	int iR1Local;
	int iC1Local;

	iR1Local = imgTargetTemp.iHeight-1;
	iC1Local = imgTargetTemp.iWidth-1;


	int iScanHeight;
	int iScanWidth;
	iScanHeight = iR1Local-iModelHeight + 2;
	iScanWidth = iC1Local-iModelWidth + 2;

	if(iScanHeight<=0){return FALSE;}
	if(iScanWidth<=0){return FALSE;}
	
	BOOL bFound;


	int iPtrTarget;
	int iPtrModel;

	memset(uiMap,0,iMapW*iMapH);
	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iMapR=0; iMapR<iMapH; iMapR++)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{

				int iTargetR=iMapR;
				int iTargetC=iMapC;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						if(iTargetR + r>=imgTargetTemp.iHeight){uiMap[iMapR*iMapW+iMapC]+=255*3;break;}
						if(iTargetC + c>=imgTargetTemp.iWidth){uiMap[iMapR*iMapW+iMapC]+=255*3;break;}
						iPtrTarget = 3*((iTargetR + r)*imgTargetTemp.iWidth+(iTargetC+c));
						iPtrModel = (r)*imgModelTemp.iWidth+(c);

						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTargetTemp.byImgR[iPtrTarget + 0] , (imgModelTemp.byImgB[iPtrModel]));
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTargetTemp.byImgR[iPtrTarget + 2] , (imgModelTemp.byImgG[iPtrModel]));
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTargetTemp.byImgR[iPtrTarget + 3] , (imgModelTemp.byImgR[iPtrModel]));

					}
				}
			}
		}
		int iScoreMax;
		iScoreMax=0;
		int iMaxR;
		int iMaxC;


		iMaxR=-1;
		iMaxC=-1;
		int iFoundR0Temp;
		int iFoundR1Temp;
		int iFoundC0Temp;
		int iFoundC1Temp;
		iFoundR0Temp=0;
		for(int iMapR=0; iMapR<iMapH; iMapR++)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{
				if(uiMap[iMapR*iMapW+iMapC]>uiThresh){iFoundR0Temp=iMapR; break;}
			}
			if(iFoundR0Temp>0){break;}
		}
		iFoundR1Temp=iMapH-1;
		for(int iMapR=iMapH-1; iMapR>=0; iMapR--)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{
				if(uiMap[iMapR*iMapW+iMapC]>uiThresh){iFoundR1Temp=iMapR; break;}
			}
			if(iFoundR1Temp<iMapH-1){break;}
		}
		iFoundC0Temp=0;
		for(int iMapC=0; iMapC<iMapW; iMapC++)
		{
			for(int iMapR=0; iMapR<iMapH; iMapR++)
			{
				if(uiMap[iMapR*iMapW+iMapC]>uiThresh){iFoundC0Temp=iMapC; break;}
			}
			if(iFoundC0Temp>0){break;}
		}

		iFoundC1Temp=iMapW-1;
		for(int iMapC=iMapW-1; iMapC>=0; iMapC--)
		{			for(int iMapR=0; iMapR<iMapH; iMapR++)
			{
				if(uiMap[iMapR*iMapW+iMapC]>uiThresh){iFoundC1Temp=iMapC; break;}
			}
			if(iFoundC1Temp<iMapW-1){break;}
		}

		*iFoundR0=iFoundR0Temp*2;
		*iFoundR1=iFoundR1Temp*2+imgModel->iHeight;
		*iFoundC0=iFoundC0Temp*2;
		*iFoundC1=iFoundC1Temp*2+imgModel->iWidth;
		return TRUE;
	}
	return FALSE;
}

BOOL IsInRegionMask(ImgRGB* imgTarget, ImgRGB* imgModel, ImgRGB* imgMask, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC)
{
	int iModelHeight;
	int iModelWidth;

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}
	if(imgMask == NULL){return FALSE;}

	if(imgModel->iHeight != imgMask->iHeight){return FALSE;}
	if(imgModel->iWidth != imgMask->iWidth){return FALSE;}

	
	iModelHeight = imgModel->iHeight;
	iModelWidth = imgModel->iWidth;


	int iR1Local;
	int iC1Local;

	iR1Local = iR1;
	iC1Local = iC1;

	if(iR1Local>=imgTarget->iHeight){iR1Local = imgTarget->iHeight-1;}
	if(iC1Local>=imgTarget->iWidth){iC1Local = imgTarget->iWidth-1;}

	int iScanHeight;
	int iScanWidth;
	iScanHeight = iR1Local-iR0-iModelHeight + 2;
	iScanWidth = iC1Local-iC0-iModelWidth + 2;

	if(iScanHeight<=0){return FALSE;}
	if(iScanWidth<=0){return FALSE;}

	BOOL bFound;
	int iREnd, iCEnd;

	iREnd = iR0+iScanHeight;
	iCEnd = iC0+iScanWidth;

	int iPtrTarget;
	int iPtrModel;

	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR = iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC = iC0; iTargetC<iCEnd; iTargetC++)
			{
				BOOL bOK_R=FALSE;
				for(int r=0; r<iModelHeight; r++)
				{
					bOK_R=FALSE;
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = ((r)*imgModel->iWidth)+(c);
						if((bySubAbs(imgTarget->byImgR[iPtrTarget + 0] , (imgModel->byImgB[iPtrModel])) <= imgMask->byImgB[iPtrModel])
							&&(bySubAbs(imgTarget->byImgR[iPtrTarget + 1] , (imgModel->byImgG[iPtrModel])) <= imgMask->byImgG[iPtrModel])
							&&(bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgR[iPtrModel])) <= imgMask->byImgR[iPtrModel])){bOK_R=TRUE;break;}
					}
					if(bOK_R==FALSE){break;}

				}
				if(bOK_R==TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC; return TRUE;}
			}
		}
	}

	if((imgTarget->iChannel==CHANNEL_3_8) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR=iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iCEnd; iTargetC++)
			{
				BOOL bOK_R=FALSE;
				for(int r=0; r<iModelHeight; r++)
				{
					bOK_R=FALSE;
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = (iTargetR + r)*imgTarget->iWidth+(iTargetC+c);
						iPtrModel = (r)*imgModel->iWidth+(c);
						if((bySubAbs(imgTarget->byImgR[iPtrTarget] , (imgModel->byImgR[iPtrModel])) <= imgMask->byImgR[iPtrModel])
							&&(bySubAbs(imgTarget->byImgG[iPtrTarget] , (imgModel->byImgG[iPtrModel])) <= imgMask->byImgG[iPtrModel])
							&&(bySubAbs(imgTarget->byImgB[iPtrTarget] , (imgModel->byImgB[iPtrModel])) <= imgMask->byImgB[iPtrModel])){bOK_R=TRUE;break;}
					}
					if(bOK_R==FALSE){break;}
				}
				if(bOK_R==TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC; return TRUE;}
			}
		}
	}

	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_1_24))
	{
		for(int iTargetR=iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iCEnd; iTargetC++)
			{
				BOOL bOK_R=FALSE;
				for(int r=0; r<iModelHeight; r++)
				{
					bOK_R=FALSE;
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = 3*((r)*imgModel->iWidth+(c));
						if((bySubAbs(imgTarget->byImgR[iPtrTarget + 0] , (imgModel->byImgR[iPtrModel + 0])) <= imgMask->byImgR[iPtrModel + 0])
							&&(bySubAbs(imgTarget->byImgR[iPtrTarget + 1] , (imgModel->byImgR[iPtrModel + 1])) <= imgMask->byImgR[iPtrModel + 1])
							&&(bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgR[iPtrModel + 2])) <= imgMask->byImgR[iPtrModel + 2])){bOK_R=TRUE;break;}
					}
					if(bOK_R==FALSE){break;}
				}
				if(bOK_R==TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC; return TRUE;}
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
/*
BOOL Search()
{
int* iMap;
iSearchWidth = imgTarget->iWidth - imgModel->iWidth +1;
iSearchHeight = imgTarget->iHeight - imgModel->iHeight+1;
if(iSearchWidth<=0){return FALSE;}
if(iSearchHeight<=0){return FALSE;}
iMap = new int[iSearchWidth * iSearchHeight];
for(int r = 0; r<iSearchHeight; r++)
{
for(int c=0;c<iSearchWidth;c++){}
}
}
*/