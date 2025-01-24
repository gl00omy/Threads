// Threads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <stdio.h>

DWORD WINAPI DoWork(PVOID program) {
    int data = *(int*)program;
    printf("Worker thread: %u\n", GetCurrentThreadId());
    Sleep(GetCurrentThreadId() / 5);
    printf("Worker done\n");
    return data * data;
}

int main()
{
    int x = 20; 
    HANDLE hThread = CreateThread(nullptr, 0, DoWork, &x, 0, nullptr);
    x = 10;
    HANDLE hThread2 = CreateThread(nullptr, 0, DoWork, &y, 0, nullptr);
    
    printf("Main thread: %u\n", GetCurrentThreadId());

    HANDLE h[] = { hThread, hThread2 };
    WaitForMultipleObjects(_countof(h), h, TRUE, INFINITE);
    DWORD sum = 0;
    for (int i = 0; i < _countof(h); i++) {
        DWORD code;
        GetExitCodeThread(h[i], &code);
        printf("Thread %u is done. Result+%u\n", GetThreadId(h[i]), code);
        sum += code;
        CloseHandle(h[i]);
    }

    printf("Work done, Total=%u\n", sum);

    return 0;
}

