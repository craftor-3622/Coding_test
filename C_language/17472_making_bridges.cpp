// https://www.acmicpc.net/problem/17472
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int length, width, ans;
vector<vector<int>> country;
vector<vector<int>> island;
map<int, vector<pair<int, int>>> areas;
vector<pair<int, int>> graph[10];
int del[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

struct Edge {
	int start, end, dist;

	bool operator<(Edge right) const {
		if (dist > right.dist) return true;
		if (dist < right.dist) return false;

		return false;
	}
};

void bfs(int n, int si, int sj) {
	if (areas.find(n) != areas.end()) areas[n] = {};
	queue<pair<int, int>> q;

	if (island[si][sj]) return;
	island[si][sj] = n;
	areas[n].push_back({ si, sj });
	q.push({ si, sj });

	int oi, oj, ni, nj;
	while (!q.empty()) {
		pair<int, int> now = q.front(); q.pop();

		oi = now.first; oj = now.second;
		for (auto d : del) {
			ni = oi + d[0];
			nj = oj + d[1];

			if (ni < 0 || ni >= length || nj < 0 || nj >= width) continue;
			if (!country[ni][nj] || island[ni][nj]) continue;

			island[ni][nj] = n;
			areas[n].push_back({ ni, nj });
			q.push({ ni, nj });
		}
	}
}

void create_bridge(int n, int si, int sj) {
	int oi, oj, ni, nj;
	int num;
	for (auto d : del) {
		oi = si; oj = sj;
		num = 0;
		while (true) {
			ni = oi + d[0];
			nj = oj + d[1];

			if (ni < 0 || ni >= length || nj < 0 || nj >= width) break;
			if (island[ni][nj] == n) break;

			if (island[ni][nj] != 0) {
				if (num >= 2) graph[n].push_back({ island[ni][nj], num });
				break;
			}

			++num;
			oi = ni;  oj = nj;
		}
	}
}

int least_res(int start, int num) {
	ans = -1;
	int res = 0;
	priority_queue<Edge> pq;
	int visited = 1;

	for (auto se : graph[start]) pq.push({ start, se.first, se.second });
	visited |= 1 << start;

	while (!pq.empty()) {
		auto e = pq.top(); pq.pop();

		if (visited & (1 << e.end)) continue;
		res += e.dist;
		for (auto next : graph[e.end]) pq.push({ e.end, next.first, next.second });
		visited |= 1 << e.end;

		if (visited == (1 << num) - 1) {
			ans = res;
			break;
		}
	}

	return ans;
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;
	length = N; width = M;

	// 초기화
	country.resize(N, vector<int>(M));
	island.resize(N, vector<int>(M, 0));
	areas.clear();
	ans = -1;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> country[i][j];

	int num = 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (country[i][j] == 1 && island[i][j] == 0) bfs(num++, i, j);

	// 디버그용
	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << island[i][j] << " ";
		cout << endl;
	}
	*/

	// 다리 후보 생성
	for (int n = 1; n < num; n++)
		for (auto pos : areas[n]) create_bridge(n, pos.first, pos.second);

	least_res(1, num);

	cout << ans;

	return 0;
}
/*
후기.

이게 dfs가 아니라 kruskal or prim이네...
하다보니, 다리가 일자 노드처럼 이어진 게 아니라 트리도 가능하다는 것을
뒤늦게 인지하고 바꿨는데, 하필 MST 구현 방법을 거의 까먹어서...

번외로, graph에 대한 개선점이 있는데, 중복 간선이 존재한다.
문제에 제시된 조건에서 섬을 정점으로 간주하면 정점의 개수가 적고,
graph 연결 상태가 어떻게 될 지 모르기에
행렬 방식으로 그래프를 표현하는 것이 더 간결해진다.
*/