/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	do{

		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//노드 p를 first로 둠

	listNode* prev = NULL;//이전 노드인 prev를 NULL로 둠
	while(p != NULL) {//p가 존재하는 동안
		prev = p;//이전노드 갱신
		p = p->link;//p를 다음 노드로
		free(prev);//prev 노드 해제
	}
	free(h);//headNode 메모리 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 하나 생성
	node->key = key;//노드 키값 설정

	node->link = h->first;//node->link=NULL
	h->first = node;//first를 노드로 설정

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	node->link=NULL;
	/* 노드 초기 설정*/

	listNode* cur;//탐색 노드
	listNode* prev;//탐색 노드의 이전 노드

	if(h->first==NULL)//first가 없으면
	{
		node->link=h->first;//node->link=NULL
		h->first=node;//노드를 first로 설정

	}
	else
	{
		cur=h->first;//탐색 노드 위치 first로 세팅
		prev=NULL;//이전노드는 NULL

		while(cur->link!=NULL)//탐색노드의 다음노드가 존재하는 동안
		{
			if(key<cur->key)//key값이 탐색한 노드의 키값보다 작으면
			{
				node->link=cur;//노드의 다음노드는 탐색 노드
				if(prev==NULL)//이전노드가 없으면(탐색노드 가 맨 앞 노드였으면)
				{
					h->first=node;//노드를 first로 설정
				}
				else//노드와 노드 사이에 넣는 경우(prev존재)
				{
					prev->link=node;//prev의 다음 노드를 노드로 설정
				}
				return 0;

			}

			prev=cur;//prev노드 갱신
			cur=cur->link;//탐색 노드 이동
		}

  /*마지막 노드에 도착했을때*/
		if(key<cur->key)//key값이 탐색한 노드의 키값보다 작으면(현재 마지막 노드 앞이 위치해야하는 경우)
		{
			node->link=cur;//노드의 다음 노드를 탐색노드로 설정
			if(prev==NULL)//이전 노드가 없는 경우
			{

				h->first=node;//노드를 first로 설정
			}
			else
			{
				prev->link=node;////prev의 다음 노드를 노드로 설정
			}
		}
		if(key>=cur->key)//키 값이 탐색 노드의 키값 보다 큰 경우
		{
			cur->link=node;//탐색 노드의 다음 노드를 노드로 설정
			node->link=NULL;//노드의 다음 노드는 NULL(노드는 마지막 노드)
			return 0;
		}


	}


	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	node->link=NULL;
	/* 노드 생성*/
	listNode* cur;//탐색 노드

	if(h->first==NULL)//first가 없다면
	{
		node->link=h->first;//노드의 다음 노드는 first
		h->first=node;//first를 노드로 설정
	}
	else
	{
		cur=h->first;//탐색 노드를 first로 설정
		while(cur->link!=NULL)//탐색 노드의 다음노드가 없을 때까지(마지막 노드까지)
		{
			cur=cur->link;//탐색노드를 다음으로 이동
		}

		cur->link=node;//탐색노드의 다음 노드를 노드로 설정
		node->link=NULL;//노드의 다음노드를 NULL로 설정

	}

	return 0;

}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	listNode* cur;//탐색노드 설정
	if(h->first!=NULL)//first가 존재하면
	{
		cur=h->first;//탐색노드를 first로 설정
		h->first=cur->link;//first를 탐색노드의 다음노드로 설정
		free(cur);//탐색노드 해제
		return 0;
	}

}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* cur;//탐색노드
	listNode* prev;//탐색 노드의 이전 노드
	if(h->first!=NULL)//first가 존재하면
	{
			cur=h->first;//탐색노드를 first로 설정
			prev=NULL;//이전 노드 NULL
			while(cur->link!=NULL)//탐색 노드의 다음 노드가 존재하는 동안
			{
				if(cur->key==key)//탐색노드의 키값이 찾는 값과 같으면
				{
					if(prev==NULL)//이전 노드가 존재하지 않으면(탐색 노드가 맨 앞이면)
					{
						h->first=cur->link;//탐색노드의 다음 노드를 first로 설정
						free(cur);//탐색노드 해제
					}
					else
					{
						prev->link=cur->link;//이전노드의 다음 노드는 탐색 노드의 다음 노드
						free(cur);//탐색 노드 해제
					}

					return 0;
				}

				prev=cur;//이전 노드 갱신
				cur=cur->link;//탐색 노드를 다음으로 이동
			}

			/*마지막 노드에 대한 처리*/
			if(cur->key==key)//만약 탐색노드 키값이 찾는 값과 같으면
			{
				if(prev==NULL)//prev가 존재하지 않으면
				{
					h->first=cur->link;//first를 탐색 노드의 다음 노드로 설정
					free(cur);//탐색 노드 해제
				}
				else
				{
					prev->link=cur->link;//이전노드의 다음 노드는 탐색 노드의 다음 노드로 설정
					free(cur);//탐색 노드 해제
				}
			}

			return 0;
	}

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* cur;//탐색 노드
	listNode* prev;//탐색 노드의 이전 노드
	if(h->first!=NULL)//first가 존재하면
	{
			cur=h->first;//탐색 노드를  first로 설정
			prev=NULL;//이전노드를 NULL로 설정
			while(cur->link!=NULL)//탐색 노드의 다음 노드가 존재하는 동안
			{
				prev=cur;//이전노드 갱신
				cur=cur->link;//탐색 노드 이동
			}

			prev->link=NULL;//이전노드의 다음 노드를 NULL로 설정
			free(cur);//탐색 노드 해제
			return 0;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode*cur;//탐색 노드
	listNode* prev;//탐색 노드의 이전 노드
	listNode* middle;//탐색 노드를 임시적으로 저장해놓을 노드

	if(h->first!=NULL)//fist가 존재하면
	{
		cur=h->first;//탐색 노드를 first로 설정
		middle=NULL;//middle을 NULL로 설정
		while(cur)//탐색 노드가 존재하는 동안
			{
				prev=middle;//이전 노드를 middle로 갱신
				middle=cur;//middle에 탐색 노드 값 저장
				cur=cur->link;//탐색 노드 이동
				middle->link=prev;//middle의 다음 노드를 이전 노드로 설정
			}

			h->first=middle;//first를 middle노드로 설정
			return 0;
	}

}

/* 리스트 출력*/
void printList(headNode* h) {
	int i = 0;//리스트 원소 번호
	listNode* p;//탐색 노드

	printf("\n---PRINT\n");

	if(h == NULL) {//Initialize 안한 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//탐색 노드를 first로 설정

	while(p != NULL) {//탐색 노드가 존재하는 동안
		printf("[ [%d]=%d ] ", i, p->key);//노드의 번호와 키값 출력
		p = p->link;//탐색 노드 이동
		i++;//번호 증가
	}

	printf("  items = %d\n", i);//원소 총 번호 출력
}

