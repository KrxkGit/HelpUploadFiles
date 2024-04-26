#include "CIgnoreInfo.h"

// ����ͬ������
LPCTSTR SharedMemoryName = _T("HelpUploadFileSharedMemory");
LPCTSTR EventName = _T("HelpUploadEvent");
LPCTSTR EventWaitReadName = _T("HelpUploadWaitReadEvent");

VOID CIgnoreInfo::Serialize(LPVOID lpData)
{
	size_t endPos = lstrlen(this->fileName) + 1;
	this->fileName[endPos] = '\0'; // �����ֹ��

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