
// MFC_Calu01.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Calu01App:
// �� Ŭ������ ������ ���ؼ��� MFC_Calu01.cpp�� �����Ͻʽÿ�.
//

class CMFC_Calu01App : public CWinApp
{
public:
	CMFC_Calu01App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Calu01App theApp;