#pragma once
#include <iostream>

using namespace std;

//获取文件路径不包含文件名
string GetFilePath(string strFilePath);

//获取文件名称
string GetFileName(string strFilePath);

//获取文件名称不包含后缀名
string GetFileTitle(string strFilePath);

//获取文件后缀名
string GetFileNameExt(string strFilePath);

//指定文件大概路径，在子目录中找文件
string FindFilepath(string strDirPath, string strFileName);