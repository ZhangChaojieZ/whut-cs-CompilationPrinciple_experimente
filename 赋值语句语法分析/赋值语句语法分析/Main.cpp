#include<iostream>
#include<string>
#include<fstream>
#include"LexicalAnalysis.h"
#include"Parser.h"

using namespace std;

/*
 * 此程序为PL/0语言的词法分析程序
 * 文中的分隔符为方便自己记忆而定义的一个名字，并非PL/0语言中的专业术语
 * 类型对应，1-标识符，2-常数，3-关键字，4-运算符，5-界符
*/

int main() {
	ifstream sourceFile("parserSource.txt");
	ofstream targetFile("parserResult.txt");

	int wordIndex = 1;	//用于提示第几个单词出现了错误

	if (sourceFile.is_open() && targetFile.is_open()) {
		char ch;					// 文件读取
		string strWord = "";		// 存储保留字、标识符、数字字符串
		string strOperator = "";	// 存储操作符字符串
		string strBaun = "";		// 存储界符字符串
		string strTemp = "";		// 临时字符串，用于存入到文档中
		int tempFlag;				// 词法分析函数返回的结果
		int parserfalg = 1;				// 是否进行语法分析的标志.默认进行，值为1，否则为0
		vector<char> inputStr;		// 存储词法分析的结果，即输入串

		cout << "词法分析结果序列格式如下：" << endl;
		cout << "单词\t对应文法的符号" << endl;

		// 读到文件结尾停止
		while (!sourceFile.eof()) {
			ch = sourceFile.get();
			tempFlag = LexAnalysis(wordIndex, ch, strWord, strOperator, strBaun, strTemp,inputStr);
			if (tempFlag == 0) {
				parserfalg = 0;
			}
			else {
				continue;
			}
		}

		if (parserfalg == 0) {
			cout << "单词输入错误，不再进行语法分析！" << endl;
			return 0;
		}

		inputStr.push_back('#');	// 输入串末尾加个#结束符

		if (parser(inputStr)) {
			cout << "语法分析正确！" << endl;
		}
		else {
			cout << "语法分析错误！" << endl;
		}

		sourceFile.close();
		targetFile.close();
	}
	else if (!sourceFile.is_open()) {
		cout << "打开parserSource文件失败！" << endl;
	}
	else {
		cout << "打开parserResult文件失败！" << endl;
	}

	return 0;
}