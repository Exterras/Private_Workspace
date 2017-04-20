
// MFC_Calc03Dlg.h : 헤더 파일
//

#pragma once


// CMFC_Calc03Dlg 대화 상자
class CMFC_Calc03Dlg : public CDialogEx
{
private:
	char calc_oper = 0; // 1: plus, 2: sub, 3: mul, 4: div
	char clr_flag = 0; // 1: clear and new write 
	double first_value = 0; // save input value in edit control
// 생성입니다.
public:
	CMFC_Calc03Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CALC03_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnCommand(WPARAM _wParam, LPARAM _lParam);

	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedSub();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedEqual();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedClr();
	afx_msg void OnBnClickedDot();
};


