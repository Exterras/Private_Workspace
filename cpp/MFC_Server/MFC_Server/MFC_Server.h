
// MFC_Server.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_ServerApp:
// �� Ŭ������ ������ ���ؼ��� MFC_Server.cpp�� �����Ͻʽÿ�.
//

class CMFC_ServerApp : public CWinApp
{
public:
	CMFC_ServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_ServerApp theApp;