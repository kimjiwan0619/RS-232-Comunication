// SerialTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"
#include ".\serialtestdlg.h"
#include "MD5Checksum.h"
#include "MD5ChecksumDefines.h"

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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Comm = NULL;
}

void CSerialTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_RECEIVE, m_RData);
	DDX_Control(pDX, IDC_PROGRESS1, m_Pgrs_File);
}

BEGIN_MESSAGE_MAP(CSerialTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnBnClickedButtonConnect)
	ON_MESSAGE(WM_MYRECEIVE, OnReceive)
	ON_COMMAND(ID_SerialPort, &CSerialTestDlg::OnSerialPort)
	ON_COMMAND(ID_FileSend, &CSerialTestDlg::OnFilesend)
	ON_BN_CLICKED(IDC_BUTTON_SENDTEXT, &CSerialTestDlg::OnBnClickedButtonSendtext)
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, &CSerialTestDlg::OnBnClickedButtonSendfile)
	ON_BN_CLICKED(IDC_BUTTON_FILECHK, &CSerialTestDlg::OnBnClickedButtonFilechk)
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
enum
{

};
void CSerialTestDlg::OnBnClickedButtonConnect()
{
	char *key = NULL;
	key = new char[20];

	GetPrivateProfileString(_T("PORT_SETTING"), _T("CommPort"), _T("COM3"), key, 20, _T("C:/test2/PortSave.ini"));
	m_strCommPort = key;
	GetPrivateProfileString(_T("PORT_SETTING"), _T("BaudRate"), _T("115200"), key, 20, _T("C:/test2/PortSave.ini"));
	m_strBaudRate = key;
	GetPrivateProfileString(_T("PORT_SETTING"),_T("Parity"), _T("None"), key, 20, _T("C:/test2/PortSave.ini"));
	m_strParity = key;
	GetPrivateProfileString(_T("PORT_SETTING"), _T("DataBit"), _T("8 Bit"), key,20, _T("C:/test2/PortSave.ini"));
	m_strDataBit = key;
	GetPrivateProfileString(_T("PORT_SETTING"), _T("StopBit"), _T("1 Bit"), key, 20, _T("C:/test2/PortSave.ini"));
	m_strStopBit = key;
	delete[] key;

	m_Comm = new CPYH_Comm(_T("\\\\.\\") + m_strCommPort, m_strBaudRate, m_strParity, m_strDataBit, m_strStopBit, this);
	if (m_Comm->Create(GetSafeHwnd()) != 0)	//통신포트를 열고 윈도우의 핸들을 넘긴다.
	{
		AfxMessageBox(_T("Connected"));
		m_Comm->Clear();
	}
	else
		AfxMessageBox(_T("Can't Open CommPort"));
}

void CSerialTestDlg::InitRichEdit(void)
{
	m_RData.SetBackgroundColor(false, RGB(221, 220, 222));
	CHARFORMAT cf;
	m_RData.GetDefaultCharFormat(cf);
	cf.crTextColor = RGB(55, 55, 55);
	cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_SIZE;
	cf.dwEffects &= (~CFE_AUTOCOLOR);
	cf.yHeight = 160;
	m_RData.SetDefaultCharFormat(cf);
}

