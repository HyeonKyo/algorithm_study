#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	ROUND -1
#define ANGLED -2

typedef struct	s_stack
{
	int	element[31];
	int	top;
}				stack;

void	push(stack *st, int bracket)
{
	st->element[++(st->top)] = bracket;
}

int		pop(stack *st)
{
	return (st->element[(st->top)--]);
}

int		check(int ln, stack *st, char *input);
void	print_sum(int ln, stack *st, char *input);

int main()
{
	char	input[31];
	stack	st;
	int		length;

	scanf("%s", input);
	length = strlen(input);
	
	memset(&st, 0, sizeof(stack));
	st.top = -1;
	if (!check(length, &st, input))
		printf("0\n");
	else
		print_sum(length, &st, input);
	return (0);
}

int		check(int ln, stack *st, char *input)
{
	int	tmp;

	for (int i = 0; i < ln; i++)
	{
		if (input[i] == '(')
			push(st, ROUND);
		else if (input[i] == '[')
			push(st, ANGLED);
		else if (input[i] == ')')
		{
			if (st->top == -1)
				return (0);
			if ((tmp = pop(st)) != ROUND)
				return (0);
		}
		else if (input[i] == ']')
		{
			if (st->top == -1)
				return (0);
			if ((tmp = pop(st)) != ANGLED)
				return (0);
		}
	}
	return (1);
}

void	print_sum(int ln, stack *st, char *input)
{
	int tmp, sum, i = 0;
	
	memset(st, 0, sizeof(stack));
	st->top = -1;
	for (i = 0; i < ln; i++)
	{
		sum = 0;
		if (input[i] == '(')
			push(st, ROUND);
		else if (input[i] == '[')
			push(st, ANGLED);
		else if (input[i] == ')')
		{
			while ((tmp = pop(st)) != ROUND)
				sum += tmp;
			if (sum == 0)
				push(st, 2);
			else
				push(st, sum * 2);
		}
		else
		{
			while ((tmp = pop(st)) != ANGLED)
				sum += tmp;
			if (sum == 0)
				push(st, 3);
			else
				push(st, sum * 3);
		}
	}
	sum = 0;
	while (st->top >= 0)
		sum += st->element[(st->top)--];
	printf("%d\n", sum);
}