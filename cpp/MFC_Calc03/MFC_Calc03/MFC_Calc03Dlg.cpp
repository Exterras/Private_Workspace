
// MFC_Calc03Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Calc03.h"
#include "MFC_Calc03Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Calc03Dlg 대화 상자



CMFC_Calc03Dlg::CMFC_Calc03Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CALC03_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Calc03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// 컴포넌트의 이벤트를 처리해주는 부분
BEGIN_MESSAGE_MAP(CMFC_Calc03Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLUS, &CMFC_Calc03Dlg::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_SUB, &CMFC_Calc03Dlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_MUL, &CMFC_Calc03Dlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_DIV, &CMFC_Calc03Dlg::OnBnClickedDiv)
	ON_BN_CLICKED(IDC_EQUAL, &CMFC_Calc03Dlg::OnBnClickedEqual)

	ON_BN_CLICKED(IDC_BACK, &CMFC_Calc03Dlg::OnBnClickedBack)
	ON_BN_CLICKED(IDC_CLR, &CMFC_Calc03Dlg::OnBnClickedClr)
	ON_BN_CLICKED(IDC_DOT, &CMFC_Calc03Dlg::OnBnClickedDot)
END_MESSAGE_MAP()


// CMFC_Calc03Dlg 메시지 처리기

BOOL CMFC_Calc03Dlg::OnInitDialog()
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

void CMFC_Calc03Dlg::OnPaint()
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
HCURSOR CMFC_Calc03Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// OnCommand : 클래스가 메시지를 받았을 때의 동작을 정하는 함수입니다.
BOOL CMFC_Calc03Dlg::OnCommand(WPARAM _wParam, LPARAM _lParam) {
	// resource.h 를 참고하여 IDC_NUM0에서 IDC_NUM9 사이의 값을 누른다면 
	// 아래 내용과 같은 이벤트 처리를 하여라
	if (IDC_NUM0 <= _wParam && IDC_NUM9 >= _wParam) {
		
		// 첫번째 숫자와 두번째 숫자를 저장할 변수를 만드는 작업
		CString num_str, str1, str2;

		// (입력받은 컴포넌트의 resource) - (컴포넌트 '0'의 resource) = 해당 문자열의 값
		num_str.Format(L"%d", _wParam - IDC_NUM0);
		
		// 클리어 버튼을 누르지 않았다면 첫번째 입력된 값을 str2에 집어넣는다.
		if (clr_flag == 0) {
			GetDlgItemText(IDC_EDIT1, str2);
		}
		// 그러나 클리어 버튼을 누른 상태에서 다시 해당 숫자 컴포넌트를 입력하였다면
		// str1에 집어넣는다.
		else if (clr_flag == 1) {
			GetDlgItemText(IDC_EDIT1, str1);
			first_value = _wtof(str1); // 문자열을 숫자로 변환하여 fv에 저장
			clr_flag = 0; // 클리어 여부 초기화
		}

		// 버튼을 누를때마다 입력부분에 오른쪽으로 추가한다.
		SetDlgItemText(IDC_EDIT1, str2 + num_str);
	}
	return CDialogEx::OnCommand(_wParam, _lParam);
}
// 첫번째 숫자를 누른 후 점, +, -, *, / 버튼입력에 대한 이벤트처리
void CMFC_Calc03Dlg::OnBnClickedDot() {
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	SetDlgItemText(IDC_EDIT1, str + '.');
}
void CMFC_Calc03Dlg::OnBnClickedPlus(){
	calc_oper = 1;
	clr_flag = 1;
}
void CMFC_Calc03Dlg::OnBnClickedSub() {
	calc_oper = 2;
	clr_flag = 1;
}
void CMFC_Calc03Dlg::OnBnClickedMul() {
	calc_oper = 3;
	clr_flag = 1;
}
void CMFC_Calc03Dlg::OnBnClickedDiv() {
	calc_oper = 4;
	clr_flag = 1;
}

// 두번째 숫자를 누른 후 = 버튼입력에 대한 이벤트처리
void CMFC_Calc03Dlg::OnBnClickedEqual() {
	CString str;
	double second_value;
	GetDlgItemText(IDC_EDIT1, str);
	second_value = _wtof(str);

	switch (calc_oper) {
	case 1:
		first_value += second_value;
		clr_flag = 1;
		break;
	case 2:
		first_value -= second_value;
		clr_flag = 1;
		break;
	case 3:
		first_value *= second_value;
		clr_flag = 1;
		break;
	case 4:
		if (second_value != 0) {
			first_value /= second_value;
		} else {
			first_value = 0;
		}
		clr_flag = 1;
		break;
	}
	calc_oper = 0;
	str.Format(L"%f", first_value);
	str.TrimRight(L"0");
	str.TrimRight(L".");
	SetDlgItemText(IDC_EDIT1, str);
}

// Back, C 버튼입력에 대한 이벤트처리
void CMFC_Calc03Dlg::OnBnClickedBack() {
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	str.Delete(str.GetLength() - 1, 1);
	SetDlgItemText(IDC_EDIT1, str);
}
void CMFC_Calc03Dlg::OnBnClickedClr() {
	SetDlgItemInt(IDC_EDIT1, 0);
	clr_flag = 1;
	calc_oper = 0;
}

