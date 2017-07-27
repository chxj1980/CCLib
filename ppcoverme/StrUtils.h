#pragma once
#include <iostream>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 参数解析：
	1.需要拆分的字符串
	2.按什么字符串拆分
	3.拆分后存储在什么数组里
	4.是不是删除空格，是 = true, 否 = false
*/
/************************************************************************/
void strSplit(const string &strInput, char ch, vector<std::string> & arrStr, char chSep = ',', bool bRemovePair = false);

//清楚空格函数
char* Trim(char* str, const char* szBlank);

//清除左侧空格
string LTrim(const string &str, const char * szBlank);

//清除右侧空格
string RTrim(const string &str, const char * szBlank);

//清除字符串空格
string Trim(const string &str, const char* szBlank = NULL);

//清除右侧空格
char* RTrim(char* str, const char* szBlank);

//清除左侧空格
char* LTrim(char* str, const char* szBlank);