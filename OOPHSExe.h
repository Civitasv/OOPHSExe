
// OOPHSExe.h : OOPHSExe Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COOPHSExeApp:
// �йش����ʵ�֣������ OOPHSExe.cpp
//

class COOPHSExeApp : public CWinApp
{
public:
	COOPHSExeApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COOPHSExeApp theApp;
