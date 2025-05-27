#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

typedef NTSTATUS(NTAPI* pNtResumeProcess)(
    HANDLE ProcessHandle
    );

typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);

void suspend(HANDLE processHandle)
{
    NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(
        GetModuleHandle(L"ntdll"), "NtSuspendProcess");

    pfnNtSuspendProcess(processHandle);
}

void resume(HANDLE processHandle)
{
    HMODULE hNtdll = GetModuleHandle(L"NTDLL");
    pNtResumeProcess pfnNtSuspendProcess = (pNtResumeProcess)GetProcAddress(hNtdll,
        "NtResumeProcess");
    pfnNtSuspendProcess(processHandle);
}

BOOL SetDebugPrivilege() {
    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES TokenPrivileges = { 0 };

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken)) {
        printf("Could not get current process token with TOKEN_ADJUST_PRIVILEGES\n");
        return FALSE;
    }

    TokenPrivileges.PrivilegeCount = 1;
    TokenPrivileges.Privileges[0].Attributes = TRUE ? SE_PRIVILEGE_ENABLED : 0;

    char sPriv[] = { 'S','e','D','e','b','u','g','P','r','i','v','i','l','e','g','e',0 };
    if (!LookupPrivilegeValueA(NULL, (LPCSTR)sPriv, &TokenPrivileges.Privileges[0].Luid)) {
        CloseHandle(hToken);
        printf("Run as admin\n");
        return FALSE;
    }

    if (!AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        CloseHandle(hToken);
        return FALSE;
    }

    CloseHandle(hToken);
    return TRUE;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
        return(FALSE);

    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32))
    {
        CloseHandle(hThreadSnap);
        return(FALSE);
    }

    do
    {
        std::cout << te32.th32ThreadID << "\n" << te32.th32OwnerProcessID << "\n";
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return(TRUE);
}

int main()
{
    if (!SetDebugPrivilege()) {
        std::cout << "Failed to set debug privilege";
        return 0;
    }
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(entry);
        if (Process32First(snapshot, &entry)) {
            do {
                if (std::wstring(entry.szExeFile) == L"RobloxPlayerBeta.exe") { // you could technically suspend anything
                    processId = entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &entry));
        }
        CloseHandle(snapshot);
    };

    if (processId != 0) {
        //std::cout << ListProcessThreads(processId);
        HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        if (processHandle == NULL) {
            return FALSE;
        }
        suspend(processHandle);
        CloseHandle(processHandle);
    }

    return 0;
}
