// 이전 문제 : https://www.acmicpc.net/problem/12015

// https://www.acmicpc.net/problem/14003
// LIS O(n log n) + 경로 복원 (DP는 무슨 의미일까?)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<int> dp;
vector<int> arr;
vector<int> parent;
vector<int> last;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	arr.resize(N);
	parent.resize(N);
	last.resize(N + 1);

	int left, right, mid;
	for (int i = 0; i < N; i++) {
		left = 0;
		right = dp.size();
		mid = (left + right) / 2;

		cin >> arr[i];

		if (dp.empty()) {
			dp.push_back(arr[i]);
			parent[i] = -1;
			last[arr.size()] = 0;
			continue;
		}
		else {
			while (left < right) {
				if (arr[i] > dp[mid]) left = mid + 1;
				else right = mid;
				mid = (left + right) / 2;
			}

			if (mid == dp.size()) dp.push_back(arr[i]);
			else dp[mid] = arr[i];
			if (mid == 0) parent[i] = -1;
			else parent[i] = last[mid];
			last[mid + 1] = i;
		}
	}

	int len = dp.size();
	vector<int> ans;
	
	int now = last[len];
	while (now != -1) {
		ans.push_back(arr[now]);
		now = parent[now];
	}

	cout << len << endl;
	for (int i = len - 1; i >= 0; i--)
		cout << ans[i] << " ";

	return 0;
}
/*
후기.
O(N log N) LIS 계산과 경로 복원을 명확히 분리할 것을 요구하는 고난도 문제.
dp에서 Tree 구조의 개념을 떠올려 경로 복원까지 떠올린 것은 좋았으나,
이분 탐색 및 DP 구조를 같이 구현하려다 보니 실수가 너무 많이 나버림.
그래서 이 부분은 상태(dp 배열)과 경로 배열 (tree 관련 배열)을 분리하면
역할 분리가 잘 이루어지고, 경로 복원 안정성도 생긴다.

그와 별개로, 부모가 최대 1개라는 Tree의 특성을 이용해,
명시적 Tree를 선언하지 않아도 된다는 점이 특징.
전체 Tree를 순회하는 문제가 아니기에, 단지 부모 노드의 위치만 참조하면 됨.
이 구조를 통해 최소한의 구조로 문제 요구 사항을 적절하게 맞출 수 있다.
*/