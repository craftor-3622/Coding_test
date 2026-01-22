// https://www.acmicpc.net/problem/1967
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	int num, dist;
};

vector<vector<Node>> graph;
vector<vector<int>> radius;

void dfs(Node now) {
	for (Node next : graph[now.num]) {
		dfs(next);
		radius[now.num].push_back(radius[next.num][0] + next.dist);
	}
	if (radius[now.num].empty()) radius[now.num].push_back(0);
	sort(radius[now.num].begin(), radius[now.num].end(), greater<>());
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	graph.resize(N + 1);
	radius.resize(N + 1);

	for (int i = 1; i < N; i++) {
		int parent, child, dist;
		cin >> parent >> child >> dist;
		graph[parent].push_back({ child, dist });
	}

	dfs({ 1, 0 });

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (radius[i].size() >= 2) ans = max(ans, radius[i][0] + radius[i][1]);
		else if (radius[i].size() == 1) ans = max(ans, radius[i][0]);
	}

	cout << ans;

	return 0;
}
/*
후기.
알고 나면 단순한 구조지만,
무엇을 상태로 저장해야 할지 정의하는 과정이 까다로운 문제.

트리 지름을 직접 상태로 들고 가기보다는,
각 노드에서 아래로 내려가는 최대 거리만을
radius로 정의해 관리하는 편이 코드 안정성이 높다.
지름은 결국 두 개의 하향 경로가 만나는 지점에서
결정된다는 점을 정리하고 나니,
DFS 흐름 안에서 자연스럽게 전역 값을 갱신할 수 있기 때문.
*/