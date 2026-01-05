// https://www.acmicpc.net/problem/2342
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<vector<vector<int>>> dp;
vector<int> order;

int cost(int now, int order) {
	if (now == order) return 1;
	else if (now == 0) return 2;
	else if ((now + order) % 2 == 1) return 3;
	else return 4;
}

int dfs(int size, int now, int left, int right) {
	if (now == size) return 0;
	if (dp[now][left][right] != 1e8) return dp[now][left][right];

	dp[now][left][right] = min(cost(left, order[now]) + dfs(size, now + 1, order[now], right),
		cost(right, order[now]) + dfs(size, now + 1, left, order[now]));

	return dp[now][left][right];
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int temp;
	while (true) {
		cin >> temp;
		if (temp == 0) break;
		order.push_back(temp);
	}

	int N = order.size();
	dp.resize(N + 1, vector<vector<int>>(5, vector<int>(5, 1e8)));
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			dp[N][i][j] = 0;

	cout << dfs(N, 0, 0, 0);

	return 0;
}
/*
후기.
직관적으로는 Greedy가 성립할 것처럼 보이지만,
입력 수열에 따라 이전 선택이 이후 비용에 영향을 미치는 구조로 인해
국소 최적해가 전체 최적해를 보장하지 않는다는 점에서 함정이 존재.
반례 - 2 1 3 2 3 0
Top-down DP로 상태를 정의하자, dp의 최소값을 구하는 형태로 정리됨.

이 과정에서 DP가 과거의 선택을 저장하는 것이 아니라,
현재 상태에서 앞으로의 최적 비용만을 저장한다는 개념을
다시 한 번 명확히 이해할 수 있었다.
상태 정의와 DP의 의미를 정확히 잡는 것이 훨씬 중요하다는 점을 잘 보여주는 예제.
*/