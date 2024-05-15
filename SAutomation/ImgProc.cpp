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

int GetPointerOffset(int iW, int iH, int iLevel)
{
	int iOffset=0;
	int iParentLevelH=iH;
	int iParentLevelW=iW;
	for(int i=0; i<iLevel; i++)
	{
		iOffset+=iParentLevelH*iParentLevelW;
		iParentLevelH = (((iParentLevelH%1)==1) ? (iParentLevelH+1)/2 : (iParentLevelH)/2);
		iParentLevelW = (((iParentLevelW%1)==1) ? (iParentLevelW+1)/2 : (iParentLevelW)/2);
	}
	return iOffset;
}
BOOL ImgRGBPyramid::SetPyramid(ImgRGB* imgRGBIn)
{
	this->Set(imgRGBIn->iWidth*2, imgRGBIn->iHeight*2,imgRGBIn->iChannel);

	int iOffset = 0;
	int iParentLevelH=imgRGBIn->iHeight;
	int iParentLevelW=imgRGBIn->iWidth;

	for(int r=0; r<iParentLevelH; r++)
	{for(int c=0; c<iParentLevelW; c++)
	{
		this->byImgB[r*imgRGBIn->iWidth+c]=imgRGBIn->byImgB[r*imgRGBIn->iWidth+c];
		this->byImgG[r*imgRGBIn->iWidth+c]=imgRGBIn->byImgG[r*imgRGBIn->iWidth+c];
		this->byImgR[r*imgRGBIn->iWidth+c]=imgRGBIn->byImgR[r*imgRGBIn->iWidth+c];

	}
	}
	int iLevel=0;
	int iLevelW;
	int iLevelH;
	while(1)
	{
		iLevelH = (((iParentLevelH%1)==1) ? (iParentLevelH+1)/2 : (iParentLevelH)/2);
		iLevelW = (((iParentLevelW%1)==1) ? (iParentLevelW+1)/2 : (iParentLevelW)/2);
		int iParentOffset=iOffset;
		iOffset=GetPointerOffset(imgRGBIn->iWidth, imgRGBIn->iHeight, iLevel);
		for(int r=0; r<iLevelH; r++)
		{
			if(((iParentLevelW%1)==1) && (r==iLevelW-1))
			{
				for(int c=0; c<iLevelW; c++)
				{
					if(((iParentLevelW%1)==1) && (c==iLevelW-1))
					{
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgB[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgB[(2*r+1)*iParentLevelW+2*c+iParentOffset])/2;
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgG[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgG[(2*r+1)*iParentLevelW+2*c+iParentOffset])/2;
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgR[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgR[(2*r+1)*iParentLevelW+2*c+iParentOffset])/2;
					}
					else
					{
						this->byImgB[r*iLevelW+c+iOffset]=this->byImgB[2*r*iParentLevelW+2*c+iParentOffset];
						this->byImgG[r*iLevelW+c+iOffset]=this->byImgB[2*r*iParentLevelW+2*c+iParentOffset];
						this->byImgR[r*iLevelW+c+iOffset]=this->byImgB[2*r*iParentLevelW+2*c+iParentOffset];
					}
				}
			}
			else
			{
				for(int c=0; c<iLevelW; c++)
				{
					if(((iParentLevelW%1)==1) && (c==iLevelW-1))
					{
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgB[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgB[(2*r+1)*iParentLevelW+2*c+iParentOffset])/2;
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgG[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgG[(2*r+1)*iParentLevelW+2*c+iParentOffset])/2;
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgR[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgR[(2*r+1)*iParentLevelW+2*c+iParentOffset])/2;
					}
					else
					{
						this->byImgB[r*iLevelW+c+iOffset]=((int)this->byImgB[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgB[2*r*iParentLevelW+(2*c+1)+iParentOffset]+(int)this->byImgB[(2*r+1)*iParentLevelW+2*c+iParentOffset]+(int)this->byImgB[2*r*iParentLevelW+(2*c+1)+iParentOffset])/4;
						this->byImgG[r*iLevelW+c+iOffset]=((int)this->byImgG[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgG[2*r*iParentLevelW+(2*c+1)+iParentOffset]+(int)this->byImgG[(2*r+1)*iParentLevelW+2*c+iParentOffset]+(int)this->byImgG[2*r*iParentLevelW+(2*c+1)+iParentOffset])/4;
						this->byImgR[r*iLevelW+c+iOffset]=((int)this->byImgR[2*r*iParentLevelW+2*c+iParentOffset]+(int)this->byImgR[2*r*iParentLevelW+(2*c+1)+iParentOffset]+(int)this->byImgR[(2*r+1)*iParentLevelW+2*c+iParentOffset]+(int)this->byImgR[2*r*iParentLevelW+(2*c+1)+iParentOffset])/4;
					}
				}
			}
		}
	}
}
/*
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


inline BOOL SumRDirection(
	BYTE* byTargetCropped, int iImgTargetCroppedW,
	BYTE* byModel, int iModelW, int iModelH, 
	UINT* uiMap, int iMapW, int iMapR, int iMapC, 
	int c, 
	BYTE* byMinOfEachCTarget, 
	BYTE* byMaxOfEachCTarget, 
	UINT* uiSumOfEachCTarget,
	BYTE* byMinOfEachCModel, 
	BYTE* byMaxOfEachCModel,
	UINT* uiSumOfEachCModel)
{
	if(byMaxOfEachCTarget[c] < byMinOfEachCModel[c])
	{
		uiMap[iMapR*iMapW+iMapC]+=uiSumOfEachCModel[c] - uiSumOfEachCTarget[c];
		return TRUE;
	}
	if(byMinOfEachCTarget[c] > byMaxOfEachCModel[c])
	{
		uiMap[iMapR*iMapW+iMapC]+=uiSumOfEachCTarget[c] - uiSumOfEachCModel[c];
		return TRUE;
	}

	for(int r=0; r<iModelH; r++)
	{
		uiMap[iMapR*iMapW+iMapC]+=bySubAbs(byTargetCropped[r*iImgTargetCroppedW+c+iMapC] , (byModel[r*iModelW+c]));
	}

	return TRUE;
}
BOOL UpdateVerticalInformation(BYTE* byDataR, BYTE* byDataG, BYTE* byDataB, int R BYTE* byMinOfEachCTargetR, BYTE* byMaxOfEachCTargetR, UINT* uiSumOfEachCTargetR, BYTE* byMinOfEachCTargetG, BYTE* byMaxOfEachCTargetG, UINT* uiSumOfEachCTargetG,
BYTE* byMinOfEachCTargetB, BYTE* byMaxOfEachCTargetB, UINT* uiSumOfEachCTargetB, int iCropW, int iModelHeight)
{
	for(int c=0; c<iCropW; c++)
	{
		uiSumOfEachCTargetR[c]+=byDataR[iModelHe*iCropW+c];
		uiSumOfEachCTargetG[c]+=byDataG[r*iCropW+c];
		uiSumOfEachCTargetB[c]+=byDataB[r*iCropW+c];
	}
			for(int r=0; r<iModelHeight; r++)
			{
				if(byMinOfEachCTargetR[c]<byDataR[r*iCropW+c]){byMinOfEachCTargetR[c]=byDataR[r*iCropW+c];}
				if(byMinOfEachCTargetG[c]<byDataG[r*iCropW+c]){byMinOfEachCTargetG[c]=byDataG[r*iCropW+c];}
				if(byMinOfEachCTargetB[c]<byDataB[r*iCropW+c]){byMinOfEachCTargetB[c]=byDataB[r*iCropW+c];}
				
				if(byMaxOfEachCTargetR[c]>byDataR[r*iCropW+c]){byMaxOfEachCTargetR[c]=byDataR[r*iCropW+c];}
				if(byMaxOfEachCTargetG[c]>byDataG[r*iCropW+c]){byMaxOfEachCTargetG[c]=byDataG[r*iCropW+c];}
				if(byMaxOfEachCTargetB[c]>byDataB[r*iCropW+c]){byMaxOfEachCTargetB[c]=byDataB[r*iCropW+c];}

			}
		}
		return TRUE;
}

BOOL FindModelFast(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC)
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
	int iCropH;
	int iCropW;
	iCropH=iR1Local-iR0+1;
	iCropW=iC1Local-iC0+1;
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
	BYTE* byDataR;
	BYTE* byDataG;
	BYTE* byDataB;

	BYTE* byMaxOfEachCModelR;
	BYTE* byMinOfEachCModelR;
	UINT* uiSumOfEachCModelR;
	BYTE* byMaxOfEachCModelG;
	BYTE* byMinOfEachCModelG;
	UINT* uiSumOfEachCModelG;
	BYTE* byMaxOfEachCModelB;
	BYTE* byMinOfEachCModelB;
	UINT* uiSumOfEachCModelB;

	BYTE* byMaxOfEachCTargetR;
	BYTE* byMinOfEachCTargetR;
	UINT* uiSumOfEachCTargetR;
	BYTE* byMaxOfEachCTargetG;
	BYTE* byMinOfEachCTargetG;
	UINT* uiSumOfEachCTargetG;
	BYTE* byMaxOfEachCTargetB;
	BYTE* byMinOfEachCTargetB;
	UINT* uiSumOfEachCTargetB;
	
	byDataR = new BYTE[iCropH*iCropW];
	byDataG = new BYTE[iCropH*iCropW];
	byDataB = new BYTE[iCropH*iCropW];

	byMaxOfEachCModelR = new BYTE[iModelWidth];
	byMinOfEachCModelR = new BYTE[iModelWidth];
	uiSumOfEachCModelR = new UINT[iModelWidth];
	byMaxOfEachCModelG = new BYTE[iModelWidth];
	byMinOfEachCModelG = new BYTE[iModelWidth];
	uiSumOfEachCModelG = new UINT[iModelWidth];
	byMaxOfEachCModelB = new BYTE[iModelWidth];
	byMinOfEachCModelB = new BYTE[iModelWidth];
	uiSumOfEachCModelB = new UINT[iModelWidth];

	byMaxOfEachCTargetR = new BYTE[iCropW];
	byMinOfEachCTargetR = new BYTE[iCropW];
	uiSumOfEachCTargetR = new UINT[iCropW];
	byMaxOfEachCTargetG = new BYTE[iCropW];
	byMinOfEachCTargetG = new BYTE[iCropW];
	uiSumOfEachCTargetG = new UINT[iCropW];
	byMaxOfEachCTargetB = new BYTE[iCropW];
	byMinOfEachCTargetB = new BYTE[iCropW];
	uiSumOfEachCTargetB = new UINT[iCropW];

	for(int r=0;r<iCropH; r++)
	{
		int iTargetR=iR0+r;
		for(int c=0; c<iCropW; c++)
		{
			int iTargetC=iC0+c;
			byDataR[r*iCropW+c] = imgTarget->byImgR[3*(iTargetR*imgTarget->iWidth+(iTargetC))+2];
			byDataG[r*iCropW+c] = imgTarget->byImgR[3*(iTargetR*imgTarget->iWidth+(iTargetC))+1];
			byDataB[r*iCropW+c] = imgTarget->byImgR[3*(iTargetR*imgTarget->iWidth+(iTargetC))+0];

		}
	}

	if((imgTarget->iChannel==CHANNEL_1_24) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int c=0; c<iModelWidth; c++)
		{
			byMinOfEachCModelR[c]=255;
			byMaxOfEachCModelR[c]=0;
			uiSumOfEachCModelR[c]=0;
			byMinOfEachCModelG[c]=255;
			byMaxOfEachCModelG[c]=0;
			uiSumOfEachCModelG[c]=0;
			byMinOfEachCModelB[c]=255;
			byMaxOfEachCModelB[c]=0;
			uiSumOfEachCModelB[c]=0;
			for(int r=0; r<iModelHeight; r++)
			{
				if(byMinOfEachCModelR[c]<imgModel->byImgR[r*iModelWidth+c]){byMinOfEachCModelR[c]=imgModel->byImgR[r*iModelWidth+c];}
				if(byMinOfEachCModelG[c]<imgModel->byImgG[r*iModelWidth+c]){byMinOfEachCModelG[c]=imgModel->byImgG[r*iModelWidth+c];}
				if(byMinOfEachCModelB[c]<imgModel->byImgB[r*iModelWidth+c]){byMinOfEachCModelB[c]=imgModel->byImgB[r*iModelWidth+c];}
				
				if(byMaxOfEachCModelR[c]>imgModel->byImgR[r*iModelWidth+c]){byMaxOfEachCModelR[c]=imgModel->byImgR[r*iModelWidth+c];}
				if(byMaxOfEachCModelG[c]>imgModel->byImgG[r*iModelWidth+c]){byMaxOfEachCModelG[c]=imgModel->byImgG[r*iModelWidth+c];}
				if(byMaxOfEachCModelB[c]>imgModel->byImgB[r*iModelWidth+c]){byMaxOfEachCModelB[c]=imgModel->byImgB[r*iModelWidth+c];}

				uiSumOfEachCModelR[c]+=imgModel->byImgR[r*iModelWidth+c];
				uiSumOfEachCModelG[c]+=imgModel->byImgG[r*iModelWidth+c];
				uiSumOfEachCModelB[c]+=imgModel->byImgB[r*iModelWidth+c];
			}
		}
		
		for(int c=0; c<iCropW; c++)
		{
			byMinOfEachCTargetR[c]=255;
			byMaxOfEachCTargetR[c]=0;
			uiSumOfEachCTargetR[c]=0;
			byMinOfEachCTargetG[c]=255;
			byMaxOfEachCTargetG[c]=0;
			uiSumOfEachCTargetG[c]=0;
			byMinOfEachCTargetB[c]=255;
			byMaxOfEachCTargetB[c]=0;
			uiSumOfEachCTargetB[c]=0;
			for(int r=0; r<iModelHeight; r++)
			{
				if(byMinOfEachCTargetR[c]<byDataR[r*iCropW+c]){byMinOfEachCTargetR[c]=byDataR[r*iCropW+c];}
				if(byMinOfEachCTargetG[c]<byDataG[r*iCropW+c]){byMinOfEachCTargetG[c]=byDataG[r*iCropW+c];}
				if(byMinOfEachCTargetB[c]<byDataB[r*iCropW+c]){byMinOfEachCTargetB[c]=byDataB[r*iCropW+c];}
				
				if(byMaxOfEachCTargetR[c]>byDataR[r*iCropW+c]){byMaxOfEachCTargetR[c]=byDataR[r*iCropW+c];}
				if(byMaxOfEachCTargetG[c]>byDataG[r*iCropW+c]){byMaxOfEachCTargetG[c]=byDataG[r*iCropW+c];}
				if(byMaxOfEachCTargetB[c]>byDataB[r*iCropW+c]){byMaxOfEachCTargetB[c]=byDataB[r*iCropW+c];}

				uiSumOfEachCTargetR[c]+=byDataR[r*iCropW+c];
				uiSumOfEachCTargetG[c]+=byDataG[r*iCropW+c];
				uiSumOfEachCTargetB[c]+=byDataB[r*iCropW+c];
			}
		}

		int iMapR=0;
		for(int iMapC=0; iMapC<iMapW; iMapC++)
		{
			for(int c=0; c<iModelWidth; c++)
			{
				SumRDirection(
					byDataR, iCropW,  
					imgModel->byImgR, imgModel->iWidth, imgModel->iHeight,
					uiMap, iMapW, iMapR, iMapC,
					c,
					byMinOfEachCTargetR, 
					byMaxOfEachCTargetR, 
					uiSumOfEachCTargetR,
					byMinOfEachCModelR, 
					byMaxOfEachCModelR,
					uiSumOfEachCModelR);
				
				SumRDirection(
					byDataG, iCropW,  
					imgModel->byImgG, imgModel->iWidth, imgModel->iHeight,
					uiMap, iMapW, iMapR, iMapC,
					c,
					byMinOfEachCTargetG, 
					byMaxOfEachCTargetG, 
					uiSumOfEachCTargetG,
					byMinOfEachCModelG, 
					byMaxOfEachCModelG,
					uiSumOfEachCModelG);
				
				SumRDirection(
					byDataB, iCropW,  
					imgModel->byImgB, imgModel->iWidth, imgModel->iHeight,
					uiMap, iMapW, iMapR, iMapC,
					c,
					byMinOfEachCTargetB, 
					byMaxOfEachCTargetB, 
					uiSumOfEachCTargetB,
					byMinOfEachCModelB, 
					byMaxOfEachCModelB,
					uiSumOfEachCModelB);
			}
		}


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
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 1] , (imgModel->byImgG[iPtrModel]));
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgR[iPtrModel]));

					}
				}
			}
		}
		UINT iScoreMin;
		iScoreMin=UINT_MAX;
		int iMaxR;
		int iMaxC;


		iMaxR=-1;
		iMaxC=-1;
		for(int iMapR=0; iMapR<iMapH; iMapR++)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{
				if(uiMap[iMapR*iMapW+iMapC]<iScoreMin){iScoreMin=uiMap[iMapR*iMapW+iMapC]; iMaxR=iMapR; iMaxC=iMapC;}

			}
		}
		(*iFoundR)=iMaxR+iR0;
		(*iFoundC)=iMaxC+iC0;
		return TRUE;
	}
	return FALSE;
}
BOOL FindModel2(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC)
{
	int iModelHeight;
	int iModelWidth;

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}

	
	iModelHeight = imgModel->iHeight;
	iModelWidth = imgModel->iWidth;



	if(
		((imgTarget->iHeight>128) || (imgTarget->iWidth>128))
		&&(imgTarget->iHeight>64)
		&&(imgTarget->iWidth>64)
		&&(imgModel->iHeight>16)
		&&(imgModel->iWidth>16)
		)

	{
		ImgRGB imgTargetCropped;
		ImgRGB imgTargetPylam;
		ImgRGB imgModelPylam;
		CropImage(imgTarget, &imgTargetCropped,iR0, iC0, iR1, iC1);
		CreatePyramid(&imgTargetCropped, &imgTargetPylam);
		CreatePyramid(imgModel, &imgModelPylam);
		BOOL bRet;
		int iFoundR0, iFoundC0, iFoundR1, iFoundC1;
//		bRet = FindModel2(&imgTargetPylam, &imgModelPylam, 0, 0, imgTargetPylam.iHeight-1, imgTargetPylam.iWidth-1, &iFoundR0, &iFoundC0, &iFoundR1, &iFoundC1);
		if(bRet != TRUE){return FALSE;}
	}
	else
	{
		int iFoundR, iFoundC;
		BOOL bRet;
//		bRet = FindModel(&imgTarget, imgModel, iR0, iC0, iR1, iC1,&iFoundR, &iFoundC);
		if(bRet != TRUE){return FALSE;}
	}
	return TRUE;
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

BOOL FindModelPylamidRecursion(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, double dThreshPercent, int* iFoundR0, int* iFoundC0, int* iFoundR1, int* iFoundC1)
{

	if(imgTarget == NULL){return FALSE;}
	if(imgModel == NULL){return FALSE;}
	if(dThreshPercent<0){return FALSE;}
	if(dThreshPercent>1){dThreshPercent=1;}
	ImgRGB imgTargetCropped;
	ImgRGB imgModelCropped;
	ImgRGB imgTargetPylam;
	ImgRGB imgModelPylam;
	
	if(
		(imgTarget->iHeight<=64)
		||(imgTarget->iWidth<=64)
		||(imgModel->iHeight<=16)
		||(imgModel->iWidth<=16)
		)

	{
		return FindModelPylamid(imgTarget, imgModel, iR0, iC0, iR1, iC1, dThreshPercent, iFoundR0, iFoundC0, iFoundR1, iFoundC1);
	}

	CropImage2(imgTarget, &imgTargetCropped, iR0, iC0, iR1, iC1);
	CropImage2(imgModel, &imgModelCropped, 0, 0, imgModel->iHeight-1, imgModel->iWidth-1);

	CreatePyramid(&imgTargetCropped, &imgTargetPylam);
	CreatePyramid(&imgModelCropped, &imgModelPylam);

	
	return FindModelPylamidRecursion(&imgTargetPylam, &imgModelPylam, 0, 0, imgTargetPylam.iHeight-1, imgTargetPylam.iWidth-1, dThreshPercent, iFoundR0, iFoundC0, iFoundR1, iFoundC1);
}

*/


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
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 1] , (imgModel->byImgG[iPtrModel]));
						uiMap[iMapR*iMapW+iMapC]+=bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgR[iPtrModel]));

					}
				}
			}
		}
		UINT iScoreMin;
		iScoreMin=UINT_MAX;
		int iMaxR;
		int iMaxC;


		iMaxR=-1;
		iMaxC=-1;
		for(int iMapR=0; iMapR<iMapH; iMapR++)
		{
			for(int iMapC=0; iMapC<iMapW; iMapC++)
			{
				if(uiMap[iMapR*iMapW+iMapC]<iScoreMin){iScoreMin=uiMap[iMapR*iMapW+iMapC]; iMaxR=iMapR; iMaxC=iMapC;}

			}
		}
		(*iFoundR)=iMaxR+iR0;
		(*iFoundC)=iMaxC+iC0;
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
				BOOL bOK_R=TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = ((r)*imgModel->iWidth)+(c);
						if(bySubAbs(imgTarget->byImgR[iPtrTarget + 0] , (imgModel->byImgB[iPtrModel])) > imgMask->byImgB[iPtrModel]){bOK_R=FALSE;break;}
						if(bySubAbs(imgTarget->byImgR[iPtrTarget + 1] , (imgModel->byImgG[iPtrModel])) > imgMask->byImgG[iPtrModel]){bOK_R=FALSE;break;}
						if(bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgR[iPtrModel])) > imgMask->byImgR[iPtrModel]){bOK_R=FALSE;break;}
					}
					if(bOK_R==FALSE){break;}
				}
				if(bOK_R==TRUE){*iFoundR = iTargetR; *iFoundC = iTargetC;return TRUE;}
			}
		}
	}

	if((imgTarget->iChannel==CHANNEL_3_8) && (imgModel->iChannel == CHANNEL_3_8))
	{
		for(int iTargetR=iR0; iTargetR<iREnd; iTargetR++)
		{
			for(int iTargetC=iC0; iTargetC<iCEnd; iTargetC++)
			{
				BOOL bOK_R=TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = (iTargetR + r)*imgTarget->iWidth+(iTargetC+c);
						iPtrModel = (r)*imgModel->iWidth+(c);
						if(bySubAbs(imgTarget->byImgR[iPtrTarget] , (imgModel->byImgR[iPtrModel])) > imgMask->byImgR[iPtrModel]){bOK_R=FALSE;break;}
						if(bySubAbs(imgTarget->byImgG[iPtrTarget] , (imgModel->byImgG[iPtrModel])) > imgMask->byImgG[iPtrModel]){bOK_R=FALSE;break;}
						if(bySubAbs(imgTarget->byImgB[iPtrTarget] , (imgModel->byImgB[iPtrModel])) > imgMask->byImgB[iPtrModel]){bOK_R=FALSE;break;}
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
				BOOL bOK_R=TRUE;
				for(int r=0; r<iModelHeight; r++)
				{
					for(int c=0; c<iModelWidth; c++)
					{
						iPtrTarget = 3*((iTargetR + r)*imgTarget->iWidth+(iTargetC+c));
						iPtrModel = 3*((r)*imgModel->iWidth+(c));
						if(bySubAbs(imgTarget->byImgR[iPtrTarget + 0] , (imgModel->byImgR[iPtrModel + 0])) > imgMask->byImgR[iPtrModel + 0]){bOK_R=FALSE;break;}
						if(bySubAbs(imgTarget->byImgR[iPtrTarget + 1] , (imgModel->byImgR[iPtrModel + 1])) > imgMask->byImgR[iPtrModel + 1]){bOK_R=FALSE;break;}
						if(bySubAbs(imgTarget->byImgR[iPtrTarget + 2] , (imgModel->byImgR[iPtrModel + 2])) > imgMask->byImgR[iPtrModel + 2]){bOK_R=FALSE;break;}
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
	if(bmfh.bfType != 0x4d42){delete [] byData; return FALSE;}

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