// https://www.acmicpc.net/problem/9019
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	string order;
	int n;
};

int dslrOperator(int n, char mode) {
	switch (mode) {
	case 'D':
		return (n * 2) % 10000;

	case 'S':
		return (10000 + (n - 1)) % 10000;

	case 'L':
		return (n % 1000) * 10 + (n / 1000);

	case 'R':
		return (n % 10) * 1000 + n / 10;

	default:
		return n;
	}
}

string bfs(int init, int target) {
	vector<int> visited(10000, 0);
	queue<Node> q;
	Node ans;

	q.push({ "", init });
	visited[init] = 1;

	while (!q.empty()) {
		Node now = q.front(); q.pop();

		if (now.n == target) {
			ans = now;
			break;
		}

		for (char c : "DSLR") {
			int num = dslrOperator(now.n, c);
			if (visited[num]) continue;
			visited[num] = 1;

			string s = now.order;
			auto it = s.end();
			s.insert(it, c);

			q.push({ s, num });
		}
	}

	return ans.order;
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 0; tc < T; ++tc) {
		int a, b;
		cin >> a >> b;
		cout << bfs(a, b) << endl;
	}

	return 0;
}
/*
후기.
BFS 자체는 정점 수 V에 대해 O(V) 수준으로 충분히 빠르다.
문제는 탐색 과정에서 큐(Node)에 경로 문자열을 함께 넣어,
매 확장마다 string을 복사하고 한 글자씩 덧붙이는 비용이 누적된다는 점.
이 비용은 깊이가 커질수록 커지며, 전체적으로 O(V^2)에 가까운 체감 성능 저하를 만들 수 있다.

따라서 경로를 탐색 중에 직접 누적하기보다,
각 상태에 대해 prev[state]와 how[state]를 저장해 두고,
목표 상태에서 시작 상태까지 역추적하는 방식이 적합하다.
초기 상태의 prev는 -1로 두고, 이후에는 prev[next] = cur 형태로 부모 포인터를 기록하면 된다.
*/