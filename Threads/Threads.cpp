// Threads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <stdio.h>

DWORD WINAPI DoWork(PVOID program) {
    int data = *(int*)program;  // dereference the pointer to get the integer value passed from the main thread
    printf("Worker thread: %u\n", GetCurrentThreadId());//print the ID of current Worker thread
    Sleep(GetCurrentThreadId() / 5);//randomization based on thread ID
    printf("Worker done\n");
    return data * data;
}

int main()
{
    int x = 20; 
    HANDLE hThread = CreateThread(nullptr, 0, DoWork, &x, 0, nullptr);
    x = 10; //changing the value of x, which result in having the same value due to passing by reference and order of function being called and executed
    HANDLE hThread2 = CreateThread(nullptr, 0, DoWork, &x, 0, nullptr);
    
    printf("Main thread: %u\n", GetCurrentThreadId()); //main thread ID

    HANDLE h[] = { hThread, hThread2 };//array of created threads for future convenience
    WaitForMultipleObjects(_countof(h), h, TRUE, INFINITE);//we use waitforMULTIPLEobjects when create multiple threads
    DWORD sum = 0;
    for (int i = 0; i < _countof(h); i++) {//looping multiple threads
        DWORD code;
        GetExitCodeThread(h[i], &code); // Get the exit code of the thread (i.e., the value returned from DoWork)
        printf("Thread %u is done. Result+%u\n", GetThreadId(h[i]), code);//print result from each thread with thread ID and return value
        sum += code;//sum results of each thread
        CloseHandle(h[i]);
    }

    printf("Work done, Total=%u\n", sum);

    return 0;
}

