#include "pch.h"
#include "CAdvice.h"
#include "CIgnoreInfo.h"


// 单例初始化
CAdvice* CAdvice::singleton = new CAdvice;

bool CAdvice::isMatch(LPWIN32_FIND_DATA lpFindFileData)
{
	bool bMatch = false;
	std::wstring fileNameStr = lpFindFileData->cFileName;

	for (std::list<std::wstring>::iterator iter = this->interceptTable.begin(); iter != this->interceptTable.end(); iter++) {
		std::wstring subStr = *iter;
		if (fileNameStr.find(subStr) != std::wstring::npos)
		{
			bMatch = true;
			break;
		}
	}
	return bMatch;
}

/**
 * @brief 添加忽略的文件
 * @param ignoreFileName 
*/
void CAdvice::addIgnoreFile(std::wstring ignoreFileName)
{
	this->interceptTable.push_back(ignoreFileName);
}

/**
 * @brief 移除忽略的文件
 * @param ignoreFileName 
*/
void CAdvice::removeIgnoreFile(std::wstring ignoreFileName)
{
	this->interceptTable.remove(ignoreFileName);
}

/**
 * @brief 监听忽略列表的事件变化线程
 * @param pParam 
 * @return 
*/
UINT CALLBACK CAdvice::ListenThread(LPVOID pParam)
{
	CAdvice* pAdvice = CAdvice::singleton;
	CIgnoreInfo* pIgnoreInfo = CIgnoreInfo::GetInstance();

	while (true) {
		WaitForSingleObject(pAdvice->hEvent, INFINITE);

		
		LPVOID sharedMemory = MapViewOfFile(pAdvice->hSharedMem, FILE_MAP_READ, 0, 0, sizeof(CIgnoreInfo));
		if (sharedMemory != NULL) {
			pIgnoreInfo->Deserialize(sharedMemory);

			if (pIgnoreInfo->type == CIgnoreInfo::ADD) {
				pAdvice->addIgnoreFile(pIgnoreInfo->fileName);
			}
			else if (pIgnoreInfo->type == CIgnoreInfo::REMOVE) {
				pAdvice->removeIgnoreFile(pIgnoreInfo->fileName);
			}

			UnmapViewOfFile(sharedMemory);

			SetEvent(pAdvice->hWaitReadEvent);
		}
	}
}

void CAdvice::startListenThread()
{
	_beginthreadex(0, 0, CAdvice::ListenThread, 0, 0, 0);
}

CAdvice::CAdvice()
{
	this->hEvent = CreateEvent(0, FALSE, FALSE, EventName);
	if (this->hEvent == INVALID_HANDLE_VALUE) {
		wchar_t sz[100];
		std::swprintf(sz, _countof(sz), _T("创建失败 : %d"), GetLastError());
		MessageBox(NULL, sz, _T("初始化事件"), MB_ICONINFORMATION);
	}

	this->hWaitReadEvent = CreateEvent(0, FALSE, TRUE, EventWaitReadName);
	if (this->hWaitReadEvent == INVALID_HANDLE_VALUE) {
		wchar_t sz[100];
		std::swprintf(sz, _countof(sz), _T("创建失败 : %d"), GetLastError());
		MessageBox(NULL, sz, _T("初始化读等待事件"), MB_ICONINFORMATION);
	}

	this->hSharedMem = OpenFileMapping(FILE_MAP_READ, FALSE, SharedMemoryName);
	if (this->hSharedMem == INVALID_HANDLE_VALUE) {
		wchar_t sz[100];
		std::swprintf(sz, _countof(sz), _T("创建失败 : %d"), GetLastError());
		MessageBox(NULL, sz, _T("初始化共享内存"), MB_ICONINFORMATION);
	}
}

CAdvice::~CAdvice()
{
	CloseHandle(this->hSharedMem);
	CloseHandle(this->hEvent);
}