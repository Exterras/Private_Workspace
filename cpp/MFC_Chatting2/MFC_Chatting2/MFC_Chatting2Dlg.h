
// MFC_Chatting2Dlg.h : ��� ����
//

#pragma once
#define MAX_USER_COUNT 100

struct UserInfo
{	
	SOCKET h_socket;
	char ip_address[16];
};

// CMFC_Chatting2Dlg ��ȭ ����
class CMFC_Chatting2Dlg : public CDialogEx
{
private:
	// �������� ���α׷����� ���� �ڵ��� SOCKET�̶�� Ÿ������ �����Ѵ�.
	// �׸��� ���� Ÿ�Կ� ������ �����.
	// �� ������ Ŭ���̾�Ʈ ������ �޾��ִ� ������ ��.
	SOCKET mh_socket;

	UserInfo m_user_list[MAX_USER_COUNT]; // ����ڸ� �� 100������ �ް� �迭�� ������
	unsigned int m_user_count = 0; // ���� ����ϴ� ����� ��, 0���� �ʱ�ȭ, ����� ���� ������ �ȵ�

// �����Դϴ�.
public:
	CMFC_Chatting2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATTING2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
};
