
// MFC_Paint2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Paint2.h"
#include "MFC_Paint2Dlg.h"
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
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_Paint2Dlg 대화 상자



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


// CMFC_Paint2Dlg 메시지 처리기

BOOL CMFC_Paint2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	flag = 0; // 초기값 : 마우스를 누르지 않은 상태

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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_Paint2Dlg::OnPaint()
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
HCURSOR CMFC_Paint2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Paint2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	nSX = point.x; // x 좌표값을 nSX에 입력
	nSY = point.y; // y 좌표값을 nSX에 입력
	flag = 1; // 좌측 마우스버튼이 눌려진 상태를 1로 한다.
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFC_Paint2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	flag = 0; // 좌측 마우스버튼이 눌려진 상태를 0으로 한다.
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFC_Paint2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen;
	int color[3] = {0, 0, 255}; // blue

	pen.CreatePen(PS_SOLID, 3, RGB(color[0], color[1], color[2]));
	dc.SelectObject(&pen);

	if (flag == 1) { // 마우스 좌측 버튼이 눌러진 경우에만 실행
		dc.MoveTo(nSX, nSY); // 마우스 좌측 버튼이 눌려진 위치로 이동
		dc.LineTo(point.x, point.y); // 새로 이동한 곳까지 선을 긋는다.

		nSX = point.x;
		nSY = point.y; // 새로 이동한 위치의 좌표를 변수에 넣는다.
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}

// 지우기 버튼
void CMFC_Paint2Dlg::OnBnClickedErase()
{
	InvalidateRect(NULL, TRUE); // 윈도우를 지우고 갱신한다.
	UpdateWindow();
}
