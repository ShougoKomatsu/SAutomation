#include "stdafx.h"
#include "variables.h"
#include "perser.h"

int g_iVar[MAX_THREAD][MAX_VARIABLES];


#define MAXLINE 120
#define MAXERROR 30	
#define MAXNUM 14
#define TAB  5
#define INSERT_C "#0000FF" 
#define DELETE_C "#FF0000"
#define TYPE_C "#00FF00"


static CString s_sLine;
static int s_iLineIndex;
static TCHAR s_cLast;

static Token s_tokenLast;
static int s_idKind;
static int s_iSpaceNum;
static int s_iCRNum;
static int s_iTokenHasBeenPrinted;

static int s_iErrorCount = 0;
static int isKeySymbole(int iKind);
static int isKeyWord(int iKind);

struct keyWord
{
	char* szWord;
	int iKeyID;
};

static struct keyWord KeywordTable[] = 
{
	{"begin", KIND_BEGIN},
	{"end", KIND_END},
	{"if", KIND_IF},
	{"then", KIND_THEN},
	{"while", KIND_WHILE},
	{"do", KIND_DO},
	{"return", KIND_RET},
	{"function", KIND_FUNC},
	{"var", KIND_VAR},
	{"const", KIND_CONST},
	{"odd", KIND_ODD},
	{"write", KIND_WRITE},
	{"writeln",KIND_WRITE_LINE},
	{"$dummy1",KIND_END_OF_KEYWORD},

	{"+", KIND_PLUS},
	{"-", KIND_MINUS},
	{"*", KIND_MULT},
	{"/", KIND_DIV},
	{"(", KIND_PARENTHESIS_L},
	{")", KIND_PARENTHESIS_R},
	{"=", KIND_EQUAL},
	{"<", KIND_LESS},
	{">", KIND_GREATER},
	{"<>", KIND_NOT_EQUAL},
	{"<=", KIND_LESS_EQUAL},
	{">=", KIND_GREATER_EQUAL},
	{",", KIND_COMMA},
	{".", KIND_PERIOD},
	{";", KIND_SEMICOLON},
	{":=", KIND_ASSIGN},
	{"$dummy2",KIND_END_OF_SYMBOLE}
};

int isKeyWord(int iKind)
{
	return (iKind < KIND_END_OF_KEYWORD);
}

int isKeySymbole(int iKind)
{
	if (iKind < KIND_END_OF_KEYWORD){return 0;}
	return (iKind < KIND_END_OF_SYMBOLE);
}

static int s_ClassTable[256];

static void CreateClassTable()
{
	for (int i=0; i<256; i++){s_ClassTable[i] = KIND_OTHERS;}
	for (int i='0'; i<='9'; i++){s_ClassTable[i] = KIND_DIGIT;}
	for (int i='A'; i<='Z'; i++){s_ClassTable[i] = KIND_LETTER;}
	for (int i='a'; i<='z'; i++){s_ClassTable[i] = KIND_LETTER;}
	s_ClassTable['+'] = KIND_PLUS; 
	s_ClassTable['-'] = KIND_MINUS;
	s_ClassTable['*'] = KIND_MULT; 
	s_ClassTable['/'] = KIND_DIV;
	s_ClassTable['('] = KIND_PARENTHESIS_L; 
	s_ClassTable[')'] = KIND_PARENTHESIS_R;
	s_ClassTable['='] = KIND_EQUAL; 
	s_ClassTable['<'] = KIND_LESS;
	s_ClassTable['>'] = KIND_GREATER; 
	s_ClassTable[','] = KIND_COMMA;
	s_ClassTable['.'] = KIND_PERIOD; 
	s_ClassTable[';'] = KIND_SEMICOLON;
	s_ClassTable[':'] = KIND_COLON;
}

void InitSource()
{
	s_iLineIndex = -1;
	s_cLast= '\n';
	s_iTokenHasBeenPrinted = 1;
	CreateClassTable();
}

void FinalSource()
{
	/*
	if (s_tokenLast.m_iKind == KIND_PERIOD)
	{
		printcToken();
	}
	else
	{
		BOOL bRet;
		bRet = OutputErrorInsert(KIND_PERIOD);
		if(bRet != TRUE){exit(1);}
	}
	*/
}




TCHAR GetNextCharAndProgress(CString sLine)
{
	TCHAR tch;
	if (tch= sLine.GetAt(s_iLineIndex) == '\n')
	{
		s_iLineIndex = 0;
		return '\n';
	}
	s_iLineIndex++;
	return tch;
}

