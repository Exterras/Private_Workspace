
// MFC_ClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMFC_ClientDlg 대화 상자
class CMFC_ClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_ClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CLIENT_DIALOG };
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
public:
	// chatting window
	CListBox m_chat_list;
	afx_msg void OnBnClickedSendBtn();
	void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char * ap_send_data);
private:
	// 비트가 변하는 환경에 영향받지 않음
	SOCKET mh_socket = INVALID_SOCKET; 
	
	// 클라이언트의 연결 상태를 나타내는 옵션 값
	// 0 : 접속해제, 1 : 접속중, 2 : 접속됨
	char m_connect_flag = 0;
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
};
