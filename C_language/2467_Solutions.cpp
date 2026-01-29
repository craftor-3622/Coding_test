// https://www.acmicpc.net/problem/2467
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<int> solutions;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	
	solutions.resize(N);
	for (int n = 0; n < N; n++) cin >> solutions[n];

	int i = 0;
	int j = N - 1;

	int left = solutions[i];
	int right = solutions[j];
	int res = solutions[i] + solutions[j];

	if (left >= 0) right = solutions[i + 1];
	else if (right <= 0) left = solutions[j - 1];
	else while (i < j) {
		res = solutions[i] + solutions[j];
		if (abs(res) < abs(left + right)) {
			left = solutions[i];
			right = solutions[j];
		}

		if (res == 0) break;
		else if (res > 0) --j;
		else if (res < 0) ++i;
	}

	cout << left << " " << right;

	return 0;
}
