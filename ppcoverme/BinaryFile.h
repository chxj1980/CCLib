#pragma once

#include "OpenSource.h"

UNSING_STD


/************************************************************************/
/* 
*  ����ת�����������ӿ��ļ�
*  �����ˣ�������
*  ����ʱ�䣺
*  ����޸�ʱ�䣺
*/
/************************************************************************/

//����ת������,��Ҫת�������֣�ת��Ϊ�����Ƶ���
char* BinaryToOther(int nNumSrc, int nNumInd)
{
	int rs[32];//����ת��������ݣ�����ת��������32λ����4�ֽ�*8λ��
	
	//16���ƴ洢����
	char map[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	//ת���ɼ�����
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

	//������ʼ��
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
