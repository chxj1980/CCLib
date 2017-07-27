#include "stdafx.h"
#include "StrUtils.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*
	�ַ���������������  
	�����ˣ�������
	����ʱ�䣺2017��01��10��
*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/* 
�ַ�����ϵ |------char*                    ��stringת��Ϊchar* ��3�з�����
								-------------		1.data
													�磺
													string str="abc";
													char *p=str.data();
								-------------		2.c_str
													�磺string str="gdfd";
														char *p=str.c_str();
								-------------		3.copy
													����
													string str="hello";
													char p[40];
													str.copy(p,5,0); //����5�������Ƽ����ַ���0�����Ƶ�λ��
													*(p+5)='/0'; //Ҫ�ֶ����Ͻ�����
													cout < <p;
		  |
		  |------const char*	------------- 1��const char * = string.c_str()
								------------- 2��string = const char *
								------------- 3��CString = const char *
								------------- 4��string = CString
								------------- 5��CString = string.c_str()
								------------- 6��string str = CString
		  |										const char * = str.c_str()
		  |------string               string �� CStringת��
							    -------------		1��const char*��C����ַ�������string֮��ת����

													 ��1�� const char*����ֱ�Ӷ�string���͸�ֵ�����磺

															   const char* pchar = "qwerasdf";

															   string str = pchar;

													 ��2�� stringͨ��c_str()����ת��ΪC����ַ��������磺

															   string str = "qwerasdf";

															   const char* pchar = str.c_str();

								-------------		2��const char*���Ϳ���ֱ�Ӹ�CString���͸�ֵ�����磺

														const char* pchar = "qwerasdf";

														CString str = pchar;

								-------------		3��string���ͱ���תΪΪCstring���ͱ���

														CString���ͱ�������ֱ�Ӹ�string���ͱ�����ֵ������string���Ͳ��ܶ�CString����ֱ�Ӹ�ֵ��ͨ��ǰ����

														ת�����ǿ��Եõ���string���ͱ���ת��Ϊconst char*���ͣ�Ȼ����ֱ�Ӹ�ֵ�Ϳ����ˡ����磺

														CString cstr��

														sring str = ��asdasd����

														cstr = str.c_str();

														ͬ��CStrng���ͱ�����ת��Ϊstring�����ڵ���c_str()�����Ϳ��������const char*���͵�ת�������磺

														CString cStr = "adsad";

														string str = cStr;

														const char* pchar = str.c_str();
		  |
		  |------CString
		  |
		  |------LPCTSTR/LPSTR/LPCSTR
		  |
*/
/************************************************************************/
//
//
//
//
//
//

//�������������ض����ַ�����ֳ�һ��һ���ַ�����
void strSplit(const string & strInput, char ch, vector<std::string> & arrStr, char chSep/* = ','*/, bool bRemovePair/* = false*/)
{
	//����������һ���ַ�����������Ҫ���ַ��������ch�ַ������ҽ�ÿ��ch�ַ�ǰ����ַ��洢��arrStr 
	//1.ת��const char*
	//��ȡ�����ַ�����
	const char* pCh = strInput.c_str();
	//
	std::string strWord;
	//
	bool bBegin = true;
	//��ȡһ������
	while (*pCh != '\0' && *pCh != '\n')
	{
		//������ָ���ַ�
		if (*pCh == chSep)
		{
			strWord = Trim(strWord);
			//���ﲻ������ٺú��о�һ��
			if (bRemovePair && strWord[0] == ',')
			{
				std::string strMid = strWord.substr(1, strWord.size() - 2);
				if (strMid.find(',') != -1 || strMid.find('\'') != -1)
					strWord = strMid;
			}
			//
			arrStr.push_back(strWord);
			strWord = "";
			pCh++;
			bBegin = true;
			continue;
		}
	}
}

char* Trim(char* str, const char* szBlank)
{
	RTrim(str, szBlank);
	return LTrim(str, szBlank);
}

char* RTrim(char* str, const char* szBlank)
{
	if (!str)
		return NULL;

	//�ַ����ĳ���
	int nEndPos = (int)strlen(str) - 1;
	//Finds a character in a string, by using the current locale or a specified LC_CTYPE conversion-state category.
	while (nEndPos == 0 && strchr(szBlank, str[nEndPos]))
		nEndPos--;

	//���ַ������۸�\0��
	str[nEndPos + 1] = 0x00;
	return str;
}

