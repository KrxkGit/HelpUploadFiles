#include "pch.h"
#include "CSkin.h"

CSkin::CSkin()
{
    typedef bool (*LOADSKINPROC)(const char* szSkinFile, BOOL bFromIni);
    
    this->hSkinMod = LoadLibrary(_T("SkinPPWTL"));
    if (hSkinMod != NULL) {
        LOADSKINPROC pfn = (LOADSKINPROC)GetProcAddress(this->hSkinMod, "skinppLoadSkin");

        char szSkinPath[MAX_PATH];
        FindSkinFile(szSkinPath);
        pfn(szSkinPath, FALSE);
    }
}

CSkin::~CSkin() 
{
    FARPROC pfn = GetProcAddress(this->hSkinMod, "skinppExitSkin");
    pfn();
}



void CSkin::FindSkinFile(char* skinPath)
{
    namespace fs = std::filesystem;

    std::string path = "."; // µ±Ç°Ä¿Â¼
    std::string extension = ".ssk";

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            sprintf_s(skinPath, MAX_PATH, "%s", entry.path().string().c_str());
        }
    }
}
