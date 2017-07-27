#include "stdafx.h"
#include "FileUtils.h"
/************************************************************************/
/* 
	文件路径操作类
*/
/************************************************************************/

//获取文件路径不含文件名
string GetFilePath(string strFilePath)
{
	//初始化很重要
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//获取文件名称包含后缀名
string GetFileName(string strFilePath)
{
	//初始化很重要
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//获取文件名称不包含后缀名
string GetFileTitle(string strFilePath)
{
	//初始化很重要
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//获取文件后缀名
string GetFileNameExt(string strFilePath)
{
	//初始化很重要
	char* drive = "";
	char* dir = "";
	char* fileName = "";
	char* ext = "";
	_tsplitpath(strFilePath.c_str(), drive, dir, fileName, ext);
	return NULL;
}

//指定文件大概路径，在子目录中找文件
string FindFilepath(string strDirPath, string strFileName)
{
	//递归循环的利用
	return NULL;
}