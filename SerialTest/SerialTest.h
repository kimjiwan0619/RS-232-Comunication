
// SerialTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSerialTestApp:
// �� Ŭ������ ������ ���ؼ��� SerialTest.cpp�� �����Ͻʽÿ�.
//

class CSerialTestApp : public CWinApp
{
public:
	CSerialTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSerialTestApp theApp;