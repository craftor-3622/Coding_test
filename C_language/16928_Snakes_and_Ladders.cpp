// https://www.acmicpc.net/problem/16928
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 105

vector<int> goTo;
vector<int> dist;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;

	goTo.resize(MAX_N);
	dist.resize(MAX_N, -1);

	for (int n = 1; n <= 100; ++n) goTo[n] = n;

	int a, b;
	for (int i = 0; i < N + M; ++i) {
		cin >> a >> b;
		goTo[a] = b;
	}

	queue<int> q;
	q.push(1);
	dist[1] = 0;

	while (!q.empty()) {
		int now = q.front(); q.pop();

		for (int n = 1; n <= 6; ++n) {
			int temp = now + n;
			if (temp > 100) continue;
			if (dist[goTo[temp]] != -1) continue;
			q.push(goTo[temp]);
			dist[goTo[temp]] = dist[now] + 1;
		}

		if (dist[100] != -1) break;
	}

	cout << dist[100];

	return 0;
}
/*
후기.
사용된 알고리즘 확인은 최대한 문제를 풀어보려고 한 뒤에 해보자...
이번 건 무심코 눌렀다가 알게 되서 의미가 퇴색된다.

별개로, 최단 코스가 나오면 우선 BFS를 의심하자.
그 때 안되면 다른 알고리즘을 생각하자.
*/