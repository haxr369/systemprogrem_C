// �������� ���� �ڵ� ¥����
//************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
typedef struct node {
	int data;
	struct node* pNext;
} Node;
typedef struct linkedList {
	Node* pHead;
	HANDLE hMutex; //mutex ��� �߰�
	int dummy;
} LinkedList;

typedef struct listBucket {
	LinkedList* pLL1, * pLL2;
	int threds;
} ListBucket;

//�Լ� printLL()
//�Է�: Linked List�� ������
//���: ����
//�μ�ȿ��: ȭ�鿡 Linked List ������ ���� ����Ѵ�.
void printLL(LinkedList* pLL) {
	Node* pNode;
	pNode = pLL->pHead;
	while (pNode != NULL) {
		printf("data = %d\n", pNode->data);
		pNode = pNode->pNext;
	}
}
int countNode(LinkedList* pLL) {
	Node* pNode;
	pNode = pLL->pHead;
	int num = 0;
	while (pNode != NULL) {
		num++;
		pNode = pNode->pNext;
	}
	return num;
}
//�Լ� createNode()
//�Է�: ������(int)
//���: ����� ������
//�μ�ȿ��: ���� �޸��Ҵ��� ����Ͽ� �ϳ��� ��带 ����
Node* createNode(int num) {
	Node* pNode;
	pNode = (Node*)malloc(sizeof(Node));
	pNode->data = num;
	pNode->pNext = NULL;
	return pNode;
}
//�Լ� addHead()
//�Է�: linked list(������), ���(������)
//���: ����
//�μ�ȿ��: linked list �� �տ� �Է��� ��带 ����
void addHead(LinkedList* pLL, Node* pNode) {
	WaitForSingleObject(pLL->hMutex, INFINITE);
	pNode->pNext = pLL->pHead;
	pLL->pHead = pNode;
	ReleaseMutex(pLL->hMutex);
}
//�Լ� createLinkedList()
//�Է�: ����
//���: linked list(������)
//�μ�ȿ��: �����޸��Ҵ����� linked list���� ���
LinkedList* createLinkedList() {
	LinkedList* pLL;
	pLL = (LinkedList*)malloc(sizeof(LinkedList));
	pLL->pHead = NULL;
	pLL->hMutex = CreateMutex(NULL, FALSE, NULL); //mutex�ʱ�ȭ ó�� ����� ��� �ø�
	return pLL;
}
//�Լ� deleteHead()
//�Է�: Linked List(������)
//���: ����
//�μ�ȿ��: linked list�� �� ó�� ��带 ����
void deleteHead(LinkedList* pLL) {
	Node* pNode = pLL->pHead;
	if (pLL->pHead == NULL) return;
	pLL->pHead = pLL->pHead->pNext;
	free(pNode);
}
void swapLists(LinkedList* list1, LinkedList* list2, int thread) { //�ΰ��� ����Ʈ�� �����ͷ� ������
	LinkedList* tmp_list = createLinkedList();
	WaitForSingleObject(list1->hMutex, INFINITE);//possible context switch
	printf("========between line in thread %d\n ", thread);
	WaitForSingleObject(list2->hMutex, INFINITE);//possible context switch
	tmp_list->pHead = list1->pHead;
	list1->pHead = list2->pHead;
	list2->pHead = tmp_list->pHead;
	ReleaseMutex(list1->hMutex);
	ReleaseMutex(list2->hMutex);
}

//HW1_dead_lock : global variable�� ������� �ʴ� �ڵ带 �ۼ��ϼ���. ���� ����... 11.15�� 2�ñ���...

		//global for demo's sake!!! sorry  
DWORD WINAPI ThreadFunc1(LPVOID parm) { //n ��ſ� pLL�� ����ִ� ����ü�� �־�����Ѵ�..

	ListBucket* pLLs1 = (ListBucket*)parm;

	while (1) {
		printf("begin swapping in Thread%d\n", pLLs1->threds);
		swapLists(pLLs1->pLL1, pLLs1->pLL2, pLLs1->threds);
		printf("end swapping in Thread%d\n", pLLs1->threds);
	}

	return 0;
}

int main() {
	HANDLE hThrd[5];
	DWORD threadId;
	ListBucket* pLLs1, * pLLs2;
	pLLs1 = (ListBucket*)malloc(sizeof(ListBucket));
	pLLs2 = (ListBucket*)malloc(sizeof(ListBucket));

	LinkedList* pLL1, * pLL2;
	int i;
	pLL1 = createLinkedList();
	pLL2 = createLinkedList();
	pLLs1->pLL1 = pLL1;
	pLLs1->pLL2 = pLL2;
	pLLs1->threds = 1;

	pLLs2->pLL2 = pLL2;
	pLLs2->pLL1 = pLL1;
	pLLs2->threds = 2;

	addHead(pLL1, createNode((int)1));//pLL1�� data�� 1�� ��� �ϳ��� ������
	addHead(pLL2, createNode((int)2));//pLL2�� data�� 2�� ��� �ϳ��� ������
	printLL(pLL1);// ���: data = 1 
	swapLists(pLL1, pLL2, 100);
	printLL(pLL1);// ���: data = 2


	printf("�׽���\n");
	printLL(pLLs1->pLL1);
	printLL(pLLs1->pLL2);
	swapLists(pLLs1->pLL1, pLLs1->pLL2, 100);
	printLL(pLLs1->pLL1);
	printLL(pLLs1->pLL2);

	printf("thread %d", pLLs1->threds);

	hThrd[0] = CreateThread(NULL, 0, ThreadFunc1, (LPVOID)pLLs1, 0, &threadId);
	hThrd[1] = CreateThread(NULL, 0, ThreadFunc1, (LPVOID)pLLs2, 0, &threadId);

	WaitForMultipleObjects(2, hThrd, true, INFINITE); //�̰� ������ �����̸Ӹ� �����尡 �׳� �������� ���α׷��� ����������. �׷� ��� �����带 �����ϰ� ��.. �װ��� �����ϱ� ����
	for (i = 0; i < 5; i++) {
		CloseHandle(hThrd[i]);
	}
	printf("End of Program!!!\n");

	return EXIT_SUCCESS;
}