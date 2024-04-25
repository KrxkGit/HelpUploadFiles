#include "CIgnoreFileManager.h"


// 需要延后获取，否则无法感知到容器上下文
CIgnoreFileManager* CIgnoreFileManager::singleton = NULL;

CIgnoreFileManager* CIgnoreFileManager::getSingleton()
{
    if (CIgnoreFileManager::singleton == NULL) {
        CIgnoreFileManager::singleton = new CIgnoreFileManager;
    }

    return CIgnoreFileManager::singleton;
}

CIgnoreFileManager::CIgnoreFileManager()
{
    // 容器的感知
    this->context = CContext::singleton;
}

void CIgnoreFileManager::addIgnoreFile(std::wstring fileName)
{
    this->context->AddInnoreFile(fileName);
}

void CIgnoreFileManager::removeIgnoreFile(std::wstring fileName)
{
    this->context->RemoveInnoreFile(fileName);
}