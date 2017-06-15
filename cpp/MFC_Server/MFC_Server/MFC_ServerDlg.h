
// MFC_ServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#define MAX_USER_COUNT 100

// CMFC_ServerDlg 대화 상자
class CMFC_ServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_ServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void AddEventString(const char * ap_string);
	DECLARE_MESSAGE_MAP()
	struct UserData {
		SOCKET h_socket; // '-1' is Not Using, Others Use.
		char ip_address[16]; // xxx.xxx.xxx.xxx
	};
private:
	CListBox m_event_list;
	SOCKET mh_listen_socket;
	UserData m_user_list[MAX_USER_COUNT];
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
	void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char * ap_send_data);
public:
	afx_msg void OnDestroy();
};
