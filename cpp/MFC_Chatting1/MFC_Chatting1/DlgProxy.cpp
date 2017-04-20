
// DlgProxy.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Chatting1.h"
#include "DlgProxy.h"
#include "MFC_Chatting1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Chatting1DlgAutoProxy

IMPLEMENT_DYNCREATE(CMFC_Chatting1DlgAutoProxy, CCmdTarget)

CMFC_Chatting1DlgAutoProxy::CMFC_Chatting1DlgAutoProxy()
{
	EnableAutomation();
	
	// 자동화 개체가 활성화되어 있는 동안 계속 응용 프로그램을 실행하기 위해 
	//	생성자에서 AfxOleLockApp를 호출합니다.
	AfxOleLockApp();

	// 응용 프로그램의 주 창 포인터를 통해 대화 상자에 대한
	//  액세스를 가져옵니다.  프록시의 내부 포인터를 설정하여
	//  대화 상자를 가리키고 대화 상자의 후방 포인터를 이 프록시로
	//  설정합니다.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMFC_Chatting1Dlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFC_Chatting1Dlg)))
		{
			m_pDialog = reinterpret_cast<CMFC_Chatting1Dlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFC_Chatting1DlgAutoProxy::~CMFC_Chatting1DlgAutoProxy()
{
	// 모든 개체가 OLE 자동화로 만들어졌을 때 응용 프로그램을 종료하기 위해
	// 	소멸자가 AfxOleUnlockApp를 호출합니다.
	//  이러한 호출로 주 대화 상자가 삭제될 수 있습니다.
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFC_Chatting1DlgAutoProxy::OnFinalRelease()
{
	// 자동화 개체에 대한 마지막 참조가 해제되면
	// OnFinalRelease가 호출됩니다.  기본 클래스에서 자동으로 개체를 삭제합니다.
	// 기본 클래스를 호출하기 전에 개체에 필요한 추가 정리 작업을
	// 추가하십시오.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFC_Chatting1DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFC_Chatting1DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 참고: IID_IMFC_Chatting1에 대한 지원을 추가하여
//  VBA에서 형식 안전 바인딩을 지원합니다.
//  이 IID는 .IDL 파일에 있는 dispinterface의 GUID와 일치해야 합니다.

// {60F06000-353E-48FB-A96D-BE953EBB271C}
static const IID IID_IMFC_Chatting1 =
{ 0x60F06000, 0x353E, 0x48FB, { 0xA9, 0x6D, 0xBE, 0x95, 0x3E, 0xBB, 0x27, 0x1C } };

BEGIN_INTERFACE_MAP(CMFC_Chatting1DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFC_Chatting1DlgAutoProxy, IID_IMFC_Chatting1, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 매크로가 이 프로젝트의 StdAfx.h에 정의됩니다.
// {7ED26032-BF0A-41A8-9ADA-806ED20D5F4A}
IMPLEMENT_OLECREATE2(CMFC_Chatting1DlgAutoProxy, "MFC_Chatting1.Application", 0x7ed26032, 0xbf0a, 0x41a8, 0x9a, 0xda, 0x80, 0x6e, 0xd2, 0xd, 0x5f, 0x4a)


// CMFC_Chatting1DlgAutoProxy 메시지 처리기
