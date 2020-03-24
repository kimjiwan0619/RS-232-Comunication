// SerialTestDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "PYH_Comm.h"
#include "afxwin.h"
#include "SettingsDlg.h"
#include <Windows.h>
#include "CIni.h"

#define MD5SEND 0x06
#define FILERECEIVED 0x05
#define SENDOK 0x04
#define FILENAMESEND 0x03
#define TEXT 0x02
#define FILE 0x01

// CSerialTestDlg 대화 상자
class CSerialTestDlg : public CDialog
{
	// 생성
public:
	CPYH_Comm* m_Comm;
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
	CSerialTestDlg(CWnd* pParent = NULL);	// 표준 생성자
	~CSerialTestDlg()
	{
		if( m_Comm != NULL )
			m_Comm->m_bIsOpenned = FALSE;

		Sleep(100);
	};
											// 대화 상자 데이터
	enum { IDD = IDD_SERIALTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


														// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	SettingsDlg dlg;

	CRichEditCtrl m_RData;
	afx_msg void OnBnClickedButtonConnect();
	void InitRichEdit(void);
	CString m_strCommPort;
	CString m_strBaudRate;
	CString m_strParity;
	CString m_strType;
	CString m_strDataBit;
	CString m_strStopBit;
	CString strFileName;
	CString strMDName;
	CString m_file;
	CString m_strFlowChk;
	CString m_strFilePath;
	CFile m_fileSave;
	CFile m_PortSave;
	CString filename;
	CString strPathName;
	CString strFile;
	CString m_strFileName;
	CString Rename;
	CString m_strText = "";
	CString m_strRcvFileName;
	afx_msg void OnSerialPort();
	afx_msg void OnFilesend();
	afx_msg void OnBnClickedButtonSendtext();
	afx_msg void OnBnClickedButtonSendfile();
	afx_msg void OnBnClickedButtonFilechk();
	char * m_pData = NULL;
	byte byteRecvData[12800] = { 0 };
	UINT32 nRecvCount = 0;
	UINT32 nDataLength = 0;
	UINT m_nType = 0;
	UINT32 nTemp = 0;
	
	char* m_FileName = NULL;
	
	BOOL bChk = FALSE;
	BOOL m_bIsOpened;
	void FileReceiveOk();
	void FileReceive(LPSTR, int);
	void reset();
	
	CProgressCtrl m_Pgrs_File;
	void MD5Send();
	void MD5RECEIVED(CString checkSum);
	void FileReceived();	
};
