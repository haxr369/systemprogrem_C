// 20211103linkedlist.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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

 //구조체 Node
typedef struct node {
    int data;
    struct node* pNext;
} Node;
//함수: createNode()
//입력: data 값
//출력: 생성한 노드의 포인터, 
//노드의 데이터값은 입력값, pNext = NULL
Node* createNode(int value) {
    Node* ptr;
    ptr = (Node*)malloc(sizeof(Node));
    ptr->data = value;
    ptr->pNext = NULL;
    return ptr;
}
void printLL(Node* pHead) {
    Node* ptr = pHead;
    while (ptr != NULL) {
        printf("data = %d\n", ptr->data);
        ptr = ptr->pNext;
    }
}
//함수: countNode()
//입력: pHead
//출력: 노드 갯수
int countNode(Node* pHead) {
    Node* ptr = pHead;
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->pNext;
    }
    return count;
}
//함수: insertHead()
//입력: 헤드노드포인터, 새 노드 포인터
//출력: 없음
void insertHead(Node** ppHead, Node* newNode) {
    newNode->pNext = *ppHead; //#1
    *ppHead = newNode; //#2
}

DWORD WINAPI ThreadFunc(LPVOID);// LPVOID ==> void*

int main()
{
    HANDLE hThrd[5];
    DWORD threadId;
    int i;
    Node* pHead = NULL;

    for (i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL,//스레드KO(kernel object) 생성 후 핸들을 반환한다.
            0,
            ThreadFunc,//함수 포인터
            (LPVOID)&pHead,//함수의 매개변수, 단 하나만 허락
            0,
            &threadId);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
            //CloseHandle(hThrd);
        }
        else { //스레드 생성에 실패하면 hThrd == NULL
            printf("error creating a thread\n ");
            return 0;
        }
    }
    WaitForMultipleObjects(5, hThrd, TRUE, INFINITE);//모든 스레드가 종료되어야 넘어간다.
    for (i = 0; i < 5; i++) {
        CloseHandle(hThrd[i]);//1.스레드 실행 종료 2. CloseHandle() 스레드 KO를 소멸
    }
    //ThreadFunc(&pHead);
    printf("the number of Nodes is %d\n", countNode(pHead));
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID ptr)
{

    Node** ppHead = (Node**)ptr;     //void를 node 구조체로 변환
    for (int i = 0; i < 1000000; i++)
        insertHead(ppHead, createNode(100));
    return 0;
}

