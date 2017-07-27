#ifndef _STR_UTIL_H_
#define _STR_UTIL_H_
#include <string.h>
#include <iostream>
#include <vector>

char* RTrim(char* str, const char* szBlank = "\t\r\n");

std::string RTrim(const std::string & str, const char* szBlank = "\t\r\n");

char* LTrim(char* str, const char* szBlank = "\t\r\n");

std::string LTrim(const std::string &str, const char * szBlank = "\t\r\n");

char* Trim(char* str, const char* szBlank = "\t\r\n");

std::string Trim(const std::string &str, const char* szBlank = "\t\r\n");

std::string DoubleToStr(double dVal, int nDec = -1, bool bDelZero = false);

//���һ��������ʾ�Ƿ���˿ո�
int SplitStr(const std::string &strInput, std::vector<std::string>& arrStr, char chSep = ',', bool bMark = false);

//const char* To cosnt wchar_t *
const wchar_t* CharToWChar(const char* p);

//char* to LPWSTR
LPWSTR CharToLpwStr(char* p);

#endif // inc
