// 20211006mutithread.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
/*
 * Numbers.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 2, Listing 2-1
 *
 * Starts five threads and gives visible feedback
 * of these threads running by printing a number
 * passed in from the primary thread.
 *
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

 //createThread�Լ��� ���� ȣ��Ǵ� �Լ��� 
 //�ݵ�� �Ʒ��� ���� �Լ����� ������ �Ѵ�.
 //�� 1. �Ű������� �ϳ��̰� �ڷ����� LPVOID ��, void*
 //2.��ȯ�� DWORD
 //3. calling convention(�Լ�ȣ����) WINAPI
DWORD WINAPI ThreadFunc(LPVOID);// LPVOID ==> void*

int main()
{
    HANDLE hThrd;
    DWORD threadId;
    int i;

    for (i = 0; i < 5; i++)
    {
        hThrd = CreateThread(NULL,
            0,
            ThreadFunc,//�Լ� ������
            (LPVOID)i,//�Լ��� �Ű�����, �� �ϳ��� ���
            0,
            &threadId);
        if (hThrd)
        {
            printf("Thread launched %d\n", i);
            CloseHandle(hThrd);
        }
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    Sleep(2000);

    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    int i;
    int n = (int)in;
    for (i = 0; i < 10; i++)
        printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
    return 0;
}

