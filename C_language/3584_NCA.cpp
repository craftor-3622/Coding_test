// https://www.acmicpc.net/problem/3584
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<int> parent;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int T;
	cin >> T;

	vector<int> aList;
	vector<int> bList;

	for (int tc = 0; tc < T; tc++) {
		aList.clear();
		bList.clear();

		int N;
		cin >> N;

		parent.assign(N + 1, -1);

		for (int n = 0; n < N - 1; n++) {
			int p, c;
			cin >> p >> c;
			parent[c] = p;
		}

		int a, b;
		cin >> a >> b;

		int now = a;
		while (now != -1) {
			aList.push_back(now);
			now = parent[now];
		}

		now = b;
		while (now != -1) {
			bList.push_back(now);
			now = parent[now];
		}

		int nca = -1;
		while (!aList.empty() && !bList.empty()) {
			int aParent = aList.back();
			int bParent = bList.back();
			aList.pop_back();  bList.pop_back();
			if (aParent == bParent) nca = aParent;
			else break;
		}

		cout << nca << "\n";
	}

	return 0;
}