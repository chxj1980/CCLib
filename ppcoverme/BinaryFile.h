#pragma once

#include "OpenSource.h"

UNSING_STD


/************************************************************************/
/* 
*  进制转换与操作处理接口文件
*  创建人：许立龙
*  创建时间：
*  最后修改时间：
*/
/************************************************************************/

//进制转换函数,需要转换的数字，转换为几进制的数
char* BinaryToOther(int nNumSrc, int nNumInd)
{
	int rs[32];//保存转换后的数据，整数转换结果最多32位，（4字节*8位）
	
	//16进制存储数据
	char map[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	//转换成几进制
	int i;

	//do {
	//	printf("please enter a num: ");
	//	scanf("%d", &nNumSrc);
	//} while (nNumSrc < 0);

	//do {
	//	printf("please enter a num you want to change: ");
	//	scanf("%d", &nNumInd);
	//} while (nNumInd < 2 || nNumInd >16);

	if (nNumSrc < 0)
		return NULL;

	if (nNumInd > 16 || nNumInd < 2)
		return NULL;

	i = 0;

	do {
		rs[i++] = nNumSrc%nNumInd;
		nNumSrc /= nNumInd;
	} while (nNumSrc != 0);

	//变量初始化
	char* str = "";
	vector<char> arrStr;

	arrStr.clear();
	for (i--; i >= 0; i--)
	{
		//sprintf(str, "%c", map[rs[i]]);
		arrStr.push_back(map[rs[i]]);
		*str++ = map[rs[i]];
	}
	//printf("\n");
	return str;
}
