#pragma once

#include "pch.h"
#include "resource.h"
#include "CIgnoreFileManager.h"
#include "CAboutDlg.h"
#include "CEscapeRegex.h"
#include "CSetProcessDlg.h"

class CMainDlg
{
public:
	static CMainDlg* singleton;
	HINSTANCE hInst;
private:
	HWND hDlg;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;

	HICON hIcon;
	HCURSOR hOldCur;
	HCURSOR hCaptureCur;
	HWND hListBox;
	TCHAR szInput[MAX_PATH];

	HWND hInjectWnd;
	TCHAR szTitle[MAX_PATH]; // 注入的窗口标题 / 类
	bool haveInject;
public:
	static INT_PTR CALLBACK MainDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
protected:
	VOID OnDlgInit();
	void OnCommand();
	void SaveParameters(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void OnAdd();
	void OnRemove();
	int GetInputString();
public:
	void OnInject();
	void OnOpenAbout();
protected:
	void OnDropFile();
	void DoAdd();
	void OnMouseMove();
	void OnLButtonDown();
	void OnLButtonUp();
	bool isHaveInject();
	void OnSetProcessId();
};

