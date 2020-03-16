// SerialTestDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "PYH_Comm.h"
#include "afxwin.h"
#include "SettingsDlg.h"

// CSerialTestDlg 대화 상자
class CSerialTestDlg : public CDialog
{
	// 생성
public:
	CPYH_Comm* m_Comm;
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
	CSerialTestDlg(CWnd* pParent = NULL);	// 표준 생성자

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
	CString m_SendData;
	CRichEditCtrl m_RData;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	void InitRichEdit(void);
	CString m_strCommPort;
	CString m_strBaudRate;
	CString m_strParity;
	CString m_strType;
	CString m_strDataBit;
	CString m_strStopBit;
	CString m_strFlowChk;
	CString m_strFilePath;

	afx_msg void OnSerialPort();
	afx_msg void OnFilesend();
};
