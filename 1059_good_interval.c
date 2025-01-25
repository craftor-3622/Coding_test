// https://www.acmicpc.net/problem/1059

#include <stdio.h>
#include <stdlib.h>

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main() {
	int L;
	scanf("%d", &L);

	// 집합 S 입력
	int* S = (int*)malloc((L + 1) * sizeof(int));
	S[0] = 0;
	for (int i = 1; i <= L; i++)
		scanf("%d", &S[i]);

	// Sorting (bubble-sort)
	for (int i = 1; i <= L - 1; i++)
		for (int j = i; j <= L; j++)
			if (S[i] > S[j]) swap(&S[i], &S[j]);

	// finding
	int n;
	scanf("%d", &n);
	int min = 0;
	int	max = S[L];

	int amount = 0;
	int isSet = 1;

	// 좋은 구간 가능 여부
	for (int i = 0; i <= L; i++) {
		if (S[i] == n) isSet = 0;
	}

	// n보다 작은 최대 min 값 및 n보다 큰 최소 max 값 설정
	for (int i = 0;  isSet = 1 && i < L; i++) {
		if (n > S[i] && n < S[i + 1]) {
			min = S[i]; max = S[i + 1];
			break;
		}
	}

	// 구간 개수 구하기
    // 좋은 구간의 왼쪽의 숫자 범위는 min + 1 ~ n 까지
    // 오른쪽의 숫자 범위는 n ~ max - 1 까지
    // 단, [n, n]은 구간이 아니므로 제외
	if (isSet == 1) {
		amount = (n - min) * (max - n) - 1;
	}

	printf("%d", amount);

	free(S);
	return 0;
}