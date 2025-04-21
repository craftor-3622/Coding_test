// https://www.acmicpc.net/problem/1202
// Matching 기반 Greedy 알고리즘
// 기존 N-knapsack 문제와의 차이점은 가방에는 단 한개의 아이템만 들어간다는 점.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct jewel {
	int mass;
	int value;

	bool operator< (jewel right) const {
		return mass > right.mass;
	}
};

int main()
{
	freopen("input.txt", "r", stdin);

	int N, K, M, V;
	cin >> N >> K;

	priority_queue<jewel> store;
	priority_queue<int> max_heap;
	vector<int> knapsack(K);

	for (int n = 0; n < N; n++)	{
		cin >> M >> V;
		store.push({ M, V });
	}

	for (int k = 0; k < K; k++) cin >> knapsack[k];
	sort(knapsack.begin(), knapsack.end());

	long long int answer = 0;

	int m, v;
	int n = 0;
	for (int k = 0; k < K; k++)	{
		while (!store.empty() && store.top().mass <= knapsack[k]) {
			max_heap.push( store.top().value );
			store.pop();
		}
		
		if (!max_heap.empty()) {
			answer += max_heap.top();
			max_heap.pop();
		}
	}

	cout << answer;

	return 0;
}