
// MFC_Notepad3Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Notepad3.h"
#include "MFC_Notepad3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMFC_Notepad3Dlg ��ȭ ����



CMFC_Notepad3Dlg::CMFC_Notepad3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_NOTEPAD3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Notepad3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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


// CMFC_Notepad3Dlg �޽��� ó����

BOOL CMFC_Notepad3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_Notepad3Dlg::OnPaint()
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
HCURSOR CMFC_Notepad3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Notepad3Dlg::OnOpen()
{
	CStdioFile f;
	CString tmpTxt, strTxt;

	TCHAR fileFilter[] = _T("�ؽ�Ʈ ����(*.txt)");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, fileFilter);

	if (dlg.DoModal() == IDOK)
	{
		if (f.Open(dlg.GetPathName(), CFile::modeRead | CFile::typeText))
		{
			// ���������� �о���.
			while (f.ReadString(tmpTxt)) strTxt += tmpTxt;
			AfxMessageBox(strTxt);
			f.Close(); // ���� �ݱ�
		}
	}
}


void CMFC_Notepad3Dlg::OnSave()
{
	/*
	CString strMsg;
	TCHAR fileFilter[] = _T("�ؽ�Ʈ ����(*.txt)");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, fileFilter);

	if (dlg.DoModal() == IDOK)
	{
		strMsg.Format(_T("�����̸�:%s\n����Ȯ����:%s\n����Ÿ��Ʋ:%s\n���ϰ��:%s"),
			dlg.GetFileName(), dlg.GetFileExt(),
			dlg.GetFileTitle(), dlg.GetFolderPath());

		AfxMessageBox(strMsg);
	}
	*/

	
	CStdioFile file;
	CFileException ex;
	TCHAR fileExt[] = _T(".txt");
	TCHAR fileFilter[] = _T("�ؽ�Ʈ ����(*.txt)");
	CFileDialog dlg(FALSE, fileExt, NULL, OFN_HIDEREADONLY, fileFilter);
	if (dlg.DoModal() == IDOK)
	{
		// �Է� ��Ʈ�ѿ� ������ �ִ� ������ ��� �ҷ�������?
		file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite, &ex);
		UpdateData(TRUE);
		file.Close();
	}
	
}


void CMFC_Notepad3Dlg::OnPrint()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMFC_Notepad3Dlg::OnQuit()
{
	OnOK();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
