#pragma once
#include <iostream>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ����������
	1.��Ҫ��ֵ��ַ���
	2.��ʲô�ַ������
	3.��ֺ�洢��ʲô������
	4.�ǲ���ɾ���ո��� = true, �� = false
*/
/************************************************************************/
void strSplit(const string &strInput, char ch, vector<std::string> & arrStr, char chSep = ',', bool bRemovePair = false);

//����ո���
char* Trim(char* str, const char* szBlank);

//������ո�
string LTrim(const string &str, const char * szBlank);

//����Ҳ�ո�
string RTrim(const string &str, const char * szBlank);

//����ַ����ո�
string Trim(const string &str, const char* szBlank = NULL);

//����Ҳ�ո�
char* RTrim(char* str, const char* szBlank);

//������ո�
char* LTrim(char* str, const char* szBlank);