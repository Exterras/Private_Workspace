
// MFC_Notepad3.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Notepad3App:
// �� Ŭ������ ������ ���ؼ��� MFC_Notepad3.cpp�� �����Ͻʽÿ�.
//

class CMFC_Notepad3App : public CWinApp
{
public:
	CMFC_Notepad3App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Notepad3App theApp;