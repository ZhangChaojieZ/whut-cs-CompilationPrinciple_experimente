#include<iostream>
#include<string>
#include<map>
#include<iterator>
#include<stack>
#include<iomanip>
#include"Parser.h"
#include"DataStructure.h"

using namespace std;

void init() {
	/*
	文法描述：
	赋值语句：A->f=B
	表达式：B->C|BGC
	项：C->D|CHD
	因子：D->f|e|(B)
	无符号整数：e
	标识符：f
	加法运算符：G->+|-
	乘法运算符：H->*|/
	*/
	/*
	文法初始化,将赋值语句文法的文字表述改为字符表达
	使用map<string，char>存放文法，以产生式右部为Key，左部为Value
	*/
	G[0]["A"] = 'S';
	G[1]["f=B"] = 'A';
	G[2]["C"] = 'B';
	G[3]["BGC"] = 'B';
	G[4]["D"] = 'C';
	G[5]["CHD"] = 'C';
	G[6]["f"] = 'D';
	G[7]["e"] = 'D';
	G[8]["(B)"] = 'D';
	G[9]["+"] = 'G';
	G[10]["-"] = 'G';
	G[11]["*"] = 'H';
	G[12]["/"] = 'H';
	/* 
	LR分析表初始化，文法为SLR文法
	使用map<char,int>结构存储每一个状态下的ACTION表和GOTO表，并且用数组存储所有的map,构成一份LR分析表
	在map中使用文法的符号作为Key，对应的结构作为Value,终结符对应的为ACTION表，非终结符对应的项为GOTO表
	1000为基数的项表示要进行进行规约，使用的产生式的序号就是减去1000之后的值
	*/
	SLR[0]['f'] = 2;
	SLR[0]['A'] = 1;
	SLR[1]['#'] = -1;
	SLR[2]['='] = 3;
	SLR[3]['f'] = 7;
	SLR[3]['e'] = 8;
	SLR[3]['('] = 9;
	SLR[3]['B'] = 4;
	SLR[3]['C'] = 5;
	SLR[3]['D'] = 6;
	SLR[4]['+'] = 11;
	SLR[4]['-'] = 12;
	SLR[4]['#'] = 1001;
	SLR[4]['G'] = 10;
	SLR[5][')'] = 1002;
	SLR[5]['+'] = 1002;
	SLR[5]['-'] = 1002;
	SLR[5]['*'] = 14;
	SLR[5]['/'] = 15;
	SLR[5]['#'] = 1002;
	SLR[5]['H'] = 13;
	SLR[6][')'] = 1004;
	SLR[6]['+'] = 1004;
	SLR[6]['-'] = 1004;
	SLR[6]['*'] = 1004;
	SLR[6]['/'] = 1004;
	SLR[6]['#'] = 1004;
	SLR[7][')'] = 1006;
	SLR[7]['+'] = 1006;
	SLR[7]['-'] = 1006;
	SLR[7]['*'] = 1006;
	SLR[7]['/'] = 1006;
	SLR[7]['#'] = 1006;
	SLR[8][')'] = 1007;
	SLR[8]['+'] = 1007;
	SLR[8]['-'] = 1007;
	SLR[8]['*'] = 1007;
	SLR[8]['/'] = 1007;
	SLR[8]['#'] = 1007;
	SLR[9]['f'] = 7;
	SLR[9]['e'] = 8;
	SLR[9]['('] = 9;
	SLR[9]['B'] = 16;
	SLR[9]['C'] = 5;
	SLR[9]['D'] = 6;
	SLR[10]['f'] = 7;
	SLR[10]['e'] = 8;
	SLR[10]['('] = 9;
	SLR[10]['C'] = 17;
	SLR[10]['D'] = 6;
	SLR[11]['f'] = 1009;
	SLR[11]['e'] = 1009;
	SLR[11]['('] = 1009;
	SLR[12]['f'] = 1010;
	SLR[12]['e'] = 1010;
	SLR[12]['('] = 1010;
	SLR[13]['f'] = 7;
	SLR[13]['e'] = 8;
	SLR[13]['('] = 9;
	SLR[13]['D'] = 18;
	SLR[14]['f'] = 1011;
	SLR[14]['e'] = 1011;
	SLR[14]['('] = 1011;
	SLR[15]['f'] = 1012;
	SLR[15]['e'] = 1012;
	SLR[15]['('] = 1012;
	SLR[16][')'] = 19;
	SLR[16]['+'] = 11;
	SLR[16]['-'] = 12;
	SLR[16]['G'] = 10;
	SLR[17][')'] = 1003;
	SLR[17]['+'] = 1003;
	SLR[17]['-'] = 1003;
	SLR[17]['*'] = 14;
	SLR[17]['/'] = 15;
	SLR[17]['#'] = 1003;
	SLR[17]['H'] = 13;
	SLR[18][')'] = 1005;
	SLR[18]['+'] = 1005;
	SLR[18]['-'] = 1005;
	SLR[18]['*'] = 1005;
	SLR[18]['/'] = 1005;
	SLR[18]['#'] = 1005;
	SLR[19][')'] = 1008;
	SLR[19]['+'] = 1008;
	SLR[19]['-'] = 1008;
	SLR[19]['*'] = 1008;
	SLR[19]['/'] = 1008;
	SLR[19]['#'] = 1008;

}

