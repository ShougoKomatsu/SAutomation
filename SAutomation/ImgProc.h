#include "stdafx.h"
#pragma once
#define CHANNEL_UNDEFINED (0)
#define CHANNEL_1_8 (1)
#define CHANNEL_3_8 (3)
#define CHANNEL_1_24BGR (24)

struct ImgRGB
{
	int iWidth;
	int iHeight;
	int iChannel;
	BYTE* byImgR;
	BYTE* byImgG;
	BYTE* byImgB;
	BYTE* byImg;
	BOOL Set(int iWidthIn, int iHeightIn, int iChannelIn)
	{
		Init();
		if(iWidthIn<=0){return FALSE;}
		if(iHeightIn<=0){return FALSE;}

		iWidth = iWidthIn;
		iHeight = iHeightIn;
		iChannel = iChannelIn;
		if(iChannel == CHANNEL_1_8)
		{
			byImg = new BYTE[iWidth*iHeight];
		}
		if(iChannel == CHANNEL_3_8)
		{
			byImgR = new BYTE[iWidth*iHeight];
			byImgG = new BYTE[iWidth*iHeight];
			byImgB = new BYTE[iWidth*iHeight];
			byImg=NULL;
		}
		if(iChannel == CHANNEL_1_24BGR)
		{
			byImg = new BYTE[iWidth*iHeight*3];
		}
		return TRUE;
	}
	BOOL Init()
	{
		if(byImg!=NULL){delete [] byImg; byImg=NULL;}
		if(byImgR!=NULL){delete [] byImgR; byImgR=NULL;}
		if(byImgG!=NULL){delete [] byImgG; byImgG=NULL;}
		if(byImgB!=NULL){delete [] byImgB; byImgB=NULL;}
		iWidth=0;
		iHeight=0;
		iChannel=CHANNEL_UNDEFINED;
		return TRUE;
	}
	ImgRGB(){byImg = NULL; byImgR=NULL; byImgG=NULL; byImgB=NULL; Init();}
	~ImgRGB(){Init();}
	BOOL Assign(CString sFilePath);
BOOL ImgRGB::Assign(ImgRGB* imgRGBIn);
};
struct ImgRGBPyramid
{
	ImgRGB imgRGB;
	int iWidthOriginal;
	int iHeightOriginal;
	BOOL SetPyramid(ImgRGB* imgRGBIn);
};

struct ImgMap
{

	int iWidth;
	int iHeight;
	UINT* uiMap;
	BOOL Set(int iWidthIn, int iHeightIn)
	{
		Init();
		if(iWidthIn<=0){return FALSE;}
		if(iHeightIn<=0){return FALSE;}

		if(iWidthIn*iHeightIn>(UINT_MAX>>8)){return FALSE;}

		iWidth = iWidthIn;
		iHeight = iHeightIn;
		uiMap = new UINT[iWidth*iHeight];
		memset(uiMap,0,iWidth*iHeight);
		return TRUE;
	}
	BOOL Init()
	{
		if(uiMap!=NULL){delete [] uiMap; uiMap=NULL;}
		iWidth=0;
		iHeight=0;
		return TRUE;
	}
	ImgMap(){uiMap=NULL;Init();}
	~ImgMap(){Init();}
};

BOOL Screenshot(ImgRGB* imgRGB);
BOOL CropImage(ImgRGB* imgRGBin, ImgRGB* imgRGBout, int iR0, int iC0, int iR1, int iC1);

BOOL IsInRegion(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC);
BOOL IsInRegionMask(ImgRGB* imgTarget, ImgRGB* imgModel, ImgRGB* imgMask, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC);
BOOL FindModel(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, int* iFoundR, int* iFoundC, double dThreshPercent=0.0);
BOOL FindModelPyramid(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1, double dThreshPercent, int* iFoundR, int* iFoundC);

BOOL WriteImage(ImgRGB* imgRGB, CString sFilePath);