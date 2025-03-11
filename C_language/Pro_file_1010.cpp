#define MAX_N 350
#define MAX_V 200

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> Country(MAX_N, vector<int>(MAX_N, 0));
map<vector<int>, int> stations;

int L = 0;
int K = 0;

struct Edge {
	int num;
	int cost;

	bool operator<(Edge right) const {
		if (cost > right.cost) return true;
		if (cost < right.cost) return false;

		return false;
	}
};
vector<Edge> alis[MAX_V];
int dist[MAX_V];

vector<vector<int>> delta = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

// Flood-fill
void calculate_distance(int id, int si, int sj) {
	vector<int> visited(L * L, 0);

	queue<vector<int>> q;
	q.push({ si, sj });
	visited[si * L + sj] = 1;

	while (!q.empty()) {
		int i = q.front()[0];
		int j = q.front()[1];
		q.pop();

		for (auto d : delta) {
			int ni = i + d[0];
			int nj = j + d[1];

			if (ni == si && nj == sj) continue;
			if (ni < 0 || ni >= L || nj < 0 || nj >= L) continue;

			if (visited[ni * L + nj] != 0 || visited[i * L + j] >= K) continue;
			if (Country[ni][nj] != 0) continue;

			visited[ni * L + nj] = visited[i * L + j] + 1;
			q.push({ ni, nj });
				
			if (stations.find({ ni,nj }) != stations.end()) {
				int v = stations.at({ ni,nj });
				alis[id].push_back({ v, visited[ni * L + nj] });
				alis[v].push_back({ id, visited[ni * L + nj] });
			}
		}
	}
}

// 명령어 0번
void init(int N, int mRange, int mMap[MAX_N][MAX_N])
{
	stations.clear();
	for (int i = 0; i < MAX_V; i++)	dist[i] = -1;
	L = N;
	K = mRange;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			Country[i][j] = mMap[i][j];
		}
	}
	return;
}

// 명령어 1번
void add(int mID, int mRow, int mCol)
{
	calculate_distance(mID, mRow, mCol);
	stations.insert({ {mRow, mCol}, mID });
	cout << stations.size() << endl;
	return;
}

// 명령어 2번
// Dijkstra (무방향 간선)
int distance(int mFrom, int mTo)
{
	/*

	priority_queue<Edge> pq;
	dist[mFrom] = 0;
	pq.push({ mFrom, 0 });

	while (!pq.empty()) {
		Edge v = pq.top();  pq.pop();
	}

	return dist[mTo];
	*/
	return 0;
}