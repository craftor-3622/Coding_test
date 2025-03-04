// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXQsLWKd5cDFAUo&categoryId=AWXQsLWKd5cDFAUo&categoryType=CODE&problemTitle=%ED%82%A4&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
// 올해 2월 SWEA A형 기출, DFS 활용 문제 - cpp로 재도전

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void dfs(const unordered_map<int, vector<int>>& tree, int target, vector<int>& ban, int& count) {
	ban[target] = 1;
	if (tree.find(target) != tree.end()) {
		for (auto child : tree.at(target)) {
			if (ban[child] == 0) {
				count++;
				dfs(tree, child, ban, count);
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int answer = 0;
		int N, M;
		cin >> N >> M;

		unordered_map<int, vector<int>> asc_order;
		unordered_map<int, vector<int>> desc_order;

		for (int n = 0; n < M; n++) {
			int a, b;
			cin >> a >> b;
			asc_order[a].push_back(b);
			desc_order[b].push_back(a);
		}

		for (int n = 1; n <= N; n++) {		
			int founded = 0;
			vector<int> visited(N + 1, 0);

			for (int i = 1; i <= N; i++) visited[i] = 0;

			dfs(asc_order, n, visited, founded);
			dfs(desc_order, n, visited, founded);

			if (founded == N - 1) answer++;
		}

		cout << "#" << t << " " << answer << endl;
	}

	return 0;
}

/*
소요시간 - 1시간 20분
시간초과 난 이유 : dfs 함수에서 매개변수의 원본을 그대로 가져오는 것이 성능상 높기 때문.
& 참조자 사용 없이 매개 변수를 그대로 가져오는 경우, 원본을 복사하기 때문에 이 과정에서 O(N) 만큼 시간 소요 발생.
Copilot의 답변 : DFS/BFS 같은 탐색 함수에서는 참조(const &)를 사용해야 성능이 저하되지 않음.
*/
