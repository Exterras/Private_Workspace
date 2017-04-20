
// MFC_Chatting1Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

class CMFC_Chatting1DlgAutoProxy;

#define MAX_USER_COUNT 100

// CMFC_Chatting1Dlg 대화 상자
class CMFC_Chatting1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFC_Chatting1Dlg);
	friend class CMFC_Chatting1DlgAutoProxy;

// 생성입니다.
public:
	CMFC_Chatting1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CMFC_Chatting1Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATTING1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	CMFC_Chatting1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	void AddEventString(const char * ap_string);

	// 생성된 메시지 맵 함수
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