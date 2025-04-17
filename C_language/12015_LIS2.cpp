// 이전 문제 : https://www.acmicpc.net/problem/11053
// N 범위가 작은 경우 dp로 해결 가능

// https://www.acmicpc.net/problem/12015
// 하지만 N 범위가 크다면?
// 같은 문제임에도 범위가 커지면서 해결 방법이 전혀 달라지는 case

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);

	int N;
	cin >> N;

	vector<int> arr(N, 0);
	vector<int> lis;

	for (int i = 0; i < N; i++) cin >> arr[i];
	lis.push_back(arr[0]);

	int l, r, m;

	for (int i = 1; i < N; i++)	{
		if (arr[i] > lis.back()) lis.push_back(arr[i]);
		else {
			l = 0, r = lis.size() - 1;
			m = (l + r) / 2;
			while (l != r) {
				if (lis[m] < arr[i]) l = m + 1;
				else r = m;
				m = (l + r) / 2;
			}
			lis[m] = arr[i];
		}
	}

	cout << lis.size();
}