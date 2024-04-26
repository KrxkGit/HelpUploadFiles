#pragma once
#include "pch.h"


// ����ͬ������
extern LPCTSTR SharedMemoryName;
extern LPCTSTR EventName;
extern LPCTSTR EventWaitReadName;

class CIgnoreInfo
{
public:
    enum TYPE {
        ADD,
        REMOVE
    } type;
    wchar_t fileName[MAX_PATH];
public:
    VOID Serialize(LPVOID lpData);
    VOID Deserialize(LPVOID lpData);
    static CIgnoreInfo* GetInstance();
};