LRESULT CSerialTestDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	
	if (m_Comm)
	{
		if (nDataLength + 16 < 12800 && bChk != TRUE)
		{
			if (nRecvCount == 0)
			{
				int low = 0;
				if (m_nType == FILE)
				{
					int high = nDataLength;
					m_Pgrs_File.SetRange(low, high);
					m_Pgrs_File.SetPos(nRecvCount);
				}
			}
			m_Comm->Receive((char*)&byteRecvData[nRecvCount], length);
			_trace(_T("===========================================\r\n"));
			for (int j = 0; j < length; j++)
			{
				_trace(_T("%02X "), byteRecvData[j]);
				if( j % 20 == 0 )
					_trace(_T("\r\n"));
			}

			nRecvCount += length;
		}

		TRACE(_T("nRecvCount: %d\r\n"), nRecvCount);


		if (nRecvCount >= 12 && bChk != TRUE)
		{
			memcpy(&nTemp, byteRecvData, 4);
			UINT debug = 0x12345678;

			if (nTemp != 0x12345678) //sop chk
			{
				TRACE("sop not chk 0%08X\r\n", nTemp);
				nRecvCount = 0;
				nDataLength = 0;
				m_nType = 0;
				nTemp = 0;
				bChk = FALSE;
				return 0;
			}
			memcpy(&m_nType, byteRecvData + 4, 4); // type chk
			memcpy(&nDataLength, byteRecvData + 8, 4); // length chk
			TRACE("nDataLength : %d\r\n", nDataLength);
			bChk = TRUE;
			if (m_nType == MD5SEND)
			{
				if (nRecvCount >= nDataLength + 16)
				{
					CString checkSum;
					memcpy((unsigned char*)(LPCTSTR)checkSum, &byteRecvData[12], nDataLength);
					MD5RECEIVED(checkSum);
					reset();
				}
				else
				{
					m_pData = new char[nDataLength + 4];
					ZeroMemory(m_pData, nDataLength + 4);
					memcpy(m_pData, &byteRecvData[12], nRecvCount - 12);
				}
			}
			else if (m_nType == FILERECEIVED)
			{
				TRACE(_T("m_nType : FILERECEIVED\r\n"));
				MD5Send();
				reset();
			}
			else if (m_nType == SENDOK) // file 받는다 수락할때
			{
				OnBnClickedButtonSendfile();
				reset();
			}
			else if (m_nType == FILENAMESEND)  //  filename 넘기기
			{
				if (nRecvCount >= nDataLength + 16)
				{
					TRACE(_T("filename 한번에 다받음\r\n"));
					m_pData = new char[nDataLength + 4];
					ZeroMemory(m_pData, nDataLength + 4);
					m_FileName = new char[nDataLength+1];
					ZeroMemory(m_FileName, nDataLength + 1);
					memcpy(m_pData, &byteRecvData[12], nDataLength + 4);
					memcpy(&nTemp, m_pData + nDataLength, 4);
					memcpy(m_FileName, m_pData, nDataLength);
					if (nTemp == 0x87654321)
					{
						FileReceive(m_FileName, nDataLength);
						reset();
					}
				}
				else
				{
					m_pData = new char[nDataLength + 4];
					ZeroMemory(m_pData, nDataLength + 4);
					memcpy(m_pData, &byteRecvData[12], nRecvCount - 12);
				}
			}
			else if (m_nType == TEXT) // text
			{
				if (nRecvCount >= nDataLength + 16) //text 한번에 다받았을때
				{
					m_pData = new char[nDataLength + 4];
					ZeroMemory(m_pData, nDataLength + 4);
					memcpy(m_pData, &byteRecvData[12], nDataLength + 4);
					memcpy(&nTemp, &m_pData[nDataLength], 4);
					if (nTemp == 0x87654321)
					{
						for (int i = 0; i < nDataLength; i++)
						{
							m_strText += m_pData[i];
						}
						m_strText += _T("\r\n");
						m_RData.ReplaceSel(m_strText);
						reset();
					}
				}
				else // text 한번에 다 못받았을때
				{
					m_pData = new char[nDataLength + 4];
					ZeroMemory(m_pData, nDataLength + 4);
					memcpy(m_pData, &byteRecvData[12], nRecvCount - 12);

				}
			}
			else if (m_nType == FILE) // file
			{
				if (nRecvCount >= nDataLength + 16) //file 한번에 다받았을때
				{
					m_pData = new char[nDataLength + 4];
					ZeroMemory(m_pData, nDataLength + 4);
					memcpy(m_pData, &byteRecvData[12], nDataLength + 4);
					memcpy(&nTemp, &m_pData[nDataLength], 4);
					if (nTemp == 0x87654321)
					{
						if (m_fileSave.Open(m_file, CFile::modeCreate | CFile::modeReadWrite))
						{
							m_fileSave.Write(m_pData, nDataLength - 4);
							m_fileSave.Close();
						}
						AfxMessageBox(_T("File Transfer Done"));
						reset();
						FileReceived();
					}
				}
				else
				{
					int low = 0;
					int high = nDataLength;
					m_Pgrs_File.SetRange(low, high);
					m_Pgrs_File.SetPos(nRecvCount);
					m_pData = new char[nDataLength + 4];
					TRACE("nDataLength : %d\r\n", nDataLength);
					ZeroMemory(m_pData, nDataLength + 4);
					memcpy(m_pData, &byteRecvData[12], nRecvCount - 12);
				}
			}
		}
		else if (nRecvCount >= 12 && bChk == TRUE)
		{
			m_Comm->Receive((char*)&m_pData[nRecvCount - 12], length);
			_trace(_T("-----------------------------------------------\r\n"));
			for (int j = 0; j < length; j++)
			{
				_trace(_T("%02X "), m_pData[j]);
				if (j % 20 == 0)
					_trace(_T("\r\n"));
			}
			nRecvCount += length;
			if (m_nType == FILE)
				m_Pgrs_File.SetPos(nRecvCount);
		}
		
		if (nRecvCount >= nDataLength + 16) //file fin
		{
			TRACE(_T("--nRecvCount>=nDataLength + 16: %d\r\n"), nRecvCount);
			memcpy(&nTemp, &m_pData[nDataLength], 4);
			if (m_nType == MD5SEND)
			{
				if (nTemp == 0x87654321) // eop
				{
					CString checkSum;
					memcpy((unsigned char*)(LPCTSTR)checkSum, m_pData, nDataLength);
					MD5RECEIVED(checkSum);
				}
				reset();
			}
			else if (m_nType == TEXT)
			{
				if (nTemp == 0x87654321) // eop
				{
					for (int i = 0; i < nDataLength; i++)
					{
						m_strText += m_pData[i];
					}
					m_strText += '\n';
					m_RData.ReplaceSel(m_strText);
				}
				reset();
			}
			else if (m_nType == FILE)
			{
				if (nTemp == 0x87654321) // eop
				{
					CFileDialog dlg(FALSE, _T("*.*"), Rename, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*|"), NULL);
					if (dlg.DoModal() == IDOK)
					{
						strPathName = dlg.GetPathName();
						if (m_fileSave.Open(strPathName, CFile::modeCreate | CFile::modeReadWrite))
						{
							TRACE("fileOpened\r\n");
							UpdateData(TRUE);
							m_fileSave.Write(m_pData, nDataLength - 4);
							m_fileSave.Close();
							AfxMessageBox(_T("File Transfer Done"));
							m_Pgrs_File.SetPos(0);
							FileReceived();
						}
						reset();
					}
				}
			}
			else if (m_nType == FILENAMESEND)
			{
				if (nTemp == 0x87654321) // eop
				{
					TRACE(_T("filename 한번에 다못받음\r\n"));
					m_FileName = new char[nDataLength + 1];
					ZeroMemory(m_FileName, nDataLength + 1);
					memcpy(m_FileName, m_pData, nDataLength);
					FileReceive(m_FileName, nDataLength);
				}
				reset();
			}
		}
	}
	return 0;
}

