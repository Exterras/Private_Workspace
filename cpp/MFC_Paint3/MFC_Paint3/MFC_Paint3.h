
// MFC_Paint3.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Paint3App:
// �� Ŭ������ ������ ���ؼ��� MFC_Paint3.cpp�� �����Ͻʽÿ�.
//

class CMFC_Paint3App : public CWinApp
{
public:
	CMFC_Paint3App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Paint3App theApp;