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
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {//singly linked list에서는 temp를 만들어서 리턴했다면 이번에는 h에 직접 연결한다(h값을 변경한다). 따라서 이중포인터 이용

	if(*h!=NULL)//만일 *h가 존재하면
	{
		freeList(*h);//*h를 해제한다(리스트 삭제)
	}

	*h=(headNode*)malloc(sizeof(headNode));//*h에 리스트 메모리 할당
	(*h)->first=NULL;//*h의 구조체멤버인 first를 초기화

	return 1;
}

int freeList(headNode* h){//이 함수에서는 단순하게 h값을 참조하고 있으므로 싱글포인터를 사용한다.

	listNode* p=h->first;//p를 first노드로 초기화
	listNode* prev=NULL;//이전노드 초기화

	while(p!=NULL)//p가 존재하는 동안
	{
		prev=p;//이전노드 갱신
		p=p->rlink;//p를 다음 노드로 이동
		free(prev);//이전 노드 삭제
	}

	free(h);//리스트 전체를 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//h가 NULL이면(리스트가 존재하지 않으면)
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//p를 first노드로 초기화

	while(p != NULL) {//P가 있는 동안
		printf("[ [%d]=%d ] ", i, p->key);//노드 인덱스와 키값 출력
		p = p->rlink;//노드 이동
		i++;//인덱스 값 증가
	}

	printf("  items = %d\n", i);//최대 인덱스 값
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	/* 노드 생성 및 초기화*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->rlink=NULL;
	newNode->llink=NULL;

	listNode* cur;//탐색 노드

	if(h->first==NULL)//first가 없으면
	{
		h->first=newNode;//새로 만든 노드가 first
	}
	else
	{
		cur=h->first;//탐색 노드가 first노드 가리키게 함
		while(cur->rlink!=NULL)//cur의 오른쪽 링크가 존재하는 동안
		{
			cur=cur->rlink;//탐색 노드 이동
		}

		cur->rlink=newNode;//탐색노드의 오른쪽 링크는 새로 만든노드
		newNode->llink=cur;//새로운 노드의 왼쪽 링크는 탐색노드

	}
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* cur;//탐색 노드
	listNode* prev;//이전 노드
	if(h->first!=NULL)//first가 존재하면
	{
		cur=h->first;//탐색 노드가 first를 가리키게 함
		prev=NULL;//이전 노드를 null로 초기화
		while(cur->rlink!=NULL)//탐색노드의 오른쪽 링크가 존재하는 동안
		{
			prev=cur;//이전노드 갱신
			cur=cur->rlink;//탐색 노드 이동
		}//탐색노드가 마지막 노드를 가리키게됨

		if(prev==NULL)//이전노드가 존재하지 않으면(탐색 노드가 맨 앞이면)
		{
			h->first=NULL;//노드가 없음
			free(cur);//탐색 노드 메모리 반환
		}
		else//이전노드가 존재하면(탐색 노드가 맨 앞이 아니면)
		{
			prev->rlink=NULL;//이전노드의 오른쪽 링크를 비운다
			free(cur);//탐색 노드 메모리 반환
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

	if(h->first==NULL)//first가 없으면
	{
		h->first=newNode;//first를 새로운 노드로 지정
	}
	else
	{
		newNode->rlink=h->first;//새로운 노드의 오른쪽 링크는 first
		h->first->llink=newNode;//first의 왼쪽 링크는 새로운 노드
		h->first=newNode;//first를 새로운 노드로 바꾼다
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* cur;//탐색 노드
	if(h->first!=NULL)//first가 존재하면
	{
		cur=h->first;//탐색노드가 first를 가리키게 함
		h->first=cur->rlink;//first를 탐색노드의 오른쪽 링크로 연결
		free(cur);//탐색노드 메모리 해제
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
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->rlink=NULL;
	newNode->llink=NULL;
	/* 노드 초기 설정*/

	listNode* cur;//탐색 노드
	listNode* prev;//탐색 노드의 이전 노드

	if(h->first==NULL)//first가 없으면
	{
		newNode->rlink=h->first;//node->link=NULL
		h->first=newNode;//노드를 first로 설정

	}
	else
	{
		cur=h->first;//탐색 노드 위치 first로 세팅
		prev=NULL;//이전노드는 NULL

		while(cur->rlink!=NULL)//탐색노드의 다음노드가 존재하는 동안
		{
			if(key<cur->key)//key값이 탐색한 노드의 키값보다 작으면
			{
				newNode->rlink=cur;//노드의 다음노드는 탐색 노드
				if(prev==NULL)//이전노드가 없으면(탐색노드 가 맨 앞 노드였으면)
				{
					cur->llink=newNode;//탐색노드의 왼쪽노드는 새로운노드
					h->first=newNode;//노드를 first로 설정
				}
				else//노드와 노드 사이에 넣는 경우(prev존재)
				{
					prev->rlink=newNode;//prev의 다음 노드를 노드로 설정
					newNode->llink=prev;
					cur->llink=newNode;

				}
				return 0;

			}

			prev=cur;//prev노드 갱신
			cur=cur->rlink;//탐색 노드 이동
		}

  /*마지막 노드에 도착했을때*/
		if(key<cur->key)//key값이 탐색한 노드의 키값보다 작으면(현재 마지막 노드 앞이 위치해야하는 경우)
		{
			newNode->rlink=cur;//노드의 다음 노드를 탐색노드로 설정
			if(prev==NULL)//이전 노드가 없는 경우
			{
				cur->llink=newNode;//탐색노드의 왼쪽노드는 새로운노드
				h->first=newNode;//노드를 first로 설정
			}
			else
			{
				prev->rlink=newNode;//prev의 다음 노드를 노드로 설정
				newNode->llink=prev;//새로운 노드의 왼쪽노드는 이전노드
				cur->llink=newNode;//탐색 노드의 이전 노드는 새로운 노드
			}
		}
		if(key>=cur->key)//키 값이 탐색 노드의 키값 보다 큰 경우
		{
			cur->rlink=newNode;//탐색 노드의 다음 노드를 노드로 설정
			newNode->rlink=NULL;//노드의 다음 노드는 NULL(노드는 마지막 노드)
			newNode->llink=cur;//새로운 노드의 왼쪽 노드는 탐색노드
			return 0;
		}


	}


	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* cur;//탐색노드
	listNode* prev;//이전노드

	if(h->first!=NULL)//first가 존재하면
	{
		cur=h->first;//탐색노드가 first가리킴
		prev=NULL;//이전노드 초기화
		while(cur->rlink!=NULL)//탐색 노드의 오른쪽 링크가 존재하는 동안
		{
			if(cur->key==key)//삭제할 노드를 찾으면
			{
				if(prev==NULL)//이전노드가 없으면(맨앞이면)
				{
					h->first=cur->rlink;//first를 탐색 노드의 오른쪽 링크노드로
					free(cur);//탐색노드 메모리 해제
				}
				else
				{
					prev->rlink=cur->rlink;//이전노드의 오른쪽 링크는 탐색노드의 오른쪽 링크
					free(cur);//탐색 노드 메모리 해제

				}

				return 0;
			}

			prev=cur;//이전노드 갱신
			cur=cur->rlink;//탐색 노드 이동
		}

		/*마지막 노드에서*/
		if(cur->key==key)//삭제할 노드 발견하면
		{
			if(prev==NULL)//이전노드 없으면(맨 앞이면)
			{
				h->first=cur->rlink;//first는 탐색 노드의 오른쪽 링크노드
				free(cur);//탐색노드 메모리 해제
			}
			else
			{
				prev->rlink=cur->rlink;//이전노드의 오른쪽 링크는 탐색 노드의 오른쪽 링크
				free(cur);//탐색노드 메모리 해제
			}
		}


	}
	return 0;
}

