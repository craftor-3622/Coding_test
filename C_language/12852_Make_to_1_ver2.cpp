// 이전 버전 : https://www.acmicpc.net/problem/1463
// https://www.acmicpc.net/problem/12852
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> dp;
vector<int> parent;

// 1. Top-down DP 로직 구성 
// 2. 경로 복원 구현

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	dp.resize(N + 1, 0);
	parent.resize(N + 1, -1);

	int div3, div2;
	for (int n = 2; n <= N; n++) {
		div3 = n % 3 == 0 ? n / 3 : n - 1;
		div2 = n % 2 == 0 ? n / 2 : n - 1;
		dp[n] = 1 + min({ dp[div3], dp[div2], dp[n - 1] });

		int p = div3;
		if (dp[p] > dp[div2]) p = div2;
		if (dp[p] > dp[n - 1]) p = n - 1;
		parent[n] = p;
	}

	cout << dp[N] << endl;

	int now = N;
	while (now != -1) {
		cout << now << " ";
		now = parent[now];
	}

	return 0;
}