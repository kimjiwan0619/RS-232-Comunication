
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// SerialTest.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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