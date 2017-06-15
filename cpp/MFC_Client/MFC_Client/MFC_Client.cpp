
// MFC_Client.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CMFC_ClientApp 생성

CMFC_ClientApp::CMFC_ClientApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFC_ClientApp 개체입니다.

CMFC_ClientApp theApp;


// CMFC_ClientApp 초기화
BOOL CMFC_ClientApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	WSADATA temp; // 소켓 사용은 해당 코드 이후 부터 가능함****

	WSAStartup(0x0202, &temp);

	CMFC_ClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	WSACleanup(); // 소켓을 지운다 -> 쓰고 있는 건 다 쓰고 지움
	return FALSE;
}