Token ProgressAndGetNextToken()
{
	int num;
	int cc;
	Token temp;
	char szIdent[MAXNAME];

	s_iSpaceNum = 0; 
	s_iCRNum = 0;
	while (1)
	{				//次のトークンまでの空白や改行をカウント
		if (s_cLast == ' ')
		{
			s_iSpaceNum++;
		}
		else if	(s_cLast == '\t')
		{
			s_iSpaceNum+=TAB;
		}
		else if (s_cLast == '\n')
		{
			s_iSpaceNum = 0; 
			s_iCRNum++;
		}
		else {break;}
		s_cLast= GetNextCharAndProgress(s_sLine);
	}

	switch (cc = s_ClassTable[s_cLast]) 
	{
	case KIND_LETTER:
		{//identifier
			szIdent[0] = s_cLast;
			s_cLast= GetNextCharAndProgress(s_sLine);
			int i = 1;
			while(1);
			{
				if(s_ClassTable[s_cLast] == KIND_LETTER){break;}	
				if(s_ClassTable[s_cLast] == KIND_DIGIT) {break;}

				if (i < MAXNAME){szIdent[i] = s_cLast;}
				i++; 
				s_cLast= GetNextCharAndProgress(s_sLine);
			} 

			if (i >= MAXNAME)
			{
				//
				i = MAXNAME - 1;
			}	
			szIdent[i] = '\0'; 
			for (i=0; i<KIND_END_OF_KEYWORD; i++)
			{
				if (strcmp(szIdent, KeywordTable[i].szWord) == 0) 
				{
					temp.m_iKind = KeywordTable[i].iKeyID; 		//予約語の場合
					s_tokenLast = temp; 
					s_iTokenHasBeenPrinted = 0;
				}
			}
			temp.m_iKind = KIND_ID;		//ユーザの宣言した名前の場合
			strcpy(temp.u.m_szID, szIdent);
			break;
		}
	case KIND_DIGIT:
		{//number
			num = 0;

			num = s_cLast-'0';
			s_cLast= GetNextCharAndProgress(s_sLine);

			int i = 1;
			while(1) 
			{
				num = 10*num+(s_cLast-'0');
				i++; 
				s_cLast= GetNextCharAndProgress(s_sLine);
				if(s_ClassTable[s_cLast] != KIND_DIGIT){break;}
			} 

			if (i>MAXNUM)
			{
				//
			}
			temp.m_iKind = KIND_NUM;
			temp.u.m_iValue = num;
			break;
		}
	case KIND_COLON:
		{
			s_cLast= GetNextCharAndProgress(s_sLine);
			if (s_cLast == '=') 
			{
				s_cLast= GetNextCharAndProgress(s_sLine);
				temp.m_iKind = KIND_ASSIGN;		//":="
				break;
			} 

			temp.m_iKind = KIND_NUL;
			break;
		}
	case KIND_LESS:
		{
			s_cLast= GetNextCharAndProgress(s_sLine);
			if (s_cLast == '=') 
			{
				s_cLast= GetNextCharAndProgress(s_sLine);
				temp.m_iKind = KIND_LESS_EQUAL;		//"<="
				break;
			} 

			if (s_cLast == '>') 
			{
				s_cLast= GetNextCharAndProgress(s_sLine);
				temp.m_iKind = KIND_NOT_EQUAL;		//"<>"
				break;
			} 

			temp.m_iKind = KIND_LESS;
			break;
		}
	case KIND_GREATER:
		{
			s_cLast= GetNextCharAndProgress(s_sLine);
			if (s_cLast == '=') 
			{
				s_cLast= GetNextCharAndProgress(s_sLine);
				temp.m_iKind = KIND_GREATER_EQUAL;		//">="
				break;
			} 
			temp.m_iKind = KIND_GREATER;
			break;
		}
	default:
		{
			temp.m_iKind = cc;
			s_cLast= GetNextCharAndProgress(s_sLine); 
			break;
		}
	}
	s_tokenLast = temp;
	s_iTokenHasBeenPrinted = 0;
	return temp;
}

Token GetTokenWithCheck(Token token, int iKeyID)			//t.m_iKind == k のチェック
	//t.m_iKind == k なら、次のトークンを読んで返す
	//t.m_iKind != k ならエラーメッセージを出し、t と k が共に記号、または予約語なら
	//t を捨て、次のトークンを読んで返す（ t を k で置き換えたことになる）
	//それ以外の場合、k を挿入したことにして、t を返す
{
	int iRet;
	if (token.m_iKind == iKeyID){return ProgressAndGetNextToken();}


	if (((isKeyWord(iKeyID) == TRUE) && (isKeyWord(token.m_iKind)) == TRUE) )
	{
		//
		return ProgressAndGetNextToken();
	}

	if (((isKeySymbole(iKeyID) == TRUE) && (isKeySymbole(token.m_iKind) == TRUE)))
	{
		//
		return ProgressAndGetNextToken();
	}
	//

	return token;
}


