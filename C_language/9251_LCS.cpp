// https://www.acmicpc.net/problem/9251
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string a, b;
vector<vector<int>> dp;

int main() {
	freopen("sample_input.txt", "r", stdin);

	cin >> a >> b;

	int length = a.size();
	int width = b.size();

	dp.resize(length + 1, vector<int>(width + 1, 0));

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (a[i] == b[j]) dp[i + 1][j + 1] = max({ dp[i][j] + 1, dp[i][j + 1], dp[i + 1][j] });
			else dp[i + 1][j + 1] = max({ dp[i][j], dp[i][j + 1], dp[i + 1][j] });
		}
	}

	cout << dp[length][width];

	return 0;
}
/*
후기.
LCS 문제. (Longest Common Subsequence(최장 공통 부분수열))
기존 최장 공통 문자열과는 달리, 패턴 매칭 알고리즘을
사용할 수 없다는 것을 알게 되었다.
*/