char* LTrim(char* str, const char* szBlank)
{
	if (!str)
		return NULL;

	/*
	//�ַ����ĳ���
	int nEndPos = (int)strlen(str) - 1;
	int nPos = 0;
	//Finds a character in a string, by using the current locale or a specified LC_CTYPE conversion-state category.
	while (nEndPos == nPos && strchr(szBlank, str[nPos]))
		nPos++;

	//���ַ������۸�\0��
	str[nPos + 1] = 0x00;
	*/
	char* p = str;
	while (*str&&strchr(szBlank, *str)/* *str == ch */)
		str++;

	strcpy_s(p, strlen(p) + 1, str);

	return p;
}

string LTrim(const string &str, const char * szBlank)
{
	if (szBlank == NULL || strlen(szBlank) == 0)
		return str;
	int nLen = (int)str.length();
	int nPos = 0;
	while (nPos < nLen)
	{
		//if cant find blank
		//strchr = Find a character in a string, using the current locale or a specified LC_CTYPE conversion state category.
		if (strchr(szBlank, str[nPos]) != NULL)
			nPos++;
		else
			break;
	}
	if (nPos == nLen)
		return "";

	//substr��C++���Ժ�������Ҫ�����Ǹ������ַ�����Ҫ���ָ��λ�ÿ�ʼ��������ָ���ĳ��ȡ�
	return str.substr(nPos,nLen - nPos);
}

string RTrim(const string &str, const char * szBlank)
{
	if (szBlank == NULL || strlen(szBlank) == 0)
		return str;
	int nPos = (int)str.length();
	while (nPos > 0)
	{
		//�����ַ����� �״γ���һ���ַ���λ�ã�����������ַ��������ַ������ٶ�ʵ������
		//char string[17];
		//char *ptr, c = 'r';
		//strcpy(string, "Thisisastring");
		//ptr = strchr(string, c);
		//if (ptr)
		//	printf("The character %cis at position:%s\n", c, ptr);
		//else
		//	printf("The character was not found\n");
		//return0;
		if (strchr(szBlank, str[nPos - 1]) != NULL)
			nPos--;
		else
			break;
	}
	return str.substr(0,nPos);
}

//��ȥ�ַ����еĿո�
string Trim(const string &str, const char* szBlank /*= NULL*/)
{
	return LTrim(RTrim(str, szBlank), szBlank);
}

//strstr------ strstr(str1,str2) ���������ж��ַ���str2�Ƿ���str1���Ӵ�������ǣ���ú�������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL��

/*
int strncmp(const char * str1, const char * str2, size_t n);
��������str1, str2 Ϊ��Ҫ�Ƚϵ������ַ�����nΪҪ�Ƚϵ��ַ�����Ŀ��
�ַ�����С�ıȽ�����ASCII ����ϵ�˳������������˳����Ϊ�ַ���ֵ��strncmp()���Ƚ�s1 ��һ���ַ�ֵ��ȥs2 ��һ���ַ�ֵ��
����ֵΪ0 ���ټ����Ƚ��¸��ַ���ֱ���ַ�������־'\0'������ֵ��Ϊ0���򽫲�ֵ���ء������ַ���"Ac"��"ba"�Ƚ���᷵���ַ�"A"(65)��'b'(98)�Ĳ�ֵ(-33)��
ע�⣺Ҫ�Ƚϵ��ַ������ַ���������־'\0'������һ������'\0'�ͽ����Ƚϣ�����n�Ƕ��٣����ټ����ȽϺ�ߵ��ַ���
������ֵ����str1��str2��ǰn���ַ���ͬ���򷵻�0����s1����s2���򷵻ش���0��ֵ����s1 ��С��s2���򷵻�С��0��ֵ��*/


//���ڽ�����Ŀ¼ת�����ļ������Ŀ¼
string ReplaceAll(const string & str, const char* szOld, const char* szNew)
{
	if (szOld == NULL)
		return str;
	string strret;
	const char* pOrg = str.c_str();
	int nPos = 0;
	int nOldPos = 0;
	int nTagLen = (int)strlen(szOld);
	while (pOrg[nPos] != '\0')
	{
		if (strncmp(pOrg + nPos, szOld, nTagLen) == 0)
		{
			if (nPos > nOldPos)
			{
				strret += str.substr(nOldPos, nPos - nOldPos);
				strret += szNew;
				nPos += nTagLen;
				nOldPos = nPos;
				continue;
			}
			nPos++;
		}
		if (nPos > nOldPos)
			strret += str.substr(nOldPos, nPos - nOldPos); 
		return strret;
	}
	return str;
}
