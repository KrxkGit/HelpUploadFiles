// Startup.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Startup.h"

HINSTANCE hInst;
LPCTSTR programName = _T("HelpUploadFiles.exe");

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    hInst = hInstance;
    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, MainDlg);
   
}

VOID OnDlgInit(HWND hDlg)
{
  
    HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_STARTUP));;
    SendMessage(hDlg, WM_SETICON, FALSE, (LPARAM)hIcon);
}

VOID OnDlgCommand(HWND hDlg, WPARAM wParam)
{
    TCHAR szWorkDirectory[MAX_PATH];
    GetCurrentDirectory(_countof(szWorkDirectory), szWorkDirectory);

    switch (LOWORD(wParam))
    {
    case IDC_BUTTON1: // 32位
        std::swprintf(szWorkDirectory, _countof(szWorkDirectory), _T("%s\\x86"), szWorkDirectory);
        break;
    case IDC_BUTTON2: // 64位
        std::swprintf(szWorkDirectory, _countof(szWorkDirectory), _T("%s\\x64"), szWorkDirectory);
        break;
    case IDCANCEL:
        EndDialog(hDlg, LOWORD(wParam));
        return;
    }
    ShellExecute(NULL, _T("Open"), programName, NULL, szWorkDirectory, SW_SHOWNORMAL);
    EndDialog(hDlg, LOWORD(wParam));
}

INT_PTR CALLBACK MainDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        OnDlgInit(hDlg);
        break;

    case WM_COMMAND:
        OnDlgCommand(hDlg, wParam);
        break;
    }
    return (INT_PTR)FALSE;
}
