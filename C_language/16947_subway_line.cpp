// https://www.acmicpc.net/problem/16947
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 3005

bool loop[MAX_N] = { false, };
int length[MAX_N];
vector<int> graph[MAX_N];

void dfs(int start, int prev, int now, vector<int>& route, vector<int>& visited) {
	if (start == now) {
		for (auto node : route) loop[node] = true;
	}
	else if (visited[now]) return;
	else {
		route.push_back(now);
		visited[now] = 1;
		for (auto next : graph[now]) {
			if (visited[next] || next == prev) continue;
			dfs(start, now, next, route, visited);
		}
		route.pop_back();
		visited[now] = 0;
	}
}

void bfs() {
	queue<int> q;

	for (int i = 1; i <= MAX_N; i++)
		if (loop[i]) {
			q.push(i);
			length[i] = 0;
			break;
		}

	while (!q.empty()) {
		int now = q.front(); q.pop();

		for (int next : graph[now]) {
			if (length[next] != -1) continue;
			
			q.push(next);
			if (loop[next]) length[next] = 0;
			else length[next] = length[now] + 1;
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;

	fill(length, length + MAX_N, -1);

	// graph 생성
	int a, b;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	// loop 체크 (dfs)
	for (int i = 1; i <= N; i++) {
		if (loop[i]) continue;
		vector<int> temp = { i };
		vector<int> visited(N + 1, 0);
		for (auto next : graph[i])
			dfs(i, i, next, temp, visited);
	}

	//for (int i = 1; i <= N; i++) cout << loop[i] << " ";

	bfs();

	for (int i = 1; i <= N; i++) cout << length[i] << " ";

	return 0;
}
