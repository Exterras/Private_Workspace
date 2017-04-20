
// MFC_Chatting1Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

class CMFC_Chatting1DlgAutoProxy;

#define MAX_USER_COUNT 100

// CMFC_Chatting1Dlg ��ȭ ����
class CMFC_Chatting1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFC_Chatting1Dlg);
	friend class CMFC_Chatting1DlgAutoProxy;

// �����Դϴ�.
public:
	CMFC_Chatting1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CMFC_Chatting1Dlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATTING1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	CMFC_Chatting1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	void AddEventString(const char * ap_string);

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
	
private:
	CListBox m_event_list;
	SOCKET mh_listen_socket;
	UserData m_user_list[MAX_USER_COUNT];
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
};

struct UserData
{
	SOCKET h_socket; // -1 : no use socket, else : use socket
	char ip4_address[16]; // 255.255.255.255, num 12 and dot 4
};