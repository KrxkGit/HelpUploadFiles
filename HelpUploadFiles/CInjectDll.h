#pragma once
class CInjectDll
{
private:
	static LPCWSTR dllName;
	static DWORD dwProcessId;
	static UINT CALLBACK MyCreateRemoteThread(LPVOID pParam);
public:
	static VOID DoInject(HWND hWnd);
};

