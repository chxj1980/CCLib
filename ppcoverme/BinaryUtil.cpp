#include "stdafx.h"

//����ת������
/*
	ʹ��
	char s1[] = "E";
	int a = toTen(s1, 16);
	cout << a << endl;
	char temp[200];
	int b= 15;
	_itoa(a, temp, 16);
	cout << temp;
*/
void TenToAny(int TenNum, int HexOrBina) 
{
	int i = 0;
	char array[64] = "";
	while (TenNum != 0)
	{
		array[i] = TenNum%HexOrBina;
		if (array[i] >= 10)
			array[i] = array[i] - 10 + 'A';
		else
			array[i] += 48;
		TenNum /= HexOrBina;
		i++;
	}
	i--;
	while (i >= 0)
	{
		printf("%c", array[i]);
		i--;
	}
	printf("\n");
	return;
}

long  toTen(char a[], int bit)
{
	int length = strlen(a);
	int i, b = 1, sum = 0; //iҪ������a���±꣬ע������ֹ��Χ 
	for (i = length - 1; i >= 0; i--)
	{
		if (a[i] >= 'A')
		{
			sum += (a[i] - 'A' + 10) *b;
			b *= bit;
		}
		else
		{
			sum += (a[i] - '0') *b;
			b *= bit;
		}
	}
	return sum;
}


/*
		Unicode���ŷ�Χ        |   UTF-8���뷽ʽ
		(ʮ������)                 |   �������ƣ�
		------------------------------+--------------------------------------------------------------
		0000 0000-0000 007F | 0xxxxxxx
		0000 0080-0000 07FF | 110xxxxx 10xxxxxx
		0000 0800-0000 FFFF | 1110xxxx 10xxxxx 10xxxxxx
		0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

		1�ֽ� 0xxxxxxx   �м����ֽ�ǰ����м���һ
		2�ֽ� 110xxxxx 10xxxxxx
		3�ֽ� 1110xxxx 10xxxxxx 10xxxxxx
		4�ֽ� 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		5�ֽ� 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		6�ֽ� 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		---------------------------------------------------------------------------------------------
*/

