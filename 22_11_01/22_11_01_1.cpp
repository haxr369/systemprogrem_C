// 20211110criticalsection.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
// 20211103linkedlist.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

/*
1. Linked list ����ü ����
2. ��� �Լ� ������
3. race condition ����
4. critical setion�� ����� ����ȭ
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

 //����ü Node
typedef struct node {
    int data;
    struct node* pNext;
} Node;
//����ü List
typedef struct list {
    Node* pHead;
} List;
//�Լ�: createNode()
//�Է�: data ��
//���: ������ ����� ������, 
//����� �����Ͱ��� �Է°�, pNext = NULL
Node* createNode(int value) {
    Node* ptr;
    ptr = (Node*)malloc(sizeof(Node));
    ptr->data = value;
    ptr->pNext = NULL;
    return ptr;
}
void printLL(List* pList) {
    Node* ptr = pList->pHead;
    while (ptr != NULL) {
        printf("data = %d\n", ptr->data);
        ptr = ptr->pNext;
    }
}
//�Լ�: countNode()
//�Է�: pHead
//���: ��� ����
int countNode(List* pList) {
    Node* ptr = pList->pHead;
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->pNext;
    }
    return count;
}
//�Լ�: insertHead()
//�Է�: �����������, �� ��� ������
//���: ����
void insertHead(List* pList, Node* newNode) {
    newNode->pNext = pList->pHead; //#1
    pList->pHead = newNode; //#2
}

DWORD WINAPI ThreadFunc(LPVOID);// LPVOID ==> void*

int main()
{
    HANDLE hThrd[5];
    DWORD threadId;
    int i;
    List list;
    List* pList = &list;
    pList->pHead = NULL;
    clock_t start = clock();

    for (i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL,//������KO(kernel object) ���� �� �ڵ��� ��ȯ�Ѵ�.
            0,
            ThreadFunc,//�Լ� ������
            (LPVOID)pList,//�Լ��� �Ű�����, �� �ϳ��� ���
            0,
            &threadId);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
            //CloseHandle(hThrd);
        }
        else { //������ ������ �����ϸ� hThrd == NULL
            printf("error creating a thread\n ");
            return 0;
        }
    }
    WaitForMultipleObjects(5, hThrd, TRUE, INFINITE);//��� �����尡 ����Ǿ�� �Ѿ��.
    for (i = 0; i < 5; i++) {
        CloseHandle(hThrd[i]);//1.������ ���� ���� 2. CloseHandle() ������ KO�� �Ҹ�
    }
    //ThreadFunc(&pHead);
    printf("the number of Nodes is %d\n", countNode(pList));
    clock_t end = clock();
    double time = double(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ
    printf("����ð� : %0.3lf\n", time); //�Ҽ��� ��° �ڸ�����
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID ptr)
{

    List* pList = (List*)ptr;
    for (int i = 0; i < 1000000; i++)
        insertHead(pList, createNode(100));
    return 0;
}

