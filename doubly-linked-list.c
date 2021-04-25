/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[이정민], [2018038030]---\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			freeList(&headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {//singly linked list에서는 temp를 만들어서 리턴했다면 이번에는 h에 직접 연결한다(h값을 변경한다). 따라서 이중포인터 이용

	if(*h!=NULL) freeList(*h);//*h가 존재하면 *h값을 해제
	*h=(headNode*)malloc(sizeof(headNode));//*h에 메모리 할당(리스트 생성)
	(*h)->first=NULL;//first값 초기화
	return 1;
}

int freeList(headNode* h){//h의 값을 직접 변경하지 않고, 참조만 하여 사용,메모리해제에 p, prev를 이용하므로 싱글포인터를 이용한다.

	listNode* p=h->first;//탐색 노드를 헤드노드로 지정
	listNode* prev=NULL;//이전 노드 선언
	while(p!=NULL)//탐색 노드가 존재하는 동안
	{
		prev=p;//이전노드 갱신
		p=p->rlink;//탐색 노드 이동
		free(prev);//이전 노드 해제
	}
	free(h);//h 해제
	return 0;
}


void printList(headNode* h) {//연결리스트 출력
	int i = 0;
	listNode* p;//탐색 노드

	printf("\n---PRINT\n");

	if(h == NULL) {//리스트가 없다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//탐색노드를 헤드에 위치

	while(p != NULL) {//노드가 존재하는동안
		printf("[ [%d]=%d ] ", i, p->key);//인덱스와 노드의 키값 출력
		p = p->rlink;//노드 이동
		i++;//인덱스 증가
	}

	printf("  items = %d\n", i);//최대 인덱스 값 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	/* 노드 생성 및 초기화*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=NULL;//탐색노드 선언
	if(h->first==NULL)//노드가 없으면
	{
		h->first=newNode;//헤드노드를 새로운 노드로 할당
	}
	else
	{
		cur=h->first;//탐색노드를 헤드에 위치
		while(cur->rlink!=NULL)//마지막 노드까지
		{
			cur=cur->rlink;//노드 이동
		}

		cur->rlink=newNode;//탐색 노드의 오른쪽 노드는 새로운 노드
		newNode->llink=cur;//새로운 노드의 왼쪽 노드는 탐색노드

	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* cur=NULL;//탐색 노드 선언
	if(h->first!=NULL)//노드가 존재하면
	{
		cur=h->first;//탐색노드를 헤드에 위치
		while(cur->rlink!=NULL)//마지막 노드까지
		{
			cur=cur->rlink;//노드 이동
		}
		if(cur->llink==NULL)//탐색 노드의 왼쪽 노드가 없으면(노드가 유일)
		{
			h->first=NULL;//헤드노드를 비움
			free(cur);//탐색노드 해제
		}
		else
		{
			cur->llink->rlink=NULL;//탐색노드 왼쪽 노드의 다음 노드를 비움
			free(cur);//탐색 노드 해제
		}
	}


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	/* 노드 생성 및 초기화*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	if(h->first==NULL)//헤드 노드가 없다면
	{
		h->first=newNode;//새로운 노드를 헤드에 위치
	}
	else
	{
		newNode->rlink=h->first;//새로운 노드의 다음 노드는 헤드노드
		h->first->llink=newNode;//헤드노드의 이전노드는 새로운노드
		h->first=newNode;//헤드노드를 새로운 노드로 지정
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* cur=NULL;//탐색 노드 선언
	if(h->first!=NULL)//노드가 존재하면
	{
		cur=h->first;//탐색노드를 헤드노드로 위치
		h->first=cur->rlink;//헤드노드를 탐색 노드의 다음노드로 변경
		if(h->first!=NULL)//헤드노드가 존재하면
		{
			h->first->llink=NULL;//헤드노드의 이전노드를 비움
		}
		free(cur);//탐색 노드 메모리 해제
	}
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* cur;//탐색노드
	listNode* middle;//임시로 저장할 노드

		if(h->first!=NULL)//first가 존재하면
		{
			cur=h->first;//탐색노드가 first를 가리킴
			middle=NULL;//임시노드를 NULL로 초기화
			while(cur!=NULL)//cur이 존재하는 동안
			{
				middle=cur->llink;//임시 노드에 탐색 노드의 왼쪽 링크를 저장
				cur->llink=cur->rlink;//탐색노드의 왼쪽 링크는 탐색 노드의 오른쪽 링크
				cur->rlink=middle;//탐색 노드의 오른쪽 링크는 임시노드
				cur=cur->llink;//탐색 노드 이동

			}

			h->first=middle->llink;//first는 임시노드의 왼쪽 링크
		}
		return 0;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	/*노드 생성 및 초기화*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=NULL;//탐색 노드 선언
	if(h->first==NULL)//노드가 없으면
	{
		h->first=newNode;//새로운 노드를 헤드로 지정
	}
	else
	{
		cur=h->first;//탐색 노드가 헤드를 가리킴
		while(cur->rlink!=NULL)//마지막 노드까지
		{
			if(cur->key>key)//탐색 노드의 키값이 새로운 노드의 키값보다 크면
			{
				newNode->rlink=cur;//새로운 노드의 다음 노드는 탐색노드
				if(cur->llink==NULL)//탐색 노드의 이전노드가 없으면(맨 앞이면)
				{
					cur->llink=newNode;//탐색 노드의 이전노드는 새로운 노드
				}
				else
				{
					cur->llink->rlink=newNode;//탐색노드의 왼쪽 노드의 다음 노드는 새로운 노드
					newNode->llink=cur->llink;//새로운 노드의 이전노드는 탐색 노드의 이전노드
					cur->llink=newNode;//탐색 노드의 이전노드는 새로운 노드
				}
				return 0;
			}
			cur=cur->rlink;//노드 이동
		}

		/* 마지막 노드에서의 처리*/
		if(cur->key>key)//탐색 노드의 키값이 새로운 노드의 키값보다 크면(마지막 노드 앞에 삽입하는 경우)
		{
			newNode->rlink=cur;//새로운 노드의 다음 노드는 탐색 노드
			if(cur->llink==NULL)//탐색노드의 이전노드가 없으면(노드가 유일하면)
			{
				cur->llink=newNode;//탐색노드의 이전노드는 새로운 노드
			}
			else
			{
				cur->llink->rlink=newNode;//탐색노드의 왼쪽노드의 다음 노드는 새로운 노드
				newNode->llink=cur->llink;//새로운 노드의 왼쪽 노드는 탐색 노드의 이전 노드
				cur->llink=newNode;//탐색 노드의 이전노드는 새로운 노드
			}
		}

		if(cur->key<=key)//탐색노드의 키값이 새 노드보다 작거나 같으면(맨뒤에 삽입하는 경우)
		{
			cur->rlink=newNode;//탐색 노드의 다음 노드는 새로운 노드
			newNode->llink=cur;//새로운 노드의 이전 노드는 탐색 노드
		}

	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* cur=NULL;//탐색 노드 선언
	if(h->first!=NULL)//헤드 노드가 존재하면
	{
		cur=h->first;//탐색노드를 헤드노드로 지정
		while(cur->rlink!=NULL)//마지막 노드까지
		{
			if(cur->key==key)//삭제 노드를 찾으면
			{
				if(cur->llink==NULL)//탐색 노드의 이전 노드가 없으면(맨 앞이면)
				{
					h->first=cur->rlink;//헤드노드는 탐색 노드의 다음노드
					if(h->first!=NULL)//헤드노드가 존재하면
					{
						h->first->llink=NULL;//헤드노드의 이전노드를 비움
					}
					free(cur);//탐색 노드 해제
				}
				else
				{
					cur->llink->rlink=cur->rlink;//탐색노드의 왼쪽노드의 다음노드는 탐색 노드의 다음 노드
					if(cur->rlink!=NULL)//탐색 노드의 다음 노드가 존재하면
					{
						cur->rlink->llink=cur->llink;//탐색 노드의 다음노드의 왼쪽 노드는 탐색노드의 왼쪽노드
					}
					free(cur);//탐색 노드 해제
				}

				return 1;
			}

			cur=cur->rlink;//노드 이동
		}

		/* 마지막 노드에서의 처리*/
		if(cur->key==key)//삭제할 노드를 찾으면
		{
			if(cur->llink==NULL)//탐색노드의 왼쪽 노드가 없으면(유일한 노드)
			{
				h->first=cur->rlink;//헤드노드는 탐색 노드의 다음노드
				if(h->first!=NULL)//헤드노드가 존재하면
				{
					h->first->llink=NULL;//헤드노드의 이전노드를 비움
				}
				free(cur);//탐색 노드 해제
			}
			else
			{
				cur->llink->rlink=cur->rlink;//탐색 노드의 왼쪽 노드의 다음 노드는 탐색 노드의 다음 노드
				if(cur->rlink!=NULL)//탐색 노드의 다음 노드가 존재하면
				{
					cur->rlink->llink=cur->llink;//탐색노드의 다음노드의 왼쪽 노드는 탐색 노드의 이전노드
				}
				free(cur);//탐색노드 해제
			}


		}
	}

	return 1;
}

