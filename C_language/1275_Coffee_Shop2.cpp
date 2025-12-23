// https://www.acmicpc.net/problem/1275
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<long long> segTree;
vector<long long> arr;

// left, right는 현재 탐색 구간 (변동)
void build(int pos, int left, int right) {
	if (left == right) {
		segTree[pos] = arr[left];
		return;
	}

	int mid = (left + right) / 2;
	build(2 * pos, left, mid);
	build(2 * pos + 1, mid + 1, right);

	segTree[pos] = segTree[2 * pos] + segTree[2 * pos + 1];
}

// left, right는 현재 탐색 구간 (변동)
void update(int n, int pos, int val, int left, int right) {
	if (n < left || n > right) return; 
	else if (left == right && left == n) { segTree[pos] = val; return; }
	
	int mid = (left + right) / 2;
	update(n, 2 * pos, val, left, mid);
	update(n, 2 * pos + 1, val, mid + 1, right);

	segTree[pos] = segTree[2 * pos] + segTree[2 * pos + 1];
}

// start, end는 query 구간 (고정), left, right는 현재 탐색 구간 (변동)
long long query(int pos, int start, int end, int left, int right) {
	if (end < left || start > right) return 0;
	else if (start <= left && end >= right) return segTree[pos];

	int mid = (left + right) / 2;
	return query(2 * pos, start, end, left, mid) +
		query(2 * pos + 1, start, end, mid + 1, right);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	freopen("sample_input.txt", "r", stdin);

	int N, Q;
	cin >> N >> Q;
	arr.resize(N + 1);
	segTree.resize(4 * N, 0);

	for (int i = 1; i <= N; ++i) cin >> arr[i];
	build(1, 1, N);

	int x, y, a, b;
	for (int i = 0; i < Q; ++i) {
		cin >> x >> y >> a >> b;
		if (x > y) cout << query(1, y, x, 1, N) << "\n";
		else cout << query(1, x, y, 1, N) << "\n";
		update(a, 1, b, 1, N);
	}

	return 0;
}
/*
후기.
segTree 타입을 int로 선언한 것이 원인. (2%에서 어쩐지 자꾸 틀리더라)
조건에 따른 누적합은 long long을 사용하는 것이 옳다는 것을 다시 상기하자.

초기화를 update로 처리할 수도 있으나 build 단계를 분리하니
트리의 역할이 명확해져 코드 리딩 난이도가 내려간다.
*/