//  멀티쓰레드 만들거에요..
// 최중호 교수님 시스템 프로그래밍 OS concepts를 꼭 보자!!!

// 20211027multithread.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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
#include <windows.h>         //마이크로소프트에서 제공한 라이브러리

 //createThread함수에 의해 호출되는 함수는 
 //반드시 아래와 같은 함수형을 가져야 한다.
 //즉 1. 매개변수는 하나이고 자료형은 LPVOID 즉, void*
 //2.반환형 DWORD
 //3. calling convention(함수호출방법) WINAPI    LPVOID : LP== long pointer, Long= 16bit 포인터 이상의 포인터를 사용하기 위해서 
DWORD WINAPI ThreadFunc(LPVOID);// LPVOID ==> void*  WINAPI : 2주전에 정리했을거야, 출력:DWORD, calling convention=WINAPI,입력은 LPVOID
// 대부분의 대문자 단어는 마이크로소프트사가 정의한 자료형이다.
int main()
{
    HANDLE hThrd;
    DWORD threadId;
    int i;

    for (i = 0; i < 5; i++)
    {
        hThrd = CreateThread(NULL,    //맨날 NULL을 사용한다. 함수의 설명을 알고싶으면 F1을 누른다.
            0,
            ThreadFunc,//함수 포인터
            (LPVOID)i,//함수의 매개변수, 단 하나만 허락
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
