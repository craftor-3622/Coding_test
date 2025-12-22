// https://www.acmicpc.net/problem/2644
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 105
vector<int> childs[MAX_N];
int parent[MAX_N];

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, A, B, M;
	cin >> N >> A >> B >> M;
	fill(parent, parent + MAX_N, -1);

	int x, y;
	for (int i = 0; i < M; ++i) {
		cin >> x >> y;
		childs[x].push_back(y);
		parent[y] = x;
	}

	vector<int> xParent, yParent;
	int ans = -1;

	int now = A;
	while (now != -1) {
		xParent.push_back(now);
		now = parent[now];
	}

	now = B;
	while (now != -1) {
		yParent.push_back(now);
		now = parent[now];
	}

	for (int i = 0; i < xParent.size(); ++i) {
		for (int j = 0; j < yParent.size(); ++j)
			if (xParent[i] == yParent[j]) {
				ans = i + j;
				break;
			}
		if (ans != -1) break;
	}
		
	cout << ans << endl;

	return 0;
}
/*
후기.

N이 100 이하라 O(N^2)으로도 풀수 있어 난이도가 쉬움.
다만 N이 10000까지 올라가면 O(N)으로 풀어야 된다.

이때는 부모-자식 관계를 무방향 그래프로 구성한 뒤,
한쪽(A)에서 DFS/BFS를 한 번 수행하며 dist(촌수)를 기록하고,
목표 노드(B)의 dist 값을 정답으로 사용하면 된다.
*/