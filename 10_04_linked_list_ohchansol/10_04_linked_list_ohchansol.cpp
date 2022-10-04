#include <stdio.h>
#include <stdlib.h>
//struct node {
//	int data;
//	struct node* pNext;
//
//
//};
//typedef struct node Node;


typedef struct node {
	int data;				//사용자가 원하는 데이터
	struct node* pNext;		//다음 데이터의 주소
} Node;


void printLL(Node* pHead) {
	Node* pNode = pHead;  //pNode를 초기화
	while (pNode != NULL) {
		printf("data = %d\n", pNode->data); //현재 pNdoe의 데이터 출력
		pNode = pNode->pNext;			    // pNode를 다음 노드의 주소로 update
	}
}
//함수 :creatNode()
//입력 : 데이터 값
//출력 : 노드를 생성해 그 포인터를 반환 데이터 값은 입력값 pNext는 NULL.

Node* createNode(int val) {
	Node* pNode = (Node*)malloc(sizeof(Node));  //malloc(원하는 바이트 수) //힙영역
	//=> 반환형이 void*(=니 마음대로 쓰라 but 형변환을 해라.) => 앞으로 pNode는  Node라는 구조를 사용하겠다.
	// pNode의 값은 Node크기의 메모리 주소
	//Node node;
	//Node* pNode = &node;  // 스택영역=> 스택영역은 함수 콜 할 때마다 업데이트된다.
	pNode->data = val;  //data에 value를 집어넣는다. 
	pNode->pNext = NULL;  // Node* 값이 NULL로 pNode는 tail node와 같다.
	return pNode;
}


//함수 : insertHead()
//입력 : int val, Node* pHead
//출력 : x

void insertHead(int val, Node** ppHead) { //포이터 변수의 주소값을 stack에 입력
	Node* pNode = createNode(val);  //새로운 노드를 생성
	pNode->data = val;
	pNode->pNext = *ppHead; //step1 ppHead가 가리키는 포인터를 pNext에 입력
	*ppHead = pNode;		  //step2  ppHead가 가리키는 포인터에 pNode값 입력
}


int main()
{
	//struct node a; // a라는 변수 이름의 node 자료구조의 메모리 확보.
	//Node a;

	Node* pNode, * pNode1, * pHead; //구조체 포인터 변수
	//static int n; // 정적 변수: 프로그램이 시작 할 때 메모리를 할당된다.	


	pHead = NULL;  //pHead가 NULL이면 linked list가 빈것이라 약속
	pHead = createNode(10);  //pHead는 포인터 변수 => 현재는 스택영역을 가리킴 문제 발생 

	insertHead(100, &pHead); //포인트 변수의 주소값 입력
	//pHead->pNext->pNext; //NULL이 나온다. 왜? ->는 왼쪽 부터 연산하기 때문에
	printf("인서트 결과");
	printLL(pHead);

	printf("Program Ends");

	return 0;
}