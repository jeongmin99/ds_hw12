#include <stdio.h>

void main()
{
	int** x;//int** 형 변수 선언

	printf("[----- [이정민] [2018038030] -----\n");
	printf("sizeof(x) = %lu\n",sizeof(x));//x의 크기 출력
	printf("sizeof(*x) = %lu\n",sizeof(*x));//*x의 크기 출력
	printf("sizeof(**x) = %lu\n",sizeof(**x));//**x의 크기 출력

}
