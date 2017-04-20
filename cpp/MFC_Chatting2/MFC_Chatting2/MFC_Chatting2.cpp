
// MFC_Chatting2.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CMFC_Chatting2App 생성

CMFC_Chatting2App::CMFC_Chatting2App()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFC_Chatting2App 개체입니다.

CMFC_Chatting2App theApp;


// CMFC_Chatting2App 초기화

BOOL CMFC_Chatting2App::InitInstance()
{
	CWinApp::InitInstance();

	// WSADATA 구조체의 변수를 하나 만듬
	// 이 함수가 초기화하면서 현재 설치된 윈도우즈 소켓 버전과 관련된 여러가지 정보를
	// 변수 temp에 넣어준다. 따라서 temp 변수를 통해 현재 그 시스템의 버전이나 소켓 버전을
	// 확인해 버전이 너무 넞으면 이 버전은 프로그램에서 동작하지 않는다는 의미로 사용.
	WSADATA temp;

	// 소켓 루틴을 사용하겠다는 뜻.
	// 소켓을 이제부터 사용하겟다는 의미라 제일 먼저 선언해줘야하고 매우 중요하다.
	// 첫 번째 인자는 소켓 2.2 버전을 사용하겠다는 의미
	// 두 번째 인자는 시작과 에러처리 용으로 사용했으나 요즘은 시작의 의미로만 사용/
	WSAStartup(0x0202, &temp);

	CMFC_Chatting2Dlg dlg; // 다이얼로그를 만든다.
	m_pMainWnd = &dlg; // 메인 윈도우를 넘겨준다.
	dlg.DoModal(); // 다이얼로그를 실행한다.
	
	WSACleanup(); // 소켓을 더 이상 쓰지 않는다.
	// 이 함수를 쓰지 않는다면 운영체제에 스텍에서 소켓과 관련된 데이터가 남아있다.
	// 소켓 생성을 했다면 반드시 소멸을 해주어야 한다.

	return FALSE; 
}
