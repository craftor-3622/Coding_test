// https://www.acmicpc.net/problem/7579
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<int> cost;
vector<int> memory;
vector<int> dp;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;

	memory.resize(N);
	for (int n = 0; n < N; n++) cin >> memory[n];
	cost.resize(N);
	for (int n = 0; n < N; n++) cin >> cost[n];
	dp.resize(N * 100 + 1, -1);
	dp[0] = 0;

	for (int n = 0; n < N; n++) {
		for (int i = N * 100; i > 0; i--)
			if (dp[i] != -1)
				dp[i + cost[n]] = max(dp[i] + memory[n], dp[i + cost[n]]);
		dp[cost[n]] = max(dp[0] + memory[n], dp[cost[n]]);
	}

	int ans;
	for (int c = 0; c <= N * 100; c++) {
		if (dp[c] >= M) { ans = c; break; }
	}

	cout << ans;

	return 0;
}