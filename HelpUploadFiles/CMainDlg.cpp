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
    SetDlgItemText(this->hDlg, IDC_CAPTUREWND, _T("长按鼠标开启捕获"));

    this->hListBox = GetDlgItem(this->hDlg, IDC_LIST1);
    this->hIcon = LoadIcon(this->hInst, MAKEINTRESOURCE(IDI_HELPUPLOADFILES));
    SendMessage(this->hDlg, WM_SETICON, FALSE, (LPARAM)this->hIcon);

    this->hCaptureCur = LoadCursor(this->hInst, MAKEINTRESOURCE(IDC_CURSOR1));

    DragAcceptFiles(this->hDlg, TRUE);
}



void CMainDlg::OnCommand()
{
    // TODO: 在此处添加实现代码.
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
    case IDM_IMPORT:
        OnImportSetting();
        break;
    case IDM_EXPORT:
        OnExportSetting();
        break;
    case IDM_SETPROCESS:
        OnSetProcessId();
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

    // 设置下一个选中的位置
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
        DragFinish(hDrop); // 结束此次拖拽
        return;
    }

    if (IDCANCEL == MessageBox(this->hDlg, _T("检测到拖拽文件，是否添加到忽略列表？"), _T("提示"), MB_ICONQUESTION | MB_OKCANCEL | MB_DEFBUTTON1)) {
        DragFinish(hDrop); // 结束此次拖拽
        return;
    }
    
    UINT numFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

    // 此功能从 C++ 17 开始支持
    namespace fs = std::filesystem;

    for (UINT i = 0; i < numFiles; i++)
    {
        //TCHAR szFileName[MAX_PATH];
        DragQueryFile(hDrop, i, this->szInput, MAX_PATH);

        // 在这里处理拖放的文件，比如显示文件名
        fs::path path = this->szInput;
        _tcscpy_s(this->szInput, _countof(this->szInput), path.filename().c_str());

        // 拖拽将逃逸正则规则
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
        // 窗口未发送变化，不处理
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
    std::swprintf(sz, _countof(sz), _T("是否为窗口 %s 加载赋能模块"), this->szTitle);

    if (IDOK == MessageBox(this->hDlg, sz, _T("加载赋能模块"), MB_ICONQUESTION | MB_OKCANCEL)) {
        OnInject();
    }
}


bool CMainDlg::isHaveInject()
{
    bool b = this->haveInject;
    if (!b) {
        TCHAR sz[MAX_PATH];
        std::swprintf(sz, _countof(sz), _T("尚未注入赋能模块，请先完成注入操作"));
        MessageBox(this->hDlg, sz, _T("提示"), MB_ICONWARNING);
    }
    return b;
}


void CMainDlg::OnSetProcessId()
{
    // TODO: 在此处添加实现代码.
    INT_PTR res = DialogBox(hInst, MAKEINTRESOURCE(IDD_SETPROCESSDLG), this->hDlg, CSetProcessDlg::SetProcess);
    if (res == IDCANCEL) {
        return;
    }
    
    CInjectDll::DoInject(CSetProcessDlg::singleton->getProcessId());

    this->haveInject = true;
    
}


