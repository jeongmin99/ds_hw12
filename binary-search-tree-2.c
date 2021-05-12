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

	top = -1;

	front = rear = -1;

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
		while(node!=NULL)
		{
			push(node);
			node=node->left;
		}
		node=pop();
		if(node==NULL) break;

		printf(" [%d] ",node->key);
		node=node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(ptr==NULL) return;

	enQueue(ptr);
	while(1)
	{
		ptr=deQueue();
		if(ptr)
		{
			printf(" [%d] ",ptr->key);
			if(ptr->left!=NULL)
			{
				enQueue(ptr->left);
			}
			if(ptr->right!=NULL)
			{
				enQueue(ptr->right);
			}
		}
		else break;
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

	Node* cur=head->left;
	Node* parent=cur;

	while(cur!=NULL)
	{
		if(cur->key==key)
		{
			if(cur->left==NULL && cur->right==NULL)
			{
				if(cur==head->left)
				{
					head->left=NULL;
					free(cur);
					return 1;
				}

				if(parent->key>key)
				{
					parent->left=NULL;
					free(cur);
					return 1;
				}
				else
				{
					parent->right=NULL;
					free(cur);
					return 1;
				}

			}
			else if((cur->left==NULL && cur->right!=NULL) || (cur->left!=NULL && cur->right==NULL))
			{
				if(cur==head->left)
				{
					if(cur->left==NULL)
					{
						head->left=cur->right;
						free(cur);
						return 1;

					}
					else
					{
						head->left=cur->left;
						free(cur);
						return 1;
					}

				}

				if(parent->key>key)
				{
					if(cur->left==NULL)
					{
						parent->left=cur->right;
						free(cur);
						return 1;
					}
					else
					{
						parent->left=cur->left;
						free(cur);
						return 1;
					}

				}
				else
				{
					if(cur->left==NULL)
					{
						parent->right=cur->right;
						free(cur);
						return 1;
					}
					else
					{
						parent->right=cur->left;
						free(cur);
						return 1;
					}
				}


			}
			else
			{
				Node* LeftSubMax=cur->left;
				Node* LeftSubMaxParent=NULL;
				while(LeftSubMax->right!=NULL)
				{
					LeftSubMaxParent=LeftSubMax;
					LeftSubMax=LeftSubMax->right;
				}

				//왼쪽서브트리에서 가장큰 원소를 찾는다
				cur->key=LeftSubMax->key;

				if(LeftSubMax==cur->left)
				{
					if(LeftSubMax->left==NULL)
					{
						cur->left=NULL;
						free(LeftSubMax);
						return 1;
					}
					else
					{
						cur->left=LeftSubMax->left;
						free(LeftSubMax);
						return 1;
					}
				}

				if(LeftSubMax->left==NULL)
				{
					LeftSubMaxParent->right=NULL;

				}
				else
				{
					LeftSubMaxParent->right=LeftSubMax->left;
				}
				//링크 연결
				free(LeftSubMax);//왼쪽서브트리에 있는 가장큰원소 삭제
				return 1;

			}
		}


		parent=cur;
		if(cur->key<key)
		{
			cur=cur->right;
		}
		else
		{
			cur=cur->left;
		}
	}


}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if(top>-1)
	{
		return stack[top--];
	}

	return NULL;

}

void push(Node* aNode)
{
	if(top+1<MAX_STACK_SIZE)
	{
		stack[++top]=aNode;
	}

}



Node* deQueue()
{
	if(front!=rear)
	{
		front=(front+1)%MAX_QUEUE_SIZE;
		return queue[front];

	}

	return NULL;


}

void enQueue(Node* aNode)
{
	if((rear+1)%MAX_QUEUE_SIZE!=front)
	{
		rear=(rear+1)%MAX_QUEUE_SIZE;
		queue[rear]=aNode;
	}

}

void printStack()
{

}





