/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
Node* modifiedSearch(Node* head,int key);//노드를 삽입할 곳을 찾아주는 함수
int postorderFree(Node* ptr);//후위식 순회로 노드를 해제해주는 함수
int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[이정민], [2018038030]---\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)//중위 순회 방식
{
	if(ptr!=NULL)//ptr이 존재하는 동안
	{
		inorderTraversal(ptr->left);//왼쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
		printf("[%d] ",ptr->key);//ptr값 출력
		inorderTraversal(ptr->right);//오른쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
	}

}

void preorderTraversal(Node* ptr)//전위 순회 방식
{
	if(ptr!=NULL)//ptr이 존재하는 동안
	{
		printf("[%d] ",ptr->key);//ptr값 출력
		preorderTraversal(ptr->left);//왼쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
		preorderTraversal(ptr->right);//오른쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
	}

}

void postorderTraversal(Node* ptr)
{
	if(ptr!=NULL)
	{
		postorderTraversal(ptr->left);//왼쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
		postorderTraversal(ptr->right);//오른쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
		printf("[%d] ",ptr->key);//ptr값 출력
	}

}


int insert(Node* head, int key)
{
	/* 노드 생성 및 초기화*/
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;

	if(head->left==NULL)//트리가 공백이면
	{
		head->left=newNode;//루트노드를 새로운 노드로 지정
	}
	else
	{
		Node* cur=modifiedSearch(head, key);//노드를 삽입할 자리를 탐색하여 탐색 노드 cur에 할당
		if(cur!=NULL)//탐색 노드 값이 존재하면
		{
			if(cur->key>key)//탐색노드의 값이 새로운 노드의 값보다 크면
			{
				cur->left=newNode;//탐색노드의 왼쪽 자식노드는 새로운 노드
			}
			else
			{
				cur->right=newNode;//탐색노드의 오른쪽 자식 노드는 새로운 노드
			}
		}

	}
	return 1;
}

int deleteLeafNode(Node* head, int key)//리프노드인지 판단해서 리프노드이면 삭제하는 함수
{
	if(head->left!=NULL)//루트노드가 존재하면
	{
		Node* cur=head->left;//탐색노드를 루트노드로 지정
		Node* parent=cur;//탐색노드의 부모노드
		while(cur!=NULL)//탐색노드가 존재하는 동안
		{

			if(cur->key==key)//삭제할 노드를 찾으면
			{
				if(cur->left==NULL && cur->right==NULL)//리프노드이면
				{
					if(cur==head->left)//삭제할 노드가 루트노드이면
					{
						head->left=NULL;//루트노드를 비움
						free(cur);//탐색노드 해제
						return 0;
					}
					if(parent->key>key)//부모노드의 값보다 삭제할 값이 작으면
					{
						parent->left=NULL;//부모노드의 왼쪽 자식 노드를 비움
						free(cur);//삭제할 노드 해제
						return 0;
					}
					else
					{
						parent->right=NULL;//부모노드의 오른쪽 자식 노드를 비움
						free(cur);//삭제할 노드 해제
						return 0;
					}
				}
				else
				{
					printf("the node [%d] is not a leaf\n",cur->key);//리프노드가 아니라는 문구 출력
					return 0;
				}
			}


			parent=cur;//부모 노드 값 갱신

			if(cur->key>key)//탐색 노드의 값보다 삭제할 노드 값이 작으면
			{
				cur=cur->left;//탐색 노드 왼쪽 자식으로 이동
			}
			else
			{
				cur=cur->right;//탐색 노드 오른쪽 자식으로 이동
			}
		}
	}
	return 0;
}

Node* searchRecursive(Node* ptr, int key)//재귀적으로 특정한 노드를 탐색
{
	if(ptr==NULL)//트리가 공백이면
	{
		return NULL;//NULL 리턴
	}
	if(ptr->key==key)//노드를 찾으면
	{
		return ptr;//그 노드 리턴
	}
	if(ptr->key>key)//현재 노드값보다 찾는 노드값이 작으면
	{
		return searchRecursive(ptr->left, key);//노드의 왼쪽 자식을 매개변수로 하는 함수 재귀적으로 호출
	}
	else
	{
		return searchRecursive(ptr->right, key);//노드의 오른쪽 자식을 매개변수로 하는 함수 재귀적으로 호출
	}

}

Node* searchIterative(Node* head, int key)
{
	if(head->left!=NULL)//트리가 공백이 아니면
	{
		Node* cur=head->left;//탐색노드를 루트노드로 할당
		while(cur!=NULL)//탐색 노드가 존재하면
		{
			if(cur->key==key)//값을 찾은 경우
			{
				return cur;//그 노드 리턴
			}
			if(cur->key>key)//탐색 노도의 값보다 찾는 값이 작으면
			{
				cur=cur->left;//탐색 노드의 왼쪽 자식으로 이동
			}
			else
			{
				cur=cur->right;//탐색 노드의 오른쪽 자식으로 이동
			}
		}
		return NULL;//못찾았으면 NULL리턴
	}

	return NULL;//트리 공백이면 NULL리턴
}


int freeBST(Node* head)//이진 트리를 해제
{
	postorderFree(head->left);//후위 순회로 해제하는 함수 호출
	return 0;
}
int postorderFree(Node* ptr)//후위 순회로 해제하는 함수
{
	if(ptr!=NULL)//노드가 존재하는 동안
	{
		postorderFree(ptr->left);//왼쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
		postorderFree(ptr->right);//오른쪽 자식 노드를 매개변수로 하는 함수를 재귀적으로 호출
		free(ptr);//노드 해제
	}

	return 0;
}

Node* modifiedSearch(Node* head,int key)//노드를 삽입할 위치를 반환하는 함수
{
	if(head->left!=NULL)//공백 트리가 아니면
	{
		Node* cur=head->left;//탐색노드를 루트노드로 할당
		while(!(cur->left==NULL && cur->right==NULL))//리프노드가 아닌 동안
		{
			if(cur->key==key)//중복되는 값이 존재하면
			{
				return NULL;//NULL 리턴
			}
			if(cur->key>key)//탐색노드의 값이 찾는 값보다 크면
			{
				if(cur->left==NULL)//탐색노드의 왼쪽 자식 노드가 없으면
				{
					return cur;//탐색노드 리턴
				}
				else
				{
					cur=cur->left;//탐색노드의 왼쪽 자식으로 이동
				}
			}
			else
			{
				if(cur->right==NULL)//탐색노드의 오른쪽 자식 노드가 없으면
				{
					return cur;//탐색노드 리턴
				}
				else
				{
					cur=cur->right;//탐색노드의 오른쪽 자식으로 이동
				}
			}
		}
		if(cur->key==key)//중복되는 값이 존재하면
		{
			return NULL;//NULL 리턴
		}
		return cur;//탐색 노드 리턴(리프노드)
	}

	return NULL;//NULL리턴(공백트리)
}




