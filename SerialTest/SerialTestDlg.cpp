// SerialTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"
#include ".\serialtestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

														// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSerialTestDlg ��ȭ ����



CSerialTestDlg::CSerialTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialTestDlg::IDD, pParent)
	, m_SendData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Comm = NULL;
}

void CSerialTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SendData);
	DDX_Control(pDX, IDC_RICHEDIT_RECEIVE, m_RData);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboCommport);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_comboBaudRate);
	DDX_Control(pDX, IDC_RICHEDIT_SEND, m_SData);
}

BEGIN_MESSAGE_MAP(CSerialTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnBnClickedButtonSend)
	ON_MESSAGE(WM_MYRECEIVE, OnReceive)
	ON_MESSAGE(WM_MYCLOSE, OnThreadClosed)
END_MESSAGE_MAP()


// CSerialTestDlg �޽��� ó����

BOOL CSerialTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.
	
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

									// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	//GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	m_comboCommport.AddString(_T("COM3"));
	m_comboCommport.AddString(_T("COM4"));
	m_comboCommport.SetCurSel(0);
	m_comboBaudRate.AddString(_T("300"));
	m_comboBaudRate.AddString(_T("600"));
	m_comboBaudRate.AddString(_T("1200"));
	m_comboBaudRate.AddString(_T("2400"));
	m_comboBaudRate.AddString(_T("4800"));
	m_comboBaudRate.AddString(_T("9600"));
	m_comboBaudRate.AddString(_T("14400"));
	m_comboBaudRate.AddString(_T("19200"));
	m_comboBaudRate.AddString(_T("28800"));
	m_comboBaudRate.AddString(_T("33600"));
	m_comboBaudRate.AddString(_T("38400"));
	m_comboBaudRate.AddString(_T("56000"));
	m_comboBaudRate.AddString(_T("115200"));
	m_comboBaudRate.AddString(_T("128000"));
	m_comboBaudRate.AddString(_T("256000"));
	m_comboBaudRate.AddString(_T("PCI_9600"));
	m_comboBaudRate.AddString(_T("PCI_19200"));
	m_comboBaudRate.AddString(_T("PCI_38400"));
	m_comboBaudRate.AddString(_T("PCI_57600"));
	m_comboBaudRate.AddString(_T("PCI_500k"));
	m_comboBaudRate.SetCurSel(0);

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CSerialTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSerialTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

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
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CSerialTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialTestDlg::OnBnClickedButtonConnect()
{
	this->m_comboCommport.GetLBText(this->m_comboCommport.GetCurSel(), m_strCommPort);
	this->m_comboBaudRate.GetLBText(this->m_comboBaudRate.GetCurSel(), m_strBaudRate);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Comm = new CPYH_Comm(_T("\\\\.\\") + m_strCommPort, m_strBaudRate, _T("None"), _T("8 Bit"), _T("1 Bit"));	// initial Comm port
	if (m_Comm->Create(GetSafeHwnd()) != 0)	//�����Ʈ�� ���� �������� �ڵ��� �ѱ��.
	{
		AfxMessageBox(_T("opened"));
		m_Comm->Clear();
	}
	else
		AfxMessageBox(_T("Can't Open CommPort"));
}

void CSerialTestDlg::OnBnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	str += "\r\n";
	m_Comm->Send(str, str.GetLength());
}

LRESULT CSerialTestDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o �ڵ��� �ݴ´�.
	((CPYH_Comm*)lpara)->HandleClose();
	delete ((CPYH_Comm*)lpara);

	return 0;
}

void CSerialTestDlg::InitRichEdit(void)
{
	m_RData.SetBackgroundColor(false, RGB(221, 220, 222));
	CHARFORMAT cf;
	m_RData.GetDefaultCharFormat(cf);
	cf.crTextColor = RGB(55, 55, 55);
	cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_SIZE;
	cf.dwEffects &= (~CFE_AUTOCOLOR);
	//cf.dwEffects |= CFE_BOLD;
	cf.yHeight = 160;
	m_RData.SetDefaultCharFormat(cf);
}

LRESULT CSerialTestDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str, temp;
	char data[20000] ;
	ZeroMemory(data, sizeof(char) * 20000);
	int nReceived = 0;
	static int nRecvCount = 0;
	if (m_Comm)
	{
		nReceived = m_Comm->Receive(data, length);
		
		for (int i = 0; i<(int)length; i++)
		{
			temp = data[i];
			str += temp;
		}
		m_RData.ReplaceSel(str + _T("\n"));
	}
	return 0;
}