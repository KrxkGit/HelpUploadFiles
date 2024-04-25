#pragma once
#include <process.h>

/**
 * @brief �����ļ�������
*/
class CAdvice
{
public:
	static CAdvice* singleton; // ���õ���ģʽ
private:
	HANDLE hSharedMem;
	HANDLE hEvent;
	std::list<std::wstring> interceptTable;
public:
	static UINT CALLBACK ListenThread(LPVOID pParam);
public:
	CAdvice();
	~CAdvice();
	bool isMatch(LPWIN32_FIND_DATA);
	void addIgnoreFile(std::wstring ignoreFileName);
	void removeIgnoreFile(std::wstring ignoreFileName);
	void startListenThread();
};

