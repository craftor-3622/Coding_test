// https://www.acmicpc.net/problem/2887
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
using namespace std;

struct Vec3D {
	int x, y, z;
};

struct Edge {
	int u, v, w;

	bool operator<(Edge right) const {
		return w > right.w;
	}
};

vector<Vec3D> Kingdom;
vector<array<int, 2>> XInfo;
vector<array<int, 2>> YInfo;
vector<array<int, 2>> ZInfo;
priority_queue<Edge> heap;

long long ans;

vector<int> parent;
vector<int> depth;

int find(int x) {
	if (parent[x] == x) return x;
	return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
	int Rx = find(x);
	int Ry = find(y);

	if (Rx == Ry) return;
	if (depth[Rx] > depth[Ry]) parent[Ry] = Rx;
	else if (depth[Ry] > depth[Rx]) parent[Rx] = Ry;
	else {
		if (Rx < Ry) { parent[Ry] = Rx; depth[Rx]++; }
		else { parent[Rx] = Ry; depth[Ry]++; }
	}
}

void kruskal(int N) {
	int edge_cnt = 0;
	while (!heap.empty()) {
		Edge now = heap.top(); heap.pop();
		if (find(now.u) == find(now.v)) continue;
		unite(now.u, now.v);
		ans += now.w;
		edge_cnt++;
		if (edge_cnt == N - 1) break;
	}
}
 
int main() {
	freopen("sample_input.txt", "r", stdin);

	ans = 0;
	int N;
	cin >> N;

	Kingdom.resize(N);
	parent.resize(N);
	for (int i = 0; i < N; i++) parent[i] = i;
	depth.resize(N, 1);

	for (int n = 0; n < N; n++) {
		int x, y, z;
		cin >> x >> y >> z;
		Kingdom[n] = { x, y, z };
		XInfo.push_back({ n, x });
		YInfo.push_back({ n, y });
		ZInfo.push_back({ n, z });
	}

	auto sortOrder = [](array<int, 2> a, array<int, 2> b) { return a[1] < b[1]; };
	std::sort(XInfo.begin(), XInfo.end(), sortOrder);
	std::sort(YInfo.begin(), YInfo.end(), sortOrder);
	std::sort(ZInfo.begin(), ZInfo.end(), sortOrder);

	for (int i = 0; i < N - 1; i++) {
		heap.push({ XInfo[i][0], XInfo[i + 1][0], XInfo[i + 1][1] - XInfo[i][1] });
		heap.push({ YInfo[i][0], YInfo[i + 1][0], YInfo[i + 1][1] - YInfo[i][1] });
		heap.push({ ZInfo[i][0], ZInfo[i + 1][0], ZInfo[i + 1][1] - ZInfo[i][1] });
	}

	kruskal(N);
	cout << ans;

	return 0;
}
/*
후기.

이 문제에서 중요한 것은 MST에 포함된 간선 집합을
얼마나 정확하게 정의하느냐라는 점.
완전 그래프 구현 시 E = N^2로 폭발하지만,
비용 구조를 관찰하면 실제 선택되는 간선의 개수는 매우 적어진다.

이 문제에서는 간선 비용이 좌표 차이의 최소값으로 정의되어 있어,
각 축별로 정렬했을 때 인접한 정점 간의 간선만으로도
모든 최소 간선 후보를 포함할 수 있다는 점이 핵심이 된다.
조건을 만족하는 간선 만으로 그래프를 구현하면 E = 3 * (N - 1)로 크게 감소한다.

즉 MST의 성질을 해치지 않는 선에서 간선 후보를 줄이게 되면,
그 결과 전체 문제는 그래프 탐색이 아니라
"그래프를 어떻게 구성할 것인가"에 대한 모델링 문제로 바뀐다.

이 경험을 통해, 그래프 문제를 만났을 때 주어진 구조를 그대로 구현하기보다는,
"정말 필요한 간선만 남겨도 정답이 보존되는가"를 먼저 고민하는 시각이
상위 난이도 문제에서 매우 중요하다는 것을 체감할 수 있었다.

===================================

이와 같이 시간/메모리에서 병목이 발생하는 문제(백준 골드 상위~)의 경우,
처음부터 모든 것을 설계하려면 비효율적이다.

1. 우선 정직하게 구현한다. (최적화 상관없이)
2. 병목을 확인한다. (이 문제의 경우, 간선 개수가 N^2)
3. 불필요한 부분을 제거한다. (MST 구현에서 최단 간선 후보만 필요)
*/