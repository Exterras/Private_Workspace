
// MFC_Paint2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Paint2.h"
#include "MFC_Paint2Dlg.h"
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


// CMFC_Paint2Dlg ��ȭ ����



CMFC_Paint2Dlg::CMFC_Paint2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_PAINT2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nSX = 0;
	nSY = 0;
}

void CMFC_Paint2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_Paint2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_ERASE, &CMFC_Paint2Dlg::OnBnClickedErase)
END_MESSAGE_MAP()


// CMFC_Paint2Dlg �޽��� ó����

BOOL CMFC_Paint2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	flag = 0; // �ʱⰪ : ���콺�� ������ ���� ����

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

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_Paint2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_Paint2Dlg::OnPaint()
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
HCURSOR CMFC_Paint2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Paint2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	nSX = point.x; // x ��ǥ���� nSX�� �Է�
	nSY = point.y; // y ��ǥ���� nSX�� �Է�
	flag = 1; // ���� ���콺��ư�� ������ ���¸� 1�� �Ѵ�.
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFC_Paint2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	flag = 0; // ���� ���콺��ư�� ������ ���¸� 0���� �Ѵ�.
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFC_Paint2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen;
	int color[3] = {0, 0, 255}; // blue

	pen.CreatePen(PS_SOLID, 3, RGB(color[0], color[1], color[2]));
	dc.SelectObject(&pen);

	if (flag == 1) { // ���콺 ���� ��ư�� ������ ��쿡�� ����
		dc.MoveTo(nSX, nSY); // ���콺 ���� ��ư�� ������ ��ġ�� �̵�
		dc.LineTo(point.x, point.y); // ���� �̵��� ������ ���� �ߴ´�.

		nSX = point.x;
		nSY = point.y; // ���� �̵��� ��ġ�� ��ǥ�� ������ �ִ´�.
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}

// ����� ��ư
void CMFC_Paint2Dlg::OnBnClickedErase()
{
	InvalidateRect(NULL, TRUE); // �����츦 ����� �����Ѵ�.
	UpdateWindow();
}
