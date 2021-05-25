#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 10

typedef struct node//노드 구조체 정의
{
	int vertex;
	struct node* link;

}Node;


Node* graph[MAX_VERTICES];//인접리스트 형태로 구현할 때 인접한 노드들을 관리할 배열
short int isInserted[MAX_VERTICES];//정점이 삽입되어있는지 판단하는 배열
short int visited[MAX_VERTICES];//정점을 방문했는지 판단하는 배열
int nodecount=0;//정점의 갯수


/* 큐 정의 */
int queue[MAX_VERTICES];//큐에서 데이터를 관리할 배열
int front=0;//큐의 front
int rear=0;//큐의 rear


/* 함수 프로토타입 선언*/
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
			initializeGraph();//그래프 초기화
			break;
		case 'q': case 'Q':
			freeGraph();//그래프 메모리 해제
			break;
		case 'v': case 'V':
			printf("Your Key = ");//삽입 정점 입력
			scanf("%d", &key1);
			insertVertex(key1);//정점 삽입
			break;
		case 'e': case 'E':
			printf("Your Key = ");//간선이 연결될 정점 2개입력
			scanf("%d %d", &key1,&key2);
			insertEdge(key1,key2);
			break;

		case 'd': case 'D':
			printf("Your Key = ");//dfs를 시작할 정점 입력
			scanf("%d", &key1);
			for(int i=0;i<MAX_VERTICES;i++)//방문배열 초기화
			{
				visited[i]=FALSE;
			}
			dfs(key1);
			break;
		case 'b': case 'B':
			printf("Your Key = ");//bfs를 시작할 정점 입력
			scanf("%d", &key1);
			for(int i=0;i<MAX_VERTICES;i++)//방문배열 초기화
			{
				visited[i]=FALSE;
			}
			bfs(key1);
			break;

		case 'p': case 'P':
			printGraph();//인접리스트에 연결된 노드들 출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initializeGraph()//그래프 초기화
{


	nodecount=0;//정점 갯수 초기화

	for(int i=0;i<MAX_VERTICES;i++)//인접 리스트 관리 배열에서 각각의 인덱스에 대해
	{
		if(graph[i]!=NULL)//노드가 존재하면
		{
			Node* cur=graph[i];
			Node* prev=NULL;
			while(cur!=NULL)/*노드 메모리 해제*/
			{
				prev=cur;
				cur=cur->link;
				free(prev);
			}
		}
		graph[i]=NULL;//인접 리스트 배열 초기화
		visited[i]=FALSE;//방문 배열 초기화
		isInserted[i]=FALSE;//삽입된 정점인지 확인하는 배열 초기화
	}

}

void insertVertex(int v)//정점 삽입
{
	if(nodecount+1>MAX_VERTICES)//노드 갯수가 최대 노드수를 넘어가려하면
	{
		printf("정점이 가득찼습니다.\n");
		return;
	}

	if(isInserted[v]==TRUE)//v번 정점이 이미 삽입되었다면
	{
		printf("이미 삽입된 정점입니다.\n");
		return;
	}

	isInserted[v]=TRUE;//v번 정점 삽입이 되었다고 체크
	nodecount++;//노드 갯수 증가
}

