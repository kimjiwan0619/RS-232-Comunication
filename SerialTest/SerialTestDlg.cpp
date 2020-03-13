// SerialTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"
#include ".\serialtestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

														// 구현
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


// CSerialTestDlg 대화 상자



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
	ON_COMMAND(ID_SerialPort, &CSerialTestDlg::OnSerialPort)
	ON_COMMAND(ID_FileSend, &CSerialTestDlg::OnFilesend)
END_MESSAGE_MAP()


// CSerialTestDlg 메시지 처리기

BOOL CSerialTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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
	
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

									// TODO: 여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CSerialTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CSerialTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialTestDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// initial Comm port
	AfxMessageBox(m_strCommPort);
	m_Comm = new CPYH_Comm(_T("\\\\.\\") + m_strCommPort, m_strBaudRate, m_strParity, m_strType , m_strDataBit, m_strStopBit);
	if (m_Comm->Create(GetSafeHwnd()) != 0)	//통신포트를 열고 윈도우의 핸들을 넘긴다.
	{
		AfxMessageBox(_T("opened"));
		m_Comm->Clear();
	}
	else
		AfxMessageBox(_T("Can't Open CommPort"));
}

void CSerialTestDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str, type;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	//str += _T("\r\n");
	m_Comm->Send(str, str.GetLength(), type);
}

LRESULT CSerialTestDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o 핸들을 닫는다.
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
	if (m_Comm)
	{
		m_Comm->Receive(data, length);	
		for (int i = 0; i<(int)length; i++)
		{
			temp = data[i];
			str += temp;
		}
		m_RData.ReplaceSel(str + _T("\r\n"));
	}
	return 0;
}


void CSerialTestDlg::OnSerialPort()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	dlg.DoModal();
	m_strCommPort = dlg.m_strCommPort;
	m_strBaudRate = dlg.m_strBaudRate;
	m_strParity = dlg.m_strParity;
	m_strType = dlg.m_strType;
	m_strDataBit = dlg.m_strDataBit;
	m_strStopBit = dlg.m_strStopBit;
	m_strFlowChk = dlg.m_strFlowChk;
	//dlg.DestroyWindow();
}


void CSerialTestDlg::OnFilesend()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CString strPathName;
	char szFilter[] = "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
		strPathName = dlg.GetPathName();

	// 경로를 가져와 사용할 경우, Edit Control 에 값 저장
	CString str;
	str.Format(_T("%s"), strPathName);
	SetDlgItemText(IDC_EDIT2, str);
}
