#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int answer = 0;

// 블록 이동 시, 합쳐지는 알고리즘 (queue)
vector<vector<int>> merge_blocks(vector<vector<int>> blocks, int size, int dir) {
	queue<int> q;

	switch (dir) {
	case 0:		// 왼쪽 밀기
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) q.push(blocks[i][j]);

			int temp = 0;
			int k = 0;

			while (!q.empty()) {
				if (q.front() == 0) {
					q.pop(); continue;
				}
				if (temp == q.front() && temp != 0) {
					temp *= 2; q.pop();
					blocks[i][k++] = temp;
				}
				else if (temp != 0) {
					blocks[i][k++] = temp;
				}

				if (!q.empty()) { temp = q.front(); q.pop(); }
				else temp = 0;
			}

			blocks[i][k++] = temp;

			for (int j = k; j < size; j++) blocks[i][j] = 0;
		}
		break;
	case 1:		// 오른쪽 밀기
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j >= 0; j--) q.push(blocks[i][j]);

			int temp = 0;
			int k = size - 1;

			while (!q.empty()) {
				if (q.front() == 0) {
					q.pop(); continue;
				}
				if (temp == q.front() && temp != 0) {
					temp *= 2; q.pop();
					blocks[i][k--] = temp;
				}
				else if (temp != 0) {
					blocks[i][k--] = temp;
				}



				if (!q.empty()) { temp = q.front(); q.pop(); }
				else temp = 0;
			}

			blocks[i][k--] = temp;

			for (int j = k; j >= 0; j--) blocks[i][j] = 0;
		}
		break;
	case 2:		// 위쪽 밀기
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) q.push(blocks[i][j]);

			int temp = 0;
			int k = 0;

			while (!q.empty()) {
				if (q.front() == 0) {
					q.pop(); continue;
				}
				if (temp == q.front() && temp != 0) {
					temp *= 2; q.pop();
					blocks[k++][j] = temp;
				}
				else if (temp != 0) {
					blocks[k++][j] = temp;
				}

				if (!q.empty()) { temp = q.front(); q.pop(); }
				else temp = 0;
			}

			blocks[k++][j] = temp;

			for (int i = k; i < size; i++) blocks[i][j] = 0;
		}
		break;
	case 3:		// 아래쪽 밀기
		for (int j = 0; j < size; j++) {
			for (int i = size - 1; i >= 0; i--) q.push(blocks[i][j]);

			int temp = 0;
			int k = size - 1;

			while (!q.empty()) {
				if (q.front() == 0) {
					q.pop(); continue;
				}
				if (temp == q.front() && temp != 0) {
					temp *= 2; q.pop();
					blocks[k--][j] = temp;
				}
				else if (temp != 0) {
					blocks[k--][j] = temp;
				}

				if (!q.empty()) { temp = q.front(); q.pop(); }
				else temp = 0;
			}

			blocks[k--][j] = temp;

			for (int i = k; i >= 0; i--) blocks[i][j] = 0;
		}
		break;
	}

	return blocks;
}

// 5번 동안 완전 탐색 (상하좌우)
void DFS(vector<vector<int>> current, int size, int cnt) {

	if (cnt == 0) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (current[i][j] > answer) answer = current[i][j];
			}
		}
	}
	else {
		for (int d = 0; d < 4; d++) {
			vector<vector<int>> temp = merge_blocks(current, size, d);
			DFS(temp, size, cnt - 1);
		}
	}

}

int main() {
	freopen("input.txt", "r", stdin);

	int N;
	cin >> N;
	
	// 보드 입력
	vector<vector<int>> game_board(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++) {
			cin >> game_board[i][j];
		}
	}

	DFS(game_board, N, 5);

	cout << answer;

	return 0;
}
