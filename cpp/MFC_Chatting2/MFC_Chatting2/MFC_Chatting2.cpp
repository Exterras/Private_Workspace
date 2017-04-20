
// MFC_Chatting2.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "MFC_Chatting2.h"
#include "MFC_Chatting2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Chatting2App

BEGIN_MESSAGE_MAP(CMFC_Chatting2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC_Chatting2App ����

CMFC_Chatting2App::CMFC_Chatting2App()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CMFC_Chatting2App ��ü�Դϴ�.

CMFC_Chatting2App theApp;


// CMFC_Chatting2App �ʱ�ȭ

BOOL CMFC_Chatting2App::InitInstance()
{
	CWinApp::InitInstance();

	// WSADATA ����ü�� ������ �ϳ� ����
	// �� �Լ��� �ʱ�ȭ�ϸ鼭 ���� ��ġ�� �������� ���� ������ ���õ� �������� ������
	// ���� temp�� �־��ش�. ���� temp ������ ���� ���� �� �ý����� �����̳� ���� ������
	// Ȯ���� ������ �ʹ� ������ �� ������ ���α׷����� �������� �ʴ´ٴ� �ǹ̷� ���.
	WSADATA temp;

	// ���� ��ƾ�� ����ϰڴٴ� ��.
	// ������ �������� ����ϰٴٴ� �ǹ̶� ���� ���� ����������ϰ� �ſ� �߿��ϴ�.
	// ù ��° ���ڴ� ���� 2.2 ������ ����ϰڴٴ� �ǹ�
	// �� ��° ���ڴ� ���۰� ����ó�� ������ ��������� ������ ������ �ǹ̷θ� ���/
	WSAStartup(0x0202, &temp);

	CMFC_Chatting2Dlg dlg; // ���̾�α׸� �����.
	m_pMainWnd = &dlg; // ���� �����츦 �Ѱ��ش�.
	dlg.DoModal(); // ���̾�α׸� �����Ѵ�.
	
	WSACleanup(); // ������ �� �̻� ���� �ʴ´�.
	// �� �Լ��� ���� �ʴ´ٸ� �ü���� ���ؿ��� ���ϰ� ���õ� �����Ͱ� �����ִ�.
	// ���� ������ �ߴٸ� �ݵ�� �Ҹ��� ���־�� �Ѵ�.

	return FALSE; 
}