void insertEdge(int v1,int v2)//간선 삽입
{

	if(isInserted[v1]==FALSE || isInserted[v2]==FALSE)//v1번 정점이나 v2번 정점이 삽입되지 않았다면
	{
		printf("존재하지 않는 정점입니다.\n");
		return;
	}
	else
	{
		Node* cur=graph[v2];//v2 정점(인접리스트 배열의 v2인덱스) 접근
		while(cur!=NULL)/* v1 정점이 v2와 연결되어있는지 판단*/
		{
			if(cur->vertex==v1)//연결되어있다면
			{
				printf("이미 존재하는 간선입니다.\n");
				return;
			}
			cur=cur->link;
		}

		insertNode(v1,v2);//v2정점 배열에 v1노드 연결

		cur=graph[v1];//v1 정점(인접리스트 배열의 v1 인덱스) 접근

		while(cur!=NULL)/* v2 정점이 v1과 연결되어있는지 판단*/
		{
			if(cur->vertex==v2)//연결되어있다면
			{
				printf("이미 존재하는 간선입니다.\n");
				return;
			}
			cur=cur->link;
		}

		insertNode(v2,v1);//v1 정점 배열에 v2노드 연결
	}


}
void insertNode(int v1,int v2)//연결리스트 v2 인덱스에 노드 연결
{

	/* v1 정점 노드 생성*/
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->vertex=v1;
	newNode->link=NULL;

	if(graph[v2]==NULL)//v2 인덱스가 비어있으면
	{
		graph[v2]=newNode;//노드할당
	}
	else
	{
		Node* cur=graph[v2];
		Node* prev=NULL;
		while(cur!=NULL)/* 작은 값부터 접근하기위해 리스트에 작은 노드가 앞에 오도록 삽입*/
	    {
		    if(cur->vertex>=v1)//v1보다 현재 노드가 크거나 같으면
		    {
				if(cur==graph[v2])//현재 노드 위치가 맨앞이면
				{
					newNode->link=cur;//새로운 노드의 다음노드를 현재노드로 링크
					graph[v2]=newNode;//맨 앞 노드는 새로운 노드
				}
				else
				{
					newNode->link=cur;//새로운 노드의 다음노드는 현재노드
					prev->link=newNode;//이전 노드의 다음 노드는 새로운 노드
				}
			    return;
			}

			prev=cur;//이전 노드 갱신
			cur=cur->link;//현재노드 이동

		}

	/* 리스트를 끝까지 돌은 경우*/
	prev->link=newNode;//이전노드의 다음노드는 새로운노드
	return ;

	}
}

void dfs(int v)//깊이 우선 탐색
{

	Node* cur=graph[v];//탐색 노드를 인접리스트 배열의 v인덱스로 지정
	visited[v]=TRUE;//v 정점 방문
	printf("%d ",v);//출력
	while(cur!=NULL)//탐색노드가 존재하는 동안
	{
		if(visited[cur->vertex]==FALSE)//탐색노드의 정점을 방문 안했으면
		{
			dfs(cur->vertex);//탐색노드의 정점으로 재귀적으로 dfs호출
		}
		cur=cur->link;//탐색노드 이동
	}
}

void bfs(int v)//너비 우선 탐색
{

	Node* cur;//탐색노드 선언
	visited[v]=TRUE;//v 정점 방문
	printf("%d ",v);//정점 출력
	enqueue(v);//v 정점 큐에 삽입

	while(TRUE)
	{
		v=dequeue();//큐에서 요소 꺼냄
		if(v==-1) return;//큐가 비었을 때 꺼낸거였으면 함수 종료
		for(cur=graph[v];cur!=NULL;cur=cur->link)//정점 v 인접리스트를 탐색노드의 위치로 지정, 탐색노드 이동하면서 탐색
		{
			if(visited[cur->vertex]==FALSE)//탐색노드 정점을 방문 안했으면
			{
				printf("%d ",cur->vertex);//정점 출력
				enqueue(cur->vertex);//큐에 정점 삽입
				visited[cur->vertex]=TRUE;//정점 방문
			}

		}
	}

}

void enqueue(int v)//큐에 요소 삽입
{
	if((rear+1)%MAX_VERTICES==front)//큐가 가득차있으면
	{
		return;//함수종료
	}

	rear=(rear+1)%MAX_VERTICES;//rear값 증가
	queue[rear]=v;//rear가 가리키는 곳에 요소 삽입

}

int dequeue()//큐에서 요소 꺼내기
{
	if(front==rear)//큐가 비어있으면
	{
		return -1;//-1 반환
	}

	front=(front+1)%MAX_VERTICES;//front값 증가
	return queue[front];//front가 가리키는 위치의 요소 반환
}

void printGraph()//인접리스트 배열에 연결된 노드들 출력
{
	for(int i=0;i<MAX_VERTICES;i++)//모든 인접리스트 배열 인덱스를 돌면서
	{
		printf("graph[%d]= ",i);
		Node* cur=graph[i];//탐색 노드를 인덱스에 해당하는 배열요소로 지정
		while(cur!=NULL)
		{
			printf("[%d] ",cur->vertex);//탐색노드 정점값 출력
			cur=cur->link;//탐색 노드 이동
		}

		printf("\n");
	}

}
void freeGraph()//그래프 해제
{

	for(int i=0;i<MAX_VERTICES;i++)//모든 정점 반복
	{
		if(graph[i]!=NULL)//인접리스트배열이 비어있지 않으면
		{
			Node* cur=graph[i];/* 그 배열에 있는 노드들 탐색하여 하나씩 해제*/
			Node* prev=NULL;
			while(cur!=NULL)
			{
				prev=cur;
				cur=cur->link;
				free(prev);
			}

		}
	}
}


