#include <stdio.h>

struct student{//구조체 struct student 선언

	char lastName[13];  /*13 bytes*/  //char형인 크기 13 배열 선언
	int studentId;		/*4 bytes */  //int형 변수
	short grade;		/* 2 bytes */ //short형 변수


};
int main()
{
	struct student pst;//sturct student 형 변수 선언

	printf("size of student = %ld\n",sizeof(struct student));//struct student의 크기
	printf("size of int = %ld\n",sizeof(int));//int의 크기 출력
	printf("size of short = %ld\n",sizeof(short));//short의 크기 출력

	return 0;


}
