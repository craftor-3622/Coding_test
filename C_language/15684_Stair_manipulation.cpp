// https://www.acmicpc.net/problem/15684
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> board;
int ans;

// 사다리 타기
void goStair(int height, int width, vector<pair<int, int>>& rows) {
	bool isDone = true;
	for (auto row : rows) board[row.first][row.second] = 1;

	for (int n = 1; n <= width; n++) {
		int pos = n;
		for (int h = 1; h <= height; h++) {
			if (pos - 1 > 0 && board[pos - 1][h] == 1) pos--;
			else if (board[pos][h] == 1) pos++;
		}
		if (pos != n) { isDone = false;  break; }
	}

	for (auto row : rows) board[row.first][row.second] = 0;
	if (isDone) ans = ans == -1 ? rows.size() : min(ans, (int)rows.size());
}

// 후보 가로선 군 구하기
void getList(int max_n, int cur_n, int width, int height,
	vector<pair<int, int>>& rows, int num = 0) {
	goStair(height, width, rows);
	if (cur_n >= max_n) return;

	for (int n = num; n < (width - 1) * height; n++) {
		int i = n / height + 1;
		int j = n % height + 1;
	
		if (board[i][j] == 1) continue;
		if (i + 1 < width && board[i + 1][j] == 1) continue;
		if (i - 1 > 0 && board[i - 1][j] == 1) continue;

		rows.push_back({i, j});
		getList(max_n, cur_n + 1, width, height, rows, n + 1);
		rows.pop_back();
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	ans = -1;

	int N, M, H;
	cin >> N >> M >> H;

	board.resize(N + 1, vector<int>(H + 1, 0));
	for (int m = 0; m < M; m++) {
		int a, b;
		cin >> a >> b;
		board[b][a] = 1;
	}

	vector<pair<int, int>> rowNum;
	getList(3, 0, N, H, rowNum);

	cout << ans;

	return 0;
}
/*
팁.
코테에서 메모리 비용이 큰 경우, 기능을 연결하는 과정에서
복사 또는 자료구조 생성이 가장 많이 일어나는 부분을 찾아보자.
*/