#pragma once
#include<iostream>
using namespace std;

#define CHKEYLEFTNUM 13
#define CHKEYRIGHTNUM 10
#define CHOPERNUM 11
#define CHBAUNNUM 5

char chKeyWord[CHKEYLEFTNUM][CHKEYRIGHTNUM] = { "const", "var","procedure","begin","end","odd","if","then","call","while","do","read","write" };
char chOperatorWord[CHOPERNUM][CHOPERNUM] = { "+","-","*","/","=","#","<",">",":=",">=","<=" };	// '<=',,'>='
char chBaundaryWord[CHBAUNNUM][CHBAUNNUM] = { "(",")",",",";","." };
char chOperator[] = { '+','-','*','/','<','>','=',':','#' };