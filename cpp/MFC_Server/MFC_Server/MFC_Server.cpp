
// MFC_Server.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "MFC_Server.h"
#include "MFC_ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_ServerApp

BEGIN_MESSAGE_MAP(CMFC_ServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC_ServerApp ����

CMFC_ServerApp::CMFC_ServerApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CMFC_ServerApp ��ü�Դϴ�.

CMFC_ServerApp theApp;


// CMFC_ServerApp �ʱ�ȭ

BOOL CMFC_ServerApp::InitInstance()
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

	WSADATA temp; // window socket, WSA : Window Socket API
	WSAStartup(0x0202, &temp);
	//���Ϲ���(0x0202), ������ �Ŵ������� �� ������ ���ڴٰ� ���

	CMFC_ServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	WSACleanup(); // socket close ���� ��� ����
	return FALSE;

}

