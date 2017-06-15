
// MFC_Server.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CMFC_ServerApp 생성

CMFC_ServerApp::CMFC_ServerApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFC_ServerApp 개체입니다.

CMFC_ServerApp theApp;


// CMFC_ServerApp 초기화

BOOL CMFC_ServerApp::InitInstance()
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

	WSADATA temp; // window socket, WSA : Window Socket API
	WSAStartup(0x0202, &temp);
	//소켓버젼(0x0202), 윈도우 매니저에게 이 소켓을 쓰겠다고 등록

	CMFC_ServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	WSACleanup(); // socket close 소켓 사용 안함
	return FALSE;

}

