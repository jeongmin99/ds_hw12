#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

	char command;
	printf("[----- [이정민]  [2018038030] -----]\n");

	int row, col;
	srand(time(NULL));
	setvbuf(stdout, NULL, _IONBF, 0);// Windows 용 이클립스의 콘솔창 글자 안 나오는 오류 수정


	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
	int** matrix_a = create_matrix(row, col);//행렬 A를 생성한다
	int** matrix_b = create_matrix(row, col);//행렬 B를 생성한다
	int** matrix_a_t = create_matrix(col, row);//행렬 A의 전치 행렬을 생성한다

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { return -1; }//만약 행렬A이나 행렬B가 가리키는 값이 없다면 프로그램 비정상종료

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z'://z를 누를 경우 행렬을 초기화한다(값을 배정)
			printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);//행렬 A 초기화
			fill_data(matrix_b, row, col);//행렬 B 초기화
			break;
		case 'p': case 'P'://p를 누를 경우 행렬을 출력한다.
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col);//행렬A 출력
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);//행렬B 출력
			break;
		case 'a': case 'A'://a를 누를 경우 행렬A에 행렬B를 더한다.
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
		case 's': case 'S'://s를 누를 경우 행렬A에서 행렬B를 뺀다
			printf("Subtract two matrices \n");
			subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
		case 't': case 'T'://t를 누를 경우 행렬A를 전치시킨다
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			print_matrix(matrix_a_t, col, row);
			break;
		case 'm': case 'M'://m을 누를경우 행렬A와 행렬A의 전치행렬을 곱한다.
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
		case 'q': case 'Q'://q를 누를경우 행렬들의 메모리를 해제하고 프로그램을 종료한다.
			printf("Free all matrices..\n");
			free_matrix(matrix_a_t, col, row);
			free_matrix(matrix_a, row, col);
			free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');//q를 누를 때 까지 반복

	return 1;//정상종료
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//생성 실패 메시지
		return NULL;//null값 리턴
	}
	int** matrix = (int**)malloc(sizeof(int*) * row);//int**형 변수 matrix에 row 개의 메모리를 할당

		for (int i = 0; i < row; i++)//row 크기 만큼
		{
			matrix[i] = (int*)malloc(sizeof(int) * col);//int*형 변수 matrix[i]에 col 개의 메모리를 할당

		}

	/* 후처리 부분 */
	if (matrix == NULL) {//matirx값이 null이면

		printf("matrix가 생성되지 못했습니다. 다시 시도해주세요\n");//생성 실패 메세지
		return NULL;
	}

	return matrix;//matrix값 반환

}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return;


	}
	else if (matrix == NULL)//matrix가 존재하지 않으면
	{
		printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
		return;

	}

	//이상 없는 경우
	else
	{

		for (int i = 0; i < row; i++)//행 크기 만큼 반복
		{
			for (int j = 0; j < col; j++)//열 크기 만큼 반복
			{
				printf("%2d ", matrix[i][j]);//행렬의 값들을 출력
			}

			printf("\n");
		}
	}

}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return -1;//비정상 종료

	}
	if (matrix == NULL)//matrix가 존재하지 않으면
		{
			printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
			return -1;//비정상 종료

		}

	for (int i = 0; i < row; i++)//행의 크기 만큼
	{
		if(matrix[i]!=NULL)//행렬의 열들이 존재하는 경우에
		{
			free(matrix[i]);//행렬의 열 부분 메모리 해제
		}

	}

	/* 후처리 부분 */
	if(matrix!=NULL)//행렬이 존재하면
	{
		free(matrix);//행렬 메모리 해제
		return 1;//정상 종료
	}


	return -1;//비정상 종료
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return -1;//비정상 종료

	}
	else if (matrix == NULL)//matrix가 존재하지 않으면
	{
		printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
		return -1;//비정상 종료

	}
	//이상 없는 경우
	else
	{
		for (int i = 0; i < row; i++)//행 크기 만큼
		{
			for (int j = 0; j < col; j++)//열 크기 만큼
			{
				matrix[i][j] = rand() % 20;//행렬에 0~19 사이의 값들을 배정
			}

			printf("\n");
		}
		return 1; //정상 종료
	}

	/* 후 처리(이상 있는 경우)*/
	return -1;//비정상 종료
}