//bool parser(map<string, int> outMap)
bool parser(vector<char> inputStr) {
	init();					// 进行初始化
	stack<int> stateStack;	// 状态栈
	stack<char> chStack;	// 符号栈
	char inputCh;			// 表示每次输入的的符号
	int staTop;				// 栈顶元素
	int inputStrIndex = 0;	// 遍历访问inputStr，初始值为0
	int step=1;				// 步骤，初始值为1
	string chs;				// 文法中产生式的右部
	string ssString("0");	// 状态栈中的内容
	string csString("#");	// 符号栈中的内容
	string inString;		// 输入串的内容
	stateStack.push(0);		// 初始化状态栈
	chStack.push('#');		// 初始化符号栈

	for (unsigned int m = 0; m < inputStr.size(); m++) {
		inString.push_back(inputStr[m]);
	}
	cout << "语法分析过程如下：" << endl;
	cout << setiosflags(ios::left) << setw(3)<<"步骤\t" << setw(24) << "状态栈\t" << setw(10) << "\t符号栈\t"
		<< setw(15) << "\t输入串\t" << setw(3) << "ACTION\t" << setw(3) << "GOTO" << resetiosflags(ios::left) << endl;
	
	while(true) { 
		//cout << inputStr[i] << endl;
		inputCh = inputStr[inputStrIndex];			// 输入符号
		staTop = stateStack.top();					// 得到状态栈栈顶元素
	
		if (SLR[staTop][inputCh] != 0) {			//是否存在输入input对应的ACTION和GOTO，不存在则返回0
			if (SLR[staTop][inputCh] == -1) {		//-1为acc接受
				// 输出分析过程
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(24) << ssString << "\t" << setw(10) << csString
					 <<  resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(15) << inString.substr(inputStrIndex) << "\t" << resetiosflags(ios::right);
				cout << "acc" << endl;
				//*************

				return true;
			}
			else if (SLR[staTop][inputCh] > 0 && SLR[staTop][inputCh] < 20 ) {	// 移进
				// 输出过程操作，同栈进行相同的动作，内容与栈中一致
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(24) << ssString << "\t" << setw(10) << csString
					<< resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(15) << inString.substr(inputStrIndex) << resetiosflags(ios::right);
				cout << "\t" << "S" << SLR[staTop][inputCh] << endl;

				if (SLR[staTop][inputCh] >= 10) {
					ssString.append("(" + to_string(SLR[staTop][inputCh]) + ")");
				}
				else {
					ssString.append(to_string(SLR[staTop][inputCh]));
				}
				csString.push_back(inputCh);
				//*************
				
				stateStack.push(SLR[staTop][inputCh]);	// 状态压入状态栈
				chStack.push(inputCh);					// 移进的符号压入符号栈
				if (inputStrIndex < inputStr.size() - 1) {
					inputStrIndex++;
				}
			}
			else {	// 规约
				int temp = SLR[staTop][inputCh] - 1000;
				chs = G[temp].begin()->first;
				// 用于格式化输出显示，输出各个栈里的内容
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(24) << ssString << "\t" << setw(10) << csString
					<< resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(15) << inString.substr(inputStrIndex) << resetiosflags(ios::right);
				cout << "\t" << "r" << SLR[staTop][inputCh] - 1000 << "\t";
				//*************
					
				int tempTop;
				for (unsigned int j = 0; j < chs.length(); j++) {
					tempTop = stateStack.top();	// 栈顶元素用于判断ssString删除几个符号

					chStack.pop();				// 符号栈出栈
					stateStack.pop();			// 状态栈出栈
					
					// 同栈进行相同的动作，内容与栈中一致
					if (tempTop >= 10) {
						ssString.erase(ssString.size() - 4);
					}
					else {
						ssString.erase(ssString.size() - 1);
					}
					csString.erase(csString.size() - 1);
					//**********
				}

				chStack.push(G[temp].begin()->second);					// 将规约后的结果压入符号栈
				staTop = stateStack.top();
				stateStack.push(SLR[staTop][G[temp].begin()->second]);	// 将GOTO的结果压入状态栈

				// 用于输出显示，输出各个栈里的内容
				csString.push_back(G[temp].begin()->second);
				if (SLR[staTop][G[temp].begin()->second] >= 10) {
					ssString.append("(" + to_string(SLR[staTop][G[temp].begin()->second]) + ")");
				}
				else {
					ssString.append(to_string(SLR[staTop][G[temp].begin()->second]));
				}
				cout << setiosflags(ios::left) << setw(3) << SLR[staTop][G[temp].begin()->second] << resetiosflags(ios::left) << endl;
				//**************
			}
		}
		else {
			cout << inputCh << "输入错误！" << endl;
			return false;
		}

	}
	return true;
}