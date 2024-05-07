#pragma once
#include "pch.h"
#include "resource.h"

class CSetProcessDlg
{
private:
	DWORD dwProcessId;
public:
	static CSetProcessDlg* singleton;
	static INT_PTR CALLBACK SetProcess(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	DWORD getProcessId();
};

