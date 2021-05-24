#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 10

typedef struct node
{
	int vertex;
	struct node* link;

}Node;


Node* graph[MAX_VERTICES];
short int isInserted[MAX_VERTICES];
short int visited[MAX_VERTICES];
int nodecount=0;


int queue[MAX_VERTICES];
int front=0;
int rear=0;

void initializeGraph();
void insertVertex(int);
void insertEdge(int,int);
void insertNode(int,int);
void dfs(int);
void bfs(int);
void printGraph();
void freeGraph();
void enqueue(int);
int dequeue();

int main()
{
	char command;
	int key1,key2;

	setvbuf(stdout, NULL, _IONBF, 0);
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                  		   Graph Searches                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph();
			break;
		case 'q': case 'Q':
			freeGraph();
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key1);
			insertVertex(key1);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d %d", &key1,&key2);
			insertEdge(key1,key2);
			break;

		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key1);
			for(int i=0;i<MAX_VERTICES;i++)
			{
				visited[i]=FALSE;
			}
			dfs(key1);
			break;
		case 'b': case 'B':
			printf("Your Key = ");
			scanf("%d", &key1);
			for(int i=0;i<MAX_VERTICES;i++)
			{
				visited[i]=FALSE;
			}
			bfs(key1);
			break;

		case 'p': case 'P':
			printGraph();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initializeGraph()
{
	nodecount=0;

	for(int i=0;i<MAX_VERTICES;i++)
	{
		graph[i]=NULL;
		visited[i]=FALSE;
		isInserted[i]=FALSE;
	}

}

void insertVertex(int v)
{
	if(nodecount+1>MAX_VERTICES)
	{
		printf("정점이 가득찼습니다.\n");
		return;
	}

	if(isInserted[v]==TRUE)
	{
		printf("이미 삽입된 정점입니다.\n");
		return;
	}

	isInserted[v]=TRUE;
	nodecount++;
}

void insertEdge(int v1,int v2)
{

	if(isInserted[v1]==FALSE || isInserted[v2]==FALSE)
	{
		printf("존재하지 않는 정점입니다.\n");
		return;
	}
	else
	{
		insertNode(v1,v2);
		insertNode(v2,v1);
	}


}
void insertNode(int v1,int v2)
{
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->vertex=v1;
	newNode->link=NULL;

	if(graph[v2]==NULL)
	{
		graph[v2]=newNode;
	}
	else
	{
		Node* cur=graph[v2];
		Node* prev=NULL;
		while(cur!=NULL)
	    {
		    if(cur->vertex>=v1)
		    {
				if(cur==graph[v2])
				{
					newNode->link=cur;
					graph[v2]=newNode;
				}
				else
				{
					newNode->link=cur;
					prev->link=newNode;
				}
			    return;
			}

			prev=cur;
			cur=cur->link;

		}

	prev->link=newNode;
	return ;

	}
}

void dfs(int v)
{

	Node* cur=graph[v];
	visited[v]=TRUE;
	printf("%d ",v);
	while(cur!=NULL)
	{
		if(visited[cur->vertex]==FALSE)
		{
			dfs(cur->vertex);
		}
		cur=cur->link;
	}
}

void bfs(int v)
{

	Node* cur;
	visited[v]=TRUE;
	printf("%d ",v);
	enqueue(v);

	while(TRUE)
	{
		v=dequeue();
		if(v==-1) return;
		for(cur=graph[v];cur!=NULL;cur=cur->link)
		{
			if(visited[cur->vertex]==FALSE)
			{
				printf("%d ",cur->vertex);
				enqueue(cur->vertex);
				visited[cur->vertex]=TRUE;
			}

		}
	}

}

void enqueue(int v)
{
	if((rear+1)%MAX_VERTICES==front)
	{
		return;
	}

	rear=(rear+1)%MAX_VERTICES;
	queue[rear]=v;

}

int dequeue()
{
	if(front==rear)
	{
		return -1;
	}

	front=(front+1)%MAX_VERTICES;
	return queue[front];
}

void printGraph()
{

}
void freeGraph()
{

}


