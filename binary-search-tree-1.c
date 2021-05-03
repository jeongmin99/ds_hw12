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
Node* modifiedSearch(Node* head,int key);

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[ÀÌÁ¤¹Î], [2018038030]---\n");

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



void inorderTraversal(Node* ptr)
{
	if(ptr!=NULL)
	{
		inorderTraversal(ptr->left);
		printf("[%d] ",ptr->key);
		inorderTraversal(ptr->right);
	}

}

void preorderTraversal(Node* ptr)
{
	if(ptr!=NULL)
	{
		printf("[%d] ",ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}

}

void postorderTraversal(Node* ptr)
{
	if(ptr!=NULL)
	{
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d] ",ptr->key);
	}

}


int insert(Node* head, int key)
{
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;

	if(head->left==NULL)
	{
		head->left=newNode;
	}
	else
	{
		Node* cur=modifiedSearch(head, key);
		if(cur!=NULL)
		{
			if(cur->key>key)
			{
				cur->left=newNode;
			}
			else
			{
				cur->right=newNode;
			}
		}
		else
		{
			cur=newNode;
		}


	}
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	Node* cur=searchIterative(head, key);
	if(cur->left==NULL && cur->right==NULL)
	{

	}


	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr==NULL)
	{
		return NULL;
	}
	if(ptr->key==key)
	{
		return ptr;
	}
	if(ptr->key>key)
	{
		return searchRecursive(ptr->left, key);
	}
	else
	{
		return searchRecursive(ptr->right, key);
	}

}

Node* searchIterative(Node* head, int key)
{
	if(head->left!=NULL)
	{
		Node* cur=head->left;
		while(cur!=NULL)
		{
			if(cur->key==key)
			{
				return cur;
			}
			if(cur->key>key)
			{
				cur=cur->left;
			}
			else
			{
				cur=cur->right;
			}
		}
		return NULL;
	}

	return NULL;
}


int freeBST(Node* head)
{
	return 0;
}

Node* modifiedSearch(Node* head,int key)
{
	if(head->left!=NULL)
	{
		Node* cur=head->left;
		while(!(cur->left==NULL && cur->right==NULL))
		{
			if(cur->key==key)
			{
				return NULL;
			}
			if(cur->key>key)
			{
				if(cur->left==NULL)
				{
					return cur;
				}
				else
				{
					cur=cur->left;
				}
			}
			else
			{
				if(cur->right==NULL)
				{
					return cur;
				}
				else
				{
					cur=cur->right;
				}
			}
		}
		return cur;
	}

	return NULL;
}