void CSerialTestDlg::FileReceiveOk()
{
	byte * pBuff = NULL;

	UINT32 sop = 0x12345678;
	UINT32 type = SENDOK;
	UINT32 eop = 0x87654321;
	pBuff = new byte[12];
	memcpy(pBuff, &sop, 4);
	memcpy(pBuff + 4, &type, 4);
	memcpy(pBuff + 8, &eop, 4);
	m_Comm->Send((LPCTSTR)pBuff, 12);
	delete[] pBuff;
}

void CSerialTestDlg::FileReceive(LPSTR FileName, int FileNameLen)
{

	filename = (LPCSTR)(LPSTR)FileName;
	Rename = filename;
	m_strFileName = filename;
	filename += _T(" 파일을 받겠습니까?");
	if (IDYES == AfxMessageBox(filename, MB_YESNO))
	{
		FileReceiveOk();
	}
	else
	{
		return;
	}
}


void CSerialTestDlg::OnSerialPort()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	dlg.DoModal();
}


void CSerialTestDlg::OnFilesend()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	char szFilter[] = "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
		strPathName = dlg.GetPathName();

		strFileName = dlg.GetFileName();

		strFile = dlg.GetFileName();

		strMDName = dlg.GetFileName();
	SetDlgItemText(IDC_EDIT_FILE, strPathName);
}


void CSerialTestDlg::OnBnClickedButtonSendtext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	byte * pBuff = NULL;
	CString text;
	GetDlgItemText(IDC_EDIT_TEXT, text);

	UINT32 sop = 0x12345678;
	UINT32 type = TEXT;
	UINT32 len = text.GetLength();
	UINT32 eop = 0x87654321;
	pBuff = new byte[len + 16];
	memcpy(pBuff, &sop, 4);
	memcpy(pBuff + 4, &type, 4);
	memcpy(pBuff + 8, &len, 4);
	memcpy(pBuff + 12, text, len);
	memcpy(pBuff + len + 12, &eop, 4);
	m_Comm->Send((LPCTSTR)pBuff, len + 16);
	delete[] pBuff;
	SetDlgItemText(IDC_EDIT_TEXT, _T(""));
}


