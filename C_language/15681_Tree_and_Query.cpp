// https://www.acmicpc.net/problem/15681
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100005

vector<int> dp;
vector<bool> visited;
vector<vector<int>> graph;

int search_dp(int now) {
	int node = 1;
	visited[now] = true;
	
	for (int next : graph[now]) {
		if (visited[next]) continue;
		node += search_dp(next);
	}
	
	return dp[now] = node;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("sample_input.txt", "r", stdin);

	int N, R, Q;
	cin >> N >> R >> Q;

	// 초기화
	graph.resize(N + 1);
	dp.resize(N + 1, 0);
	visited.resize(N + 1, false);

	int u, v;
	for (int i = 1; i < N; ++i) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	search_dp(R);

	int query;
	for (int i = 0; i < Q; ++i) {
		cin >> query;
		cout << dp[query] << "\n";
	}

	return 0;
}
/*
후기.
아, 이게 대용량 입력이라 문제가 되는구만...

Tree DP긴 해도 일반 DP와 크게 차이는 없다.
둘 다 이미 계산한 결과를 재사용하여 어떤 이전 결과에 의존하는 지를 파악하는 데 있음.

다만, Tree DP는 트리 구조에 의해 상태 의존 관계가 결정된다.
그래서 이 부분 같은 경우에는 반드시 자식 노드들의 상태 값을 먼저 알고,
그 뒤 계산하는 것이 정석적인 방법.
*/