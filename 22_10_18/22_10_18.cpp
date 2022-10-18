// 22_10_18.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//프로세스는 프로그램을 처리하기 위한 모든 것의 집합
//Thread는 고유의 레지스터와 stack 메모리를 가질 수 있다.

#define WIN32_LEAN_AND_MEAN //??
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //windows API를 사용하려면 반드시 포함

DWORD WINAPI ThreadFunc(LPVOID);// LPVOID ==> void*
//대부분의 대문자 단어는 마이크로소프트사가 정의한 자료형이다.

typedef struct complex { //복소수 구조체
    double real;
    double imag;

}Complex;




int main()
{
    HANDLE hThrd;
    DWORD threadId;

    Complex* ptr; //구조체에 포인터로 접근
    ptr = (Complex*)malloc(sizeof(Complex));
    ptr->real = 1.0;
    ptr->imag = 2.0;
    int i;                          // only one prime thread

    for (i = 0; i < 5; i++)
    {//make 5 worker thread
        ptr->real = i; ptr->imag= i;
        hThrd = CreateThread(NULL,   //security
            0,//stack size:default
            ThreadFunc,//함수 포인터
            (LPVOID)i,//함수의 매개변수, 단 하나만 허락 int인 i의 형변환을 시켜준다. LPVOID = 4byte => 크기는 그대로 
            CREATE_SUSPENDED, //0,   //dwCreationFunction
            &threadId); //시스템에서 고유한 thread id의 주소 

        if (hThrd)
        {
            printf("Thread launched %d\n", i);
            //CloseHandle(hThrd);
        }

    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    Sleep(2000);//2000->20000 모든 thread가 종료할 때까지 기다리기 

    ResumeThread(hThrd);
    Sleep(2000);
    //만약 프라이머리 thread가 끝나면 모든 그 thread가 생성한 모든 thread를 제거하고 종료한다.

    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID in) //thread함수는 무조건 LPVOID만 가능하고
{
    int i;
    //Complex* ptr = (Complex*)in; //LPVOID에서 complex로 입력 파라미터 형변환
    int n = (int)in;
    for (i = 0; i < 10; i++)//10->10000
        //printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
        printf("%d %d %d\n", n,n,n);
    return 0;
}