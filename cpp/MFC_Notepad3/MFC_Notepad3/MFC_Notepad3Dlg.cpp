
// MFC_Notepad3Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Notepad3.h"
#include "MFC_Notepad3Dlg.h"
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


// CMFC_Notepad3Dlg 대화 상자



CMFC_Notepad3Dlg::CMFC_Notepad3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_NOTEPAD3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Notepad3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_strName);
}

BEGIN_MESSAGE_MAP(CMFC_Notepad3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPEN, &CMFC_Notepad3Dlg::OnOpen)
	ON_COMMAND(ID_SAVE, &CMFC_Notepad3Dlg::OnSave)
	ON_COMMAND(ID_PRINT, &CMFC_Notepad3Dlg::OnPrint)
	ON_COMMAND(ID_QUIT, &CMFC_Notepad3Dlg::OnQuit)
END_MESSAGE_MAP()


// CMFC_Notepad3Dlg 메시지 처리기

BOOL CMFC_Notepad3Dlg::OnInitDialog()
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
	
	// 제목 변경
	SetWindowText(_T("20165240_최태일_메모장"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFC_Notepad3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_Notepad3Dlg::OnPaint()
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
HCURSOR CMFC_Notepad3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Notepad3Dlg::OnOpen()
{
	CStdioFile f; // 텍스트 속성의 파일을 손쉽게 처리할수 있도록 제공되는 클래스입니다.
	CString display_str, str; // 텍스트를 출력할 변수
	
	// 파일 지정자 및 파일 열기 대화상자 
	TCHAR fileFilter[] = _T("텍스트 파일(*.txt)");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, fileFilter);

	// 다이얼로그 종료시 반환되는 값을 검사
	if (dlg.DoModal() == IDOK)
	{
		if (f.Open(dlg.GetPathName(), CFile::modeRead | CFile::typeText))
		{
			// 정상적으로 읽어짐.

			// 파일을 String 타입으로 읽어서 display_str에 저장 
			while (f.ReadString(str)) {
				display_str += str;
			}

			// display_str을 IDC_EDIT1에 표시하기
			SetDlgItemText(IDC_EDIT1, display_str);
			f.Close(); // 파일 닫기
		}
	}
}


void CMFC_Notepad3Dlg::OnSave()
{
	CString str;
	CStdioFile file;
	CFileException ex;
	TCHAR fileExt[] = _T(".txt");
	TCHAR fileFilter[] = _T("텍스트 파일(*.txt)");
	CFileDialog dlg(FALSE, fileExt, NULL, OFN_HIDEREADONLY, fileFilter);
	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite, &ex);
	
		GetDlgItemText(IDC_EDIT1, str); // IDC_EDIT1의 내용을 str로 저장
		file.WriteString(str); // str의 내용을 텍스트 클래스로 쓰기
		
		UpdateData(TRUE); // 업데이트
		file.Close();
	}
}


void CMFC_Notepad3Dlg::OnPrint()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFC_Notepad3Dlg::OnQuit()
{
	OnOK();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
