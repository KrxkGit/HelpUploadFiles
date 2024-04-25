#pragma once
#include "pch.h"

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

