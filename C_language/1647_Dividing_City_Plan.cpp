// https://www.acmicpc.net/problem/1647
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
	int v, dist;

	bool operator<(Edge right) const {
		return dist > right.dist;
	}
};

vector<vector<Edge>> graph;
vector<int> visited;
int large_cost;

int mst(int start) {
	priority_queue<Edge> pq;
	int N = graph.size() - 1;
	int res = 0;

	for (Edge e : graph[start]) pq.push(e);
	visited[start] = 1;
	int vertex_cnt = 1;

	while (vertex_cnt < N && !pq.empty()) {
		Edge now = pq.top();  pq.pop();

		if (visited[now.v] == 1) continue;
		visited[now.v] = 1;
		res += now.dist;
		large_cost = max(large_cost, now.dist);

		for (Edge next : graph[now.v]) {
			if (visited[next.v] == 1) continue;
			pq.push(next);
		}
	}

	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("sample_input.txt", "r", stdin);

	large_cost = 0;
	int N, M;
	cin >> N >> M;

	graph.resize(N + 1);
	visited.resize(N + 1, 0);
	for (int m = 0; m < M; m++) {
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}

	int ans = mst(1);

	cout << ans - large_cost;

	return 0;
}
/* 
팁.
두 개의 MST를 따로 만들 필요는 없다.
MST에 대한 성질을 이용하면 남은 비용의 합이 최소인
두 개의 구역으로 나눌 수 있다.
*/