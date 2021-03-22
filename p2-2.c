#include <stdio.h>

void print1(int* ptr,int rows);//int*형 변수와 int형 변수를 매개변수로 기지고 반환형이 없는 함수 프로토타입 선언

int main()
{
	int one[]={0,1,2,3,4};//int형 배열 선언후 값 초기화

	printf("[----- [이정민] [2018038030] -----\n");
	printf("one     =%p\n",one);//one 출력
	printf("&one    =%p\n",&one);//&one 출력
	printf("&one[0] =%p\n",&one[0]);//&one[0] 출력
	printf("\n");
	print1(&one[0],5);//print()


	return 0;
}
void print1(int* ptr,int rows)
{
	/*print out a one-dimensional array using a pointer*/

	int i;//int형 변수 선언
	printf("Address \t Contents\n");
	for(i=0;i<rows;i++)//i는 0부터 row-1까지 반복
		printf("%p \t  %5d\n",ptr+i,*(ptr+i));//포인터 변수에 i를 더한 값과 *(ptr+i) 출력
	printf("\n");
}

