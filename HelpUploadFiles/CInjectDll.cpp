#include "framework.h"
#include "CInjectDll.h"

/*
* 静态成员初始化
*/
DWORD CInjectDll::dwProcessId = 0;
LPCWSTR CInjectDll::dllName = _T("WorkDll.dll");

UINT CALLBACK CInjectDll::MyCreateRemoteThread(LPVOID pParam)
{
	try {
		HWND hDlg = (HWND)pParam;
		HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION,
			FALSE, CInjectDll::dwProcessId);
		if (hProcess == NULL) {
			//AddText(GetDlgItem(hDlg, IDC_LIST1), _T("错误: %u"), GetLastError());
			throw _T("打开进程失败");
			return FALSE;
		}
		LPTHREAD_START_ROUTINE pfn = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32")), "LoadLibraryW");
		/*获取DLL绝对路径*/
		TCHAR sz[MAX_PATH] = _T("");
		GetModuleFileName(NULL, sz, _countof(sz));
		int cbSize = _countof(sz);
		for (LPTSTR p = &sz[cbSize]; *p != TEXT('\\'); p--, cbSize--);
		sz[cbSize + 1] = '\0';//截断
		StringCchPrintf(sz, _countof(sz), _T("%s%s"), sz, CInjectDll::dllName);
		/*获取DLL绝对路径*/
		PVOID pData = VirtualAllocEx(hProcess, NULL, _countof(sz) * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
		WriteProcessMemory(hProcess, pData, sz, _countof(sz) * sizeof(TCHAR), NULL);
		HANDLE newThread = CreateRemoteThread(hProcess, NULL, 0, pfn, pData, 0, NULL);
		if (newThread == NULL) {
			//AddText(GetDlgItem(hDlg, IDC_LIST1), _T("错误: %u"), GetLastError());
			throw _T("尝试注入赋能模块失败");
		}
		WaitForSingleObject(newThread, INFINITE);//等待载入完成
		VirtualFreeEx(hProcess, pData, 0, MEM_RELEASE);
		return TRUE;
	}
	catch (LPCTSTR p) {
		MessageBox(NULL, p, _T("异常"), MB_ICONERROR);
		return FALSE;
	}
}

VOID CInjectDll::DoInject(HWND hWnd)
{
	// 查找百度网盘 窗口 并获取进程 id
	//HWND hBaiduWnd = FindWindow(_T("DuiHostWnd"), NULL);
	GetWindowThreadProcessId(hWnd, &CInjectDll::dwProcessId);

	// 开启新线程注入 dll
	_beginthreadex(0, 0, CInjectDll::MyCreateRemoteThread, 0, 0, 0);
}