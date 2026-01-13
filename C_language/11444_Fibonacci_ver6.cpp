// https://www.acmicpc.net/problem/11444
// 이전 문제 : https://www.acmicpc.net/problem/1003
/*
피보나치 문제는 순수 컴퓨터 공학을 활용한다면 recursive + DP로 O(N)까지 줄일 수 있다.
여기서 수학 지식인 행렬을 활용하면 O(log N)까지 줄일 수 있다.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define DIVISOR 1000000007

vector<vector<long long>> dp[100];

// 2차 정방 행렬 기준 연산
vector<vector<long long>> multiplyMatrix(vector<vector<long long>>& a, vector<vector<long long>>& b) {
	long long x = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % DIVISOR;
	long long y = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % DIVISOR;
	long long m = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % DIVISOR;
	long long n = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % DIVISOR;
	return { { x, y}, {m, n} };
}

int main() {
	// freopen("sample_input.txt", "r", stdin);

	// Matrix 배열 설정
	for (int i = 0; i < 100; i++) dp[i].resize(2, vector<long long>(2));

	dp[0] = { {1, 1}, {1, 0} };
	for (int i = 1; i < 100; i++) dp[i] = multiplyMatrix(dp[i - 1], dp[i - 1]);

	// 입력 받기
	long long N;
	cin >> N;

	vector<vector<long long>> A = { {1, 0}, {0, 1} };
	int cnt = 0;
	while (N != 0) {
		if (N % 2 == 1)
			A = multiplyMatrix(A, dp[cnt]);
		N /= 2;
		cnt++;
	}

	cout << A[0][1];

	return 0;
}