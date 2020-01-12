#include<iostream>
#include<string>
#include"LexicalAnalysis.h"
#include"DataStructure.h"
using namespace std;

//	保留字、标识符、数字的词法分析程序
bool KeyIdentNumAnalysis(string strKeyNumIdWord, string& strTemp) {

	if (KeywordAnalysis(strKeyNumIdWord)) {
		strTemp = "( '" + strKeyNumIdWord + "' , " + "3" + " )";
		cout << strTemp << endl;
		return true;
	}
	else if (IdentAnalysis(strKeyNumIdWord)) {
		strTemp = "( '" + strKeyNumIdWord + "' , " + "1" + " )";
		cout << strTemp << endl;
		return true;
	}
	else if (NumberAnalysis(strKeyNumIdWord) != -1) {
		strTemp = "( " + strKeyNumIdWord + " , " + "2" + " )";
		cout << strTemp << endl;
		return true;
	}
	else {
		cout << "输入有误！" << endl;
		return false;
	}
}
// 关键字词法分析
bool KeywordAnalysis(string strKeyword) {
	const char* strchar = strKeyword.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strKeyword == chKeyWord[i]) {
				string strTemp = "( '" + strKeyword + "' , " + "3" + " )";
				cout << strTemp << endl;
				return true;
			}
		}
	}
	return false;
}
// 标识符词法分析
bool IdentAnalysis(string strIdent) {
	const char* strchar = strIdent.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strIdent == chKeyWord[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}
// 数字词法分析
int NumberAnalysis(string strNum) {
	const char* strchar = strNum.c_str();
	char ch = strchar[0];
	int d = 0;
	int sum = 0;

	for (int i = 0; i < strNum.length(); i++) {
		if (ch >= '0'&&ch <= '9') {
			d = (int)strchar[i] - 48;	// 因为字符'0'的ASCII码值为48
			sum = sum * 10 + d;
		}
		else {
			return -1;
		}
	}
	return sum;
}
// 运算符词法分析
bool OperatorAnalysis(string strOperator) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (strOperator == chOperatorWord[i]) {
			string strTemp = "( '" + strOperator + "' , " + "4" + " )";
			cout << strTemp << endl;
			return true;
		}
	}
	return false;
}
// 界限符词法分析
bool BaundaryAnlysis(string strBaundary) {
	for (int i = 0; i < CHBAUNNUM; i++) {
		if (strBaundary == chBaundaryWord[i]) {
			string strTemp = "( '" + strBaundary + "' , " + "5" + " )";
			cout << strTemp << endl;
			return true;
		}
	}
	return false;
}
// 判断是否是运算符字符
bool IsOperator(char ch) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (ch == chOperator[i]) {
			return true;
		}	
	}
	return false;
}