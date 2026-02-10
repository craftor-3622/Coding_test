// https://www.acmicpc.net/problem/2170
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Line {
	int x, y;
};

vector<Line> board;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("sample_input.txt", "r", stdin);
	
	int N;
	cin >> N;

	board.resize(N);
	for (int n = 0; n < N; n++) cin >> board[n].x >> board[n].y;

	auto sortX = [](Line a, Line b) { return a.x < b.x; };
	sort(board.begin(), board.end(), sortX);

	int left = board[0].x;
	int right = board[0].y;
	long long ans = 0;
	int i = 1;

	while (i < N) {
		if (board[i].x > right) {
			ans += right - left;
			left = board[i].x;
			right = board[i].y;
		}
		else if (board[i].y > right) {
			right = board[i].y;
		}
		
		i++;
	}

	ans += right - left;

	cout << ans;

	return 0;
}
/*
스위핑 (Sweeping)
문제에서 발생한 이벤트들을 한 축(좌표, 시간 등) 기준으로 정렬한 뒤,
축에 따라 이동하면서 현재 상태를 유지하고
필요한 값을 갱신하는 방법.

문제의 경우...
- 선분의 시작점 순으로 정렬
- 끝점 상태 갱신
- 선분 길이 누적 계산
*/