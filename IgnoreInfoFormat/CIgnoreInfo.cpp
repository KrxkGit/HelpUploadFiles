#include "CIgnoreInfo.h"

VOID CIgnoreInfo::Serialize(LPVOID lpData)
{
	size_t endPos = lstrlen(this->fileName) + 1;
	this->fileName[endPos] = '\0'; // Ìí¼ÓÖÕÖ¹·û

	CopyMemory(lpData, this, sizeof(CIgnoreInfo));
}

VOID CIgnoreInfo::Deserialize(LPVOID lpData)
{
	CopyMemory(this, lpData, sizeof(CIgnoreInfo));
}

CIgnoreInfo* CIgnoreInfo::GetInstance()
{
	return new CIgnoreInfo;
}