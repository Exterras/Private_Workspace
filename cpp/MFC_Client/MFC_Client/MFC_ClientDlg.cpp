
// MFC_ClientDlg.cpp : ���� ����
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


// CMFC_ClientDlg ��ȭ ����



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


// CMFC_ClientDlg �޽��� ó����

BOOL CMFC_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	//  �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE); // ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE); // ���� �������� �����մϴ�.

	mh_socket = socket(AF_INET, SOCK_STREAM, 0); // ���� ����

	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(MY_IP_ADDRESS);
	srv_addr.sin_port = htons(MY_PORT);

	WSAAsyncSelect(mh_socket, m_hWnd, 25001, FD_CONNECT);
	m_connect_flag = 1; // ������ ���¸� ��Ÿ���� �÷��װ�

	AddEventString("������ ������ �õ��մϴ�...");

	//������ ����ǰ�(listen) �־�ߵ�, Ŀ��Ʈ �Լ��� �����ϸ� �ִ� 28�� ���� ������� ���¿� ����
	connect(mh_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.

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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_ClientDlg::OnPaint()
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
HCURSOR CMFC_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_ClientDlg::AddEventString(const char *ap_string) {
	// 500������ ���ڿ��� �����ϰ�, ���� �ֱ��� ���ڸ� �� �Ʒ���, ���콺 Ŀ���� �ڵ����� ���� �ֱ��� ���ڸ� �� �� �ֵ��� ���ҽ��ϴ�.
	while (m_chat_list.GetCount() > 500) {
		m_chat_list.DeleteString(0); // �׸��� ������ 500���� �Ѿ��, ���� �����ִ� �׸��� ����ڴ�
	}

	// ���ڿ��� �߰��ϴ� ����
	// ù��° ���ڴ� ������ -> ���� �߰��ϰ����ϴ� ��ġ
	int index = m_chat_list.InsertString(-1, ap_string);

	// ������ �Է� �׸� Ŀ���� ���̰� �ϴ� �Լ�
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
		// Ư�� ��ȭ���� ��Ʈ�ѷ� ������. -> ����
		// GotoDlgCtrl �Լ��� ������ edit box�� ������ ������ ���� ������ �����Ͽ� ���õǰ� �մϴ�.
	}
}

void CMFC_ClientDlg::SendFrameData
	(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char* ap_send_data)
{
	char *p_send_data = new char[4 + a_body_size];
	*p_send_data = 27; // ��� ����
	*(p_send_data + 1) = a_message_id;
	*(unsigned short *)(p_send_data + 2) = a_body_size;

	memcpy(p_send_data + 4, ap_send_data, a_body_size);
	send(ah_socket, p_send_data, a_body_size + 4, 0);
	delete[] p_send_data;
}


// 25001 �޽��� ó��( connect ���� Ȯ�� )
afx_msg LRESULT CMFC_ClientDlg::On25001(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam)) {
		m_connect_flag = 0;
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET;
		AddEventString("������ ������ �����߽��ϴ�.~");
	}
	else {
		m_connect_flag = 2;
		WSAAsyncSelect(mh_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		AddEventString("������ �����߽��ϴ�.");
	}
	return 0;
}

// 25002 �޽��� ( FD_READ, FD_CLOSE ó�� )
afx_msg LRESULT CMFC_ClientDlg::On25002(WPARAM wParam, LPARAM lParam)
{
	CString str;

	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
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
					if (x == SOCKET_ERROR)break;
					total = total + x;
					if (total < body_size) {
						Sleep(50); // 50ms
						retry++;
						if (retry > 5) break; // ��õ� 5�� ������ break
					}
				}
			}

			// ������ �ٸ� �κ�-1
			if (message_id == 1) { 
				AddEventString(p_body_data);
			} // �������-1

			if (p_body_data != NULL)delete[] p_body_data;
			WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}

	// FD_CLOSE
	// ������ �ٸ� �κ�-2
	else {
		closesocket(mh_socket); // Ŭ���̾�Ʈ ���� Ŭ����
		mh_socket = INVALID_SOCKET;
		m_connect_flag = 0; // ���� ���� flag ����
		AddEventString("������ ������ ���� �߽��ϴ�.~");
	// �������-2
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
