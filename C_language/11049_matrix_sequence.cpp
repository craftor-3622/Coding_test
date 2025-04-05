// https://www.acmicpc.net/problem/11049
// DP + 분할 정복. DP 활용 중 어려운 케이스 (Floyd-Warshall도 같은 로직 사용)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#define min(a, b) a < b ? a : b

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);

	int N;
	cin >> N;

	vector<int> rows(N);
	vector<int> cols(N);

	for (int i = 0; i < N; i++) cin >> rows[i] >> cols[i];

	// dp[i][j] : i번째부터 j번째 까지의 행렬 곱셈 연산 최소 횟수
	vector<vector<long long int>> dp(N, vector<long long int>(N, 1e15));
	for (int i = 0; i < N; i++) dp[i][i] = 0;

	for (int n = 1; n < N; n++)	{
		for (int i = 0; i < N - n; i++)	{
			for (int k = i; k < i + n; k++)	{
				dp[i][i + n] = min(dp[i][i + n],
					dp[i][k] + dp[k + 1][i + n] + rows[i] * cols[k] * cols[i + n]);
			}
		}
	}

	cout << dp[0][N - 1];

	return 0;
}