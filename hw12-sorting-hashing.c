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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

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
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;//*a�� �� temp�� ����

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; //0���� n-1����

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)//a�� �޸𸮰� ������
		free(a);//a �޸� ����
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {//a���� ������
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);//a�迭 �� ���
	printf("\n");
}


int selectionSort(int *a)//���� ����
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//���� ��

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;//�ּڰ� �ε����� ���� �����ϴ� ���� �ε���
		min = a[i];//�ּڰ��� ���� �����ϴ� ��
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])//�ּڰ����� ���� ���� ��Ÿ����
			{
				min = a[j];//�ּڰ� ����
				minindex = j;//�ּڰ� �ε��� ����
			}
		}
		a[minindex] = a[i];//���� �����ϰ� �ִ� ����  �ּڰ��� �ִ� ���� ����
		a[i] = min;//�ּڰ��� ���� �����ϰ� �ִ� �� ��ġ�� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ��
	return 0;
}

int insertionSort(int *a)//���� ����
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//���� ��

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//�迭�� i��° ���� �������� ����
		j = i;//j�� �̿��� i�� �ε��� ������ ������ �̵��ϸ� ����
		while (a[j-1] > t && j > 0)//j-1�� ���� ���� �����ϴ� ������ ũ�ٸ�
		{
			a[j] = a[j-1];/* ��ĭ �ڷ� �о*/
			j--;
		}
		a[j] = t;//j�� �ڸ��� �� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ��

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//���� ��

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//�迭 �����ŭ �ݺ�
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//�迭�� ������ ��ҿ� �����ϱ� ���� �ݺ�
		{
			if (a[j-1] > a[j])//j���� ���� ���Ұ� j�ǰ����� ũ��
			{
				t = a[j-1];    /* swap */
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ��

	return 0;
}

int shellSort(int *a)//�� ����
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//���� ��

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//������ �迭�� 1/2�� �� �� �ܰ谡 ����� ������ ������ 1/2�Ѵ�.
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j�� �ϳ����� �ƴ� ���� ��ŭ ����
			{
				/* �� ������ �������� ���������� ����ȴ�. */
				v = a[j];//v�� j��° ��
				k = j;//k�� �̿��� j ���� �ε��� �պκ� ����
				while (k > h-1 && a[k-h] > v)	//k-h�� ���� ���� �����ϴ� ������ ũ��
				{
					a[k] = a[k-h];//��ĭ �ڷ� �δ�.
					k -= h;
				}
				a[k] = v;//k�� �ڸ��� �� ����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ��

	return 0;
}

int quickSort(int *a, int n)//�� ����
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//�ǹ��� �� ������
		i = -1;//left�� �迭�� �� ���� -1
		j = n - 1;//right�� �迭�� �� ������

		while(1)
		{
			while(a[++i] < v);//i��° ���� �ǹ����� ������ i�� ����
			while(a[--j] > v);//j��° ���� �ǹ����� ũ�� j�� ����

			if (i >= j) break;//i�� j�� �����Ǹ� while�� ��������
			t = a[i];/*i��° ���� j��° �� swap*/
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];/* �ǹ��� ���ڵ� �κп����� ���� swap*/
		a[i] = a[n-1];
		a[n-1] = t;

		//������ �κ��� �������� �ΰ��� ������ ����Ʈ ��� ȣ��
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key)//�ؽ� �Լ�(���� �Լ��� �̿�) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)//�ؽ��� ���� �ϴ� �Լ�(������ ���Խ� ��������� �̿�)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//�ؽ� ���̺� ���� -1�� �ʱ�ȭ
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
		key = a[i];//a�� i��° �ε����� Ű�� �Ѵ�.
		hashcode = hashCode(key);//�ؽ� �Լ��� ���� Ű�� ���� �ؽ��ڵ�(�ּ�) �ο�.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)//�ؽ��ڵ�(�ּ�)�� ���� ���̺��� ���� ������
		{
			hashtable[hashcode] = key;//�ؽ��ڵ�(�ּ�)�� ���� ���̺��� Ű���� ����
		} else 	{

			index = hashcode;//index�� �ؽ��ڵ�(�ּ�)

			while(hashtable[index] != -1)//index�� ���� �ؽ� ���̺� ���� �����ϸ�(�� ��Ŷ�� ������)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//index���� �������� �����Լ� �����(�ٸ� ��Ŷ�� ã�´�)
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//index(�ּ�)�� ���� ���̺����� Ű�� ����
		}
	}

	return 0;
}

int search(int *ht, int key)//���� ����� Ž���Լ�
{
	int index = hashCode(key);//Ű���� ���� �ؽ��ڵ带 ���� �ε���(�ּ�)�� ����

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}


