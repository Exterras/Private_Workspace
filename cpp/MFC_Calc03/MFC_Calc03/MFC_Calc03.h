
// MFC_Calc03.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Calc03App:
// �� Ŭ������ ������ ���ؼ��� MFC_Calc03.cpp�� �����Ͻʽÿ�.
//

class CMFC_Calc03App : public CWinApp
{
public:
	CMFC_Calc03App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Calc03App theApp;