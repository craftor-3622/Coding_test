// https://swexpertacademy.com/main/code/userProblem/userProblemDetail.do?contestProbId=AYFofW8qpXYDFAR4
// DP 문제. 나머지 처리를 어떻게 하는 것이 좋을까?

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		cin >> N;

		int max_h = 0;
		int max_i;
		vector<int> trees(N, 0);
		// 홀수 나머지가 많은 경우 예외를 처리하기 위한 연산
		vector<vector<int>> ration;
		int odd = 0; int even = 0;
		int days = 0;
	
		// 입력과 동시에 최대 값 및 index 연산
		for (int i = 0; i < N; i++) {
			cin >> trees[i];
			if (max_h < trees[i]) max_h = trees[i]; max_i = i;
		}
		
		// 몫, 나머지로 나누기
		for (int i = 0; i < N; i++) {
			int quo = (max_h - trees[i]) / 3;
			int mod = (max_h - trees[i]) % 3;

			days += quo * 2;
			if (quo != 0) ration.push_back({ i,quo,mod });
			if (mod == 1) odd++;
			if (mod == 2) even++;
		}
		
		int diff = abs(odd - even);

		if (odd == even) days += odd * 2;
		if (even > odd) {
			days += odd * 2 + 4 * (int)(diff / 3);
			if (diff % 3 != 0) days += diff % 3 + 1;
		}
		if (odd > even) {
			for (int n = 0; n < size(ration) && diff > 1; n++) {
				

			}
		}

		cout << "#" << test_case << " " << days << endl;
	}
	return 0;
}