void SetIdKind (int iKind)
{
	s_idKind = iKind;
}

static int s_iCodeIndex;

#define MAXCODE (200)
#define MAXMEM (2000)
#define MAXREG (20)
#define MAXLEVEL (5)

typedef struct relAddr
{
	int level;
	int addr;
}RelAddr; 


typedef struct inst
{				//命令語の型
	int opCode;
	union
	{
		RelAddr addr;
		int value;
		int optr;
	}u;
}Inst;
static Inst s_instCode[MAXCODE];
#define OPERATION_CODE_LIT (1)
#define OPERATION_CODE_OPR (2)
#define OPERATION_CODE_LOD (3)
#define OPERATION_CODE_STO (4)
#define OPERATION_CODE_CAL (5)
#define OPERATION_CODE_RET (6)
#define OPERATION_CODE_ICT (7)
#define OPERATION_CODE_JMP (8)
#define OPERATION_CODE_JPC (9)

#define MAXTABLE (100)
typedef struct tableE 
{		//名前表のエントリーの型
	int iKind;			//名前の種類
	char name[MAXNAME];	//名前のつづり
	union 
	{
		int value;			//定数の場合：値
		struct 
		{
			RelAddr raddr;	//関数の場合：先頭アドレス
			int ParameterNum;		//関数の場合：パラメタ数
		}f;
		RelAddr raddr;		//変数、パラメタの場合：アドレス
	}u;
}TabelE;


static TabelE s_tableName[MAXTABLE];		//名前表

RelAddr relAddr(int ti)				//名前表[ti]のアドレスを返す
{
	return s_tableName[ti].u.raddr;
}


void IncrimentCodeIndex()		//目的コードのインデックスの増加とチェック
{
	s_iCodeIndex++;
	if (s_iCodeIndex < MAXCODE){return;}

}

int genCodeV(int op, int v)		//命令語の生成、アドレス部にv
{
	IncrimentCodeIndex();
	s_instCode[s_iCodeIndex].opCode = op;
	s_instCode[s_iCodeIndex].u.value = v;
	return s_iCodeIndex;
}

int genCodeT(int op, int ti)		//命令語の生成、アドレスは名前表から
{
	IncrimentCodeIndex();
	s_instCode[s_iCodeIndex].opCode = op;
	s_instCode[s_iCodeIndex].u.addr = relAddr(ti);
	return s_iCodeIndex;
}

int genCodeO(int p)			//命令語の生成、アドレス部に演算命令
{
	IncrimentCodeIndex();
	s_instCode[s_iCodeIndex].opCode = OPERATION_CODE_OPR;
	s_instCode[s_iCodeIndex].u.optr = p;
	return s_iCodeIndex;
}


static int s_iNameIndex = 0;			//名前表のインデックス
static int s_iBlockLevel = -1;			//現在のブロックレベル
static int s_iBlockindex[MAXLEVEL];  	//index[i]にはブロックレベルiの最後のインデックス
static int s_iValAddress[MAXLEVEL];  	//addr[i]にはブロックレベルiの最後の変数の番地
static int s_iLocalValAddress;			//現在のブロックの最後の変数の番地
static int s_tfIndex;

int iGetBlockLevel()				//現ブロックのレベルを返す
{
	return s_iBlockLevel;
}

int GetFunctionParameterNum()					//現ブロックの関数のパラメタ数を返す
{
	return s_tableName[s_iBlockindex[s_iBlockLevel-1]].u.f.ParameterNum;
}


int GenCodeR()					//ret命令語の生成
{
	if (s_instCode[s_iCodeIndex].opCode == OPERATION_CODE_RET){return s_iCodeIndex;}			//直前がretなら生成せず

	IncrimentCodeIndex();
	s_instCode[s_iCodeIndex].opCode = OPERATION_CODE_RET;
	s_instCode[s_iCodeIndex].u.addr.level = iGetBlockLevel();
	s_instCode[s_iCodeIndex].u.addr.addr = GetFunctionParameterNum();	//パラメタ数（実行スタックの解放用）*/
	return s_iCodeIndex;
}
