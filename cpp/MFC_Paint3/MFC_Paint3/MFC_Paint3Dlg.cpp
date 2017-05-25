
// MFC_Paint3Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Paint3.h"
#include "MFC_Paint3Dlg.h"
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


// CMFC_Paint3Dlg ��ȭ ����



CMFC_Paint3Dlg::CMFC_Paint3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_PAINT3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nSX = 0;
	//  xSY = 0;
	nSY = 0;
	nRed = 0;
	nGreen = 0;
	nBlue = 0;
	nWidth = 0;
	toolFlag = 0;
}

void CMFC_Paint3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINESLIDER, m_sliderCtrl);
}

BEGIN_MESSAGE_MAP(CMFC_Paint3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_ERASE, &CMFC_Paint3Dlg::OnBnClickedErase)
	ON_BN_CLICKED(IDC_EXIT, &CMFC_Paint3Dlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_RED, &CMFC_Paint3Dlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_GREEN, &CMFC_Paint3Dlg::OnBnClickedGreen)
	ON_BN_CLICKED(IDC_BLUE, &CMFC_Paint3Dlg::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_WID3, &CMFC_Paint3Dlg::OnBnClickedWid3)
	ON_BN_CLICKED(IDC_WID10, &CMFC_Paint3Dlg::OnBnClickedWid10)
	ON_BN_CLICKED(IDC_DEFAULT, &CMFC_Paint3Dlg::OnBnClickedDefault)
	ON_BN_CLICKED(IDC_WID1, &CMFC_Paint3Dlg::OnBnClickedWid1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RECT, &CMFC_Paint3Dlg::OnBnClickedRect)
	ON_BN_CLICKED(IDC_LINE, &CMFC_Paint3Dlg::OnBnClickedLine)
	ON_BN_CLICKED(IDC_CIRCLE, &CMFC_Paint3Dlg::OnBnClickedCircle)
	ON_BN_CLICKED(IDC_COLORPIC, &CMFC_Paint3Dlg::OnBnClickedColorpic)
END_MESSAGE_MAP()


// CMFC_Paint3Dlg �޽��� ó����

BOOL CMFC_Paint3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	flag = 0; // ���콺��ư �ʱⰪ (������ ���� ����)

	// �ʱⰪ : ������
	nRed = 0;
	nGreen = 0;
	nBlue = 0;

	// �ʱ� �� ����
	nWidth = 1;

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

	// �����̴� �ʱ�ȭ
	m_sliderCtrl.SetRange(0, 100, TRUE); // ����
	m_sliderCtrl.SetTicFreq(10); // ������
	m_sliderCtrl.SetPos(0); // ���� �����̴� �ʱ�ȭ

	// m_strSliderVal.Format(_T("%d"), 0); �����̴� Ȯ������

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_Paint3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_Paint3Dlg::OnPaint()
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
HCURSOR CMFC_Paint3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Paint3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	nSX = point.x; // x ��ǥ���� nSX�� �Է�
	nSY = point.y; // y ��ǥ���� nSX�� �Է�
	flag = 1; // ���� ���콺��ư�� ������ ���¸� 1�� �Ѵ�.

	if (toolFlag == 0) {
		CDialogEx::OnLButtonDown(nFlags, point);
	}
}


