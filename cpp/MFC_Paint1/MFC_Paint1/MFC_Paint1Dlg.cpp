
// MFC_Paint1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Paint1.h"
#include "MFC_Paint1Dlg.h"
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
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_Paint1Dlg ��ȭ ����



CMFC_Paint1Dlg::CMFC_Paint1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_PAINT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Paint1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_Paint1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFC_Paint1Dlg �޽��� ó����

BOOL CMFC_Paint1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ���� ������ �־�� �մϴ�.
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

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_Paint1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_Paint1Dlg::OnPaint()
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
HCURSOR CMFC_Paint1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���� ��ư�� ������ �� ����� �̺�Ʈ�� ó���ϴ� �Լ�
// OnLButtonDown(���콺�� Ŭ���Ǿ��� �� ����Ű�� �ִ����� ���� ����, Ŭ���� ��ġ�� ��ǥ��)
void CMFC_Paint1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// �����쿡�� �׸��� �׸��� ���ؼ��� �ش� DC�� ���;��մϴ�.
	// ������ ���α׷����� ��� �ڵ鰪�� �̿��ϱ� ������ 
	// HDC�� ������ �ϳ� �������ص� DC�� �ڵ鰪�� �޾ƿɴϴ�(GetDC).
	// ������ Ŭ������ �ڱⰡ �����ϴ� �������� �ڵ��� ��������� ������ �ִµ� 
	// m_hWnd�� �ٷ� �װ��Դϴ�.
	// ::�Լ� = API, �Լ� = MFC

	int shape_distance = 15; int sd = shape_distance; 

	/* HDC h_dc = ::GetDC(m_hWnd);
	Rectangle(h_dc, point.x - sd, point.y - sd, point.x + sd, point.y + sd);
	::ReleaseDC(m_hWnd, h_dc); */

	// ���� ��ư�� ��Ʈ�� Ű�� ������ �� �簢���� �ƴ� ���� ������ �ϰ� �ʹٸ� 
	// CClientDC�� ���� DC�� ���ɴϴ�. 
	// �ڱⰡ ���� �������� �ּҸ� �־�����ϱ� ������ �ڱ������������� this�� ���ݴϴ�.
	// �׸��� wParam�� �ش��ϴ� ���� nFlags�� ���� ��Ʈ�� Ű�� ���������� ���� �ڵ带 �ۼ��մϴ�.
	
	CClientDC dc(this);
	if (nFlags & MK_CONTROL) dc.Ellipse(point.x - sd, point.y - sd, point.x + sd, point.y + sd);
	else dc.Rectangle(point.x - sd, point.y - sd, point.x + sd, point.y + sd);	
}