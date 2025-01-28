// https://www.acmicpc.net/problem/10828
// 스택 자료 구조를 배열로 구현한 코드입니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int N; scanf("%d", &N);

    int stacks[10000] = { 0, };
    int size = 0;
    
    for (int i = 1; i <= N; i++) {
		char order[6]; scanf("%s", order);

		if (strcmp(order, "push") == 0) {           // push
			int component; scanf("%d", &component);
			stacks[size] = component;
			size++;
		}
		else if (strcmp(order, "pop") == 0) {       // pop
			if (size <= 0) printf("-1\n");
			else {
				printf("%d\n", stacks[size - 1]);
				stacks[size - 1] = 0;
				size--;
			}
		}
		else if (strcmp(order, "size") == 0) {      // size
			printf("%d\n", size);
		}
		else if (strcmp(order, "empty") == 0) {     // empty
			if (size <= 0) printf("1\n");
			else printf("0\n");
		}
		else {                                    // top
			if (size <= 0) printf("-1\n");
			else printf("%d\n", stacks[size - 1]);
		}
	}

    return 0;
}