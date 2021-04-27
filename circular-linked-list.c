/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[이정민], [2018038030]---\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* 원형의 성질로 인해 앞 뒤에서 NULL검사를 안하는 것, 코드 표현의 용이
 더미노드 방식을 이용함으로써 노드가 비어있을때 앞에 넣는경우 중간에 넣는 경우 등등 여러 경우의수들을 따져서 구현하는 수고가 덜해짐 */



int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);


	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));//더미 노드 생성
	/*원형 리스트 초기상태*/
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;//키값이 무의미하다
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){/* h가 곧 리스트 구조 이므로 유실되어서는 안된다. */


	listNode* p = h->llink;//반복되기 전 끝에서 부터 시작한다.
	listNode* tmp;//임시 노드

	while (p != h)//탐색노드가 h가 아닌동안
	{
		tmp = p;//tmp에 탐색 노드 위치
		p = p->llink;//탐색 노드 이동
		free(tmp);//tmp 해제
	}

	free(h);//h해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//리스트가 없으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//탐색노드를 더미노드 다음 노드로 위치

	while(p != NULL && p != h) {//반복되기 전 마지막 노드까지
		printf("[ [%d]=%d ] ", i, p->key);//인덱스 값과 키값 출력
		p = p->rlink;//탐색 노드 이동
		i++;//인덱스 증가
	}
	printf("  items = %d\n", i);//총 인덱스


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//헤드 노드의 주소값, 왼쪽 노드 주솟값, 오른쪽 노드 주솟값

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {//반복되기 전 마지막 노드까지
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//헤드노드 이외의 노드 주솟값, 왼쪽 오른쪽 노드 주솟값
		p = p->rlink;//노드 이동
		i++;//인덱스 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	/* 노드 생성 및 초기화 */
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=h->rlink;//탐색 노드 위치를 더미노드 다음 노드로 위치
	while(cur->rlink!=h)//반복되기전 마지막 노드까지
	{
		cur=cur->rlink;//탐색 노드 이동
	}

	newNode->rlink=cur->rlink;//새로운 노드의 오른쪽은 탐색 노드의 오른쪽
	cur->rlink->llink=newNode;//탐색 노드 이후 노드의 왼쪽 링크는 새로운 노드
	cur->rlink=newNode;//탐색 노드의 오른쪽 링크는 새로운 노드
	newNode->llink=cur;//새로운 링크의 왼쪽 노드는 탐색 노드


	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* cur=h->rlink;//탐색노드를 더미노드 다음 노드로 위치
	while(cur->rlink!=h)//반복되기전 마지막 노드까지
	{
		cur=cur->rlink;//탐색 노드 이동
	}

		cur->llink->rlink=cur->rlink;//탐색 노드 왼쪽노드의 오른쪽 링크는 탐색 노드의 오른쪽 노드
		cur->rlink->llink=cur->llink;//탐색 노드의 오른쪽 노드의 왼쪽 링크는 탐색 노드의 왼쪽 링크
		if(cur!=h)//h의 유실 방지
		{
			free(cur);//탐색 노드를 해제
		}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	/*노드 생성 및 초기화 */
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	newNode->rlink=h->rlink;//새 노드의 오른쪽 링크는 더미노드의 오른쪽 노드
	h->rlink->llink=newNode;//더미노드의 오른쪽 노드의 왼쪽 링크는 새로운 노드
	h->rlink=newNode;//더미노드의 오른쪽 링크는 새로운 노드
	newNode->llink=h;//새로운 노드의 왼쪽 링크는 더미노드

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* cur=h->rlink;//탐색 노드를 더미노드의 다음 노드로 위치
	h->rlink=cur->rlink;//더미노드의 오른쪽 링크는 탐색 노드의 오른쪽 노드
	cur->rlink->llink=cur->llink;//탐색노드의 오른쪽 노드의 왼쪽 링크는 탐색 노드의 왼쪽 노드
	if(cur!=h)//h의 유실 방지
	{
		free(cur);//탐색노드 해제
	}

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	listNode* cur=h;//탐색 노드를 더미노드에 위치
	listNode* middle=NULL;//임시 노드 선언

	do//처음에 cur=h이지만 이때도 실행해야한다.
	{
		middle=cur->llink;//임시노드는 탐색노드의 왼쪽 노드
		cur->llink=cur->rlink;//탐색 노드의 왼쪽 링크는 탐색 노드의 오른쪽 노드
		cur->rlink=middle;//탐색 노드의 오른쪽 링크는 임시 노드
		cur=cur->llink;//탐색 노드 이동

	}while(cur!=h);




	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	/*노드 생성 및 초기화*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=h->rlink;//탐색노드를 더미노드 다음 노드로 지정
	while(cur->rlink!=h)//반복 되기전 마지막 노드까지
	{
		if(cur->key>key)//탐색노드의 키값이 새 노드의 키값보다 크면
		{
			newNode->rlink=cur;//새 노드의 오른쪽 링크는 탐색 노드
			cur->llink->rlink=newNode;//탐색노드의 왼쪽노드의 오른쪽 링크는 새로운 노드
			newNode->llink=cur->llink;//새로운 노드의 왼쪽 링크는 탐색 노드의 왼쪽 노드
			cur->llink=newNode;//탐색 노드의 왼쪽 링크는 새 노드
			return 0;
		}

		cur=cur->rlink;//노드 이동

	}

	/*반복 되기전 마지막 노드에서의 처리*/
	if(cur->key>key)//탐색 노드 키값이 새 노드 키값 보다 크면
	{
		newNode->rlink=cur;//새노드의 오른쪽 링크는 탐색 노드
		cur->llink->rlink=newNode;//탐색 노드의 왼쪽 노드의 오른쪽 링크는 새 노드
		newNode->llink=cur->llink;//새 노드의 왼쪽 링크는 탐색 노드의 왼쪽 링크
		cur->llink=newNode;//탐색 노드의 왼쪽 링크는 새로운 노드

	}
	else
	{
		newNode->rlink=cur->rlink;//새로운 노드의 오른쪽 링크는 탐색 노드의 오른쪽 노드
		cur->rlink->llink=newNode;//탐색 노드의 오른쪽 노드의 왼쪽 링크는 새 노드
		cur->rlink=newNode;//탐색 노드의 오른쪽 링크는 새 노드
		newNode->llink=cur;//새 노드의 왼쪽 링크는 탐색 노드

	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* cur=h->rlink;//탐색 노드를 더미노드 다음 노드로 지정
	while(cur->rlink!=h)//반복 되기 전 마지막 노드까지
	{
		if(cur->key==key)//키값을 찾으면
		{
			cur->llink->rlink=cur->rlink;//탐색 노드의 왼쪽 노드의 오른쪽 링크는 탐색 노드의 오른쪽 노드
			cur->rlink->llink=cur->llink;//탐색 노드의 오른쪽 노드의 왼쪽 링크는 탐색 노드의 왼쪽 노드
			if(cur!=h)//h의 유실 방지
			{
				free(cur);//탐색 노드 해제
			}
			return 0;
		}

		cur=cur->rlink;//노드 이동
	}

	//반복되기전 마지막 노드에서의 처리
	if(cur->key==key)//키값 찾으면
	{
		cur->llink->rlink=cur->rlink;//탐색 노드의 왼쪽 노드의 오른쪽 링크는 탐색 노드의 오른쪽 노드
		cur->rlink->llink=cur->llink;//탐색 노드의 오른쪽 노드의 왼쪽 링크는 탐색 노드의 왼쪽 노드
		if(cur!=h)//h의 유실 방지
		{
				free(cur);//탐색 노드 해제
		}

	}

	return 0;
}

