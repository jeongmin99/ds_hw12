#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5];//int형 크기 5 배열 선언
	int* plist[5];//int*형 크기 5 배열 선언

	list[0]=10;//list[0]에 10 대입
	list[1]=11;//list[1]에 11 대입

	plist[0]=(int*)malloc(sizeof(int));//plist[0]에 메모리 할당

	printf("[----- [이정민] [2018038030] -----\n");
	printf("list[0] \t= %d\n",list[0]);//list[0]의 값
	printf("address of list \t= %p\n",list);//list
	printf("address of list[0] \t= %p\n",&list[0]);//list[0]의 주소
	printf("address of list+0 \t= %p\n",list+0);//list+0
	printf("address of list+1 \t= %p\n",list+1);//list+1
	printf("address of list+2 \t= %p\n",list+2);//list+2
	printf("address of list+3 \t= %p\n",list+3);//list+3
	printf("address of list+4 \t= %p\n",list+4);//list+4
	printf("address of list[4] \t= %p\n",&list[4]);//list[4]의 주소

	free(plist[0]);//plist[0] 할당 해제


}
