// https://www.acmicpc.net/problem/3190
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> board;
queue<pair<int, int>> snake;
vector<pair<int, char>> order;
int gN;
int nextOrd;
int del[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

bool moveHead(int dir, int boardSize) {
	pair<int, int> prev = snake.back();

	int ni = prev.first + del[dir][0];
	int nj = prev.second + del[dir][1];

	if (ni <= 0 || ni > boardSize) return false;
	if (nj <= 0 || nj > boardSize) return false;
	if (board[ni][nj] == 2) return false;

	return true;
}

void moveTail(int dir) {
	pair<int, int> prev = snake.back();
	int ni = prev.first + del[dir][0];
	int nj = prev.second + del[dir][1];

	int nextTile = board[ni][nj];
	snake.push({ ni, nj });
	board[ni][nj] = 2;
	
	if (nextTile != 1) {
		pair<int, int> tail = snake.front();
		snake.pop();
		board[tail.first][tail.second] = 0;
	}
}

int turnHead(int dir, int curTime) {
	if (curTime != order[nextOrd].first) return dir;
	else if (order[nextOrd].second == 'D') {
		nextOrd++;
		return (dir + 1) % 4;
	}
	else if (order[nextOrd].second == 'L') {
		nextOrd++;
		return (dir + 3) % 4;
	}
}

int main() {
	// freopen("sample_input.txt", "r", stdin);

	int N, K, L;
	cin >> N >> K;

	board.resize(N + 1, vector<int>(N + 1, 0));
	for (int k = 0; k < K; k++) {
		int a, b;
		cin >> a >> b;
		board[a][b] = 1;
	}

	cin >> L;
	order.resize(L);
	for (int i = 0; i < L; i++) cin >> order[i].first >> order[i].second;

	board[1][1] = 2;
	snake.push({ 1, 1 });
	int headDir = 0;
	int curTime = 1;
	nextOrd = 0;

	while (true) {
		if (!moveHead(headDir, N)) break;

		moveTail(headDir);
		if (nextOrd < L) headDir = turnHead(headDir, curTime);

		curTime++;
	}

	cout << curTime;

	return 0;
}