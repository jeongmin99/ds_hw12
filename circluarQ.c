/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4//큐 배열의 최대 사이즈

typedef char element;//큐에 넣을 데이터타입
typedef struct {
	element queue[MAX_QUEUE_SIZE];//큐에 실질적으로 데이터를 넣을 배열
	int front, rear;//큐에서 데이터가 들어가는 곳과 나오는 곳을 가리킴
}QueueType;//QueueType 구조체로 선언


/* 함수 프로토타입 선언*/
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;
	setvbuf(stdout, NULL, _IONBF, 0);//window용 이클립스에서 scanf 관련 버퍼문제로 사용하는 함수
	printf("[----- [이정민] [2018038030] -----]");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");


		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()//큐를 생성하는 함수
{
	QueueType *cQ;//QueueType 변수 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ에 타입사이즈만큼 메모리 할당
	cQ->front = 0;//front 0으로 초기화
	cQ->rear = 0;//rear 0으로 초기화
	return cQ;//cQ 리턴
}

int freeQueue(QueueType *cQ)//큐를 해제하는 함수
{
    if(cQ == NULL) return 1;//cQ가 null이면 함수 종료
    free(cQ);//cQ에 할당된 메모리 해제
    return 1;//함수 종료
}

element getElement()//값을 입력받고 그 값을 반환하는 함수
{
	element item;//item변수 선언
	printf("Input element = ");
	scanf(" %c", &item);//값 입력 후 저장
	return item;//값 반환
}


/* complete the function */
int isEmpty(QueueType *cQ)//큐가 비었는지 판별하는 함수
{
	if(cQ->front==cQ->rear)//큐의 front값과 rear값이 같다면
	{
		return 1;//참 리턴
	}
    return 0;//거짓 리턴
}

/* complete the function */
int isFull(QueueType *cQ)//큐가 가득 찼는지 판별하는 함수
{
	if(cQ->front==((cQ->rear)+1)%MAX_QUEUE_SIZE)//큐의 front값이 rear+1값과 같다면(이때 모듈러 연산을 통해 rear+1이 큐의 전체사이즈와 같다면 0으로 보내어 원형 큐 성질을 구현)
	{
		return 1;//참 리턴
	}
   return 0;//거짓 리턴
}


/* complete the function */
void enQueue(QueueType *cQ, element item)//큐에 데이터를 추가하는 함수
{

	if(isFull(cQ))//큐가 가득찼다면
	{
		printf("Queue is full.\n");
		return;//함수 종료
	}

	cQ->rear=((cQ->rear)+1)%MAX_QUEUE_SIZE;//rear를 한칸 앞으로(이때 모듈러 연산을 통해 rear+1이 큐의 전체사이즈와 같다면 0으로 보내어 원형 큐 성질을 구현)
	cQ->queue[cQ->rear]=item;//rear가 가리키는 곳에 데이터 저장


}

/* complete the function */
void deQueue(QueueType *cQ, element *item)//큐에서 데이터를 삭제하는 함수
{
	if(isEmpty(cQ))//큐가 비어있다면
	{
		printf("Queue is empty.\n");
		return;//함수 종료
	}

	cQ->front=((cQ->front)+1)%MAX_QUEUE_SIZE;//front를 한칸 앞으로(이때 모듈러 연산을 통해 front+1이 큐의 전체사이즈와 같다면 0으로 보내어 원형 큐 성질을 구현)
	*item=cQ->queue[cQ->front];//front가 가리키는 값을 *item에 전달

}


void printQ(QueueType *cQ)//큐에 저장된 데이터를 출력하는 함수
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//시작점은 front+1(이때 모듈러 연산을 통해 front+1이 큐의 전체사이즈와 같다면 0으로 보내어 원형 큐 성질을 구현)
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//끝점은 rear+1(이때 모듈러 연산을 통해 rear+1이 큐의 전체사이즈와 같다면 0으로 보내어 원형 큐 성질을 구현)

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);/*시작점 부터 끝점 전 까지 큐에 저장된 데이터를 출력*/
		i = (i+1)%MAX_QUEUE_SIZE;//i를 1씩 증가(이때 모듈러 연산을 통해 i+1이 큐의 전체사이즈와 같다면 0으로 보내어 원형 큐 성질을 구현)

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//큐를 구현한 배열에 실제로 어떤 값을이 들어가 있는지 확인하는 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//배열 전체 크기 만큼
	{
		if(i == cQ->front) {//i가 front에 있으면
			printf("  [%d] = front\n", i);//front 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//각 인덱스에 있는 값들을 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front와 rear의 위치 출력
}

