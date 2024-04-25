#pragma once
class CAboutDlg
{
private:
	static CAboutDlg* singleton;
public:
	static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

