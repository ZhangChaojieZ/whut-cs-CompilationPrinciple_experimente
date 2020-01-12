#include<iostream>
#include<fstream>
#include<string>
#include"LexicalAnalysis.h"
using namespace std;

/*
 * 此程序为PL/0语言的词法分析程序
 * 文中的分隔符为方便自己记忆而定义的一个名字，并非PL/0语言中的专业术语
 * 类型对应，1-标识符，2-常数，3-关键字，4-运算符，5-界符
*/

int main() {
	ifstream sourceFile("C:\\VS2017C++项目源码\\词法分析源程序.txt");
	ofstream targetFile("C:\\VS2017C++项目源码\\词法分析生成序列.txt");
	int wordIndex = 1;	//用于提示第几个单词出现了错误
	
	if (sourceFile.is_open() && targetFile.is_open()) {
		char ch;
		string strWord = "";		// 存储保留字、标识符、数字字符串
		string strOperator = "";	// 存储操作符字符串
		string strBaun = "";		// 存储界符字符串
		string strTemp = "";		// 临时字符串，用于存入到文档中

		cout << "词法分析结果序列格式如下：('单词'，类型)" << endl;

		// 读到文件结尾停止
		while (!sourceFile.eof()) {
			ch = sourceFile.get();

			// 过滤掉空格、换行符、制表符 
			if (ch != ' '&&ch != '\n'&&ch != '\t') {
				// 如果是非空格、制表符、回车符、界符、运算符等字符，则添加到strWord字符串中
				if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {
					strWord += ch;
					if (strOperator != "") {
						wordIndex++;
						if (OperatorAnalysis(strOperator)) {
							strTemp = "( '" + strOperator + "' , " + "4" + " )";
							targetFile << strTemp << endl;
							strOperator = "";
						}
						else {
							cout << "第" << wordIndex << "个单词分析有误！" << endl;
						}
					}
				}
				// 如果是操作符则添加到strOpertor字符串中
				else if (IsOperator(ch)) {
					strOperator += ch;
					/* 要判断strWord字符串是否为空，可能会出现连续空格、制表符、回车符的情况
					 * 连续遇到空格等分隔符均会被识别为分隔符，进而执行字符串词法分析子程序
					 * 但在识别到第一个空格时，已经执行过词法分析子程序，应当避免重复执行
					 * 所以要判断strWord字符串是否为空，若为空值，则不执行词法分析子程序；反之执行词法分析子程序
					 * 下方判断strWord字符串是否为空的目的与此类似
					*/
					if (!(strWord == "")) {
						wordIndex++;
						// 遇到运算符会分割标识符、关键字等，也要将strWord作判断
						if (KeyIdentNumAnalysis(strWord,strTemp)) {
							targetFile << strTemp << endl;
							// 一旦成功识别，写入文件后，将strWord设为空串，读取下一个字符串
							strWord = "";
						}
						else {
							cout << "第" << wordIndex << "个单词分析有误！" << endl;
						}
					}

					// 可能会出现>=,<=,:=等类型，所以另加一步判断
					if (ch == '<' || ch == '>' || ch == ':') {
						wordIndex--;
						continue;
					}
					
					if (strOperator != "") {
						wordIndex++;
						if (OperatorAnalysis(strOperator)) {
							strTemp = "( '" + strOperator + "' , " + "4" + " )";
							targetFile << strTemp << endl;
							strOperator = "";
						}
						else {
							cout << "第" << wordIndex << "个单词分析有误！" << endl;
						}
					}

				}else if(ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == '.') {
					strBaun += ch;

					if (strOperator != "") {
						wordIndex++;
						if (OperatorAnalysis(strOperator)) {
							strTemp = "( '" + strOperator + "' , " + "4" + " )";
							targetFile << strTemp << endl;
							strOperator = "";
						}
						else {
							cout << "第" << wordIndex << "个单词分析有误！" << endl;
						}
					}

					if (!(strWord == "")) {
						wordIndex++;
						// 遇到界符会分割标识符、关键字等，也要将strWord作判断
						if (KeyIdentNumAnalysis(strWord, strTemp)) {
							targetFile << strTemp << endl;
							// 一旦成功识别，写入文件后，将strWord设为空串，读取下一个字符串
							strWord = "";
						}
						else {
							cout << "第" << wordIndex << "个单词分析有误！" << endl;
						}

					}
					if (BaundaryAnlysis(strBaun)) {
						strTemp = "( '" + strBaun + "' , " + "5" + " )";
						targetFile << strTemp << endl;
						strBaun = "";
					}
					else {
						cout << "第" << wordIndex << "个单词分析有误！" << endl;
					}

				}else {
					
					if (int(ch) != -1) {
						targetFile<< "第" << wordIndex << "个单词错误！" << endl;
						strWord = "";
						cout << "第" << wordIndex << "个单词错误！" << endl;
					}
				}
			}
			else {
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator)) {
					strTemp = "( '" + strOperator + "' , " + "4" + " )";
					targetFile << strTemp << endl;
					strOperator = "";
				}
				else {
					cout << "第" << wordIndex << "个单词分析有误！" << endl;
				}
			}

				if (!(strWord == "")) {
					wordIndex++;
					// 再次遇到空格等字符时，应该对字符串进行词法分析
					if (KeyIdentNumAnalysis(strWord, strTemp)) {
						targetFile << strTemp << endl;
						// 一旦成功识别，写入文件后，将strWord设为空串，读取下一个字符串
						strWord = "";
					}
					else {
						cout << "第" << wordIndex << "个单词分析有误！" << endl;
					}
				}
			}
		}
		sourceFile.close();
		targetFile.close();
		
	}else if(!targetFile.is_open()){
		cout << "打开target文件失败！" << endl;
	}
	else {
		cout << "打开source文件失败！" << endl;
	}
	
	return 0;
}