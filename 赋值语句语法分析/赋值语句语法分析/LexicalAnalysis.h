#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
//#include"DataStructure.h"
using namespace std;

//	保留字、标识符、数字的词法分析程序
//int KeyIdentNumAnalysis(string strKeyNumIdWord, string& strTemp, map<string, int> &outMap);
int KeyIdentNumAnalysis(string strKeyNumIdWord, string &strTemp, vector<char> &inputStr);
// 关键字词法分析
int KeywordAnalysis(string strKeyword);
// 标识符词法分析
int IdentAnalysis(string strIdent);
// 数字词法分析
int NumberAnalysis(string strNum);
// 运算符词法分析
int OperatorAnalysis(string strOperator);
// 界限符词法分析
int BaundaryAnlysis(string strBaundary);
// 判断是否是运算符
bool IsOperator(char ch);
// 词法分析程序
//int LexAnalysis(int &wordIndex, char &ch, string &strWord, string &strOperator, string &strBaun, string &strTemp, map<string,int> &outMap)
int LexAnalysis(int &wordIndex, char &ch, string &strWord,string &strOperator, string &strBaun, string &strTemp, vector<char> &inputStr);