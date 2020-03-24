// SettingsDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"
#include "CIni.h"

// SettingsDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(SettingsDlg, CDialogEx)

SettingsDlg::SettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETTINGS_DIALOG, pParent)
{
	
}

SettingsDlg::~SettingsDlg()
{
}

void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_comboParity);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_comboDataBit);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_comboStopBit);
	DDX_Control(pDX, IDC_COMBO_FLOWCHK, m_comboFlowChk);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboCommport);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_comboBaudRate);
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &SettingsDlg::OnBnClickedButtonSetting)
END_MESSAGE_MAP()


// SettingsDlg 메시지 처리기입니다.


BOOL SettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	m_comboBaudRate.SetCurSel(12);
	m_comboParity.AddString(_T("None"));
	m_comboParity.AddString(_T("Odd"));
	m_comboParity.AddString(_T("Even"));
	m_comboParity.SetCurSel(0);
	m_comboDataBit.AddString(_T("8 Bit"));
	m_comboDataBit.AddString(_T("7 Bit"));
	m_comboDataBit.SetCurSel(0);
	m_comboStopBit.AddString(_T("1 Bit"));
	m_comboStopBit.AddString(_T("1.5 Bit"));
	m_comboStopBit.AddString(_T("2 Bit"));
	m_comboStopBit.SetCurSel(0);
	m_comboFlowChk.AddString(_T("None"));
	m_comboFlowChk.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SettingsDlg::OnBnClickedButtonSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_comboCommport.GetLBText(m_comboCommport.GetCurSel(), m_strCommPort);
	m_comboBaudRate.GetLBText(m_comboBaudRate.GetCurSel(), m_strBaudRate);
	m_comboParity.GetLBText(m_comboParity.GetCurSel(), m_strParity);
	m_comboDataBit.GetLBText(m_comboDataBit.GetCurSel(), m_strDataBit);
	m_comboStopBit.GetLBText(m_comboStopBit.GetCurSel(), m_strStopBit);

	m_comboCommport.SetCurSel(m_comboCommport.GetCurSel());
	m_comboBaudRate.SetCurSel(m_comboBaudRate.GetCurSel());
	m_comboParity.SetCurSel(m_comboParity.GetCurSel());
	m_comboDataBit.SetCurSel(m_comboDataBit.GetCurSel());
	m_comboStopBit.SetCurSel(m_comboStopBit.GetCurSel());

	CString sIniPath;
	sIniPath.Format(_T("C:/test2/PortSave.ini"));
	

	WritePrivateProfileString(_T("PORT_SETTING"), _T("CommPort"), m_strCommPort, sIniPath);
	WritePrivateProfileString(_T("PORT_SETTING"), _T("BaudRate"), m_strBaudRate, sIniPath);
	WritePrivateProfileString(_T("PORT_SETTING"), _T("Parity"), m_strParity, sIniPath);
	WritePrivateProfileString(_T("PORT_SETTING"), _T("DataBit"), m_strDataBit, sIniPath);
	WritePrivateProfileString(_T("PORT_SETTING"), _T("StopBit"), m_strStopBit, sIniPath);

	CDialog::OnOK();
}