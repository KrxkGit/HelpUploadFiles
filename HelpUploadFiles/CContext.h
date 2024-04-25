#pragma once
#include "pch.h"
#include "framework.h"
#include "CInjectDll.h"
#include "CIgnoreInfo.h"


class CContext
{
private:
    HANDLE hSharedMem;
    HANDLE hEvent;
public:
    static CContext* singleton;
    CContext();
    ~CContext();
public:
    VOID InjectWorkDll(HWND hWnd);
    VOID AddInnoreFile(std::wstring fileName);
    VOID RemoveInnoreFile(std::wstring fileName);
protected:
    VOID DoOperation(CIgnoreInfo* pIgnoreInfo, std::wstring fileName, CIgnoreInfo::TYPE type);
};

