#include "stdafx.h"
#include "FileUtils.h"
/************************************************************************/
/* 
	�ļ�·��������
*/
/************************************************************************/

//��ȡ�ļ�·�������ļ���
string GetFilePath(string strFilePath)
{
	//��ʼ������Ҫ
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//��ȡ�ļ����ư�����׺��
string GetFileName(string strFilePath)
{
	//��ʼ������Ҫ
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//��ȡ�ļ����Ʋ�������׺��
string GetFileTitle(string strFilePath)
{
	//��ʼ������Ҫ
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//��ȡ�ļ���׺��
string GetFileNameExt(string strFilePath)
{
	//��ʼ������Ҫ
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//ָ���ļ����·��������Ŀ¼�����ļ�
string FindFilepath(string strDirPath, string strFileName)
{
	//�ݹ�ѭ��������
	return NULL;
}