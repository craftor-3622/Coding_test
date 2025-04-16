// https://www.acmicpc.net/problem/2042
// Segment Tree Tutorial
// 기본 구조는 Complete BT 기반, leaf node는 array 요소 값, 나머지 node는 구간 합
// 구간 합 등 구간 query에 활용 -> O(N)에서 O(log N)으로 높은 성능을 가진다.
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

vector<int> array_input;
vector<int> segment_tree;

// Segment tree 생성
void build(int node, int start, int end) {
	if (start == end) {
		segment_tree[node] = array_input[start];
		return;
	}
	int mid = (start + end) / 2;
	build(node * 2, start, mid);
	build(node * 2 + 1, mid + 1, end);
	segment_tree[node] = segment_tree[node * 2] + segment_tree[node * 2 + 1];
}

// Segment tree로부터 구간 합 반환
int query(int node, int start, int end, int left, int right) {
	if (right < start || left > end) return 0;
	if (left <= start && right >= end) return segment_tree[node];

	int mid = (start + end) / 2;
	return query(node * 2, start, mid, left, right)
		+ query(node * 2 + 1, mid + 1, end, left, right);
}

// Segment tree 구간
void update(int node, int start, int end, int idx, int value) {
	if (idx < start || idx > end) return;
	if (start == end) {
		segment_tree[node] = value;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, value);
	update(node * 2 + 1, mid + 1, end, idx, value);
	segment_tree[node] = segment_tree[node * 2] + segment_tree[node * 2 + 1];
}

int main() {
	freopen("input.txt", "r", stdin);

	// Array 내부 개수, 수정 횟수, Query 횟수
	int N, M, K;
	cin >> N >> M >> K;
	array_input.resize(N);

	for (int i = 0; i < N; i++) cin >> array_input[i];

	int s = 1;
	while (s < N) s *= 2;
	segment_tree.resize(s * 2, 0);
	build(1, 0, N - 1);

	int a, b, c;
	for (int i = 0; i < M + K; i++)	{
		cin >> a >> b >> c;
		switch (a)
		{
		case 1:
			update(1, 0, N - 1, b - 1, c);
			break;
		case 2:
			cout << query(1, 0, N - 1, b - 1, c - 1) << endl;
			break;
		}
	}

	return 0;
}