#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<vector>
//#include"DataStructure.h"
//#include"LexicalAnalysis.h"

using namespace std;
#define GSIZE 13	// 文法产生式的个数
#define SLRSIZE 20	// 状态个数

static map<string, char> G[GSIZE];
static map<char, int> SLR[SLRSIZE];
//bool parser(map<string,int> outMap);
// 初始化
void init();
// 语法分析程序
bool parser(vector<char> inputStr);