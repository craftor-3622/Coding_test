#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 55

vector<vector<int>> area;
vector<vector<int>> visited;
vector<int> sum;
vector<int> cnt;

int parent[MAX_N * MAX_N];
int depth[MAX_N * MAX_N];
bool flag;

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
	int Px = find(x);
	int Py = find(y);

	if (Px != Py) {
		if (depth[Px] > depth[Py]) parent[Py] = Px;
		else if (depth[Px] < depth[Py]) parent[Px] = Py;
		else {
			parent[Py] = Px;
			depth[Px]++;
		}
		flag = true;
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, L, R;
	cin >> N >> L >> R;

	area.resize(N, vector<int>(N));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> area[i][j];

	int time = 0;
	while (true) {
		for (int i = 0; i < N * N; ++i) parent[i] = i;
		fill(depth, depth + (N * N), 1);
		sum.assign(N * N, 0);
		cnt.assign(N * N, 0);

		flag = false;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N - 1; ++j) {
				int diff = abs(area[i][j] - area[i][j + 1]);
				if (diff >= L && diff <= R) unite(i * N + j, i * N + j + 1);
			}

		for (int j = 0; j < N; ++j)
			for (int i = 0; i < N - 1; ++i) {
				int diff = abs(area[i][j] - area[i + 1][j]);
				if (diff >= L && diff <= R) unite(i * N + j, (i + 1) * N + j);
			}

		if (!flag) break;
		++time;

		for (int n = 0; n < N * N; ++n) {
			int Rn = find(n);
			int ni = n / N;
			int nj = n % N;

			sum[Rn] += area[ni][nj];
			cnt[Rn]++;
		}

		for (int n = 0; n < N * N; ++n) {
			int Rn = find(n);
			int ni = n / N;
			int nj = n % N;

			area[ni][nj] = sum[Rn] / cnt[Rn];
		}

		// 디버그용
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) cout << area[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}

	cout << time << endl;

	return 0;
}
/*
후기.
Union-find 방식을 생각한 것은 좋은 접근이었으나,
합산 과정에서 BFS으로 너무 돌아서 간 점은 아쉽다고 생각.

Union-Find로 연합 판정이 끝났다면, BFS/DFS 기반 그래프 구축 없이
"루트 기반 집계"만으로 충분히 정확하고 빠른 계산이 가능하다.

이는 Union-Find가 내부적으로 Tree 기반으로 연결 요소를 대표자(root)에 매핑하는 자료구조이기 때문에,
각 원소가 속한 연합은 find() 결과인 root 값만으로 명확히 구분되며,
이를 그대로 집계 연산의 키로 사용할 수 있기 때문이다.
================================
Union-Find의 역할: "같은 연합(연결요소)인지"를 판정하고, 각 칸을 대표(root) 에 매핑하는 것
합/평균의 역할: 대표(root)별로 값을 집계(sum/cnt)해서 한 번에 갱신하는 것

즉, UF가 연결요소를 만들었다면, 그 다음 단계는 "그래프를 다시 만들기"가 아니라
대표(root)를 키로 하는 집계 문제로 바뀐다.

그래서 root 기반으로 합산만 해주면 꽤 간단한 합산 로직인데,
불필요하게 Graph를 가지고 계산을 해서 디버그가 어려웠던 것.
================================
여담으로...
BFS - O(V + E)
UF - O(E * a(V)) ~ O(E) (경로 압축 적용 시)
게다가, BFS는 Queue 기반 분기 처리로 메모리 접근이 여러번 일어나서 상수 계수가 크지만,
UF 기반 합산은 배열 인덱싱 위주이기 때문에 상수 계수가 작다.
*/