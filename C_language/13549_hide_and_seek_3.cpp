// https://www.acmicpc.net/problem/13549
// 이전 문제 : https://www.acmicpc.net/problem/12851

// 다익스트라로도 구현할 수 있지만, 더 효율적인 방법이 있다.
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define MAX_N 100000

struct Node {
	int x, dist;
};

vector<int> visited;
int ans;

void bfs(int start, int end) {
	deque<Node> q;

	q.push_back({ start, 0 });

	while (!q.empty()) {
		Node now = q.front();  q.pop_front();

		if (now.x == end) { ans = now.dist;  break; }

		if (visited[now.x] == 1) continue;
		visited[now.x] = 1;

		if (now.x + 1 <= MAX_N && visited[now.x + 1] == 0)
			q.push_back({ now.x + 1, now.dist + 1 });
		if (now.x - 1 >= 0 && visited[now.x - 1] == 0)
			q.push_back({ now.x - 1, now.dist + 1 });
		if (now.x * 2 <= MAX_N && visited[now.x * 2] == 0)
			q.push_front({ now.x * 2, now.dist });
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	visited.resize(MAX_N + 1, 0);

	int N, K;
	cin >> N >> K;

	bfs(N, K);
	cout << ans;

	return 0;
}
/*
참고.
1. 우선순위 큐로 구현하기 - O((E + V) log V)
수행 결과 : 메모리 2808KB, 전체 테케 수행 8ms.
2. deque로 구현하기 - O(E + V)
수행 결과 : 메모리 2680KB, 전체 테케 수행 ~0ms.
*/