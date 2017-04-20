
// MFC_Paint1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Paint1.h"
#include "MFC_Paint1Dlg.h"
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


// CMFC_Paint1Dlg 대화 상자



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


// CMFC_Paint1Dlg 메시지 처리기

BOOL CMFC_Paint1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_Paint1Dlg::OnPaint()
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
HCURSOR CMFC_Paint1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 왼쪽 버튼을 눌렀을 때 생기는 이벤트를 처리하는 함수
// OnLButtonDown(마우스가 클릭되었을 때 조합키가 있는지에 대한 여부, 클릭된 위치의 좌표값)
void CMFC_Paint1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 윈도우에서 그림을 그리기 위해서는 해당 DC를 얻어와야합니다.
	// 윈도우 프로그래밍은 모두 핸들값을 이용하기 때문에 
	// HDC로 변수를 하나 선언해준뒤 DC의 핸들값을 받아옵니다(GetDC).
	// 윈도우 클래스는 자기가 관리하는 윈도우의 핸들을 멤버변수로 가지고 있는데 
	// m_hWnd가 바로 그것입니다.
	// ::함수 = API, 함수 = MFC

	int shape_distance = 15; int sd = shape_distance; 

	/* HDC h_dc = ::GetDC(m_hWnd);
	Rectangle(h_dc, point.x - sd, point.y - sd, point.x + sd, point.y + sd);
	::ReleaseDC(m_hWnd, h_dc); */

	// 왼쪽 버튼과 컨트롤 키를 눌렀을 때 사각형이 아닌 원을 나오게 하고 싶다면 
	// CClientDC를 통해 DC를 얻어옵니다. 
	// 자기가 만들 윈도우의 주소를 넣어줘야하기 때문에 자기참조포인터인 this를 써줍니다.
	// 그리고 wParam에 해당하는 값인 nFlags를 통해 컨트롤 키가 눌렸을때에 대한 코드를 작성합니다.
	
	CClientDC dc(this);
	if (nFlags & MK_CONTROL) dc.Ellipse(point.x - sd, point.y - sd, point.x + sd, point.y + sd);
	else dc.Rectangle(point.x - sd, point.y - sd, point.x + sd, point.y + sd);	
}
