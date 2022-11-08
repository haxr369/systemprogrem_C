﻿// mutex를 사용해서 deadlock을 방지하는 솔루션을 만들어보자!!!
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
//함수 createNode()
//입력: 데이터(int)
//출력: 노드의 포인터
//부수효과: 동적 메모리할당을 사용하여 하나의 노드를 생성
Node* createNode(int num) {
	Node* pNode;
	pNode = (Node*)malloc(sizeof(Node));
	pNode->data = num;
	pNode->pNext = NULL;
	return pNode;
}
//함수 addHead()
//입력: linked list(포인터), 노드(포인터)
//출력: 없음
//부수효과: linked list 맨 앞에 입력한 노드를 삽입
void addHead(LinkedList* pLL, Node* pNode) {
	EnterCriticalSection(&pLL->critical_sec);
	pNode->pNext = pLL->pHead;
	pLL->pHead = pNode;
	LeaveCriticalSection(&pLL->critical_sec);
}
//함수 createLinkedList()
//입력: 없음
//출력: linked list(포인터)
//부수효과: 동적메모리할당으로 linked list공간 사용
LinkedList* createLinkedList() {
	LinkedList* pLL;
	pLL = (LinkedList*)malloc(sizeof(LinkedList));
	pLL->pHead = NULL;
	InitializeCriticalSection(&pLL->critical_sec);
	return pLL;
}
//함수 deleteHead()
//입력: Linked List(포인터)
//출력: 없음
//부수효과: linked list의 맨 처음 노드를 삭제
void deleteHead(LinkedList* pLL) {
	Node* pNode = pLL->pHead;
	if (pLL->pHead == NULL) return;
	pLL->pHead = pLL->pHead->pNext;
	free(pNode);
}
void swapLists(LinkedList* list1, LinkedList* list2, int thread) { //두개의 리스트를 포인터로 가져옴
	LinkedList* tmp_list = createLinkedList();
	EnterCriticalSection(&list1->critical_sec);//possible context switch
	printf("========between line in thread %d\n ", thread);
	EnterCriticalSection(&list2->critical_sec);
	tmp_list->pHead = list1->pHead;
	list1->pHead = list2->pHead;
	list2->pHead = tmp_list->pHead;
	LeaveCriticalSection(&list1->critical_sec);
	LeaveCriticalSection(&list2->critical_sec);
}

//HW1_dead_lock : global variable을 사용하지 않는 코드를 작성하세요. 개인 웹에... 11.15일 2시까지...

LinkedList* pLL1, * pLL2;			//global for demo's sake!!! sorry  
DWORD WINAPI ThreadFunc1(LPVOID n) { //n 대신에 pLL을 담고있는 구조체를 넣어줘야한다..
	while (1) {
		printf("begin swapping in Thread11111\n");
		swapLists(pLL1, pLL2, 1);
		printf("end swapping in Thread11111\n");
	}
	return 0;
}
DWORD WINAPI ThreadFunc2(LPVOID n) {
	while (1) {
		printf("begin swapping in Thread22222\n");
		swapLists(pLL2, pLL1, 2);
		printf("end swapping in Thread22222\n");
	}
	return 0;
}
int main() {
	HANDLE hThrd[5];
	DWORD threadId;
	int i = 0;
	pLL1 = createLinkedList();
	pLL2 = createLinkedList();
	addHead(pLL1, createNode((int)1));//pLL1은 data가 1인 노드 하나를 가진다
	addHead(pLL2, createNode((int)2));//pLL2는 data가 2인 노드 하나를 가진다
	printLL(pLL1);// 출력: data = 1 
	swapLists(pLL1, pLL2, 100);
	printLL(pLL1);// 출력: data = 2

	hThrd[0] = CreateThread(NULL, 0, ThreadFunc1, (LPVOID)i, 0, &threadId);
	hThrd[1] = CreateThread(NULL, 0, ThreadFunc2, (LPVOID)i, 0, &threadId);

	WaitForMultipleObjects(2, hThrd, true, INFINITE); //이게 없으면 프라이머리 스레드가 그냥 지나가서 프로그램이 끝나버린다. 그럼 모든 스레드를 제거하고 끝.. 그것을 방지하기 위함
	for (i = 0; i < 5; i++) {
		CloseHandle(hThrd[i]);
	}
	printf("End of Program!!!\n");

	return EXIT_SUCCESS;
}