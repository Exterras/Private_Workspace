
// MFC_Chatting2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Chatting2.h"
#include "MFC_Chatting2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW


#endif
#pragma warning(disable:4996)


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


// CMFC_Chatting2Dlg 대화 상자



CMFC_Chatting2Dlg::CMFC_Chatting2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CHATTING2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Chatting2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_Chatting2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(25001, &CMFC_Chatting2Dlg::On25001)
	ON_MESSAGE(25002, &CMFC_Chatting2Dlg::On25002)
END_MESSAGE_MAP()


// CMFC_Chatting2Dlg 메시지 처리기

BOOL CMFC_Chatting2Dlg::OnInitDialog()
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 첫 번째 인자는 어떤 소켓을 사용할 지 정한다.
	// 여러가지 주소들 중 AF_INET 이라는 주소 체계를 사용하겠다는 의미
	// stream : c++ 처럼 다형성의 개념, 새로운 장치가 나오더라도 그 장비에 맞는 방식을 사용
	// 데이터를 표준화 하는 것이 원래 의미이지만, 요즘은 데이터의 흐름이라고 생각하면 된다.
	// 두 번째 인자는 소켓의 타입을 정하는 것이다. TCP(1:1), UDP(n:n) 통신방식이 있다. 
	// SOCK_STREAM = TCP, SOCK_DGRAM : UDP
	// 세 번째 인자는 TCP인지 UDP인지 방식을 결정한다. 그래서 해당 프로토컬을 적으면 되는데
	// 0 이라 적으면 알아서 해당 프로토컬에 매칭시켜줌.
	mh_socket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in srv_addr; // 등록 서류 작성
	srv_addr.sin_family = AF_INET; // AF_INET 주소를 사용하겠다는 의미
	srv_addr.sin_addr.s_addr = inet_addr("114.71.64.101"); // "해당 주소에서" 사용하겠다는 연습용 의미
	srv_addr.sin_port = htons(2001); // ipconfig

	// link : 물리적으로 연결해야 연결 되는 것, 즉 서로 다른 두 물체가 연결되어야만 어떠한 기능을 할 때
	// bind : 서로 다른 두 물체가 연결되지 않더라도 서로 다른 기능을 하며 이 물체들이 연결될 때
	bind(mh_socket, (LPSOCKADDR)&srv_addr, sizeof(struct sockaddr_in));

	// 소켓은 발신만 할 수 있게끔 되어 있다.
	// 그래서 수신도 할 수 있게 listen 함수를 통해 가능하게 한다. 두 번째 인자는 대기자 수이다.
	listen(mh_socket, 1);
	


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFC_Chatting2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_Chatting2Dlg::OnPaint()
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
HCURSOR CMFC_Chatting2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT CMFC_Chatting2Dlg::On25001(WPARAM wParam, LPARAM lParam)
{
	sockaddr_in client_addr;
	int sockaddr_in_size = sizeof(sockaddr_in);

	SOCKET h_socket = accept((SOCKET)wParam, (LPSOCKADDR)&client_addr, &sockaddr_in_size);

	// 여기서부터는 접속을 했을 경우
	if (m_user_count < MAX_USER_COUNT) {
		m_user_list[m_user_count].h_socket = h_socket;
		strcpy(m_user_list[m_user_count].ip_address, inet_ntoa(client_addr.sin_addr));
		// inet_ntoa는 숫자를 문자열로 바꿔주는 함수

		// FD_READ : 클라이언트가 나한테 접속했다. 
		// FD_CLOSE : 접속을 끊었다.
		// 대화상자로 25002번째를 사용하겠다는 뜻
		WSAAsyncSelect(h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		
		m_user_count++;
	} else {
		closesocket(h_socket);
	}
	return 0;
}


afx_msg LRESULT CMFC_Chatting2Dlg::On25002(WPARAM wParam, LPARAM lParam)
{
	// if (IS_ERROR(IParam))
	int i;
	for (i = 0; i < m_user_count; i++) {
		if (m_user_list[i].h_socket == wParam) {
			break;
		}
	}

	// 어떤 이벤트에 의해 선택되어 고르겠다.
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		// 상대방이 나에게 접속했다.
	} else {
		// 상대방이 날 끊었다.
		m_user_count--;

		if (m_user_count != i) { // 같으면 마지막이라는 뜻
			memcpy(&m_user_list[i], &m_user_list[m_user_count], sizeof(UserInfo));
		}
		closesocket((SOCKET)wParam);
	}

	return 0;
}