void CMFC_Paint3Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen;
	
	int initShapeNum = 30;
	// PS_SOLID : �Ǽ�, DASH: ���ļ�, DOT: ª�� �ļ�, NULL: ����
	pen.CreatePen(PS_SOLID, nWidth, RGB(nRed, nGreen, nBlue));
	dc.SelectObject(&pen);

	// ���콺 �巡�� �� Ŭ������ ���� ������ ��� ������ �׸��� ���
	if (toolFlag == 1) {
		dc.Ellipse(nSX, nSY, point.x + initShapeNum, point.y + initShapeNum);
	} else if (toolFlag == 2) {
		dc.Rectangle(nSX, nSY, point.x + initShapeNum, point.y + initShapeNum);
	}
	
	flag = 0; // ���� ���콺��ư�� ������ ���¸� 0���� �Ѵ�.
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFC_Paint3Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen;

	// PS_SOLID : �Ǽ�, DASH: ���ļ�, DOT: ª�� �ļ�, NULL: ����
	pen.CreatePen(PS_SOLID, nWidth, RGB(nRed, nGreen, nBlue));
	dc.SelectObject(&pen);
	if (toolFlag == 0) { // LINE ��ư�� ������ ��
		if (flag == 1) { // ���콺 ���� ��ư�� ������ ��쿡�� ����
			dc.MoveTo(nSX, nSY); // ���콺 ���� ��ư�� ������ ��ġ�� �̵�
			dc.LineTo(point.x, point.y); // ���� �̵��� ������ ���� �ߴ´�.

			nSX = point.x;
			nSY = point.y; // ���� �̵��� ��ġ�� ��ǥ�� ������ �ִ´�.
			
		}
	} else if (toolFlag == 1) { // CIRCLE ��ư�� ������ ��
		if (flag == 1) {
			dc.MoveTo(nSX, nSY); // ���콺 ���� ��ư�� ������ ��ġ�� �̵�
		}
	} else if (toolFlag == 2) { // RECTANGLE ��ư�� ������ ��
		if (flag == 1) {
			dc.MoveTo(nSX, nSY); // ���콺 ���� ��ư�� ������ ��ġ�� �̵�
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFC_Paint3Dlg::OnBnClickedErase()
{
	InvalidateRect(NULL, TRUE); // �����츦 ����� �����Ѵ�.
	UpdateWindow();
}


void CMFC_Paint3Dlg::OnBnClickedExit()
{
	OnOK(); // ���̾�α� ���� ����
}

// ������ ��ư
void CMFC_Paint3Dlg::OnBnClickedRed()
{
	nRed = 255;
	nGreen = 0;
	nBlue = 0;
}

// �ʷϻ� ��ư
void CMFC_Paint3Dlg::OnBnClickedGreen()
{
	nRed = 0;
	nGreen = 255;
	nBlue = 0;
}

// �Ķ��� ��ư
void CMFC_Paint3Dlg::OnBnClickedBlue()
{
	nRed = 0;
	nGreen = 0;
	nBlue = 255;
}

// ������ 1
void CMFC_Paint3Dlg::OnBnClickedWid1()
{
	nWidth = 1;
}

// ������ 3
void CMFC_Paint3Dlg::OnBnClickedWid3()
{
	nWidth = 3;
}

// ������ 10
void CMFC_Paint3Dlg::OnBnClickedWid10()
{
	nWidth = 10;
}

// �ʱ�ȭ ��ư
void CMFC_Paint3Dlg::OnBnClickedDefault()
{
	nRed = 0;
	nGreen = 0;
	nBlue = 0;
	
	nWidth = 1;
}

// 20170320 �߰�����

// ������ �����̴�
void CMFC_Paint3Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar * )&m_sliderCtrl) {
		int value = m_sliderCtrl.GetPos(); // ���� �����̴��� ��ġ�� ������
		nWidth = value;

		// m_strSliderVal.Format(_T("%d"), value); 
		UpdateData(FALSE);
	} else {
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}
void CMFC_Paint3Dlg::OnBnClickedLine()
{
	toolFlag = 0;
}

void CMFC_Paint3Dlg::OnBnClickedCircle()
{
	toolFlag = 1;
}


void CMFC_Paint3Dlg::OnBnClickedRect()
{
	toolFlag = 2;
}

void CMFC_Paint3Dlg::OnBnClickedColorpic()
{
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		COLORREF color = colorDlg.GetColor();
		CString strTmp;
		
		nRed = GetRValue(color);
		nGreen = GetGValue(color);
		nBlue = GetBValue(color);
	}
}
