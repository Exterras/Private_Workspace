
// MFC_Calc03Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Calc03.h"
#include "MFC_Calc03Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Calc03Dlg ��ȭ ����



CMFC_Calc03Dlg::CMFC_Calc03Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CALC03_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Calc03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// ������Ʈ�� �̺�Ʈ�� ó�����ִ� �κ�
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


// CMFC_Calc03Dlg �޽��� ó����

BOOL CMFC_Calc03Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_Calc03Dlg::OnPaint()
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
HCURSOR CMFC_Calc03Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// OnCommand : Ŭ������ �޽����� �޾��� ���� ������ ���ϴ� �Լ��Դϴ�.
BOOL CMFC_Calc03Dlg::OnCommand(WPARAM _wParam, LPARAM _lParam) {
	// resource.h �� �����Ͽ� IDC_NUM0���� IDC_NUM9 ������ ���� �����ٸ� 
	// �Ʒ� ����� ���� �̺�Ʈ ó���� �Ͽ���
	if (IDC_NUM0 <= _wParam && IDC_NUM9 >= _wParam) {
		
		// ù��° ���ڿ� �ι�° ���ڸ� ������ ������ ����� �۾�
		CString num_str, str1, str2;

		// (�Է¹��� ������Ʈ�� resource) - (������Ʈ '0'�� resource) = �ش� ���ڿ��� ��
		num_str.Format(L"%d", _wParam - IDC_NUM0);
		
		// Ŭ���� ��ư�� ������ �ʾҴٸ� ù��° �Էµ� ���� str2�� ����ִ´�.
		if (clr_flag == 0) {
			GetDlgItemText(IDC_EDIT1, str2);
		}
		// �׷��� Ŭ���� ��ư�� ���� ���¿��� �ٽ� �ش� ���� ������Ʈ�� �Է��Ͽ��ٸ�
		// str1�� ����ִ´�.
		else if (clr_flag == 1) {
			GetDlgItemText(IDC_EDIT1, str1);
			first_value = _wtof(str1); // ���ڿ��� ���ڷ� ��ȯ�Ͽ� fv�� ����
			clr_flag = 0; // Ŭ���� ���� �ʱ�ȭ
		}

		// ��ư�� ���������� �Էºκп� ���������� �߰��Ѵ�.
		SetDlgItemText(IDC_EDIT1, str2 + num_str);
	}
	return CDialogEx::OnCommand(_wParam, _lParam);
}
// ù��° ���ڸ� ���� �� ��, +, -, *, / ��ư�Է¿� ���� �̺�Ʈó��
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

// �ι�° ���ڸ� ���� �� = ��ư�Է¿� ���� �̺�Ʈó��
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

// Back, C ��ư�Է¿� ���� �̺�Ʈó��
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

