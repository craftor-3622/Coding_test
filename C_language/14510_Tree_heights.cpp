// https://swexpertacademy.com/main/code/userProblem/userProblemDetail.do?contestProbId=AYFofW8qpXYDFAR4
// 나머지 계산 + Greedy와 합쳐 환상의 콜라보레이션을 일으킨 문제
// 문제 난이도가 왜 D2인가 싶으면서 알면 D2가 맞다 싶은 문제

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N;
		int max_height = 0;
		cin >> N;

		vector<int> trees(N, 0);
		// odd는 홀수 날 개수, even은 짝수 날 개수, days는 소요 날 수
		int odd = 0;
		int even = 0;
		int days = 0;

		for (int i = 0; i < N; i++) {
			cin >> trees[i];
			if (max_height < trees[i]) max_height = trees[i];
		}

		for (int i = 0; i < N; i++) {
			trees[i] = max_height - trees[i];
			even += trees[i] / 2;
			odd += trees[i] % 2;
		}

		if (odd > even) days = even * 2 + (odd - even) * 2 - 1;
		else if (even > odd) {
			days = odd * 2;
			days += (even - odd) / 3 * 4;
			if ((even - odd) % 3 != 0) days += (even - odd) % 3 + 1;
		}
		else days = odd * 2;

		cout << "#" << tc << " " << days << endl;
	}

	return 0;
}

// 한줄 평 : 코드 자체가 자료 구조를 요구하는 것도 아니어서 어이없었던 문제.