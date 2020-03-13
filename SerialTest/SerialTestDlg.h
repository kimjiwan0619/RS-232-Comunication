// SerialTestDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "PYH_Comm.h"
#include "afxwin.h"


// CSerialTestDlg ��ȭ ����
class CSerialTestDlg : public CDialog
{
	// ����
public:
	CPYH_Comm* m_Comm;
	LRESULT	OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
	CSerialTestDlg(CWnd* pParent = NULL);	// ǥ�� ������

											// ��ȭ ���� ������
	enum { IDD = IDD_SERIALTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


														// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_SendData;
	CRichEditCtrl m_RData;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	void InitRichEdit(void);
	CString m_strCommPort;
	CString m_strBaudRate;
	CString m_strParity;
	CString m_strDataBit;
	CString m_strStopBit;
	CString m_strFlowChk;
	CComboBox m_comboCommport;
	CComboBox m_comboBaudRate;
	CComboBox m_comboParity;
	CComboBox m_comboDataBit;
	CComboBox m_comboStopBit;
	CComboBox m_comboFlowChk;
	CRichEditCtrl m_SData;

};
