
// MFC_Notepad1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Notepad1App:
// �� Ŭ������ ������ ���ؼ��� MFC_Notepad1.cpp�� �����Ͻʽÿ�.
//

class CMFC_Notepad1App : public CWinApp
{
public:
	CMFC_Notepad1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Notepad1App theApp;