
// MFC_Client.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "MFC_Client.h"
#include "MFC_ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_ClientApp

BEGIN_MESSAGE_MAP(CMFC_ClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC_ClientApp ����

CMFC_ClientApp::CMFC_ClientApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CMFC_ClientApp ��ü�Դϴ�.

CMFC_ClientApp theApp;


// CMFC_ClientApp �ʱ�ȭ
BOOL CMFC_ClientApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	WSADATA temp; // ���� ����� �ش� �ڵ� ���� ���� ������****

	WSAStartup(0x0202, &temp);

	CMFC_ClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	WSACleanup(); // ������ ����� -> ���� �ִ� �� �� ���� ����
	return FALSE;
}

