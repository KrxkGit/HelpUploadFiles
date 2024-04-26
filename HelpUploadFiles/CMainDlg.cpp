#include "pch.h"
#include "CMainDlg.h"

CMainDlg* CMainDlg::singleton = new CMainDlg;

INT_PTR CALLBACK CMainDlg::MainDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    CMainDlg::singleton->SaveParameters(hDlg, message, wParam, lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        CMainDlg::singleton->OnDlgInit();
        break;

    case WM_COMMAND:
        CMainDlg::singleton->OnCommand();
        break;
    case WM_DROPFILES:
        CMainDlg::singleton->OnDropFile();
        break;
    case WM_LBUTTONDOWN:
        CMainDlg::singleton->OnLButtonDown();
        break;
    case WM_LBUTTONUP:
        CMainDlg::singleton->OnLButtonUp();
        break;
    case WM_MOUSEMOVE:
        CMainDlg::singleton->OnMouseMove();
        break;
    }
    return (INT_PTR)FALSE;
}

VOID CMainDlg::OnDlgInit()
{
    this->haveInject = false;

    this->hInjectWnd = NULL;
    SetDlgItemText(this->hDlg, IDC_CAPTUREWND, _T("������꿪������"));

    this->hListBox = GetDlgItem(this->hDlg, IDC_LIST1);
    this->hIcon = LoadIcon(this->hInst, MAKEINTRESOURCE(IDI_HELPUPLOADFILES));
    SendMessage(this->hDlg, WM_SETICON, FALSE, (LPARAM)this->hIcon);

    this->hCaptureCur = LoadCursor(this->hInst, MAKEINTRESOURCE(IDC_CURSOR1));

    DragAcceptFiles(this->hDlg, TRUE);
}



void CMainDlg::OnCommand()
{
    // TODO: �ڴ˴����ʵ�ִ���.
    switch (LOWORD(this->wParam))
    {
    case IDCANCEL:
        EndDialog(hDlg, LOWORD(wParam));
        break;
    case IDADD:
        OnAdd();
        break;
    case IDREMOVE:
        OnRemove();
        break;
    case IDM_INJECT:
        OnInject();
        break;
    case IDM_ABOUT:
        OnOpenAbout();
    }
}


void CMainDlg::SaveParameters(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    this->hDlg = hDlg;
    this->message = message;
    this->wParam = wParam;
    this->lParam = lParam;
}


void CMainDlg::OnAdd()
{
    if (!isHaveInject()) {
        return;
    }
    GetInputString();
    DoAdd();
}

void CMainDlg::DoAdd()
{
    CIgnoreFileManager::getSingleton()->addIgnoreFile(this->szInput);
    ListBox_AddString(this->hListBox, this->szInput);
}


void CMainDlg::OnRemove()
{
    int curSel = ListBox_GetCurSel(this->hListBox);
    if (curSel < 0) {
        return;
    }

    ListBox_GetText(this->hListBox, curSel, this->szInput);
    CIgnoreFileManager::getSingleton()->removeIgnoreFile(this->szInput);
    ListBox_DeleteString(this->hListBox, curSel);

    // ������һ��ѡ�е�λ��
    if (curSel > 0) {
        curSel--;
    }
    ListBox_SetCurSel(this->hListBox, curSel);
}


int CMainDlg::GetInputString()
{
    return GetDlgItemText(this->hDlg, IDC_EDIT1, this->szInput, _countof(this->szInput));
}


void CMainDlg::OnInject()
{
    if (this->hInjectWnd == NULL) {
        return;
    }
    CContext::singleton->InjectWorkDll(this->hInjectWnd);
    this->hInjectWnd = NULL;

    this->haveInject = true;
}


void CMainDlg::OnOpenAbout()
{
    DialogBox(this->hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), this->hDlg, CAboutDlg::About);
}


void CMainDlg::OnDropFile()
{
    HDROP hDrop = (HDROP)this->wParam;
    if (!isHaveInject()) {
        DragFinish(hDrop); // �����˴���ק
        return;
    }

    if (IDCANCEL == MessageBox(this->hDlg, _T("��⵽��ק�ļ����Ƿ���ӵ������б�"), _T("��ʾ"), MB_ICONQUESTION | MB_OKCANCEL | MB_DEFBUTTON1)) {
        DragFinish(hDrop); // �����˴���ק
        return;
    }
    
    UINT numFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

    // �˹��ܴ� C++ 17 ��ʼ֧��
    namespace fs = std::filesystem;

    for (UINT i = 0; i < numFiles; i++)
    {
        //TCHAR szFileName[MAX_PATH];
        DragQueryFile(hDrop, i, this->szInput, MAX_PATH);

        // �����ﴦ���Ϸŵ��ļ���������ʾ�ļ���
        fs::path path = this->szInput;
        _tcscpy_s(this->szInput, _countof(this->szInput), path.filename().c_str());

        // ��ק�������������
        std::swprintf(this->szInput, _countof(this->szInput), _T("%s"), CEscapeRegex::escapeRegex(this->szInput).c_str());
        
        DoAdd();
    }

    DragFinish(hDrop);
}



void CMainDlg::OnMouseMove()
{
    if (GetCapture() == NULL) {
        return;
    }
    POINT pt;
    GetCursorPos(&pt);
    HWND hWnd = WindowFromPoint(pt);
    if (hWnd == this->hInjectWnd) {
        // ����δ���ͱ仯��������
        return;
    }
    this->hInjectWnd = hWnd;
    
    TCHAR szClass[100];
    szTitle[0] = '\0';
    szClass[0] = '\0';

    HWND hCaptureTextWnd = GetDlgItem(this->hDlg, IDC_CAPTUREWND);
    GetWindowText(hWnd, szTitle, _countof(szTitle));
    if (szTitle[0] == '\0') {
        GetClassName(hWnd, szClass, _countof(szClass));

        std::swprintf(szTitle, _countof(szTitle), _T("%s - %s"), szClass, szTitle);
    }
    SetWindowText(hCaptureTextWnd, szTitle);
}


void CMainDlg::OnLButtonDown()
{
    SetCapture(this->hDlg);
    this->hOldCur = SetCursor(this->hCaptureCur);
}


void CMainDlg::OnLButtonUp()
{
    ReleaseCapture();
    SetCursor(this->hOldCur);

    TCHAR sz[MAX_PATH];
    std::swprintf(sz, _countof(sz), _T("�Ƿ�Ϊ���� %s ���ظ���ģ��"), this->szTitle);

    if (IDOK == MessageBox(this->hDlg, sz, _T("���ظ���ģ��"), MB_ICONQUESTION | MB_OKCANCEL)) {
        OnInject();
    }
}


bool CMainDlg::isHaveInject()
{
    bool b = this->haveInject;
    if (!b) {
        TCHAR sz[MAX_PATH];
        std::swprintf(sz, _countof(sz), _T("��δע�븳��ģ�飬�������ע�����"));
        MessageBox(this->hDlg, sz, _T("��ʾ"), MB_ICONWARNING);
    }
    return b;
}
