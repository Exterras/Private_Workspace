
// MFC_Notepad1Dlg.h : ��� ����
//

#pragma once


// CMFC_Notepad1Dlg ��ȭ ����
class CMFC_Notepad1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_Notepad1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_NOTEPAD1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
