#include <stdio.h>

#define MAX_SIZE 100//최대 크기 100

float sum(float[], int);//매개변수 float[], int형을 가지고 float형을 반환하는 sum 함수의 프로토타입

/*전역변수 선언*/
float input[MAX_SIZE], answer;//float형 MAX_SIZE 크기의 배열과 float형 변수 선언
int i;//int형 변수 선언
void main()
{
	printf("[----- [이정민] [2018038030] -----\n");
	for(i=0;i<MAX_SIZE;i++)//배열에 각 인덱스에 대응하는 숫자를 대입
		input[i]=i;

	/*for checking call by reference*/
	printf("address of input = %p\n",input);//input

	answer=sum(input,MAX_SIZE);//sum함수의 결과를 answer에 대입
	printf("The sum is: %f\n",answer);//answer
}

float sum(float list[], int n)
{

	printf("value of list = %p\n",list);//list의 값
	printf("address of list = %p\n",&list);//list의 주소

	int i;//int형 변수 선언
	float tempsum=0;//값들의 합을 임시로 저장할 변수 선언
	for(i=0;i<n;i++)
		tempsum+=list[i];//tempsum에 list에 저장된 값을 더함
	return tempsum;//tempsum의 값 반환
}
