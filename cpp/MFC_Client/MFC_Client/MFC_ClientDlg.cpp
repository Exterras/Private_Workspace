
// MFC_ClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Client.h"
#include "MFC_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif

#define MY_IP_ADDRESS	((const char *)"114.71.64.101")
#define MY_PORT	((int)15000)

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ClientDlg 대화 상자



CMFC_ClientDlg::CMFC_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_LIST, m_chat_list);
}

BEGIN_MESSAGE_MAP(CMFC_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFC_ClientDlg::OnBnClickedSendBtn)
	ON_MESSAGE(25001, &CMFC_ClientDlg::On25001)
	ON_MESSAGE(25002, &CMFC_ClientDlg::On25002)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFC_ClientDlg 메시지 처리기

BOOL CMFC_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//  이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE); // 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE); // 작은 아이콘을 설정합니다.

	mh_socket = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성

	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(MY_IP_ADDRESS);
	srv_addr.sin_port = htons(MY_PORT);

	WSAAsyncSelect(mh_socket, m_hWnd, 25001, FD_CONNECT);
	m_connect_flag = 1; // 접속중 상태를 나타내는 플래그값

	AddEventString("서버에 접속을 시도합니다...");

	//서버가 실행되고(listen) 있어야됨, 커넥트 함수가 실패하면 최대 28초 동안 응답없음 상태에 빠짐
	connect(mh_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

}

void CMFC_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFC_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_ClientDlg::AddEventString(const char *ap_string) {
	// 500개까지 문자열을 제한하고, 가장 최근의 문자를 맨 아래에, 마우스 커서는 자동으로 가장 최근의 글자를 볼 수 있도록 놓았습니다.
	while (m_chat_list.GetCount() > 500) {
		m_chat_list.DeleteString(0); // 항목의 갯수가 500개를 넘어서면, 가장 위에있는 항목을 지우겠다
	}

	// 문자열을 추가하는 행위
	// 첫번째 인자는 정수값 -> 내가 추가하고자하는 위치
	int index = m_chat_list.InsertString(-1, ap_string);

	// 마지막 입력 항목에 커서가 놓이게 하는 함수
	m_chat_list.SetCurSel(index);
}


void CMFC_ClientDlg::OnBnClickedSendBtn()
{
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT, str);

	if (m_connect_flag == 2) {
		SendFrameData(mh_socket, 1, str.GetLength() + 1, (char *)(const char *)str);

		SetDlgItemText(IDC_CHAT_LIST, str);
		GotoDlgCtrl(GetDlgItem(IDC_CHAT_EDIT));
		// 특정 대화상자 컨트롤로 보낸다. -> 반전
		// GotoDlgCtrl 함수의 역할은 edit box의 내용을 보내면 보낸 내용을 반전하여 선택되게 합니다.
	}
}

void CMFC_ClientDlg::SendFrameData
	(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char* ap_send_data)
{
	char *p_send_data = new char[4 + a_body_size];
	*p_send_data = 27; // 헤더 구성
	*(p_send_data + 1) = a_message_id;
	*(unsigned short *)(p_send_data + 2) = a_body_size;

	memcpy(p_send_data + 4, ap_send_data, a_body_size);
	send(ah_socket, p_send_data, a_body_size + 4, 0);
	delete[] p_send_data;
}


// 25001 메시지 처리( connect 상태 확인 )
afx_msg LRESULT CMFC_ClientDlg::On25001(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam)) {
		m_connect_flag = 0;
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET;
		AddEventString("서버에 접속을 실패했습니다.~");
	}
	else {
		m_connect_flag = 2;
		WSAAsyncSelect(mh_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		AddEventString("서버에 접속했습니다.");
	}
	return 0;
}

// 25002 메시지 ( FD_READ, FD_CLOSE 처리 )
afx_msg LRESULT CMFC_ClientDlg::On25002(WPARAM wParam, LPARAM lParam)
{
	CString str;

	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);
		char key;
		recv(wParam, &key, 1, 0);

		// 자신의 클라이언트에서 보낸 건지 확인
		if (key == 27) {
			char message_id;
			recv(wParam, &message_id, 1, 0);
			unsigned short body_size;
			recv(wParam, (char *)&body_size, 2, 0);
			char* p_body_data = NULL;

			// 0보다 큰 사이즈로 데이터가 들어왔을경우만        
			if (body_size > 0) {
				p_body_data = new char[body_size];
				int total = 0, x, retry = 0;

				//recv가 수신한 사이즈에 맞게 content를 받음
				while (total < body_size) {
					x = recv(wParam, p_body_data + total, body_size - total, 0);
					if (x == SOCKET_ERROR)break;
					total = total + x;
					if (total < body_size) {
						Sleep(50); // 50ms
						retry++;
						if (retry > 5) break; // 재시도 5번 넘으면 break
					}
				}
			}

			// 서버와 다른 부분-1
			if (message_id == 1) { 
				AddEventString(p_body_data);
			} // 여기까지-1

			if (p_body_data != NULL)delete[] p_body_data;
			WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}

	// FD_CLOSE
	// 서버와 다른 부분-2
	else {
		closesocket(mh_socket); // 클라이언트 소켓 클로즈
		mh_socket = INVALID_SOCKET;
		m_connect_flag = 0; // 연결 해제 flag 변경
		AddEventString("서버가 연결을 해제 했습니다.~");
	// 여기까지-2
	}
	return 0;

}


void CMFC_ClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (mh_socket != INVALID_SOCKET) {
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET;
	}

}
