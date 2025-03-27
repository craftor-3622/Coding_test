// https://www.acmicpc.net/problem/11404
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);

	int N, M;

	cin >> N >> M;

	vector<vector<long long int>> city(N, vector<long long int>(N, 21e8));

	for (int i = 0; i < N; i++) city[i][i] = 0;

	for (int n = 0; n < M; n++)	{
		int start, end, cost;
		cin >> start >> end >> cost;
		if (city[start-1][end-1] > cost) city[start-1][end-1] = cost;
	}

	for (int m = 0; m < N; m++) {
		for (int s = 0; s < N; s++) {
			for (int e = 0; e < N; e++) {
				if (city[s][e] > city[s][m] + city[m][e]) {
					city[s][e] = city[s][m] + city[m][e];
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (city[i][j] == 21e8) {
				cout << 0 << " ";
			}
			else {
				cout << city[i][j] << " ";
			}
		}
		cout << endl;
	}

	return 0;
}