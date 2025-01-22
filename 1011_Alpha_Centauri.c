// https://www.acmicpc.net/problem/1011

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {
	// 테스트 케이스 개수를 입력받습니다.
	int T;
	scanf("%d", &T);

	// 케이스 개수만큼 작동 횟수를 출력합니다.
	for (int i = 0; i < T; i++) {
		int x, y, length, remaining;
		scanf("%d %d", &x, &y);
		length = y - x;				// x와 y의 절대 거리입니다.
		remaining = length;			// n회차 작동 시킬 경우 남은 거리입니다.

		int n = 1;					// 작동 회차입니다.
		int count = 0;				// 작동 회수입니다.

		// 거리가 충분히 멀 경우, 여러번 작동시켜 남은 거리를 빠르게 줄입니다.
		// (매 선택마다 (k_n)+1 and (k_n)-1 선택)
		for (n; remaining >= 2 * n; n++) {
			count += 2;
			remaining = length - n * (n + 1);
		}

		// 만약 남은 거리가 충분하지 않은 경우, 작동 중간에 단 한번 k_n을 선택합니다.
		// 남은 거리가 어느 정도냐에 따라 횟수가 1회 또는 2회 더 추가됩니다.
		if (remaining > n && remaining < 2 * n) {
			count += 2;
		}
		else if (remaining > 0 && remaining <= n) {
			count++;
		}

		// 작동 횟수를 출력합니다.
		printf("%d", count);

		if (i != T - 1) {
			printf("\n");
		}

	}
	
	return 0;
}