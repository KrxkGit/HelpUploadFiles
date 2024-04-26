#include "pch.h"
#include "CAdvice.h"
#include "CIgnoreInfo.h"


// ������ʼ��
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
 * @brief ��Ӻ��Ե��ļ�
 * @param ignoreFileName 
*/
void CAdvice::addIgnoreFile(std::wstring ignoreFileName)
{
	this->interceptTable.push_back(ignoreFileName);
}

/**
 * @brief �Ƴ����Ե��ļ�
 * @param ignoreFileName 
*/
void CAdvice::removeIgnoreFile(std::wstring ignoreFileName)
{
	this->interceptTable.remove(ignoreFileName);
}

/**
 * @brief ���������б���¼��仯�߳�
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
		std::swprintf(sz, _countof(sz), _T("����ʧ�� : %d"), GetLastError());
		MessageBox(NULL, sz, _T("��ʼ���¼�"), MB_ICONINFORMATION);
	}

	this->hWaitReadEvent = CreateEvent(0, FALSE, TRUE, EventWaitReadName);
	if (this->hWaitReadEvent == INVALID_HANDLE_VALUE) {
		wchar_t sz[100];
		std::swprintf(sz, _countof(sz), _T("����ʧ�� : %d"), GetLastError());
		MessageBox(NULL, sz, _T("��ʼ�����ȴ��¼�"), MB_ICONINFORMATION);
	}

	this->hSharedMem = OpenFileMapping(FILE_MAP_READ, FALSE, SharedMemoryName);
	if (this->hSharedMem == INVALID_HANDLE_VALUE) {
		wchar_t sz[100];
		std::swprintf(sz, _countof(sz), _T("����ʧ�� : %d"), GetLastError());
		MessageBox(NULL, sz, _T("��ʼ�������ڴ�"), MB_ICONINFORMATION);
	}
}

CAdvice::~CAdvice()
{
	CloseHandle(this->hSharedMem);
	CloseHandle(this->hEvent);
}