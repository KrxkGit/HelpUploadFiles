#include "CSetProcessDlg.h"

CSetProcessDlg* CSetProcessDlg::singleton = new CSetProcessDlg;

INT_PTR CALLBACK CSetProcessDlg::SetProcess(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            CSetProcessDlg::singleton->dwProcessId = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
            break;
        case IDCANCEL:
            break;
        default:
            return FALSE;
        }

        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}


DWORD CSetProcessDlg::getProcessId()
{
    return this->dwProcessId;
}