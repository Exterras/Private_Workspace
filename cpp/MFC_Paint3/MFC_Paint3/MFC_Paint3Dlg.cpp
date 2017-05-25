
// MFC_Paint3Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Paint3.h"
#include "MFC_Paint3Dlg.h"
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


// CMFC_Paint3Dlg 대화 상자



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


// CMFC_Paint3Dlg 메시지 처리기

BOOL CMFC_Paint3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	flag = 0; // 마우스버튼 초기값 (누르지 않은 상태)

	// 초기값 : 검정색
	nRed = 0;
	nGreen = 0;
	nBlue = 0;

	// 초기 선 굵기
	nWidth = 1;

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

	// 슬라이더 초기화
	m_sliderCtrl.SetRange(0, 100, TRUE); // 범위
	m_sliderCtrl.SetTicFreq(10); // 눈금자
	m_sliderCtrl.SetPos(0); // 현재 슬라이더 초기화

	// m_strSliderVal.Format(_T("%d"), 0); 슬라이더 확인포맷

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_Paint3Dlg::OnPaint()
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
HCURSOR CMFC_Paint3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Paint3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	nSX = point.x; // x 좌표값을 nSX에 입력
	nSY = point.y; // y 좌표값을 nSX에 입력
	flag = 1; // 좌측 마우스버튼이 눌려진 상태를 1로 한다.

	if (toolFlag == 0) {
		CDialogEx::OnLButtonDown(nFlags, point);
	}
}


void CMFC_Paint3Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen;
	
	int initShapeNum = 30;
	// PS_SOLID : 실선, DASH: 긴파선, DOT: 짧은 파선, NULL: 투명
	pen.CreatePen(PS_SOLID, nWidth, RGB(nRed, nGreen, nBlue));
	dc.SelectObject(&pen);

	// 마우스 드래그 후 클릭에서 손을 놓았을 경우 도형을 그리는 제어문
	if (toolFlag == 1) {
		dc.Ellipse(nSX, nSY, point.x + initShapeNum, point.y + initShapeNum);
	} else if (toolFlag == 2) {
		dc.Rectangle(nSX, nSY, point.x + initShapeNum, point.y + initShapeNum);
	}
	
	flag = 0; // 좌측 마우스버튼이 눌려진 상태를 0으로 한다.
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFC_Paint3Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen;

	// PS_SOLID : 실선, DASH: 긴파선, DOT: 짧은 파선, NULL: 투명
	pen.CreatePen(PS_SOLID, nWidth, RGB(nRed, nGreen, nBlue));
	dc.SelectObject(&pen);
	if (toolFlag == 0) { // LINE 버튼을 눌렀을 때
		if (flag == 1) { // 마우스 좌측 버튼이 눌러진 경우에만 실행
			dc.MoveTo(nSX, nSY); // 마우스 좌측 버튼이 눌려진 위치로 이동
			dc.LineTo(point.x, point.y); // 새로 이동한 곳까지 선을 긋는다.

			nSX = point.x;
			nSY = point.y; // 새로 이동한 위치의 좌표를 변수에 넣는다.
			
		}
	} else if (toolFlag == 1) { // CIRCLE 버튼을 눌렀을 때
		if (flag == 1) {
			dc.MoveTo(nSX, nSY); // 마우스 좌측 버튼이 눌려진 위치로 이동
		}
	} else if (toolFlag == 2) { // RECTANGLE 버튼을 눌렀을 때
		if (flag == 1) {
			dc.MoveTo(nSX, nSY); // 마우스 좌측 버튼이 눌려진 위치로 이동
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFC_Paint3Dlg::OnBnClickedErase()
{
	InvalidateRect(NULL, TRUE); // 윈도우를 지우고 갱신한다.
	UpdateWindow();
}


void CMFC_Paint3Dlg::OnBnClickedExit()
{
	OnOK(); // 다이얼로그 상자 종료
}

// 빨강색 버튼
void CMFC_Paint3Dlg::OnBnClickedRed()
{
	nRed = 255;
	nGreen = 0;
	nBlue = 0;
}

// 초록색 버튼
void CMFC_Paint3Dlg::OnBnClickedGreen()
{
	nRed = 0;
	nGreen = 255;
	nBlue = 0;
}

// 파랑색 버튼
void CMFC_Paint3Dlg::OnBnClickedBlue()
{
	nRed = 0;
	nGreen = 0;
	nBlue = 255;
}

// 선굵기 1
void CMFC_Paint3Dlg::OnBnClickedWid1()
{
	nWidth = 1;
}

// 선굵기 3
void CMFC_Paint3Dlg::OnBnClickedWid3()
{
	nWidth = 3;
}

// 선굵기 10
void CMFC_Paint3Dlg::OnBnClickedWid10()
{
	nWidth = 10;
}

// 초기화 버튼
void CMFC_Paint3Dlg::OnBnClickedDefault()
{
	nRed = 0;
	nGreen = 0;
	nBlue = 0;
	
	nWidth = 1;
}

// 20170320 추가사항

// 선굵기 슬라이더
void CMFC_Paint3Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar * )&m_sliderCtrl) {
		int value = m_sliderCtrl.GetPos(); // 현재 슬라이더의 위치를 가져옴
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
