
// MFC_Chatting2Dlg.h : 헤더 파일
//

#pragma once
#define MAX_USER_COUNT 100

struct UserInfo
{	
	SOCKET h_socket;
	char ip_address[16];
};

// CMFC_Chatting2Dlg 대화 상자
class CMFC_Chatting2Dlg : public CDialogEx
{
private:
	// 윈도우즈 프로그램에서 소켓 핸들은 SOCKET이라는 타입으로 관리한다.
	// 그리고 소켓 타입에 변수를 만든다.
	// 이 변수는 클라이언트 접속을 받아주는 역할을 함.
	SOCKET mh_socket;

	UserInfo m_user_list[MAX_USER_COUNT]; // 사용자를 총 100명으로 받고 배열로 관리함
	unsigned int m_user_count = 0; // 실제 사용하는 사용자 수, 0으로 초기화, 사용자 수는 음수가 안됨

// 생성입니다.
public:
	CMFC_Chatting2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATTING2_DIALOG };
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
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
};
