/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */


/* 함수 프로토타입 선언*/
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("[----- [이정민] [2018038030] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");

		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)//postfixStack의 push연산
{
    postfixStack[++postfixStackTop] = x;//top값 증가 후 x 저장
}

char postfixPop()//postfixStack의 pop연산
{
    char x;
    if(postfixStackTop == -1)//스택이 비어있으면
        return '\0';//null 리턴
    else {
    	x = postfixStack[postfixStackTop--]; //스택의 top에 있는 요소 x에 저장후 top값 감소
    }
    return x;//x 반환
}

void evalPush(int x)//evalStack의 push연산
{
    evalStack[++evalStackTop] = x;//top값 증가 후 x 저장
}

int evalPop()//evalStack의 pop연산
{
    if(evalStackTop == -1)//스택이 비어있으면
        return -1;//-1 리턴
    else
        return evalStack[evalStackTop--];//스택의 top에 있는 요소 반환 후 top 감소
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)/*들어오는 문자에 따라서 그에 해당하는 우선순위를 리턴해주는 함수*/
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)//getToken함수의 결괏값(우선순위)을 리턴해주는 함수
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')//postfixExp가 null이면
		strncpy(postfixExp, c, 1);//문자 하나 postfixExp에 추가
	else
		strncat(postfixExp, c, 1);//문자 하나 postfixExp에 붙임
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	precedence pri;//우선순위 변수
	char a;//stack에서 pop한 문자를 담을 변수
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		x=*exp;//exp의 문자 하나를 x에 저장
		pri=getPriority(x);//x의 우선순위를 불러옴
		if(pri==operand)//우선순위가 피연산자의 우선순위이면
		{
			charCat(&x);//그대로 postfixExp에 피연산자 저장

		}
		else if(pri==rparen)//우선순위가 )의 우선순위이면
		{
			while(getPriority((postfixStack[postfixStackTop]))!=lparen)//stack에서 ( 이 나올때 까지
			{
				a=postfixPop();//stack에서 연산자 pop
				charCat(&a);//postfixExp에 저장

			}

		   a=postfixPop();//( 이 나오면 버림

		}
		else if(pri==lparen)//우선순위가 ( 의 우선순위이면
		{
			postfixPush(x);//stack에 ( push

		}
		else
		{
			while(getPriority(postfixStack[postfixStackTop])>=pri)//stack에 맨위에 있는 연산자 우선순위가 들어오는 연산자의 우선수위 보다 높거나 같은 동안
			{
				a=postfixPop();//stack에서 연산자 pop
				charCat(&a);//postfixExp에 저장
			}

			postfixPush(x);//들어온 연산자 stack에 push
		}

		exp++;//다음 문자로

	}

	while(postfixStackTop!=-1)//stack이 비기 전까지
	{

		a=postfixPop();//stack에서 연산자 pop
		charCat(&a);//postfixExp에 저장

	}


}
void debug()//연산 결과들과 stack에 쌓인 연산자를 출력하는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);//중위표기법으로 식 출력
	printf("postExp =  %s\n", postfixExp);//후위표기법으로 식 출력
	printf("eval result = %d\n", evalResult);//연산 결과 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);//중위연산에서 후위연산으로 변환할 때 stack에 쌓인 연산자 출력

	printf("\n");

}

void reset()//입력받았던 정보들을 초기화 시키는 함수
{
	infixExp[0] = '\0';//중위표기법 문자열 null로 바꿈
	postfixExp[0] = '\0';//후위표기법 문자열 null로 바꿈

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';//후위연산 stack의 요소 null로 초기화

	postfixStackTop = -1;//후위연산 stack의 top값 -1로 초기화(stack 비움)
	evalStackTop = -1;//연산결과 stack의 top값 -1로 초기화
	evalResult = 0;//연산결과 0으로 초기화
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int op1,op2;//피연산자 2개 선언
	int i=0;//문자열 순환 인덱스
	precedence pri;//우선순위 변수

	while(postfixExp[i]!='\0')//postfixExp배열이 null문자를 만나기 전까지
	{
		pri=getPriority(postfixExp[i]);//문자열 인덱스의 우선순위
		if(pri ==operand)//우선순위가 피연산자의 우선순위이면
		{
			evalPush(postfixExp[i]-'0');//피연산자를 정수형으로 바꾸어 스택에 push
		}
		else
		{
			op2=evalPop();//stack에서 숫자를 pop해 op2로 지정
			op1=evalPop();//stack에서 숫자를 pop해 op1로 지정

			switch(pri){

			case plus: evalPush(op1+op2); break;//우선순위가 덧셈 우선순위이면 피연산자 간 덧셈의 결과를 push
			case minus: evalPush(op1-op2); break;//우선순위가 뺄셈 우선순위이면 피연산자 간 뺄셈의 결과를 push
			case times: evalPush(op1*op2); break;//우선순위가 곱셈 우선순위이면 피연산자 간 곱셈의 결과를 push
			case divide: evalPush(op1/op2); break;//우선순위가 나눗셈 우선순위이면 피연산자 간 나눗셈의 결과를 push
			default: break;

			}
		}
		i++;//다음 인덱스로
	}

	evalResult=evalPop();//결국 마지막에 stack에 남는것은 연산의 결과

}
