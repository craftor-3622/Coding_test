// https://www.acmicpc.net/problem/14502
// BFS + DFS 활용

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int answer;

int bfs_virus(vector<vector<int>>& map_info, queue<vector<int>>& s_point,
	const int& height, const int& width) {
	queue<vector<int>> virus;
	vector<vector<int>> visited(height, vector<int>(width, 0));
	int delta[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
	int safe_area_cnt = 0;

	for (int n = 0; n < size(s_point); n++) {
		vector<int> point = s_point.front();
		s_point.pop();
		s_point.push(point);
		virus.push(point);
		visited[point[0]][point[1]] = 1;
	}
	
	while (size(virus) != 0) {
		vector<int> now = virus.front();
		virus.pop();
		for (auto direction : delta) {
			int ni = now[0] + direction[0];
			int nj = now[1] + direction[1];
			if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
				if (map_info[ni][nj] == 0 && visited[ni][nj] == 0) {
					visited[ni][nj] = 1;
					virus.push({ ni, nj });
				}
			}
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (visited[i][j] == 0 && map_info[i][j] == 0) safe_area_cnt++;
		}
	}

	return safe_area_cnt;
}

void dfs_wall(vector<vector<int>>& map_info, queue<vector<int>>& s_point,
	const int& height, const int& width, int cnt, int last_num = -1) {
	if (cnt == 0) {
		int result = bfs_virus(map_info, s_point, height, width);
		if (answer < result) answer = result;
	}
	else {
		for (int n = last_num + 1; n < height*width; n++) {
			if (map_info[n / width][n % width] == 0) {
				map_info[n / width][n % width] = 1;
				dfs_wall(map_info, s_point, height, width, cnt - 1, n);
				map_info[n / width][n % width] = 0;
			}
		}
	}
}


int main() {
	freopen("input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;
	answer = 0;

	vector<vector<int>> lab_area(N, vector<int>(M, 0));
	queue<vector<int>> virus_init;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> lab_area[i][j];
			if (lab_area[i][j] == 2) virus_init.push({ i, j });
		}
	}

	dfs_wall(lab_area, virus_init, N, M, 3);

	cout << answer << endl;

	return 0;
}

