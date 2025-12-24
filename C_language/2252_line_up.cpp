// https://www.acmicpc.net/problem/2252
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> students;
vector<int> phase;
queue<int> order;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;
	students.resize(N + 1);
	phase.resize(N + 1, 0);

	int a, b;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		students[a].push_back(b);
		phase[b]++;
	}

	for (int n = 1; n <= N; ++n)
		if (phase[n] == 0) order.push(n);

	while (!order.empty()) {
		int now = order.front(); order.pop();
		cout << now << " ";

		for (int next : students[now]) {
			phase[next]--;
			if (phase[next] == 0) order.push(next);
		}
	}

	return 0;
}
/*
후기.
해당 문제 기준, N이 최대 32,000 인 경우 다음의 성능이 나타난다.
- map<int, vector<int>> (Red-Black Tree 기반)
  : 메모리 5592 KB, 시간 100 ms
- vector<vector<int>>
  : 메모리 3832 KB, 시간 76 ms

그래서 정점 번호가 1 ~ N으로 고정된 상황에서는
map은 O(log N) 접근 비용과 낮은 캐시 효율로 인해
vector 기반 인접 리스트보다 불리하다.

따라서 이러한 조건에서는 map보다
vector를 사용하여 그래프를 표현하는 것이 더 효율적이다.

반대로 정점 번호가 희소하거나 범위가 매우 크고,
동적 삽입·삭제가 필요한 경우에는
map과 같은 연관 컨테이너가 더 적합할 수 있다.
*/