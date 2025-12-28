// https://www.acmicpc.net/problem/1311
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> D;
vector<int> dp;
vector<int> worked;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;

	D.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> D[i][j];

	dp.resize((1 << N), 1e8);
	worked.resize((1 << N), 0);

	dp[0] = 0;
	worked[0] = 0;

	for (int n = 0; n < (1 << N) - 1; ++n) {
		for (int k = 0; k < N; ++k) {
			if (n & (1 << k)) continue;
			if (dp[n | 1 << k] > dp[n] + D[worked[n]][k]) {
				dp[n | 1 << k] = dp[n] + D[worked[n]][k];
				worked[n | 1 << k] = worked[n] + 1;
			}
		}
	}

	cout << dp[(1 << N) - 1];

	return 0;
}
/*
후기.
pow(2, N)을 사용해 상태 공간을 계산했으나,
비트마스크 DP 문제의 성격상 적절하지 않은 선택.
1 << N 형태가 정수 비트 시프트 연산으로 정확히 2^N을 표현하며,
타입 안정성 및 성능에서도 비트마스크 기반 DP에서 적절한 표현이다.

추가 정보.
지금처럼 bit 수를 배열에 저장해도 되지만,
int step = __builtin_popcount(mask);
처럼 비트 계산 함수를 사용해도 된다.
gcc 컴파일러 내장 함수로 unsigned int를 받아서 1인 bit 개수를 반환한다.
*/