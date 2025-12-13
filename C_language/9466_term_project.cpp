// https://www.acmicpc.net/problem/9466
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <list>
using namespace std;

vector<int> team;
vector<int> selected;
vector<int> visited;

void matchTeam(int n) {
	int now, next;
	list<int> temp;
	visited.assign(n + 1, 0);

	for (int i = 1; i <= n; ++i) {
		temp.clear();
		
		if (visited[i] == 1) continue;
		now = i;
		temp.push_back(i);

		while (!visited[now]) {
			visited[now] = 1;

			next = selected[now];
			temp.push_back(next);

			now = next;
		}

		int head;
		int tail = temp.back();
		temp.pop_back();

		while (!temp.empty()) {
			head = temp.front();

			if (head == tail) {
				for (int node : temp) team[node] = 1;
				break;
			}

			temp.pop_front();
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int T, N, sum;
	cin >> T;

	for (int tc = 0; tc < T; ++tc) {
		cin >> N;
		team.assign(N + 1, 0);
		selected.resize(N + 1);

		for (int i = 1; i <= N; ++i) cin >> selected[i];
	
		matchTeam(N);

		sum = 0;
		for (int i = 0; i <= N; ++i) sum += team[i];

		cout << N - sum << endl;
	}

	return 0;
}

// + GPT : 지금처럼 구현할 수도 있지만, 3상태를 통해 구현하면 꽤 최적화가 잘 된다.
/*
static vector<int> nxt;
static vector<int> state;
static vector<int> in_team;
int n;

void dfs(int u) {
	state[u] = 1;          // visiting
	int v = nxt[u];

	if (state[v] == 0) {
		dfs(v);
	}
	else if (state[v] == 1) {
		int cur = v;
		while (true) {
			in_team[cur] = 1;
			cur = nxt[cur];
			if (cur == v) break;
		}
	}
	state[u] = 2;          // done
}
*/