
// MFC_Chatting1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Chatting1App:
// �� Ŭ������ ������ ���ؼ��� MFC_Chatting1.cpp�� �����Ͻʽÿ�.
//

class CMFC_Chatting1App : public CWinApp
{
public:
	CMFC_Chatting1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Chatting1App theApp;