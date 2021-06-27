#include <stdio.h>
#include <stdlib.h>

/*
처음부터 끝까지 하나씩 넘어가면서 바꿔주고 긴줄 찾는 함수로 보냄
가장 긴 줄 찾는 함수 = 재귀로 max값 계속 변경
max값은 전역변수로
*/

int max = 0;

char	**copy_str(char src[][51], int N)
{
	int 	i, j = 0;
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * N);
	for (int i = 0; i < N; i++)
		dst[i] = (char *)malloc(sizeof(char) * N + 1);
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			dst[i][j] = src[i][j];
	return (dst);
}

void	find_max(char **arr, int N)
{
	int 	i, j, k, ln = 0;
	char	c;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N - 1; j++)
		{
			c = arr[i][j];
			ln = 1;
			k = j + 1;
			while (k < N && c == arr[i][k])
			{
				k++;
				ln++;
			}
			if (max < ln)
				max = ln;
			if (i < N - 1)
			{
				k = i + 1;
				ln = 1;
				while (k < N && c == arr[k][j])
				{
					k++;
					ln++;
				}
				if (max < ln)
					max = ln;
			}
		}
	}
}

void	swap(int i, int j, char **arr, int N)
{
	char	tmp;

	if (j < N - 1)
	{
		if (arr[i][j] != arr[i][j + 1])
		{
			tmp = arr[i][j];
			arr[i][j] = arr[i][j + 1];
			arr[i][j + 1] = tmp;
			find_max(arr, N);
			tmp = arr[i][j];
			arr[i][j] = arr[i][j + 1];
			arr[i][j + 1] = tmp;
		}
	}
	if (i < N - 1)
	{
		if (arr[i][j] != arr[i + 1][j])
		{
			tmp = arr[i][j];
			arr[i][j] = arr[i + 1][j];
			arr[i + 1][j] = tmp;
			find_max(arr, N);
			tmp = arr[i][j];
			arr[i][j] = arr[i + 1][j];
			arr[i + 1][j] = tmp;
		}
	}
}

void	swaping(int N, char candy[][51])
{
	int 	i, j = 0;
	char	**arr;

	arr = copy_str(candy, N);
	for (i = 0; i < N; i++)
		for (j = 0; j < N - 1; j++)
			swap(i, j, arr, N);
}

int	main()
{
	int		N, i, j = 0;
	char	candy[50][51];

	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%s", candy[i]);
	//------------------------------
	swaping(N, candy);
	printf("%d\n", max);
	return (0);
}