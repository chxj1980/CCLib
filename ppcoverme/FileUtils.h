#pragma once
#include <iostream>

using namespace std;

//��ȡ�ļ�·���������ļ���
string GetFilePath(string strFilePath);

//��ȡ�ļ�����
string GetFileName(string strFilePath);

//��ȡ�ļ����Ʋ�������׺��
string GetFileTitle(string strFilePath);

//��ȡ�ļ���׺��
string GetFileNameExt(string strFilePath);

//ָ���ļ����·��������Ŀ¼�����ļ�
string FindFilepath(string strDirPath, string strFileName);