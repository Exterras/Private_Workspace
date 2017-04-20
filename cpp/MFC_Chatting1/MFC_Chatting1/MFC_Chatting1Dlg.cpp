
// MFC_Chatting1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Chatting1.h"
#include "MFC_Chatting1Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_Chatting1Dlg ��ȭ ����


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
	// �� ��ȭ ���ڿ� ���� �ڵ�ȭ ���Ͻð� ���� ��� �� ��ȭ ���ڿ� ����
	//  �Ĺ� �����͸� NULL�� �����Ͽ�
	//  ��ȭ ���ڰ� �����Ǿ����� �� �� �ְ� �մϴ�.
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


// CMFC_Chatting1Dlg �޽��� ó����

BOOL CMFC_Chatting1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	//AF_INET : ���ͳ� �⺻ TCP �ּ�, 0�� 2��° ���� ������ �ڵ����� ���������� ��������
	sockaddr_in srv_addr;
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("114.71.64.101");//ip�� �Ҵ�� ip�� ������: cmd->ipconfig
	srv_addr.sin_port = htons(18000);//htonl=host byte order to network order, s=unsigned short int

	bind(mh_listen_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	//������ ��Ʈ��ũ ī�忡 ����
	AddEventString("���񽺸� �����մϴ�.");//����Ʈ�ڽ��� ���
	listen(mh_listen_socket, 1);
	//�� �� ���� �����ų�(���ÿ� ó���ϴ� ���� �ƴ�,)������ ������� ������ ������ ����� ������ ������ ����

	WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);//�񵿱��Լ�
															   //accept�� ����ϸ� ���� ����ڰ� ������ ������ ���α׷��� ������¿� ������ ����������
															   //h_socket���� FD_ACCEPT �̺�Ʈ�� �߻��ϸ� 25001�޼����� �� ��ȭ���ڿ� ������� ��->������� ���¿� ����������

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.

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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_Chatting1Dlg::OnPaint()
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
HCURSOR CMFC_Chatting1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��Ʈ�ѷ����� �ش� ��ü �� �ϳ��� ��� ����ϰ� ���� ���
//  ����ڰ� UI�� ���� �� �ڵ�ȭ ������ �����ϸ� �� �˴ϴ�.  �̵�
//  �޽��� ó����� ���Ͻð� ���� ��� ���� ��� UI�� ��������,
//  UI�� ǥ�õ��� �ʾƵ� ��ȭ ���ڴ�
//  ���� �Ӵϴ�.

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
	// ���Ͻ� ��ü�� ��� ���� ������ �ڵ�ȭ ��Ʈ�ѷ�������
	//  �� ���� ���α׷��� ��� ����մϴ�.  ��ȭ ���ڴ� ���� ������
	//  �ش� UI�� ����ϴ�.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CMFC_Chatting1Dlg::AddEventString(const char *ap_string)
{
	//����Ʈ �ڽ��� ���� ��� �� Ŀ�� �ڵ��̵��ϴ� �Լ�
	while (m_event_list.GetCount() > 3000) {
		m_event_list.DeleteString(0);
	}
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index);
}


afx_msg LRESULT CMFC_Chatting1Dlg::On25001(WPARAM wParam, LPARAM lParam)
{
	//wParam -> �̺�Ʈ�� �߻��� ������ �ڵ��� �Ѿ��, lParam�� ���Ͽ� �߻��� �޼����� ��FD_ACCEPT 
	sockaddr_in client_addr;
	int sockaddr_in_size = sizeof(sockaddr_in);
	SOCKET h_socket = accept(mh_listen_socket, (LPSOCKADDR)&client_addr, &sockaddr_in_size);
	//���� �ڸ��� wParam�� ��� ��
	//2�� ° ���ڴ� �����ϴ� client�� ip�� �� �� �ְ��ϴ� ����(�߽��� ǥ��)
	//h_socket�� Ŭ�� ��������, listen ������ ������. listen ������ �������ʰ� accept ���ϸ� ����

	int i;//for�� �ۿ����� i�� ����ϱ� ���ؼ�
	for (i = 0; i < MAX_USER_COUNT; i++) {//����ִ� ������ ã�´�
		if (m_user_list[i].h_socket == INVALID_SOCKET)break;
	}

	if (i < MAX_USER_COUNT) {//�� ���� �ִ� ����
		m_user_list[i].h_socket = h_socket;//�ش� ������ ����
		strcpy(m_user_list[i].ip_address, inet_ntoa(client_addr.sin_addr));
		//client address ����
		WSAAsyncSelect(m_user_list[i].h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		//FD_WRITE�� �������� ������ ������ �� �޼������� �񵿱⸦ ���� ����-> ������ ������ ������ �˱� ����
		//FD_READ ������� �����͸� ���� �� �߻��Ǵ� �޼���
		//FD_CLOSE ������� ���� ��
		// | ��Ʈ �����ڸ� ����ؾ���, or�� �ϸ� ��������Ʈ �Ǽ� �������� ���� �޼����� �ްԵ�
		CString str;
		str.Format("%s���� �����߽��ϴ�.", m_user_list[i].ip_address);

	}
	else {//�� �� ����
		AddEventString("���� �ִ� �ο� �ʰ�!\n");
		closesocket(h_socket);//accept�� ���� Ŭ����->�ʿ䰡 �����Ƿ�
							  //������ client �ٽ� ���� �õ�, -> ����,, �Ǽ�ȯ �ݺ� ���� ���� ������ ������ �ƿ� ������.
	}
	return 0;
}


afx_msg LRESULT CMFC_Chatting1Dlg::On25002(WPARAM wParam, LPARAM lParam)
{
	//lParam���� FD_READ or FD_CLOSE �� ������ �������.
	//wParam�� socket�� ���� unsigned int��
	CString str;
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);
		//�񵿱⿡�� FD_READ�� ���ܽ�Ŵ(�����Ͱ� ���ܼ� ������ ��� �ߺ����� �����ʵ���)
		//FD_CLOSE�� �츰 ������ ���ڱ� ������ ���� ��쿡 ó���� �� �ֵ���        
		char key;
		recv(wParam, &key, 1, 0);
		if (key == 27) {//�ڽ��� Ŭ���̾�Ʈ���� ���� ���� Ȯ��
			char message_id;
			recv(wParam, &message_id, 1, 0);

			unsigned short body_size;
			recv(wParam, (char *)&body_size, 2, 0);
			char* p_body_data = NULL;
			if (body_size > 0) {//0���� ū ������� �����Ͱ� ��������츸        
				p_body_data = new char[body_size];
				int total = 0, x, retry = 0;
				while (total < body_size) {//recv�� ������ ����� �°� content�� ����
					x = recv(wParam, p_body_data + total, body_size - total, 0);
					if (x == SOCKET_ERROR)break;
					total = total + x;
					if (total < body_size) {
						Sleep(50);//(5�и� ������ ��)
						retry++;
						if (retry > 5)break;//��õ� 5�� ������ break
					}
				}
			}
			if (p_body_data != NULL)delete[] p_body_data;
			WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}
	else {//FD_CLOSE
		  //����
	}
	return 0;
}

// ����
// ����ü ���������� �𸣹Ƿ� ���� ���α׷����� �׳� �Ѿ��
