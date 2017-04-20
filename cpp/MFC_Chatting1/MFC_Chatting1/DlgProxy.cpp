
// DlgProxy.cpp : ���� ����
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
	
	// �ڵ�ȭ ��ü�� Ȱ��ȭ�Ǿ� �ִ� ���� ��� ���� ���α׷��� �����ϱ� ���� 
	//	�����ڿ��� AfxOleLockApp�� ȣ���մϴ�.
	AfxOleLockApp();

	// ���� ���α׷��� �� â �����͸� ���� ��ȭ ���ڿ� ����
	//  �׼����� �����ɴϴ�.  ���Ͻ��� ���� �����͸� �����Ͽ�
	//  ��ȭ ���ڸ� ����Ű�� ��ȭ ������ �Ĺ� �����͸� �� ���Ͻ÷�
	//  �����մϴ�.
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
	// ��� ��ü�� OLE �ڵ�ȭ�� ��������� �� ���� ���α׷��� �����ϱ� ����
	// 	�Ҹ��ڰ� AfxOleUnlockApp�� ȣ���մϴ�.
	//  �̷��� ȣ��� �� ��ȭ ���ڰ� ������ �� �ֽ��ϴ�.
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFC_Chatting1DlgAutoProxy::OnFinalRelease()
{
	// �ڵ�ȭ ��ü�� ���� ������ ������ �����Ǹ�
	// OnFinalRelease�� ȣ��˴ϴ�.  �⺻ Ŭ�������� �ڵ����� ��ü�� �����մϴ�.
	// �⺻ Ŭ������ ȣ���ϱ� ���� ��ü�� �ʿ��� �߰� ���� �۾���
	// �߰��Ͻʽÿ�.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFC_Chatting1DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFC_Chatting1DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ����: IID_IMFC_Chatting1�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�.
//  �� IID�� .IDL ���Ͽ� �ִ� dispinterface�� GUID�� ��ġ�ؾ� �մϴ�.

// {60F06000-353E-48FB-A96D-BE953EBB271C}
static const IID IID_IMFC_Chatting1 =
{ 0x60F06000, 0x353E, 0x48FB, { 0xA9, 0x6D, 0xBE, 0x95, 0x3E, 0xBB, 0x27, 0x1C } };

BEGIN_INTERFACE_MAP(CMFC_Chatting1DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFC_Chatting1DlgAutoProxy, IID_IMFC_Chatting1, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ��ũ�ΰ� �� ������Ʈ�� StdAfx.h�� ���ǵ˴ϴ�.
// {7ED26032-BF0A-41A8-9ADA-806ED20D5F4A}
IMPLEMENT_OLECREATE2(CMFC_Chatting1DlgAutoProxy, "MFC_Chatting1.Application", 0x7ed26032, 0xbf0a, 0x41a8, 0x9a, 0xda, 0x80, 0x6e, 0xd2, 0xd, 0x5f, 0x4a)


// CMFC_Chatting1DlgAutoProxy �޽��� ó����
