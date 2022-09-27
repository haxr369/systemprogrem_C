#include <stdio.h>

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
	static int n; // 정적 변수: 프로그램이 시작 할 때 메모리를 할당된다.	


	//struct node a; // a라는 변수 이름의 node 자료구조의 메모리 확보.
	Node a;
	a.data = 10;  // a 노드에 데이터는 10
	a.pNext = NULL; // a 노드에 포인터는 없음.

	Node* pNode; //구조체 포인터 변수
	pNode = &a;         //adress of a = pNode
	printf("member variable a is %d\n", pNode->data);



	return 0;
}


