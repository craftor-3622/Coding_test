// https://www.acmicpc.net/problem/7576
#include <iostream>
#include <queue>

using namespace std;

struct position {
	int x;
	int y;
};

queue<position> q;

int bfs(int** area, int height, int width) {
	int* visited = new int[height * width];

	int day = -1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			visited[i * width + j] = 0;
			if (area[i][j] == 1) {
				position temp;
				temp.x = j;
				temp.y = i;
				q.push(temp);
			}
		}
	}

	while (q.size() != 0) {
		day++;
		int L = q.size();
		for (int n = 0; n < L; n++) {
			position cur = q.front();
			q.pop();
			position new_pos;
			int i = cur.y;
			int j = cur.x;
			visited[i * width + j] = 1;

			if (i + 1 < height) {
				if ((area[i + 1][j] == 0) && (visited[(i + 1) * width + j] == 0)) {
					area[i + 1][j] = 1;
					visited[(i + 1) * width + j] = 1;
					new_pos = { j, i + 1 };
					q.push(new_pos);
				}
			}
			if (i - 1 >= 0) {
				if ((area[i - 1][j] == 0) && (visited[(i - 1) * width + j] == 0)) {
					area[i - 1][j] = 1;
					visited[(i - 1) * width + j] = 1;
					new_pos = { j, i - 1 };
					q.push(new_pos);
				}
			}
			if (j + 1 < width) {
				if ((area[i][j + 1] == 0) && (visited[i * width + j + 1] == 0)) {
					area[i][j + 1] = 1;
					visited[i * width + j + 1] = 1;
					new_pos = { j + 1, i };
					q.push(new_pos);
				}
			}
			if (j - 1 >= 0) {
				if ((area[i][j - 1] == 0) && (visited[i * width + j - 1] == 0)) {
					area[i][j - 1] = 1;
					visited[i * width + j - 1] = 1;
					new_pos = { j - 1, i };
					q.push(new_pos);
				}
			}
		}
	}
	
	/* 델타법 적용하기 (C++ 버전)
	int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

	for (int d = 0; d < 4; ++d) {
		int new_i = i + directions[d][0];  // 새로 계산된 i 좌표
		int new_j = j + directions[d][1];  // 새로 계산된 j 좌표

		// 유효한 범위 내에 있고, 방문하지 않은 위치라면
		if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width) {
			if (area[new_i][new_j] == 0 && visited[new_i * width + new_j] == 0) {
				area[new_i][new_j] = 1;
				visited[new_i * width + new_j] = 1;
				new_pos = { new_j, new_i };
				q.push(new_pos);
			}
		}
	}
	*/


	// 남은 부분이 있는지 검사
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (area[i][j] == 0) day = -1;
		}
	}

	delete[] visited;
	return day;
}

int main()
{
	int M, N;
	cin >> M >> N;

	// 2차원 배열 동적 할당
	int** area = new int*[N];
	for (int i = 0; i < N; i++) {
		area[i] = new int[M];
		for (int j = 0; j < M; j++) {
			cin >> area[i][j];
		}
	}

	int answer = bfs(area, N, M);

	cout << answer << endl;

	// 메모리 해제
	for (int i = 0; i < N; i++) {
		delete[] area[i];
	}
	delete[] area;

	return 0;
}

// 간단한 BFS 문제