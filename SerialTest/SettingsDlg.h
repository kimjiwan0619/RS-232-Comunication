#pragma once


// SettingsDlg 대화 상자입니다.

class SettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingsDlg)
public:
	SettingsDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SettingsDlg();
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strCommPort;
	CString m_strBaudRate;
	CString m_strParity;
	CString m_strType;
	CString m_strDataBit;
	CString m_strStopBit;
	CString m_strFlowChk;
	CComboBox m_comboCommport;
	CComboBox m_comboBaudRate;
	CComboBox m_comboParity;
	CComboBox m_comboDataBit;
	CComboBox m_comboStopBit;
	CComboBox m_comboFlowChk;
	afx_msg void OnBnClickedButtonSetting();
};
