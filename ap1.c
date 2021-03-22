#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5];//int형 크기 5 배열 선언
	int* plist[5]={NULL,};//int*형 크기 5 배열 선언

	plist[0]=(int*)malloc(sizeof(int));//plist[0]에 heap 메모리 할당

	list[0]=1;//list[0]에 1 대입
	list[1]=100;//list[1]에 100 대입

	*plist[0]=200;//plist[0]가 가리키는 곳에 200 대입

	printf("[----- [이정민] [2018038030] -----\n");
	printf("value of list[0] = %d\n",list[0]);//list[0]의 값
	printf("address of list[0] = %p\n",&list[0]);//list[0]의 주소
	printf("value of list = %p\n",list);//list의 값
	printf("address of list (&list) = %p\n",&list);//list의 주소(&list)

	printf("-------------------------------------\n\n");
	printf("value of list[1] = %d\n",list[1]);//list[1]의 값
	printf("address of list[1] = %p\n",&list[1]);//list[1]의 주소
	printf("value of *(list+1) = %d\n",*(list+1));//*(list+1)
	printf("address of list+1 = %p\n",list+1);//list+1

	printf("-------------------------------------\n\n");

	printf("value of *plist[0] = %d\n",*plist[0]);//*plist[0]
	printf("&plist[0] =%p\n",&plist[0]);//plist[0]의 주소
	printf("&plist = %p\n",&plist);//plist의 주소
	printf("plist = %p\n",plist);//plist의 값
	printf("plist[0] = %p\n",plist[0]);//plist[0]의 값
	printf("plist[1] = %p\n",plist[1]);//plist[1]의 값
	printf("plist[2] = %p\n",plist[2]);//plist[2]의 값
	printf("plist[3] = %p\n",plist[3]);//plist[3]의 값
	printf("plist[4] = %p\n",plist[4]);//plist[4]의 값

	free(plist[0]);//plist[0] 할당 해제

}
