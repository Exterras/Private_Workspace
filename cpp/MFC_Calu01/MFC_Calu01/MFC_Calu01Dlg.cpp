
// MFC_Calu01Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Calu01.h"
#include "MFC_Calu01Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Calu01Dlg 대화 상자



CMFC_Calu01Dlg::CMFC_Calu01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CALU01_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Calu01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_Calu01Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_Calu01Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_Calu01Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_Calu01Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFC_Calu01Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFC_Calu01Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFC_Calu01Dlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CMFC_Calu01Dlg 메시지 처리기

BOOL CMFC_Calu01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_Calu01Dlg::OnPaint()
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
HCURSOR CMFC_Calu01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 더하기
void CMFC_Calu01Dlg::OnBnClickedSum()
{
	int num1 = GetDlgItemInt(IDC_EDIT1);
	int num2 = GetDlgItemInt(IDC_EDIT2);
	SetDlgItemInt(IDC_EDIT, num1 + num2);

}

// 빼기
void CMFC_Calu01Dlg::OnBnClickedSub()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

// 등호
void CMFC_Calu01Dlg::OnBnClickedEqual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFC_Calu01Dlg::OnEnChangeEdit1()
{

}


void CMFC_Calu01Dlg::OnEnChangeEdit2()
{

}


void CMFC_Calu01Dlg::OnEnChangeEdit3()
{

}

