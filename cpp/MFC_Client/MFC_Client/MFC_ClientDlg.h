
// MFC_ClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMFC_ClientDlg ��ȭ ����
class CMFC_ClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_ClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void AddEventString(const char * ap_string);
	DECLARE_MESSAGE_MAP()
public:
	// chatting window
	CListBox m_chat_list;
	afx_msg void OnBnClickedSendBtn();
	void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char * ap_send_data);
private:
	// ��Ʈ�� ���ϴ� ȯ�濡 ������� ����
	SOCKET mh_socket = INVALID_SOCKET; 
	
	// Ŭ���̾�Ʈ�� ���� ���¸� ��Ÿ���� �ɼ� ��
	// 0 : ��������, 1 : ������, 2 : ���ӵ�
	char m_connect_flag = 0;
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
};
