// https://www.acmicpc.net/problem/12851
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define MAX_X 100000

vector<int> dist;
vector<int> ways;
queue<int> q;
set<int> temp;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, K;
	cin >> N >> K;
	dist.resize(MAX_X + 5, -1);
	ways.resize(MAX_X + 5, 0);

	int t = 0;
	dist[N] = 0;
	ways[N] = 1;
	q.push(N);

	while (!q.empty() && dist[K] == -1) {
		++t;
		int s = q.size();

		for (int i = 0; i < s; ++i) {
			int now = q.front(); q.pop();
			if (now + 1 <= MAX_X && dist[now + 1] == -1) {
				temp.insert(now + 1);
				ways[now + 1] += ways[now];
			}
			if (2 * now <= MAX_X && dist[2 * now] == -1) {
				temp.insert(2 * now);
				ways[2 * now] += ways[now];
			}
			if (now - 1 >= 0 && dist[now - 1] == -1) {
				temp.insert(now - 1);
				ways[now - 1] += ways[now];
			}
		}

		for (int n : temp) {
			q.push(n);
			dist[n] = t;
		}
		temp.clear();
	}

	cout << dist[K] << endl << ways[K] << endl;

	return 0;
}

/*
후기.

처음 경우의 수를 상태 저장하는 것으로 생각해서 dp를 생각했는데,
이게 dp가 아니라 bfs였네...
==========================================

dp를 사용할 경우 구현 상 틀린 부분은 없다. 다만 좌표가 0~100000로 제한되어 있어
x>50000 구간에서는 2x 이동이 범위 초과로 불가능해지고,
결과적으로 우측 구간에서는 ±1 위주의 선형 이동을 수행하게 된다.

예를 들어 75000 → 100000은 *2가 봉인되어
최소 +1을 약 25000번 반복해야 하므로 최단 시간이 수만 단위가 될 수 있다.
따라서 시간 t를 축으로 dp[t][x]를 구성하면서 t≤100 같은 가정을 두면
out-of-bounds 에러가 발생한다.
그렇다고 x좌표 개수에 비례한 dp 2차원 배열을 사용할 경우 메모리 초과에 걸린다.

==========================================
이런 경우라면 이렇게 풀어보자.
0. 문제 분석부터 하자.

1. 상태의 수(노드수)와 전이(간선) 확인
2. 가중치가 여부
3. 최단 거리/경로 수를 묻는가? (BFS/다익스트라와 연결)
4. 시간/단계 축 관련 제약 조건 확인

만약 그래프 문제라면, 이런 순서대로 접근해서 풀어보자...
그리디 → BFS/그래프 → 다익스트라/0-1 BFS → DP
*/