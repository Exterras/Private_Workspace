
// MFC_Paint2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Paint2App:
// �� Ŭ������ ������ ���ؼ��� MFC_Paint2.cpp�� �����Ͻʽÿ�.
//

class CMFC_Paint2App : public CWinApp
{
public:
	CMFC_Paint2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Paint2App theApp;