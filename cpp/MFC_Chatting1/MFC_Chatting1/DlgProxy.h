
// DlgProxy.h: ��� ����
//

#pragma once

class CMFC_Chatting1Dlg;


// CMFC_Chatting1DlgAutoProxy ��� ���

class CMFC_Chatting1DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFC_Chatting1DlgAutoProxy)

	CMFC_Chatting1DlgAutoProxy();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.

// Ư���Դϴ�.
public:
	CMFC_Chatting1Dlg* m_pDialog;

// �۾��Դϴ�.
public:

// �������Դϴ�.
	public:
	virtual void OnFinalRelease();

// �����Դϴ�.
protected:
	virtual ~CMFC_Chatting1DlgAutoProxy();

	// ������ �޽��� �� �Լ�

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFC_Chatting1DlgAutoProxy)

	// ������ OLE ����ġ �� �Լ�

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