void CSerialTestDlg::OnBnClickedButtonSendfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT_FILE, m_strFilePath);
	byte * pBuff = NULL;
	CFile file;
	if (file.Open(m_strFilePath, CFile::modeRead))
	{
		pBuff = new byte[file.GetLength() + 16];

		UINT32 sop = 0x12345678;
		UINT32 type = FILE;
		UINT32 len = file.GetLength();
		UINT32 eop = 0x87654321;
		memcpy(pBuff, &sop, 4);
		memcpy(pBuff + 4, &type, 4);
		memcpy(pBuff + 8, &len, 4);
		file.Read(pBuff + 12, len);
		memcpy(pBuff + len + 12, &eop, 4);
	}
	int low = 0;
	int high = file.GetLength();
	m_Pgrs_File.SetRange(low, high);
	m_Pgrs_File.SetPos(0);
	for (int i = 0; i < file.GetLength() + 16; i++)
	{
		m_Comm->Send((LPCTSTR)pBuff + i, 1);
		m_Pgrs_File.SetPos(i);
	}
	//m_Comm->Send((LPCTSTR)pBuff, file.GetLength() + 16);
	delete[] pBuff;
	file.Close();
	m_Pgrs_File.SetPos(0);
}

void CSerialTestDlg::reset()
{
	if( m_pData != NULL )
		delete[] m_pData;
	m_pData = NULL;
	ZeroMemory(byteRecvData, 12800);
	nRecvCount = 0;
	nDataLength = 0;
	m_nType = 0;
	nTemp = 0;
	bChk = FALSE;
	m_strText = "";
	if (m_FileName != NULL)
		delete[] m_FileName;
	m_FileName = NULL;
	TRACE("pData file deleted\r\n");
}

void CSerialTestDlg::MD5Send()
{
	GetDlgItemText(IDC_EDIT_FILE, m_strFilePath);
	CFile srcfile;
	CFile mdfile;
	CString checkSum;
	byte * pBuff = NULL;

	srcfile.Open(m_strFilePath, CFile::modeRead);
	checkSum = CMD5Checksum::GetMD5(srcfile);
	srcfile.Close();

	UINT32 sop = 0x12345678;
	UINT32 type = MD5SEND;
	UINT32 len = checkSum.GetLength();
	UINT32 eop = 0x87654321;

	pBuff = new byte[checkSum.GetLength() + 16];
	memcpy(pBuff, &sop, 4);
	memcpy(pBuff + 4, &type, 4);
	memcpy(pBuff + 8, &len, 4);
	memcpy(pBuff + 12, (unsigned char*)(LPCTSTR)checkSum, len);
	memcpy(pBuff + 12 + len, &eop, 4);
	m_Comm->Send((LPCTSTR)pBuff, len + 16);
	delete[] pBuff;
}

void CSerialTestDlg::MD5RECEIVED(CString checkSum)
{
	CFile mdfile;
	CString downData;

	mdfile.Open(Rename, CFile::modeRead);
	downData = CMD5Checksum::GetMD5(mdfile);
	mdfile.Close();

	if (checkSum.Compare(downData) == 0)
		AfxMessageBox(_T("5MD OK"));
	else
		AfxMessageBox(_T("5MD Fail"));
}

void CSerialTestDlg::FileReceived()
{
	byte * pBuff = NULL;

	UINT32 sop = 0x12345678;
	UINT32 type = FILERECEIVED;
	UINT32 eop = 0x87654321;
	pBuff = new byte[12];
	memcpy(pBuff, &sop, 4);
	memcpy(pBuff + 4, &type, 4);
	memcpy(pBuff + 8, &eop, 4);
	m_Comm->Send((LPCTSTR)pBuff, 12);
	delete[] pBuff;
}

void CSerialTestDlg::OnBnClickedButtonFilechk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TRACE(_T("OnBnClickedButtonFilechk\r\n"));
	if (m_FileName != NULL)
		delete[] m_FileName;
	m_FileName = NULL;
	GetDlgItemText(IDC_EDIT_FILE, m_strFilePath);
	byte * pBuff = NULL;
	
	m_FileName = new char[m_strFilePath.GetLength()];
	CStringA a = CStringA(m_strFilePath);

	memcpy(m_FileName, a.GetBuffer(), a.GetLength());
	pBuff = new byte[m_strFilePath.GetLength() + 16];		
	UINT32 sop = 0x12345678;
	UINT32 type = FILENAMESEND;
	UINT32 FileNameLen = m_strFilePath.GetLength();
	UINT32 eop = 0x87654321;

	memcpy(pBuff, &sop, 4);
	memcpy(pBuff + 4, &type, 4);
	memcpy(pBuff + 8, &FileNameLen, 4);
	memcpy(pBuff + 12, m_FileName, FileNameLen);
	memcpy(pBuff + 12 + FileNameLen, &eop, 4);
	
	m_Comm->Send((LPCTSTR)pBuff, m_strFilePath.GetLength() + 16);
	delete[] pBuff;
}
