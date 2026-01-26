// https://www.acmicpc.net/problem/1707
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> graph;
vector<int> team;

bool bipart(int start) {
	bool isBipart = true;

	queue<int> q;
	team[start] = 1;
	q.push(start);
	while (!q.empty() && isBipart) {
		int now = q.front(); q.pop();

		for (int next : graph[now]) {
			if (team[next] == -1) {
				team[next] = team[now] % 2 + 1;
				q.push(next);
			}
			else if (team[now] == team[next]) {
				isBipart = false; break;
			}
		}
	}

	return isBipart;
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int K, V, E;
	cin >> K;

	for (int tc = 0; tc < K; tc++) {
		graph.clear();
		team.clear();

		cin >> V >> E;
		graph.resize(V + 1);
		team.resize(V + 1, -1);

		for (int n = 0; n < E; n++) {
			int a, b;
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		bool ans = true;

		for (int i = 1; i <= V; ++i)
			if (team[i] == -1) ans = ans && bipart(i);

		string output = ans ? "YES" : "NO";
		cout << output << "\n";
	}

	return 0;
}