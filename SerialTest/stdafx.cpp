
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// SerialTest.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

#ifdef _DEBUG

bool _trace(TCHAR *format, ...)

{

	TCHAR buffer[1000];



	va_list argptr;

	va_start(argptr, format);

	wvsprintf(buffer, format, argptr);

	va_end(argptr);



	OutputDebugString(buffer);



	return true;

}



bool _trace(CString strFormat, ...)

{

	TCHAR *format = (TCHAR*)(LPCTSTR)strFormat;

	TCHAR buffer[1000];



	va_list argptr;

	va_start(argptr, format);

	wvsprintf(buffer, format, argptr);

	va_end(argptr);



	OutputDebugString(buffer);



	return true;

}

#endif