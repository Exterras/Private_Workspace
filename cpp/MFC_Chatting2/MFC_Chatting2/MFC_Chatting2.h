
// MFC_Chatting2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Chatting2App:
// �� Ŭ������ ������ ���ؼ��� MFC_Chatting2.cpp�� �����Ͻʽÿ�.
//

class CMFC_Chatting2App : public CWinApp
{
public:
	CMFC_Chatting2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Chatting2App theApp;