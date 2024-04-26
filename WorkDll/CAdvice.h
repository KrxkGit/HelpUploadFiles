#pragma once
#include <process.h>
#include <regex>

/**
 * @brief 忽略文件拦截器
*/
class CAdvice
{
public:
	static CAdvice* singleton; // 采用单例模式
private:
	HANDLE hSharedMem;
	HANDLE hEvent;
	HANDLE hWaitReadEvent;
	std::list<std::wstring> interceptTable;
	bool syntaxError;
public:
	static UINT CALLBACK ListenThread(LPVOID pParam);
public:
	CAdvice();
	~CAdvice();
	bool isMatch(LPWIN32_FIND_DATA);
	void addIgnoreFile(std::wstring ignoreFileName);
	void removeIgnoreFile(std::wstring ignoreFileName);
	void startListenThread();
	bool isSyntaxError();
protected:
	void resetSyntaxError();
};

