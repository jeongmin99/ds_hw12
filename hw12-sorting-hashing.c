/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;
	setvbuf(stdout,NULL,_IONBF,0);
	srand(time(NULL));
	printf("[----- [이정민] [2018038030] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);//배열 초기화(배열 랜덤값 배정)
			break;
		case 'q': case 'Q':
			freeArray(array);//배열 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array);//선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array);//삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array);//버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array);//셸 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);//배열 출력
			quickSort(array, MAX_ARRAY_SIZE);//퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);//정렬 후 배열 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);//배열 출력
			hashing(array, &hashtable);//해싱을 통해 해시값에 따른 키값 배정
			printArray(hashtable);//해시 테이블 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);//검색할 키값 입력
			printArray(hashtable);//해시테이블 출력
			index = search(hashtable, key);//키값에 따른 인데그
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);//배열 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;//*a의 값 temp에 전달

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; //0부터 n-1까지

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)//a에 메모리가 있으면
		free(a);//a 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {//a값이 없으면
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);//인덱스 값 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);//a배열 값 출력
	printf("\n");
}


int selectionSort(int *a)//선택 정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬 전

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;//최솟값 인덱스는 현재 조사하는 값의 인덱스
		min = a[i];//최솟값은 현재 조사하는 값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])//최솟값보다 작은 값이 나타나면
			{
				min = a[j];//최솟값 갱신
				minindex = j;//최솟값 인덱스 갱신
			}
		}
		a[minindex] = a[i];//현재 조사하고 있는 값을  최솟값이 있는 곳에 대입
		a[i] = min;//최솟값을 현재 조사하고 있는 값 위치에 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후
	return 0;
}

int insertionSort(int *a)//삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬 전

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//배열의 i번째 값을 기준으로 잡읍
		j = i;//j를 이용해 i번 인덱스 전부터 앞으로 이동하며 조사
		while (a[j-1] > t && j > 0)//j-1번 값이 현재 조사하는 값보다 크다면
		{
			a[j] = a[j-1];/* 한칸 뒤로 밀어냄*/
			j--;
		}
		a[j] = t;//j의 자리에 값 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬 전

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//배열 사이즈만큼 반복
	{
		for (j =MAX_ARRAY_SIZE-1;j>i;j--)//배열에 각각의 요소에 접근하기 위해 반복
		{
			if (a[j-1] > a[j])//j기준 인접 원소가 현재원소보다 크면
			{
				t = a[j-1];    /* swap */
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후

	return 0;
}

int shellSort(int *a)//셸 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬 전

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//간격을 배열에 1/2로 둔 후 단계가 진행될 때마다 간격을 1/2한다.
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j가 하나씩이 아닌 간격 만큼 증가
			{
				/* 그 간격을 기준으로 삽입정렬이 실행된다. */
				v = a[j];//v는 j번째 값
				k = j;//k를 이용해 j 이전 인덱스 앞부분 조사
				while (k > h-1 && a[k-h] > v)	//k-h번 값이 현재 조사하는 값보다 크면
				{
					a[k] = a[k-h];//한칸 뒤로 민다.
					k -= h;
				}
				a[k] = v;//k의 자리에 값 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후

	return 0;
}

int quickSort(int *a, int n)//퀵 정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//피벗은 맨 오른쪽
		i = -1;//left는 배열의 맨 왼쪽 -1
		j = n - 1;//right는 배열의 맨 오른쪽

		while(1)
		{
			while(a[++i] < v);//i번째 값이 피벗보다 작으면 i값 증가
			while(a[--j] > v);//j번째 값이 피벗보다 크면 j값 증가

			if (i >= j) break;//i와 j가 교차되면 while문 빠져나감
			t = a[i];/*i번째 값과 j번째 값 swap*/
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];/* 피벗과 교자된 부분에서의 값을 swap*/
		a[i] = a[n-1];
		a[n-1] = t;

		//교차된 부분을 기준으로 두개로 나누어 퀵소트 재귀 호출
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key)//해시 함수(제산 함수를 이용)
{
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)//해싱을 진행 하는 함수(데이터 삽입시 선형조사법 이용)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//해시 테이블 값들 -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];//a의 i번째 인덱스를 키로 한다.
		hashcode = hashCode(key);//해시 함수를 통해 키에 따른 해시코드(주소) 부여.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)//해시코드(주소)에 대한 테이블에 값이 없으면
		{
			hashtable[hashcode] = key;//해시코드(주소)에 따른 테이블에 키값을 대입
		} else 	{

			index = hashcode;//index는 해시코드(주소)

			while(hashtable[index] != -1)//index에 따른 해시 테이블 값이 존재하면(빈 버킷이 없으면)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//index값을 증가시켜 제산함수 재시행(다른 버킷을 찾는다)
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//index(주소)에 따른 테이블값에 키를 대입
		}
	}

	return 0;
}

int search(int *ht, int key)//선형 조사법 탐색함수
{
	int index = hashCode(key);//키값에 따른 해시코드를 구해 인덱스(주소)를 정함

	if(ht[index] == key)//키값과 인덱스에 따른 해시테이블 값이 일치하면
		return index;//인덱스(주소) 리턴

	while(ht[++index] != key)//index값을 증가시키면서
	{
		index = index % MAX_HASH_TABLE_SIZE;//해시코드를 새로 생성
	}
	return index;//인덱스(주소) 리턴
}



