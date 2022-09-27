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
	int data;
	struct node* pNext;
} Node;


int main()
{
	


	//struct node a; // a라는 변수 이름의 node 자료구조의 메모리 확보.
	//Node a;

	Node* pNode, *pNode1, *pHead; //구조체 포인터 변수
	//static int n; // 정적 변수: 프로그램이 시작 할 때 메모리를 할당된다.	

	pNode = (Node*) malloc(sizeof(Node)); //malloc(원하는 바이트 수) 
										//=> 반환형이 void*(=니 마음대로 쓰라 but 형변환을 해라.) => 앞으로 pNode는  Node라는 구조를 사용하겠다.
										// pNode의 값은 Node의 주소
	pNode->data = 20; // Node의 값을 10
	pNode->pNext = NULL; // Node* 값이 NULL로
	printf("member variable a is %d\n", pNode->data);


	pNode1 = (Node*)malloc(sizeof(Node));
	pNode1->data = 100; 
	pNode1->pNext = pNode;     // pNode1 다음 노드는 pNode 노드로 가리킨다.

	pHead = pNode1;




	return 0;
}


