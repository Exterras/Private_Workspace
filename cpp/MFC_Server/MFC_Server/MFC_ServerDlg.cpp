
// MFC_ServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Server.h"
#include "MFC_ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif

#define MY_IP_ADDRESS	((const char *)"114.71.64.101")
#define MY_PORT	((int)15000)

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMFC_ServerDlg ��ȭ ����



CMFC_ServerDlg::CMFC_ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CMFC_ServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(25001, &CMFC_ServerDlg::On25001)
	ON_MESSAGE(25002, &CMFC_ServerDlg::On25002)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFC_ServerDlg �޽��� ó����

BOOL CMFC_ServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. 
	// ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡�� �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE); // ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE); // ���� �������� �����մϴ�.

	// SOCKET�� socket�� �ڵ鰪�� ������ �� �ִ� Ÿ��
	// AF_INET : ���ͳ� �⺻ TCP �ּ�(��Ż�), ���� ��� ��������� ����ϰ������, AF_BTS ���� ��
	// SOCK_STREAM : TCP ����� ����ϰڴ�.
	// 3��° ���� : 0 -> 2��° ���� ������ �ڵ����� ���������� ��������
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// �ڵ��� �븮������ �ִ� ���� ������� �����ϸ� ��
	sockaddr_in srv_addr;

	// ������ ��Ż� �̸�, �Ʊ� socket�Լ��� �ι�° ���ڿ� ����
	srv_addr.sin_family = AF_INET;

	// MY_IP_ADDRESS : ���� ��IP�ּҸ� define �Ͽ� �����Ͽ���.
	// ���߿� Ŭ���̾�Ʈ���� �� �ּҸ� �������� ����(���� ��)�� ������ �� �ִ�.
	srv_addr.sin_addr.s_addr = inet_addr(MY_IP_ADDRESS);

	// htonl = host byte order to network order, s=unsigned short int
	// port : �� ��ǻ�Ϳ� ������ ������ ���� �� �ִµ�, ���� �� ���α׷��� ������ȣ �ǹ���
	// ARS���Ϳ� ��ǥ��ȭ(IP)�� ��ȭ�� �� ������ȣ(port)�� �Է��ϴ� �Ͱ� ����
	// port��ȣ�� ���� �����ϰ� �ؾ�, �ٸ� ���α׷����̶� ��ġ�� ����, 15000�� �̻����� ����ϴ� ���� ����
	// MY_PORT = define 15000
	srv_addr.sin_port = htons(MY_PORT);

	// �޴��� ����� ���� ����, ������ ������� ������, ���� ���� �����ϴ� ������ bind�� �Ѵ�.
	// ������ ��Ʈ��ũ ī�忡 ����
	bind(mh_listen_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	
	// ����Ʈ�ڽ��� ���
	AddEventString("���񽺸� �����մϴ�."); 
	
	// �� �� ���� �����ų�(���ÿ� ó���ϴ� ���� �ƴ�,) ������ ������� ������ ������ ����� ������ ������ ����
	listen(mh_listen_socket, 1);
	
	// �񵿱��Լ�
	// accept�� ����ϸ� ���� ����ڰ� ������ ������ ���α׷��� ������¿� ������ ����������
	// h_socket���� FD_ACCEPT �̺�Ʈ�� �߻��ϸ� 25001�޼����� �� ��ȭ���ڿ� ������� ��->������� ���¿� ����������
	WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.

}

