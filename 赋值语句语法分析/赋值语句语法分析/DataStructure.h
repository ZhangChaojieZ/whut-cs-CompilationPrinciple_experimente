#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

#define CHKEYLEFTNUM 13
#define CHKEYRIGHTNUM 10
#define CHOPERNUM 11
#define CHBAUNNUM 5

// 类型对应，1-标识符，2-常数，3-关键字，4-运算符，5-界符,-1表示继续读取下一个字符，0表示错误
#define READ -1
#define IDENT 1
#define CONSTANT 2
#define KEYWORD 3
#define OPERATOR 4
#define BAUNDARY 5
#define ERROR 0

//#define GSIZE 13	// 文法产生式的个数
//#define SLRSIZE 20	// 状态个数

static char chKeyWord[CHKEYLEFTNUM][CHKEYRIGHTNUM] = { "const", "var","procedure","begin","end","odd","if","then","call","while","do","read","write" };
static char chOperatorWord[CHOPERNUM][CHOPERNUM] = { "+","-","*","/","=","#","<",">","==",">=","<=" };	// '<=',,'>='
static char chBaundaryWord[CHBAUNNUM][CHBAUNNUM] = { "(",")",",",";","." };
static char chOperator[] = { '+','-','*','/','<','>','=',':','#' };

//static map<string, char> G[GSIZE];
//static map<char, int> SLR[SLRSIZE];
//map<string, string> SLR[SLRSIZE];
// 初始化map
//void init();