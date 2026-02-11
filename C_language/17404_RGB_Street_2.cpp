// https://www.acmicpc.net/problem/17404
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

vector<array<int, 3>> cost;
vector<array<int, 3>> dp;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;

	cost.resize(N);
	for (int i = 0; i < N; i++)
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	dp.resize(N, array<int, 3>());

	int res = 1e8;
	for (int i = 0; i < 3; i++) {
		fill(dp.begin(), dp.end(), array<int, 3>
			({ (int)1e8,(int)1e8,(int)1e8 }));
		dp[0][i] = cost[0][i];
	
		for (int n = 1; n < N - 1; n++) {
			for (int k = 0; k < 3; k++) {
				dp[n][k] = min(dp[n - 1][(k + 1) % 3], dp[n - 1][(k + 2) % 3]) + cost[n][k];
			}
		}

		dp[N - 1][(i + 1) % 3] = min(dp[N - 2][i], dp[N - 2][(i + 2) % 3]) + cost[N - 1][(i + 1) % 3];
		dp[N - 1][(i + 2) % 3] = min(dp[N - 2][i], dp[N - 2][(i + 1) % 3]) + cost[N - 1][(i + 2) % 3];

		res = min(res, dp[N - 1][(i + 1) % 3]);
		res = min(res, dp[N - 1][(i + 2) % 3]);
	}

	cout << res;
	return 0;
}
/*
원형 DP에 대한 후기.
초기 값이 마지막에도 영향을 미칠 수 있다는 점 때문에,
선형 DP처럼 한 번의 점화식으로 처리하기 어렵다.

따라서 시작 상태를 고정해 원형 제약을 끊고,
선형 DP로 접근해 각 경우 별 결과를 비교하면 된다.
*/