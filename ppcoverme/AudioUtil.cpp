#include "stdafx.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


/*
	mixerOpen��mixerClose���������򿪺͹رջ������豸
	mixerGetNumDevs����ȷ��ϵͳ���ж��ٻ������豸
	mixerGetDevCaps��������ȷ���������豸������
	mixerGetLineInfo���Լ���ָ����Ƶ��·����Ϣ
	mixerGetLineControls���ڼ���һ�����߶������Ƶ��·��صĿ��Ƶ�ͨ����Ϣ
	mixerGetControlDetails���ڼ�����ĳ����Ƶ��·��ص�һ�����Ƶ�����
	mixerSetControlDetails���������ƶ����Ƶ����ԡ�
*/