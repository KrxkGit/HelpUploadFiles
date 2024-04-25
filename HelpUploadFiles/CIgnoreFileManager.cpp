#include "CIgnoreFileManager.h"


// ��Ҫ�Ӻ��ȡ�������޷���֪������������
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
    // �����ĸ�֪
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