void CMainDlg::OnImportSetting()
{
    if (!isHaveInject()) {
        return;
    }
    // 导入配置文件：忽略列表
    OPENFILENAME ofn; // 使用OPENFILENAMEW结构体，它是OPENFILENAME的Unicode版本
    TCHAR szFile[MAX_PATH]; // 使用WCHAR数组来存储Unicode字符串
    szFile[0] = '\0';

    // 初始化OPENFILENAMEW结构体
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hDlg;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile);
    ofn.lpstrFilter = _T("HUFS Files\0*.hufs\0All Files\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // 显示打开文件对话框
    if (GetOpenFileNameW(&ofn) == TRUE && MessageBox(hDlg, _T("是否追加配置？"),_T("提示"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK) {
        // 文件路径为 ofn.lpstrFile
        SettingSerialize(TRUE, ofn.lpstrFile);
    }
    else {
        // 用户取消了操作
        return;
    }
}


void CMainDlg::OnExportSetting()
{
    // 导出配置文件：忽略列表
    OPENFILENAME ofn; // 使用OPENFILENAMEW结构体，它是OPENFILENAME的Unicode版本
    TCHAR szFile[MAX_PATH]; // 使用WCHAR数组来存储Unicode字符串
    szFile[0] = '\0';
    TCHAR szFileName[MAX_PATH]; // 存储用户选择的文件名

    // 初始化OPENFILENAMEW结构体
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile); // 确保nMaxFile是字符数，而不是字节数
    ofn.lpstrDefExt = L"hufs"; // 默认扩展名
    ofn.lpstrFilter = L"HUFS Files\0*.hufs\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER;

    // 显示保存文件对话框
    if (GetSaveFileNameW(&ofn) == TRUE) {
        // 用户选择了文件名并点击了“保存”按钮
        // szFile中包含了选择的文件的完整路径
        wcscpy_s(szFileName, ofn.lpstrFile); // 复制选择的文件名
        // 这里可以进行文件保存操作
        SettingSerialize(FALSE, szFileName);
    }
    else {
        // 用户取消了操作
        return;
    }
}


void CMainDlg::SettingSerialize(bool bReadPattern, LPTSTR filename)
{
    /*
    * 文件格式：
    * 第一行为 版本号
    * 每一行都为 TCHAR[MAX_PATH]
    */
    double version = 1.05;
    double versionRead = 0;
    DWORD dwCreationDisposition = bReadPattern ? OPEN_EXISTING : CREATE_ALWAYS;

    // 读写配置文件
    HANDLE hFile = CreateFile(
        filename,             // 文件路径
        GENERIC_READ | GENERIC_WRITE,         // 打开文件用于读取与写入
        0,                    // 不共享（独占）
        NULL,                 // 安全属性
        dwCreationDisposition,       // 打开已存在的文件
        FILE_ATTRIBUTE_NORMAL,// 正常文件属性
        NULL);                // 不使用模板

    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(hDlg, _T("配置文件打开或写入失败!"), _T("严重错误"), MB_ICONERROR);
        return;
    }

    HWND hwndListBox = GetDlgItem(hDlg, IDC_LIST1); // 获取列表框控件的句柄

    __try {
        if (bReadPattern) {
            // 读模式
            // 
            // 读取版本号
            DWORD dwSize = 0;
            if (ReadFile(hFile, &versionRead, sizeof(versionRead), &dwSize, NULL)) {
                if (dwSize == sizeof(versionRead)) {
                    if (versionRead != version) {
                        MessageBox(hDlg, _T("配置文件版本号不一致"), _T("提示"), MB_ICONERROR);
                        return;
                    }
                }
            }
            else {
                MessageBox(hDlg, _T("读取配置文件失败"), _T("提示"), MB_ICONERROR);
                return;
            }

            // 读取每一行
            TCHAR szBuffer[MAX_PATH];
            DWORD bufferSize = sizeof(szBuffer);
            dwSize = 0;
            while (ReadFile(hFile, szBuffer, bufferSize, &dwSize, NULL)) {
                if (dwSize > 0) {
                    // 添加
                    _tcscpy_s(this->szInput, _countof(this->szInput), szBuffer);
                    DoAdd();
                }
                else {
                    break;
                }
            }

            MessageBox(hDlg, _T("导入配置文件完成"), _T("提示"), MB_ICONINFORMATION);
        }
        else {
            // 写模式
            // 写入版本号
            DWORD bytesWritten = sizeof(version);
            BOOL bSuccess = WriteFile(hFile, &version, bytesWritten, &bytesWritten, NULL);
            if (!bSuccess) {
                MessageBox(hDlg, _T("写入版本号失败"), _T("提示"), MB_ICONERROR);
                return;
            }

            // 写入每一行
            int count = ListBox_GetCount(hwndListBox); // 获取列表框中的项数

            for (int i = 0; i < count; ++i) {
                TCHAR buffer[MAX_PATH]; // 每个项的文本不超过255个字符
                ListBox_GetText(hwndListBox, i, buffer); // 获取第i项的文本

                
                bSuccess = WriteFile(hFile, buffer, sizeof(buffer), &bytesWritten, NULL);
                if (!bSuccess) {
                    MessageBox(hDlg, _T("写入版本号失败"), _T("提示"), MB_ICONERROR);
                    return;
                }

            }
        }
    } __finally {
        CloseHandle(hFile);
    }
}
