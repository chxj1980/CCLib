#include "stdafx.h"
#include "StrUtils.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*
	字符串处理公共函数库  
	创建人：许立龙
	创建时间：2017年01月10日
*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/* 
字符串关系 |------char*                    把string转换为char* 有3中方法：
								-------------		1.data
													如：
													string str="abc";
													char *p=str.data();
								-------------		2.c_str
													如：string str="gdfd";
														char *p=str.c_str();
								-------------		3.copy
													比如
													string str="hello";
													char p[40];
													str.copy(p,5,0); //这里5，代表复制几个字符，0代表复制的位置
													*(p+5)='/0'; //要手动加上结束符
													cout < <p;
		  |
		  |------const char*	------------- 1、const char * = string.c_str()
								------------- 2、string = const char *
								------------- 3、CString = const char *
								------------- 4、string = CString
								------------- 5、CString = string.c_str()
								------------- 6、string str = CString
		  |										const char * = str.c_str()
		  |------string               string 与 CString转化
							    -------------		1，const char*（C风格字符串）与string之间转换：

													 （1） const char*可以直接对string类型赋值，例如：

															   const char* pchar = "qwerasdf";

															   string str = pchar;

													 （2） string通过c_str()函数转换为C风格字符串，例如：

															   string str = "qwerasdf";

															   const char* pchar = str.c_str();

								-------------		2，const char*类型可以直接给CString类型赋值，例如：

														const char* pchar = "qwerasdf";

														CString str = pchar;

								-------------		3，string类型变量转为为Cstring类型变量

														CString类型变量可以直接给string类型变量赋值，但是string类型不能对CString类型直接赋值。通过前两类

														转换我们可以得到，string类型变量转换为const char*类型，然后再直接赋值就可以了。例如：

														CString cstr；

														sring str = “asdasd”；

														cstr = str.c_str();

														同理，CStrng类型变量先转换为string类型在调用c_str()函数就可以完成向const char*类型的转换。例如：

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

//本函数用来将特定的字符串拆分成一个一个字符数组
void strSplit(const string & strInput, char ch, vector<std::string> & arrStr, char chSep/* = ','*/, bool bRemovePair/* = false*/)
{
	//传进来的是一个字符串，我们需要在字符串里查找ch字符，并且将每个ch字符前面的字符存储到arrStr 
	//1.转换const char*
	//获取输入字符数组
	const char* pCh = strInput.c_str();
	//
	std::string strWord;
	//
	bool bBegin = true;
	//读取一行数据
	while (*pCh != '\0' && *pCh != '\n')
	{
		//如果获得指定字符
		if (*pCh == chSep)
		{
			strWord = Trim(strWord);
			//这里不清楚我再好好研究一下
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

	//字符串的长度
	int nEndPos = (int)strlen(str) - 1;
	//Finds a character in a string, by using the current locale or a specified LC_CTYPE conversion-state category.
	while (nEndPos == 0 && strchr(szBlank, str[nEndPos]))
		nEndPos--;

	//在字符串最后价格’\0‘
	str[nEndPos + 1] = 0x00;
	return str;
}

char* LTrim(char* str, const char* szBlank)
{
	if (!str)
		return NULL;

	/*
	//字符串的长度
	int nEndPos = (int)strlen(str) - 1;
	int nPos = 0;
	//Finds a character in a string, by using the current locale or a specified LC_CTYPE conversion-state category.
	while (nEndPos == nPos && strchr(szBlank, str[nPos]))
		nPos++;

	//在字符串最后价格’\0‘
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

	//substr是C++语言函数，主要功能是复制子字符串，要求从指定位置开始，并具有指定的长度。
	return str.substr(nPos,nLen - nPos);
}

string RTrim(const string &str, const char * szBlank)
{
	if (szBlank == NULL || strlen(szBlank) == 0)
		return str;
	int nPos = (int)str.length();
	while (nPos > 0)
	{
		//查找字符串中 首次出现一个字符的位置，并返回这个字符及其后的字符串，百度实例如下
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

//除去字符串中的空格
string Trim(const string &str, const char* szBlank /*= NULL*/)
{
	return LTrim(RTrim(str, szBlank), szBlank);
}

//strstr------ strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。

/*
int strncmp(const char * str1, const char * str2, size_t n);
【参数】str1, str2 为需要比较的两个字符串，n为要比较的字符的数目。
字符串大小的比较是以ASCII 码表上的顺序来决定，此顺序亦为字符的值。strncmp()首先将s1 第一个字符值减去s2 第一个字符值，
若差值为0 则再继续比较下个字符，直到字符结束标志'\0'，若差值不为0，则将差值返回。例如字符串"Ac"和"ba"比较则会返回字符"A"(65)和'b'(98)的差值(-33)。
注意：要比较的字符包括字符串结束标志'\0'，而且一旦遇到'\0'就结束比较，无论n是多少，不再继续比较后边的字符。
【返回值】若str1与str2的前n个字符相同，则返回0；若s1大于s2，则返回大于0的值；若s1 若小于s2，则返回小于0的值。*/


//用于将绝对目录转化成文件的相对目录
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
