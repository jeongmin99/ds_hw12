/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];

/* 원형 큐로 구현 */
int front = 0;
int rear = 0;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[이정민], [2018038030]---\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;//stack top값 초기화

	front = rear = 0;//원형 큐로 할것이므로 0으로 초기화

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	while(1)
	{
		while(node!=NULL)//노드가 존재하는 동안
		{
			push(node);//노드를 스택에 push
			node=node->left;//왼쪽 자식 노드로 이동
		}
		/* 왼쪽 자식 끝에 도달*/

		node=pop();//노드 하나를 pop
		if(node==NULL) break;//노드가 없으면 순회 종료

		printf(" [%d] ",node->key);//노드 출력
		node=node->right;//노드를 오른쪽 노드로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(ptr==NULL) return;//공백 트리이면 종료

	enQueue(ptr);//큐에 루트 노드 삽입
	while(1)
	{
		ptr=deQueue();//큐에서 노드를 꺼내서
		if(ptr)//존재하면
		{
			printf(" [%d] ",ptr->key);//노드 출력
			if(ptr->left!=NULL)//왼쪽 자식이 존재하면
			{
				enQueue(ptr->left);//그 자식노드를 삽입
			}
			if(ptr->right!=NULL)//오른쪽 자식이 존재하면
			{
				enQueue(ptr->right);//그 자식노드를 삽입
			}
		}
		else break;//함수 종료
	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{

	Node* cur=head->left;//탐색노드를 루트노드로 초기화
	Node* parent=NULL;//부모노드 선언

	while(cur!=NULL)//탐색노드가 존재하는 동안
	{
		if(cur->key==key)//삭제할 노드를 찾으면
		{
			if(cur->left==NULL && cur->right==NULL)//그 노드가 리프노드이면
			{
				if(cur==head->left)//그 노드가 루트노드이면
				{
					head->left=NULL;//루트노드를 지움
					free(cur);//탐색 노드 해제
					return 1;
				}

				if(parent->key>key)//삭제할 노드가 부모노드보다 작으면
				{
					parent->left=NULL;//부모노드의 왼쪽 자식 삭제
					free(cur);//탐색노드 해제
					return 1;
				}
				else
				{
					parent->right=NULL;//부모노드의 오른쪽 자식 삭제
					free(cur);//탐색노드 해제
					return 1;
				}

			}
			else if((cur->left==NULL && cur->right!=NULL) || (cur->left!=NULL && cur->right==NULL))//자식노드가 1개이면
			{
				if(cur==head->left)//탐색노드가 루트노드이면
				{
					if(cur->left==NULL)//루트노드의 왼쪽 자식이 없으면
					{
						head->left=cur->right;//루트노드는 탐색노드의 오른쪽 자식
						free(cur);//탐색 노드 해제
						return 1;

					}
					else
					{
						head->left=cur->left;//루트노드는 탐색노드의 왼쪽 자식
						free(cur);//탐색 노드 해제
						return 1;
					}

				}

				if(parent->key>key)//삭제할 노드가 부모노드보다 작으면
				{
					if(cur->left==NULL)//탐색 노드의 왼쪽 자식이 없으면
					{
						parent->left=cur->right;//부모노드의 왼쪽 자식은 탐색노드의 오른쪽 자식
						free(cur);//탐색노드 해제
						return 1;
					}
					else
					{
						parent->left=cur->left;//부모노드의 왼쪽 자식은 탐색노드의 왼쪽 자식
						free(cur);//탐색 노드 해제
						return 1;
					}

				}
				else
				{
					if(cur->left==NULL)//탐색노드의 왼쪽 자식이 없으면
					{
						parent->right=cur->right;//부모노드의 오른쪽 자식은 탐색 노드의 오른쪽 자식
						free(cur);//탐색 노드 해제
						return 1;
					}
					else
					{
						parent->right=cur->left;//부모노드의 오른쪽 자신은 탐색노드의 왼쪽 자식
						free(cur);//탐색 노드 해제
						return 1;
					}
				}


			}
			else//자식이 2개이면
			{
				Node* RightSubMin=cur->right;//오른쪽 서브트리의 최솟값 노드 선언
				Node* RightSubMinParent=NULL;//그 최솟값의 부모노드 선언
				while(RightSubMin->left!=NULL)//최솟값 노드보다 작은 값이 존재하는 동안
				{
					RightSubMinParent=RightSubMin;//부모노드 갱신
					RightSubMin=RightSubMin->left;//최솟값 노드를 그 작은 값으로 이동
				}


				cur->key=RightSubMin->key;//최솟값노드의 키값을 탐색노드에 복사

				if(RightSubMin==cur->right)//최솟값 노드가 오른쪽 서브트리의 루트노드인 경우
				{
					if(RightSubMin->right==NULL)//최솟값노드의 오른쪽이 없으면
					{
						cur->right=NULL;//탐색노드의 오른쪽노드 삭제
						free(RightSubMin);//최솟값 노드 해제
						return 1;
					}
					else
					{
						cur->right=RightSubMin->right;//탐색노드의 오른쪽 노드는 최솟값 노드의 오른쪽 자식
						free(RightSubMin);//최솟값 노드 해제
						return 1;
					}
				}

				if(RightSubMin->right==NULL)//최솟값 노드의 오른쪽 자식이 없으면
				{
					RightSubMinParent->left=NULL;//최솟값 노드의 부모노드의 왼쪽 자식 삭제

				}
				else
				{
					RightSubMinParent->left=RightSubMin->right;//최솟값 노드의 부모노드의 왼쪽 자식은 최솟값 노드의 오른쪽 자식
				}

				free(RightSubMin);//최솟값 노드 해제
				return 1;

			}
		}


		parent=cur;//부모노드 갱신
		if(cur->key<key)//탐색노드보다 찾는 키값이 크면
		{
			cur=cur->right;//오른쪽 으로 이동
		}
		else
		{
			cur=cur->left;//왼쪽으로 이동
		}
	}

	/*못찾은 경우*/
	printf("no node for key [%d]\n",key);
	return -1;

}


void freeNode(Node* ptr)//모든 노드 해제
{
	/* 후위 순회를 통한 해제*/
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)//트리 구조 해제
{

	if(head->left == head)//트리에 노드가 없으면
	{
		free(head);//트리구조 자체를 해제
		return 1;
	}

	Node* p = head->left;//탐색노드에 루트노드 대입

	freeNode(p);//freeNode 호출

	free(head);//트리구조 해제
	return 1;
}



Node* pop()
{
	if(top>-1)//top이 -1보다 크면
	{
		return stack[top--];//스택 요소 pop
	}

	return NULL;//pop 실패

}

void push(Node* aNode)
{
	if(top+1<MAX_STACK_SIZE)//top이 스택 최대 사이즈에 도달하지 않은 경우
	{
		stack[++top]=aNode;//스택에 aNode push
	}

}



Node* deQueue()
{
	if(front!=rear)//큐가 공백이 아니면
	{
		front=(front+1)%MAX_QUEUE_SIZE;//front값 앞으로 이동
		return queue[front];//큐에서 데이터 꺼냄

	}

	return NULL;//dequeue 실패


}

void enQueue(Node* aNode)
{
	if((rear+1)%MAX_QUEUE_SIZE!=front)//큐가 full이 아니면
	{
		rear=(rear+1)%MAX_QUEUE_SIZE;//rear값 앞으로 이동
		queue[rear]=aNode;//큐에 데이터 삽입
	}

}

void printStack()
{
	for(int i=0;i<=top;i++)
	{
		printf(" [%d] ",stack[i]);
	}

}





