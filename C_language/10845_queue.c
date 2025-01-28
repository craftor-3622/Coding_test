// https://www.acmicpc.net/problem/10845

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10000

typedef struct
{
	int intager;
	queuePointer* ptr;
} queuePointer;

queuePointer* queue = NULL;
int queueSize = 0;

void push(int comp) {
	queuePointer* ptr = NULL;

}

void pop() {
	if (queue == NULL) {
		printf("-1");
	}
	else {
		int temp = queue->intager;
		queue = queue->ptr;
		printf("%d", temp);
	}
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i; i < N; i++) {
		char input[5]; int num;
		scanf("%s", input);

		switch (*input) {
		case 'push':
			scanf("%d", &num);
			push(num);
			break;
		case 'pop':
			pop();
			break;
		}
	}

	return 0;
}