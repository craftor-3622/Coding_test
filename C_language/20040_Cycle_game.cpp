// https://www.acmicpc.net/problem/20040
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<int> parent;

int find(int x) {
	if (parent[x] == x) return x;
	parent[x] = find(parent[x]);
	return parent[x];
}

void unite(int x, int y) {
	int Rx = find(x);
	int Ry = find(y);

	if (Rx > Ry) parent[Rx] = Ry;
	else parent[Ry] = Rx;
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;

	// 초기화
	parent.resize(N);
	for (int i = 0; i < N; ++i) parent[i] = i;

	int a, b;
	int ans = 0;
	for (int m = 1; m <= M; ++m) {
		cin >> a >> b;
		if (find(a) == find(b)) { ans = m; break; }
		else unite(a, b);
	}

	cout << ans << endl;

	return 0;
}
/*
후기.
초기는 사이클을 직접 찾아야 한다는 생각이 있었으나,
BFS/DFS 관련 연산 등이 복잡해 아닌 것 같다고 판단.
사이클이 처음 발생하는 시점만 판별하면 된다는 점으로 다시 분석해
Union-find로 바꾼 것이 꽤 좋았다.

추가적으로, union-find에서 rank 연산을 통해 O(1)에 더욱 가까운 성능을 낼 수 있다.
rank[Rx] 와 rank[Ry]간 비교 작업으로 루트 트리 깊이를 줄이는 방식.
*/