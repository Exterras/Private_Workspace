
// MFC_Client.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_ClientApp:
// �� Ŭ������ ������ ���ؼ��� MFC_Client.cpp�� �����Ͻʽÿ�.
//

class CMFC_ClientApp : public CWinApp
{
public:
	CMFC_ClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_ClientApp theApp;