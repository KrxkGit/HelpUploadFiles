#include "CIgnoreInfo.h"

// 进程同步定义
LPCTSTR SharedMemoryName = _T("HelpUploadFileSharedMemory");
LPCTSTR EventName = _T("HelpUploadEvent");
LPCTSTR EventWaitReadName = _T("HelpUploadWaitReadEvent");

VOID CIgnoreInfo::Serialize(LPVOID lpData)
{
	size_t endPos = lstrlen(this->fileName) + 1;
	this->fileName[endPos] = '\0'; // 添加终止符

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