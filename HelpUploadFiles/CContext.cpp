#include "CContext.h"

CContext* CContext::singleton = new CContext;
LPCTSTR SharedMemoryName = _T("HelpUploadFileSharedMemory");
LPCTSTR EventName = _T("HelpUploadEvent");

CContext::CContext()
{
    // 延迟注入 DLL
    //InjectWorkDll();
    this->hEvent = CreateEvent(0, FALSE, FALSE, EventName);
    if (hEvent == INVALID_HANDLE_VALUE) {
        wchar_t buffer[100];
        std::swprintf(buffer, _countof(buffer), _T("CreateEvent failed with %d"), GetLastError());
        throw buffer;
    }

    this->hSharedMem = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, SharedMemoryName);
    if (this->hSharedMem == INVALID_HANDLE_VALUE) {
        wchar_t buffer[100];
        std::swprintf(buffer, _countof(buffer), _T("CreateFileMapping failed with %d"), GetLastError());
        throw buffer;
    }
}

CContext::~CContext()
{
    CloseHandle(this->hSharedMem);
    CloseHandle(this->hEvent);
}

VOID CContext::InjectWorkDll(HWND hWnd)
{
    CInjectDll::DoInject(hWnd);
}

VOID CContext::DoOperation(CIgnoreInfo* pIgnoreInfo, std::wstring fileName, CIgnoreInfo::TYPE type)
{
    // 准备数据结构
    pIgnoreInfo->type = type;
    size_t cbWrite = _countof(pIgnoreInfo->fileName);

    _tcscpy_s(pIgnoreInfo->fileName, cbWrite, fileName.c_str());

    // 写入共享内存
    LPVOID sharedMemory = MapViewOfFile(this->hSharedMem, FILE_MAP_WRITE, 0, 0, sizeof(CIgnoreInfo));
    if (sharedMemory != NULL) {
        pIgnoreInfo->Serialize(sharedMemory);
        UnmapViewOfFile(sharedMemory);
    }
    
    // 唤醒
    SetEvent(this->hEvent);
}


VOID CContext::AddInnoreFile(std::wstring fileName)
{
    CIgnoreInfo ignoreInfo;
    DoOperation(&ignoreInfo, fileName, CIgnoreInfo::ADD);
}

VOID CContext::RemoveInnoreFile(std::wstring fileName)
{
    CIgnoreInfo ignoreInfo;
    DoOperation(&ignoreInfo, fileName, CIgnoreInfo::REMOVE);

}