void CMFC_ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//  ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_ServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFC_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ����Ʈ �ڽ��� ���� ��� �� Ŀ�� �ڵ��̵��ϴ� �Լ�
void CMFC_ServerDlg::AddEventString(const char *ap_string)
{
	// 3000������ ���ڿ��� �����ϰ�, ���� �ֱ��� ���ڸ� �� �Ʒ���, ���콺 Ŀ���� �ڵ����� ���� �ֱ��� ���ڸ� �� �� �ֵ��� ���ҽ��ϴ�.
	while (m_event_list.GetCount() > 3000) {
		m_event_list.DeleteString(0); // �׸��� ������ 3000���� �Ѿ��, ���� �����ִ� �׸��� ����ڴ�
	}

	// ���ڿ��� �߰��ϴ� ����
	// ù��° ���ڴ� ������ -> ���� �߰��ϰ����ϴ� ��ġ
	int index = m_event_list.InsertString(-1, ap_string);

	// ������ �Է� �׸� Ŀ���� ���̰� �ϴ� �Լ�
	m_event_list.SetCurSel(index);
}

// wParam -> �̺�Ʈ�� �߻��� ������ �ڵ��� �Ѿ��, lParam�� ���Ͽ� �߻��� �޼����� ��FD_ACCEPT 
// ���� �ڸ��� wParam�� ��� ��, 2��° ���ڴ� �����ϴ� client�� ip�� �� �� �ְ��ϴ� ����(�߽��� ǥ��)
afx_msg LRESULT CMFC_ServerDlg::On25001(WPARAM wParam, LPARAM lParam)
{
	sockaddr_in client_addr; 
	int sockaddr_in_size = sizeof(sockaddr_in);

	// h_socket�� Ŭ�� ��������, listen ������ ������. listen ������ �������ʰ� accept ���ϸ� ����
	SOCKET h_socket = accept(mh_listen_socket, (LPSOCKADDR)&client_addr, &sockaddr_in_size);

	// for�� �ۿ����� i�� ����ϱ� ���ؼ�
	int i;

	// backdoor code, socket initiating
	for (i = 0; i < MAX_USER_COUNT; i++) {
		m_user_list[i].h_socket = INVALID_SOCKET;
	}

	// ����ִ� ������ ã�´�
	for (i = 0; i < MAX_USER_COUNT; i++) {
		if (m_user_list[i].h_socket == INVALID_SOCKET) break;
	}

	// �� ���� �ִ� ����
	if (i < MAX_USER_COUNT) {
		m_user_list[i].h_socket = h_socket;// �ش� ������ ����
		strcpy(m_user_list[i].ip_address, inet_ntoa(client_addr.sin_addr)); // client address ����
		WSAAsyncSelect(m_user_list[i].h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		// FD_WRITE�� �������� ������ ������ �� �޼������� �񵿱⸦ ���� ����-> ������ ������ ������ �˱� ����
		// FD_READ ������� �����͸� ���� �� �߻��Ǵ� �޼���
		// FD_CLOSE ������� ���� ��
		// | ��Ʈ �����ڸ� ����ؾ���, or�� �ϸ� ��������Ʈ �Ǽ� �������� ���� �޼����� �ްԵ�
		
		CString str;
		str.Format("%s���� �����߽��ϴ�.", m_user_list[i].ip_address);

	}
	// �� �� ����
	else {
		AddEventString("���� �ִ� �ο� �ʰ�!\n");
		closesocket(h_socket);
	}
	// accept�� ���� Ŭ����->�ʿ䰡 �����Ƿ�
	// ������ client �ٽ� ���� �õ�, -> ����,, �Ǽ�ȯ �ݺ� ���� ���� ������ ������ �ƿ� ������.
	return 0;
}


afx_msg LRESULT CMFC_ServerDlg::On25002(WPARAM wParam, LPARAM lParam)
{
	// lParam���� FD_READ or FD_CLOSE �� ������ �������.
	// wParam�� socket�� ���� unsigned int��
	CString str;

	// �񵿱⿡�� FD_READ�� ���ܽ�Ŵ(�����Ͱ� ���ܼ� ������ ��� �ߺ����� �����ʵ���)
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {

		// FD_CLOSE�� �츰 ������ ���ڱ� ������ ���� ��쿡 ó���� �� �ֵ���        
		WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);

		char key;
		recv(wParam, &key, 1, 0);

		// �ڽ��� Ŭ���̾�Ʈ���� ���� ���� Ȯ��
		if (key == 27) { 
			char message_id;
			recv(wParam, &message_id, 1, 0);
			unsigned short body_size;
			recv(wParam, (char *)&body_size, 2, 0);
			char* p_body_data = NULL;

			// 0���� ū ������� �����Ͱ� ��������츸        
			if (body_size > 0) { 
				p_body_data = new char[body_size];
				int total = 0, x, retry = 0;

				//recv�� ������ ����� �°� content�� ����
				while (total < body_size) {
					x = recv(wParam, p_body_data + total, body_size - total, 0);
					if (x == SOCKET_ERROR) break;
					total = total + x;
					if (total < body_size) {
						Sleep(50); // 50ms
						retry++;
						if (retry > 5) break; // ��õ� 5�� ������ break
					}
				}
			}

			// ���� �߰��� �κ�
			if (message_id == 1) {
				int i;

				// ��� ���Ͽ��� ���´��� ã�°���
				for (i = 0; i < MAX_USER_COUNT; i++) { 
					if (m_user_list[i].h_socket == wParam)break;
				} // i��° ���Ͽ��� ���� ���� Ȯ����

				CString str2; // i��° ������ �ּҿ� ���� �����͸� str2�� ������
				str2.Format("%s : %s", m_user_list[i].ip_address, p_body_data);
				AddEventString(str2); // ���� ����Ʈ �ڽ��� ���

				//������ ��� Ŭ���̾�Ʈ���� ����(broad casting)
				for (i = 0; i < MAX_USER_COUNT; i++) {

					//��ȿ�������� ������ �ƴ϶��
					if (m_user_list[i].h_socket != INVALID_SOCKET) {
						//�ٵ� ������� NULL������ �����ؾ��ϹǷ� +1
						//CString�� char*ĳ������ (char *)(const char *)�� ����
						//���⼭ i�� ���� i�� �������
						SendFrameData(m_user_list[i].h_socket, 1, str2.GetLength() + 1, (char *)(const char*)str2);
					}
				}
			}

			if (p_body_data != NULL)delete[] p_body_data;
			WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}

	else { // FD_CLOSE
		closesocket(wParam); // ���� ���� Ŭ����
		for (int i = 0; i < MAX_USER_COUNT; i++) {

			// �迭�� �����ϴ� ���������� ����
			if (m_user_list[i].h_socket == wParam) { 
				m_user_list[i].h_socket = INVALID_SOCKET;
				str.Format("����ڰ� �����߽��ϴ�.: %s", m_user_list[i].ip_address);
				AddEventString(str);
				break;
			}
		}
	}
	return 0;
}

// ����� �������� content�� ������ �Լ�
void CMFC_ServerDlg::SendFrameData(
	SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char* ap_send_data) {
	
	char *p_send_data = new char[4 + a_body_size]; // ��� 4 byte
	*p_send_data = 27; // key�� �������� 27�� ����
	*(p_send_data + 1) = a_message_id; // message_id
	*(unsigned short *)(p_send_data + 2) = a_body_size; // �Ͻ������� char*�� short*�� �°� ������ ����

	memcpy(p_send_data + 4, ap_send_data, a_body_size); // �����͸� ����
	
	// Ŭ���̾�Ʈ���� ����
	// send(����ȭ�Լ�->�� ����ɶ����� ����� ����)
	send(ah_socket, p_send_data, a_body_size + 4, 0); 
	
	delete[] p_send_data; // ������ ����
}

void CMFC_ServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//â �ݱ��� ���� �ִ� ������ �ִٸ� ��� Ŭ����
	for (int i = 0; i < MAX_USER_COUNT; i++) {
		if (m_user_list[i].h_socket != INVALID_SOCKET) {
			closesocket(m_user_list[i].h_socket);
		}
	}
}
