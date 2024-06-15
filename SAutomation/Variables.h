#include "stdafx.h"
#include "Thread.h"

#pragma once
#define MAX_VARIABLES (8)
extern int g_iVar[MAX_THREAD][MAX_VARIABLES];

#define MAXNAME (31)
 
#define KIND_BEGIN (1)
#define KIND_END (2)
#define KIND_IF (3)
#define KIND_THEN (4)
#define KIND_WHILE (5)
#define KIND_DO (6)
#define KIND_RET (7)
#define KIND_FUNC (8)
#define KIND_VAR (9)
#define KIND_CONST (10)
#define KIND_ODD (11)
#define KIND_WRITE (12)
#define KIND_WRITE_LINE (13)
#define KIND_END_OF_KEYWORD (14)

#define KIND_PLUS (101)
#define KIND_MINUS (102)
#define KIND_MULT (103)
#define KIND_DIV (104)
#define KIND_PARENTHESIS_L (105)
#define KIND_PARENTHESIS_R (106)
#define KIND_EQUAL (107)		
#define KIND_LESS (108)
#define KIND_GREATER (109)
#define KIND_NOT_EQUAL (110)
#define KIND_LESS_EQUAL (111)
#define KIND_GREATER_EQUAL (112)
#define KIND_COMMA (113)
#define KIND_PERIOD (114)
#define KIND_SEMICOLON (115)
#define KIND_ASSIGN (116)
#define KIND_END_OF_SYMBOLE (117)

#define KIND_ID (200)
#define KIND_NUM (201)
#define KIND_NUL (202)
#define KIND_END_OF_TOKEN (203)
#define KIND_LETTER (204)
#define KIND_DIGIT (205)
#define KIND_COLON (206)
#define KIND_OTHERS (207)



typedef struct token
{int m_iKind;
	union
	{
		char m_szID[MAXNAME];
		int m_iValue;
	}u;
} Token;

Token NextToken();
Token CheckGet(Token t, int iKind);
TCHAR GetNextCharAndProgress(CString sLine);