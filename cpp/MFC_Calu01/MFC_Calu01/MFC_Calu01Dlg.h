
// MFC_Calu01Dlg.h : 헤더 파일
//

#pragma once


// CMFC_Calu01Dlg 대화 상자
class CMFC_Calu01Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_Calu01Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CALU01_DIALOG };
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
private:
	afx_msg void OnBnClickedSum();
public:
	afx_msg void OnBnClickedEqual();
	afx_msg void OnBnClickedSub();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
};
