// https://www.acmicpc.net/problem/11660
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> arr;
vector<vector<int>> subsum;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("sample_input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;

	arr.resize(N, vector<int>(N));
	subsum.resize(N + 1, vector<int>(N + 1, 0));
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i][j];

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			subsum[i][j] = subsum[i][j - 1] + arr[i - 1][j - 1];

	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			subsum[i][j] = subsum[i - 1][j] + subsum[i][j];

	int x1, y1, x2, y2;
	int ans;

	for (int m = 0; m < M; m++) {
		cin >> x1 >> y1 >> x2 >> y2;
		ans = subsum[x2][y2] - subsum[x1 - 1][y2]
			- subsum[x2][y1 - 1] + subsum[x1 - 1][y1 - 1];
		cout << ans << "\n";
	}
	return 0;
}