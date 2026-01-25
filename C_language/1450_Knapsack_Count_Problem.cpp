// https://www.acmicpc.net/problem/1450
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;
vector<int> left_res;
vector<int> right_res;

void bruteForce(int now, int end, int res, int limit, vector<int>& obj) {
	if (res > limit) return;
	else if (now > end) { obj.push_back(res); return; }

	bruteForce(now + 1, end, res, limit, obj);
	bruteForce(now + 1, end, res + arr[now], limit, obj);
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, C;
	cin >> N >> C;
	arr.resize(N);

	for (int i = 0; i < N; ++i) cin >> arr[i];
	left_res.clear();
	right_res.clear();

	int mid = N / 2;

	bruteForce(0, mid - 1, 0, C, left_res);
	bruteForce(mid, N - 1, 0, C, right_res);

	sort(left_res.begin(), left_res.end());
	sort(right_res.begin(), right_res.end(), greater<>());

	int i = 0;
	int j = 0;
	int ans = 0;
	while (i < left_res.size() && j < right_res.size()) {
		if (left_res[i] + right_res[j] > C) j++;
		else {
			int left_cnt = 1;
			for (int n = i; n < left_res.size() && left_res[i] == left_res[n]; ++n)
				left_cnt = n - i + 1;
			ans += left_cnt * (right_res.size() - j);
			i += left_cnt;
		}
	}

	cout << ans;

	return 0;
}
/*
MitM (Meet in the Middle)
전체 경우의 수를 구할 때,
완전 탐색에서 시간이 약간 안되는 경우 (N = 25~40)
시도하는 방법.
양 쪽으로 나눠 완전 탐색 후, 공유하는 결과를
토대로 경우의 수를 구하는 것이 핵심.
이 경우 기존 O(2^N) 에서 O(a * 2 ^ (N/2)) (a: 매칭 비용)으로
주어진 N에서 수행 가능하다.
*/