
// MFC_Chatting1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Chatting1.h"
#include "MFC_Chatting1Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_Chatting1Dlg 대화 상자


IMPLEMENT_DYNAMIC(CMFC_Chatting1Dlg, CDialogEx);

CMFC_Chatting1Dlg::CMFC_Chatting1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CHATTING1_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFC_Chatting1Dlg::~CMFC_Chatting1Dlg()
{
	// 이 대화 상자에 대한 자동화 프록시가 있을 경우 이 대화 상자에 대한
	//  후방 포인터를 NULL로 설정하여
	//  대화 상자가 삭제되었음을 알 수 있게 합니다.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFC_Chatting1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_Chatting1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(25001, &CMFC_Chatting1Dlg::On25001)
	ON_MESSAGE(25002, &CMFC_Chatting1Dlg::On25002)
END_MESSAGE_MAP()


// CMFC_Chatting1Dlg 메시지 처리기

BOOL CMFC_Chatting1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	//AF_INET : 인터넷 기본 TCP 주소, 0은 2번째 인자 버전과 자동으로 프로토콜을 연결해줌
	sockaddr_in srv_addr;
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("114.71.64.101");//ip는 할당된 ip에 따른다: cmd->ipconfig
	srv_addr.sin_port = htons(18000);//htonl=host byte order to network order, s=unsigned short int

	bind(mh_listen_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	//소켓을 네트워크 카드에 연결
	AddEventString("서비스를 시작합니다.");//리스트박스에 출력
	listen(mh_listen_socket, 1);
	//몇 개 까지 받을거냐(동시에 처리하는 것이 아님,)빠르게 만들려면 소켓을 여러개 만들어 리슨도 여러개 만듬

	WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);//비동기함수
															   //accept를 사용하면 실제 사용자가 접속할 때까지 프로그램이 응답상태에 빠지는 단점이있음
															   //h_socket에서 FD_ACCEPT 이벤트가 발생하면 25001메세지를 이 대화상자에 보내라는 것->응답없음 상태에 빠지지않음

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

}

void CMFC_Chatting1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_Chatting1Dlg::OnPaint()
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
HCURSOR CMFC_Chatting1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 컨트롤러에서 해당 개체 중 하나를 계속 사용하고 있을 경우
//  사용자가 UI를 닫을 때 자동화 서버를 종료하면 안 됩니다.  이들
//  메시지 처리기는 프록시가 아직 사용 중인 경우 UI는 숨기지만,
//  UI가 표시되지 않아도 대화 상자는
//  남겨 둡니다.

void CMFC_Chatting1Dlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFC_Chatting1Dlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFC_Chatting1Dlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMFC_Chatting1Dlg::CanExit()
{
	// 프록시 개체가 계속 남아 있으면 자동화 컨트롤러에서는
	//  이 응용 프로그램을 계속 사용합니다.  대화 상자는 남겨 두지만
	//  해당 UI는 숨깁니다.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CMFC_Chatting1Dlg::AddEventString(const char *ap_string)
{
	//리스트 박스에 문자 출력 및 커서 자동이동하는 함수
	while (m_event_list.GetCount() > 3000) {
		m_event_list.DeleteString(0);
	}
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index);
}


afx_msg LRESULT CMFC_Chatting1Dlg::On25001(WPARAM wParam, LPARAM lParam)
{
	//wParam -> 이벤트가 발생한 소켓의 핸들이 넘어옴, lParam에 소켓에 발생한 메세지가 옴FD_ACCEPT 
	sockaddr_in client_addr;
	int sockaddr_in_size = sizeof(sockaddr_in);
	SOCKET h_socket = accept(mh_listen_socket, (LPSOCKADDR)&client_addr, &sockaddr_in_size);
	//소켓 자리에 wParam을 적어도 됨
	//2번 째 인자는 접속하는 client의 ip를 알 수 있게하는 역할(발신자 표시)
	//h_socket은 클론 소켓으로, listen 소켓을 복제함. listen 소켓은 사용되지않고 accept 소켓만 사용됨

	int i;//for문 밖에서도 i를 사용하기 위해서
	for (i = 0; i < MAX_USER_COUNT; i++) {//비어있는 소켓을 찾는다
		if (m_user_list[i].h_socket == INVALID_SOCKET)break;
	}

	if (i < MAX_USER_COUNT) {//빈 방이 있는 상태
		m_user_list[i].h_socket = h_socket;//해당 소켓을 저장
		strcpy(m_user_list[i].ip_address, inet_ntoa(client_addr.sin_addr));
		//client address 복사
		WSAAsyncSelect(m_user_list[i].h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		//FD_WRITE는 서버에서 데이터 보낼떄 이 메세지에는 비동기를 걸지 않음-> 보내는 시점을 서버가 알기 때문
		//FD_READ 상대편이 데이터를 보낼 때 발생되는 메세지
		//FD_CLOSE 상대편이 끊을 때
		// | 비트 연산자를 사용해야함, or를 하면 오버라이트 되서 마지막에 쓰인 메세지만 받게됨
		CString str;
		str.Format("%s에서 접속했습니다.", m_user_list[i].ip_address);

	}
	else {//꽉 찬 상태
		AddEventString("관리 최대 인원 초과!\n");
		closesocket(h_socket);//accept용 소켓 클로즈->필요가 없으므로
							  //끊어진 client 다시 접속 시도, -> 끊고,, 악순환 반복 따라서 리슨 소켓을 닫으면 아예 못들어옴.
	}
	return 0;
}


afx_msg LRESULT CMFC_Chatting1Dlg::On25002(WPARAM wParam, LPARAM lParam)
{
	//lParam에는 FD_READ or FD_CLOSE 의 정보를 담고있음.
	//wParam과 socket의 형은 unsigned int형
	CString str;
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);
		//비동기에서 FD_READ를 제외시킴(데이터가 끊겨서 들어오는 경우 중복으로 읽지않도록)
		//FD_CLOSE를 살린 이유는 갑자기 연결이 끊길 경우에 처리할 수 있도록        
		char key;
		recv(wParam, &key, 1, 0);
		if (key == 27) {//자신의 클라이언트에서 보낸 건지 확인
			char message_id;
			recv(wParam, &message_id, 1, 0);

			unsigned short body_size;
			recv(wParam, (char *)&body_size, 2, 0);
			char* p_body_data = NULL;
			if (body_size > 0) {//0보다 큰 사이즈로 데이터가 들어왔을경우만        
				p_body_data = new char[body_size];
				int total = 0, x, retry = 0;
				while (total < body_size) {//recv가 수신한 사이즈에 맞게 content를 받음
					x = recv(wParam, p_body_data + total, body_size - total, 0);
					if (x == SOCKET_ERROR)break;
					total = total + x;
					if (total < body_size) {
						Sleep(50);//(5밀리 세컨드 쉼)
						retry++;
						if (retry > 5)break;//재시도 5번 넘으면 break
					}
				}
			}
			if (p_body_data != NULL)delete[] p_body_data;
			WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}
	else {//FD_CLOSE
		  //생략
	}
	return 0;
}

// 실패
// 도대체 무슨말인지 모르므로 다음 프로그램으로 그냥 넘어가자
