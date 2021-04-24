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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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


int initialize(headNode** h) {

	if(*h!=NULL)
	{
		freeList(*h);
	}

	*h=(headNode*)malloc(sizeof(headNode));
	(*h)->first=NULL;

	return 1;
}

int freeList(headNode* h){

	listNode* p=h->first;
	listNode* prev=NULL;

	while(p!=NULL)
	{
		prev=p;
		p=p->rlink;
		free(prev);
	}

	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->rlink=NULL;
	newNode->llink=NULL;

	listNode* cur;

	if(h->first==NULL)
	{
		h->first=newNode;
	}
	else
	{
		cur=h->first;
		while(cur->rlink!=NULL)
		{
			cur=cur->rlink;
		}

		cur->rlink=newNode;
		newNode->llink=cur;

	}
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode* cur;
	listNode* prev;
	if(h->first!=NULL)
	{
		cur=h->first;
		prev=NULL;
		while(cur->rlink!=NULL)
		{
			cur=cur->rlink;
		}

		if(prev==NULL)
		{
			h->first=NULL;
			free(cur);
		}
		else
		{
			prev->rlink=NULL;
			free(cur);
		}
	}

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	if(h->first==NULL)
	{
		h->first=newNode;
	}
	else
	{
		newNode->rlink=h->first;
		h->first->llink=newNode;
		h->first=newNode;
	}
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* cur;
	if(h->first!=NULL)
	{
		cur=h->first;
		h->first=cur->rlink;
		free(cur);
	}
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode* cur;
	listNode* prev;
	listNode* middle;

	if(h->first!=NULL)
	{
		cur=h->first;
		middle=NULL;
		while(cur!=NULL)
		{
			prev=middle;
			middle=cur;
			cur=cur->rlink;
			middle->rlink=prev;
		}

		h->first=middle;
	}
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur;
	listNode* prev;
	if(h->first==NULL)
	{
		h->first=newNode;
	}
	else
	{
		cur=h->first;
		prev=NULL;
		while(cur->rlink!=NULL)
		{
			if(cur->key>key)
			{
				newNode->rlink=cur;

				if(prev==NULL)
				{
					cur->llink=newNode;
					h->first=newNode;
				}
				else
				{
					prev->rlink=newNode;
					newNode->llink=prev;
					prev=newNode;
				}
			}

			prev=cur;
			cur=cur->rlink;
		}
		if(cur->key>key)
		{
			newNode->rlink=cur;

			if(prev==NULL)
			{
				prev=newNode;
				h->first=newNode;
			}
			else
			{
				prev->rlink=newNode;
				newNode->llink=prev;
				prev=newNode;
			}
			return 0;
		}
		if(cur->key<=key)
		{
			cur->rlink=newNode;
			newNode->llink=cur;
			return 0;
		}

	}
	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* cur;
	listNode* prev;

	if(h->first!=NULL)
	{
		cur=h->first;
		prev=NULL;
		while(cur->rlink!=NULL)
		{
			if(cur->key==key)
			{
				if(prev==NULL)
				{
					h->first=cur->rlink;
					free(cur);
				}
				else
				{
					prev->rlink=cur->rlink;
					cur->rlink->llink=prev;
					free(cur);

				}

				return 0;
			}

			prev=cur;
			cur=cur->rlink;
		}

		if(cur->key==key)
		{
			if(prev==NULL)
			{
				h->first=cur->rlink;
				free(cur);
			}
			else
			{
				prev->rlink=cur->rlink;
				free(cur);
			}
		}


	}
	return 0;
}
