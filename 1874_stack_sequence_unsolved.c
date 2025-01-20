// https://www.acmicpc.net/problem/1874

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int stack[100000] = {
	0,
};
int size = 0; // 스택의 현재 크기

int action[200000] = {
	0,
}; // 스택에 push한 경우 1, pop한 경우 -1을 순차적으로 저장합니다.
int act_count = 0;

void push(int comp)
{
	stack[size] = comp;
	size++;
	action[act_count] = 1;
	act_count++;
}

void pop()
{
	// return stack[size - 1];
	size--;
	action[act_count] = -1;
	act_count++;
}

int top()
{
	return stack[size - 1];
}

int main()
{
	int N;
	scanf("%d", &N);
	int num = 0;	   // 이 숫자는 마지막으로 스택에 넣은 숫자를 의미합니다.
	int available = 1; // 순열 구성이 가능한 경우 1(기본값), 불가능하면 -1을 출력합니다.

	for (int i = 1; i <= N; i++)
	{
		int input;
		scanf("%d", &input);

		// 입력 값이 마지막으로 스택에 넣은 숫자보다 큰 경우,
		// 같아질 때까지 push 후 pop하여 스택을 넣어줍니다.
		if (input > num)
		{
			while (input == num)
			{
				push(i);
				num++;
			}
			pop();
		}
		// 반대의 경우, 이 때는 최상층에 있는 스택의 숫자를 확인합니다.
		// 두 숫자가 같은 경우 스택에서 pop하며, 다른 경우 불가능함을 출력합니다.
		else
		{
			if (top() == num)
				pop;
			else
			{
				available = -1;
				break;
			}
		}
	}

	if (available == -1)
		printf("NO");
	else
		for (int i = 0; i < 2 * N; i++)
		{
			if (action[i] == 1)
				printf("+"); // push
			else
				printf("-"); // pop

			if (i != (2 * N - 1))
				printf("\n");
		}

	return 0;
}