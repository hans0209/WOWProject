#include "stdafx.h"
#include "stdlib.h"

int main()
{
	int arr1[2][3] = {};
	int arr2[2][3] = {};
	int i = 0;
	int j = 0;
	int m = 0; 
	int n = 0;
	int x = 0;
	int y = 0;

	printf("첫 번째 배열 입력\n");
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			scanf("%d", &arr1[i][j]);
		}
	}

	printf("두 번째 배열 입력\n");
	for (m = 0; m < 2; m++)
	{
		for (n = 0; n < 3; n++)
		{
			scanf("%d", &arr2[m][n]);
		}
	}


	for (x = 0; x < 2; x++)
	{
		for (y = 0; y < 3; y++)
		{
			printf("%d ", arr1[x][y] * arr2[x][y]);
		}
		printf("\n");
	}


	system("pause");
	return 0;
}
