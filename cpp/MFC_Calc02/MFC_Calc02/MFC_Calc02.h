
// MFC_Calc02.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Calc02App:
// �� Ŭ������ ������ ���ؼ��� MFC_Calc02.cpp�� �����Ͻʽÿ�.
//

class CMFC_Calc02App : public CWinApp
{
public:
	CMFC_Calc02App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Calc02App theApp;