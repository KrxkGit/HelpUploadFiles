#include "framework.h"
#include "CInjectDll.h"

/*
* ��̬��Ա��ʼ��
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
			//AddText(GetDlgItem(hDlg, IDC_LIST1), _T("����: %u"), GetLastError());
			throw _T("�򿪽���ʧ��");
			return FALSE;
		}
		LPTHREAD_START_ROUTINE pfn = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32")), "LoadLibraryW");
		/*��ȡDLL����·��*/
		TCHAR sz[MAX_PATH] = _T("");
		GetModuleFileName(NULL, sz, _countof(sz));
		int cbSize = _countof(sz);
		for (LPTSTR p = &sz[cbSize]; *p != TEXT('\\'); p--, cbSize--);
		sz[cbSize + 1] = '\0';//�ض�
		StringCchPrintf(sz, _countof(sz), _T("%s%s"), sz, CInjectDll::dllName);
		/*��ȡDLL����·��*/
		PVOID pData = VirtualAllocEx(hProcess, NULL, _countof(sz) * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
		WriteProcessMemory(hProcess, pData, sz, _countof(sz) * sizeof(TCHAR), NULL);
		HANDLE newThread = CreateRemoteThread(hProcess, NULL, 0, pfn, pData, 0, NULL);
		if (newThread == NULL) {
			//AddText(GetDlgItem(hDlg, IDC_LIST1), _T("����: %u"), GetLastError());
			throw _T("����ע�븳��ģ��ʧ��");
		}
		WaitForSingleObject(newThread, INFINITE);//�ȴ��������
		VirtualFreeEx(hProcess, pData, 0, MEM_RELEASE);
		return TRUE;
	}
	catch (LPCTSTR p) {
		MessageBox(NULL, p, _T("�쳣"), MB_ICONERROR);
		return FALSE;
	}
}

VOID CInjectDll::DoInject(HWND hWnd)
{
	// ���Ұٶ����� ���� ����ȡ���� id
	//HWND hBaiduWnd = FindWindow(_T("DuiHostWnd"), NULL);
	GetWindowThreadProcessId(hWnd, &CInjectDll::dwProcessId);

	// �������߳�ע�� dll
	_beginthreadex(0, 0, CInjectDll::MyCreateRemoteThread, 0, 0, 0);
}