
// MFC_Chatting2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Chatting2.h"
#include "MFC_Chatting2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW


#endif
#pragma warning(disable:4996)


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


// CMFC_Chatting2Dlg ��ȭ ����



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


// CMFC_Chatting2Dlg �޽��� ó����

BOOL CMFC_Chatting2Dlg::OnInitDialog()
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// ù ��° ���ڴ� � ������ ����� �� ���Ѵ�.
	// �������� �ּҵ� �� AF_INET �̶�� �ּ� ü�踦 ����ϰڴٴ� �ǹ�
	// stream : c++ ó�� �������� ����, ���ο� ��ġ�� �������� �� ��� �´� ����� ���
	// �����͸� ǥ��ȭ �ϴ� ���� ���� �ǹ�������, ������ �������� �帧�̶�� �����ϸ� �ȴ�.
	// �� ��° ���ڴ� ������ Ÿ���� ���ϴ� ���̴�. TCP(1:1), UDP(n:n) ��Ź���� �ִ�. 
	// SOCK_STREAM = TCP, SOCK_DGRAM : UDP
	// �� ��° ���ڴ� TCP���� UDP���� ����� �����Ѵ�. �׷��� �ش� ���������� ������ �Ǵµ�
	// 0 �̶� ������ �˾Ƽ� �ش� �������ÿ� ��Ī������.
	mh_socket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in srv_addr; // ��� ���� �ۼ�
	srv_addr.sin_family = AF_INET; // AF_INET �ּҸ� ����ϰڴٴ� �ǹ�
	srv_addr.sin_addr.s_addr = inet_addr("114.71.64.101"); // "�ش� �ּҿ���" ����ϰڴٴ� ������ �ǹ�
	srv_addr.sin_port = htons(2001); // ipconfig

	// link : ���������� �����ؾ� ���� �Ǵ� ��, �� ���� �ٸ� �� ��ü�� ����Ǿ�߸� ��� ����� �� ��
	// bind : ���� �ٸ� �� ��ü�� ������� �ʴ��� ���� �ٸ� ����� �ϸ� �� ��ü���� ����� ��
	bind(mh_socket, (LPSOCKADDR)&srv_addr, sizeof(struct sockaddr_in));

	// ������ �߽Ÿ� �� �� �ְԲ� �Ǿ� �ִ�.
	// �׷��� ���ŵ� �� �� �ְ� listen �Լ��� ���� �����ϰ� �Ѵ�. �� ��° ���ڴ� ����� ���̴�.
	listen(mh_socket, 1);
	


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_Chatting2Dlg::OnPaint()
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
HCURSOR CMFC_Chatting2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT CMFC_Chatting2Dlg::On25001(WPARAM wParam, LPARAM lParam)
{
	sockaddr_in client_addr;
	int sockaddr_in_size = sizeof(sockaddr_in);

	SOCKET h_socket = accept((SOCKET)wParam, (LPSOCKADDR)&client_addr, &sockaddr_in_size);

	// ���⼭���ʹ� ������ ���� ���
	if (m_user_count < MAX_USER_COUNT) {
		m_user_list[m_user_count].h_socket = h_socket;
		strcpy(m_user_list[m_user_count].ip_address, inet_ntoa(client_addr.sin_addr));
		// inet_ntoa�� ���ڸ� ���ڿ��� �ٲ��ִ� �Լ�

		// FD_READ : Ŭ���̾�Ʈ�� ������ �����ߴ�. 
		// FD_CLOSE : ������ ������.
		// ��ȭ���ڷ� 25002��°�� ����ϰڴٴ� ��
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

	// � �̺�Ʈ�� ���� ���õǾ� ���ڴ�.
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		// ������ ������ �����ߴ�.
	} else {
		// ������ �� ������.
		m_user_count--;

		if (m_user_count != i) { // ������ �������̶�� ��
			memcpy(&m_user_list[i], &m_user_list[m_user_count], sizeof(UserInfo));
		}
		closesocket((SOCKET)wParam);
	}

	return 0;
}
