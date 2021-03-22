#include <stdio.h>

struct student1{//student1 구조체 선언(사용시 sturct를 앞에 붙여야함)
	char lastName;
	int studentId;
	char grade;
};

typedef struct{//student2 구조체 선언 및 type define
	char lastName;
		int studentId;
		char grade;
}student2;

int main()
{
	struct student1 st1={'A',100,'A'};//sturct student1 타입 변수 선언 및 초기화

	printf("[----- [이정민] [2018038030] -----]\n");

	printf("st1.lastName = %c\n",st1.lastName);//st1.lastName 출력
	printf("st1.studentId = %d\n",st1.studentId);//st1.studentId 출력
	printf("st1.grade = %c\n",st1.grade);//st1.grade 출력

	student2 st2={'B',200,'B'};//student2 타입 변수 선언 및 초기화

	printf("st2.lastName = %c\n",st2.lastName);//st2.lastName 출력
	printf("st2.studentId = %d\n",st2.studentId);//st2.studentId 출력
	printf("st2.grade = %c\n",st2.grade);//st2.grade 출력

	student2 st3;//studnet2 타입 변수 선언

	st3=st2;//st3에  st2 대입(구조 치환)

	printf("st3.lastName = %c\n",st3.lastName);//st3.lastName 출력
	printf("st3.studentId = %d\n",st3.studentId);//st3.studentId 출력
	printf("st3.grade = %c\n",st3.grade);//st3.grade 출력

	/*equality Test*///==로 struct간 비교 불가(멤버간 일일히 비교해야함)
	/*if(st3==st2)
	{
		printf("equal\n");
	}
	else
	{
		printf("not equal\n");
	}*/

	return 0;
}
