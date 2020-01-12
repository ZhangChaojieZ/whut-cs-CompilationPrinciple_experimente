#pragma once
#include<iostream>
#include<string>
//#include"DataStructure.h"
using namespace std;

//	保留字、标识符、数字的词法分析程序
bool KeyIdentNumAnalysis(string strKeyNumIdWord,string& strTemp);
// 关键字词法分析
bool KeywordAnalysis(string strKeyword);
// 标识符词法分析
bool IdentAnalysis(string strIdent);
// 数字词法分析
int NumberAnalysis(string strNum);
// 运算符词法分析
bool OperatorAnalysis(string strOperator);
// 界限符词法分析
bool BaundaryAnlysis(string strBaundary);
// 判断是否是运算符
bool IsOperator(char ch);