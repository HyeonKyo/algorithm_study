#include <stdio.h>
#include <stdlib.h>

int	compare(const void *a, const void *b)
{
	int	num1 = *(int *)a;
	int	num2 = *(int *)b;

	if (num1 < num2)
		return (-1);
	else if (num1 > num2)
		return (1);
	else
		return (0);
}

int		find_down_idx(int *arr, int base, int N);
int		find_up_idx(int *arr, int base, int H, int N);


int	main()
{
	int	N, H, n, i, j, base, past, cnt = 0;
	int	down[100000], up[100000] = {0, };

	scanf("%d %d", &N, &H);
	for (i = 0; i < N / 2; i++)
	{
		scanf("%d", down + i);
		scanf("%d", up + i);
	}
	qsort(up, N / 2, sizeof(int), compare);
	qsort(down, N / 2, sizeof(int), compare);

	past = N / 2;
	cnt = 2;
	for (base = 2; base < H; base++)
	{
		n = find_down_idx(down, base, N) + find_up_idx(up, base, H, N);
		if (past > n)
		{
			past = n;
			cnt = 1;
		}
		else if (past == n)
			cnt++;
	}
	printf("%d %d\n", past, cnt);
	return (0);
}

int		find_down_idx(int *arr, int base, int N)
{
	int idx, left, right = 0;

	left = 0;
	right = N / 2;
	while (left <= right)
	{
		idx = (left + right) / 2;
		if (arr[idx] > base)
			right = idx - 1;
		else
			left = idx + 1;
	}
	while (arr[idx] <= base && idx < N / 2)
		idx++;
	return ((N / 2) - idx);
}

int		find_up_idx(int *arr, int base, int H, int N)
{
	int idx, left, right = 0;

	left = 0;
	right = N / 2;
	while (left <= right)
	{
		idx = (left + right) / 2;
		if (arr[idx] > H - base)
			right = idx - 1;
		else
			left = idx + 1;
	}
	while (arr[idx] <= H - base && idx < N / 2)
		idx++;
	return ((N / 2) - idx);
}

/*
구간 1인 곳의 장애물 개수 = 석순 개수
구간 H인 곳의 장애물 개수 = 종유석 개수 = N / 2
구간 n인 곳의 장애물 개수 = (높이 >= n인 석순 개수) + (H - 높이 > n)인 종유석 개수
구간n은 H만큼 있음(2 <= n <= H)
장애물은 N개 있음.
*/