/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{


	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return -1;//비정상 종료

	}

	else if (matrix_a == NULL || matrix_b == NULL)//행렬A 또는 행렬B가 존재하지 않으면
	{
		printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
		return -1;//비정상 종료

	}
	//이상 없는 경우
	else
	{
		int** matrix_tempa = create_matrix(row, col);//행렬A와 행렬B를 더한 행렬을 저장할 임시 행렬 생성
		for (int i = 0; i < row; i++)//행 크기 만큼 반복
		{
			for (int j = 0; j < col; j++)//열 크기 만큼 반복
			{
				matrix_tempa[i][j] = matrix_a[i][j] + matrix_b[i][j];//행렬A와 행렬B를 더한 값을 임시 행렬에 저장
			}
		}

		print_matrix(matrix_tempa, row, col);//임시 행렬을 출력

		/* 후처리 부분 */
				if(matrix_tempa!=NULL)//matrix_temp가 존재하면
				{
					free(matrix_tempa);//임시 행렬 메모리 반환
					return 1;//정상 종료
				}


	}

	/*후처리(이상 있는 경우) */
	return -1;//비정상 종료

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{

	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return -1;//비정상 종료

	}

	else if (matrix_a == NULL || matrix_b == NULL)//행렬A 또는 행렬B가 존재하지 않으면
	{
		printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
		return -1;//비정상 종료

	}
	//이상 없는 경우
	else
	{
		int** matrix_temps = create_matrix(row, col);//행렬A와 행렬B를 뺀 행렬을 저장할 임시 행렬 생성
		//전처리 부분										  */
		if(matrix_temps==NULL)//임시 행렬이 생성에 실패했으면
		{
			printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
			return -1;//비정상 종료
		}
		for (int i = 0; i < row; i++)//행 크기 만큼
		{
			for (int j = 0; j < col; j++)//열 크기 만큼
			{
				matrix_temps[i][j] = matrix_a[i][j] - matrix_b[i][j];//행렬A와 행렬B를 뺀 값을 임시 행렬에 저장
			}
		}

		print_matrix(matrix_temps, row, col);//임시 행렬을 출력


		/* 후처리 부분 */
		if(matrix_temps!=NULL)//matrix_temp가 존재하면
		{
			free(matrix_temps);//임시 행렬 메모리 반환
			return 1;//정상 종료
		}


	}

	return -1;//비정상 종료

}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return -1;//비정상 종료

	}

	else if (matrix == NULL || matrix_t == NULL)//행렬A 또는 행렬A의 전치행렬이 존재하지 않으면
	{
		printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
		return -1;//비정상 종료

	}
	//이상 없는 경우
	else
	{
		for (int i = 0; i < row; i++)//행 크기 만큼 반복
		{
			for (int j = 0; j < col; j++)//열 크기 만큼 반복
			{
				matrix_t[i][j] = matrix[j][i];//행렬을 전치 시켜 전치 행렬값을 담을 행렬에 저장
			}
		}


		return 1;//정상종료
	}

	/* 후처리(이상 있는 경우)*/
	return -1;//비정상 종료
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{

	/* 전처리 부분*/
	if (row <= 0 || col <= 0) {//row 와 col이 0 이하이면
		printf("Check the sizes of row and col!\n");//출력 실패 메시지
		return -1;//비정상 종료

	}

	else if (matrix_a == NULL || matrix_t == NULL)//행렬A 또는 행렬A의 전치행렬이 존재하지 않으면
	{
		printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
		return -1;//비정상 종료

	}

	else
	{
		int** matrix_tempm = create_matrix(row, row);/*행렬A와 전치 행렬을 곱한 행렬을 저장할 임시 행렬 생성
												  행렬 간 곱셈의 결과 행렬은 앞 행렬의 행과 뒷 행렬의 열의 크기를 가지고
												  뒷 행렬은 앞 행렬의 전치 행렬이므로 뒷행렬의 열의 크기는 앞 행렬의 행의
												  크기와 같다.
		//전처리 부분										  */
		if(matrix_tempm==NULL)
		{
			printf("matrix가 존재하지 않습니다. matrix를 생성해주세요\n");//출력실패 메시지
			return -1;//비정상 종료
		}

		for (int i = 0; i < row; i++)//행 크기 만큼
		{
			for(int j=0;j<row;j++)//헹 크기 만큼
			{
				matrix_tempm[i][j]=0;//임시 행렬의 값 초기화

				for(int k=0;k<col;k++)//열 크기 만큼
				{

					matrix_tempm[i][j]+=matrix_a[i][k]*matrix_t[k][j];//임시 행렬에 행렬곱의 값 대입
				}
			}
		}

		print_matrix(matrix_tempm, row, row);//임시 행렬을 출력

		/* 후처리 부분 */
		if(matrix_tempm!=NULL)//matrix_temp가 존재하면
		{
				free(matrix_tempm);//임시 행렬 메모리 반환
				return 1;//정상 종료
		}


	}

	return -1;//비정상 종료

}

