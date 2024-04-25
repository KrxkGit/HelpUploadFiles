﻿// HelpUploadFiles.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "HelpUploadFiles.h"
#include "CSkin.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CSkin skin; // 加载皮肤
    
    CMainDlg::singleton->hInst = hInstance;
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, CMainDlg::MainDlg);

    return GetLastError();
}



