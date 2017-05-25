
// MFC_Paint3Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"


// CMFC_Paint3Dlg 대화 상자
class CMFC_Paint3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_Paint3Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_PAINT3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int nSX;
//	int xSY;
	int nSY;
	bool flag;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedErase();
	afx_msg void OnBnClickedExit();
	int nRed;
	int nGreen;
	int nBlue;
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedGreen();
	afx_msg void OnBnClickedBlue();
	int nWidth;
	afx_msg void OnBnClickedWid3();
	afx_msg void OnBnClickedWid10();
	afx_msg void OnBnClickedDefault();
	afx_msg void OnBnClickedWid1();
	CSliderCtrl m_sliderCtrl;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int toolFlag;
	afx_msg void OnBnClickedRect();
	afx_msg void OnBnClickedLine();
	afx_msg void OnBnClickedCircle();
	afx_msg void OnBnClickedColorpic();
};
