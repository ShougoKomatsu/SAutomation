#include "stdafx.h"
#include "Common.h"
CString g_sDir;
AutomationInfo g_Automation;

	CInputDialog g_cInput;

BOOL GetFileName(CString sFilePath, CString* sFileName)
{
	int iFoundPosLast;
	int iFoundPos;

	iFoundPos = 0;
	while(iFoundPos>=0)
	{
		iFoundPosLast = iFoundPos;
		iFoundPos = sFilePath.Find(_T("\\"), iFoundPosLast+1);
	}
	CString sExeName;
	if(iFoundPosLast==0){return FALSE;}
	sFileName->Format(_T("%s"), sFilePath.Right(sFilePath.GetLength()-iFoundPosLast-1));
	return TRUE;
}

BOOL ReadUTFFile(CString sFilePath, CString* sData)
{
	CFileFind cFind;
	if(cFind.FindFile(sFilePath)==FALSE){return FALSE;}

	FILE* f;
	CString sBuf;
	CString sDocBuf;

	_tfopen_s(&f, sFilePath,_T("r, ccs=UTF-8"));
	CStdioFile cstdioF(f);
	while(cstdioF.ReadString(sBuf)!= NULL){sDocBuf = sDocBuf + sBuf+_T("\x0d\x0a");}
	cstdioF.Close();
	fclose(f);

	sData->Format(_T("%s"), sDocBuf);
	return TRUE;
}


BOOL ReadTextFile(CString sFilePath, CStringArray* saCommands)
{
	CFileFind cfind;
	BOOL bRet;
	bRet = cfind.FindFile(sFilePath);
	cfind.Close();
	if(bRet != TRUE){return FALSE;}
	

	saCommands->RemoveAll();
	CString sFileDataRaw;
	bRet = ReadUTFFile(sFilePath, &sFileDataRaw);
	if(bRet != TRUE){return FALSE;}

	unsigned long ulFileDataLength;
	long lCR1;
	long lCR2;

	lCR1 = 0;
	ulFileDataLength = sFileDataRaw.GetLength();
	for(unsigned long ulPointer = 0; ulPointer<=ulFileDataLength; ulPointer++)
	{
		lCR2 = sFileDataRaw.Find(_T("\r"),lCR1);
		if(lCR2<=0)
		{
			lCR2 = sFileDataRaw.Find(_T("\n"),lCR1);
			if(lCR2<=0)
			{
				CString sBufTemp;
				sBufTemp.Trim(_T("\r"));
				sBufTemp.Trim(_T("\n"));
				sBufTemp.Format(_T("%s"), sFileDataRaw.Mid(lCR1, sFileDataRaw.GetLength()-lCR1));
				if(sBufTemp.GetLength()>0)
				{
					if(sBufTemp.GetLength()>0){saCommands->Add(sBufTemp);}
				}
				return TRUE;
			}
		}

		CString sLineData;
		sLineData.Format(_T("%s"), sFileDataRaw.Mid(lCR1, lCR2-lCR1));
		sLineData.Trim(_T("\r"));
		sLineData.Trim(_T("\n"));
		if(sLineData.GetLength()>0)
		{
			if(sLineData.GetLength()>0){saCommands->Add(sLineData);}
		}
		lCR1=lCR2+1;
	}

	//ここには来ない
	return FALSE;
}

void SetComboItem(CComboBox* combo, CString sHotkey)
{
	combo->ResetContent();
	combo->AddString(_T(" "));
	combo->AddString(_T("0"));
	combo->AddString(_T("1"));
	combo->AddString(_T("2"));
	combo->AddString(_T("3"));
	combo->AddString(_T("4"));
	combo->AddString(_T("5"));
	combo->AddString(_T("6"));
	combo->AddString(_T("7"));
	combo->AddString(_T("8"));
	combo->AddString(_T("9"));
	combo->AddString(_T("a"));
	combo->AddString(_T("b"));
	combo->AddString(_T("c"));
	combo->AddString(_T("d"));
	combo->AddString(_T("e"));
	combo->AddString(_T("f"));
	combo->AddString(_T("g"));
	combo->AddString(_T("h"));
	combo->AddString(_T("i"));
	combo->AddString(_T("j"));
	combo->AddString(_T("k"));
	combo->AddString(_T("l"));
	combo->AddString(_T("m"));
	combo->AddString(_T("n"));
	combo->AddString(_T("o"));
	combo->AddString(_T("p"));
	combo->AddString(_T("q"));
	combo->AddString(_T("r"));
	combo->AddString(_T("s"));
	combo->AddString(_T("t"));
	combo->AddString(_T("u"));
	combo->AddString(_T("v"));
	combo->AddString(_T("w"));
	combo->AddString(_T("x"));
	combo->AddString(_T("y"));
	combo->AddString(_T("z"));
	combo->AddString(_T("F1"));
	combo->AddString(_T("F2"));
	combo->AddString(_T("F3"));
	combo->AddString(_T("F4"));
	combo->AddString(_T("F5"));
	combo->AddString(_T("F6"));
	combo->AddString(_T("F7"));
	combo->AddString(_T("F8"));
	combo->AddString(_T("F9"));
	combo->AddString(_T("F10"));
	combo->AddString(_T("F11"));
	combo->AddString(_T("F12"));
	combo->AddString(_T("Insert"));


	BOOL bFound;
	bFound = FALSE;
	for(int i=0; i<combo->GetCount(); i++)
	{
		TCHAR tch[8];
		combo->GetLBText(i, tch);
		if(sHotkey.Compare(tch)==0){combo->SetCurSel(i); bFound = TRUE;break;}
	}
	if(bFound != TRUE){combo->SetCurSel(0);}
}