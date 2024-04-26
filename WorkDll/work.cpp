#include "pch.h"
#include "work.h"

HMODULE hInstDll = NULL;
HHOOK g_Hook = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		::hInstDll = hModule;
		DllInit();//初始化DLL
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

VOID DllInit()
{
	//CreateThread(0, 0, FreeDllThread, 0, 0, 0);//等待卸载Dll
	//hCurrentProcessId = GetCurrentProcessId();
	//GetModuleFileName(NULL, szPath, _countof(szPath));
	//hWnd = FindWindow(_T("DebugView"), NULL);
	//TCHAR sz[MAX_PATH * 2];
	//StringCchPrintf(sz, _countof(sz), _T("DLL被加载！\t应用程序路径：%s"), szPath);
	//MyOutputDebugStringW(sz);
	
	wchar_t sz[100];
	std::swprintf(sz, _countof(sz), _T("赋能模块注入成功\n进程ID: %d"), GetCurrentProcessId());
	CAdvice::singleton->startListenThread();
	MessageBox(NULL, sz, _T("HelpUploadFiles"), MB_ICONINFORMATION);
}

// API 拦截
/**
 * @brief 用于拦截百度网盘 上传文件，排除指定文件
 * @param hFindFile 
 * @param lpFindFileData 
 * @return 默认状态返回原始值，遇到忽略状态跳过且自动查找下一个文件
*/
BOOL WINAPI MyFindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
{
	BOOL res = FindNextFileW(hFindFile, lpFindFileData);

	CAdvice* pAdvice = CAdvice::singleton;
	for (bool b = pAdvice->isMatch(lpFindFileData); res && !pAdvice->isSyntaxError() && b; b = pAdvice->isMatch(lpFindFileData)) {
		//MessageBox(NULL, lpFindFileData->cFileName, _T("提示"), MB_ICONINFORMATION);
		res = FindNextFileW(hFindFile, lpFindFileData); // 直接跳到下一个文件
	}
	return res;
}

/**
 * @brief 拦截 FindFirstFileW
 * @param lpFileName 
 * @param lpFindFileData 
 * @return 
*/
HANDLE WINAPI MyFindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
{
	HANDLE h = FindFirstFileW(lpFileName, lpFindFileData);
	//MessageBox(NULL, lpFindFileData->cFileName, _T("首个文件"), MB_ICONINFORMATION);

	//CAdvice* pAdvice = CAdvice::singleton;
	//for (bool b = pAdvice->isMatch(lpFindFileData); b; b = pAdvice->isMatch(lpFindFileData)) {
	//	FindNextFileW(h, lpFindFileData); // 直接跳到下一个文件
	//}

	return h;
}
// API 拦截

CAPIHook g_MyFindNextFile("Kernel32.dll", "FindNextFileW" , (PROC)MyFindNextFileW);
CAPIHook g_MyFindFirstFile("Kernel32.dll", "FindFirstFileW", (PROC)MyFindFirstFileW);