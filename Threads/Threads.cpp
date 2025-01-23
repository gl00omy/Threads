// Threads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <stdio.h>

DWORD WINAPI DoWork(PVOID program) {
    printf("Worker thread: %u\n", GetCurrentThreadId());
    Sleep(3000);
    printf("Worker done\n");
    return 42;
}

int main()
{
    HANDLE hThread = CreateThread(nullptr, 0, DoWork, nullptr, 0, nullptr);

    printf("Main thread: %u\n", GetCurrentThreadId());

    WaitForSingleObject(hThread, INFINITE);
    DWORD code;
    GetExitCodeThread(hThread, &code);
    printf("Work done, Result=%u\n", code);
    CloseHandle(hThread);

    return 0;
}

