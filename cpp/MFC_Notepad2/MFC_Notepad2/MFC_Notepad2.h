
// MFC_Notepad2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Notepad2App:
// �� Ŭ������ ������ ���ؼ��� MFC_Notepad2.cpp�� �����Ͻʽÿ�.
//

class CMFC_Notepad2App : public CWinApp
{
public:
	CMFC_Notepad2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Notepad2App theApp;