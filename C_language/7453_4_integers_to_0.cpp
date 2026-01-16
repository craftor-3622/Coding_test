// https://www.acmicpc.net/problem/7453
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> A, B, C, D;
vector<int> AB, CD;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	A.resize(N);  B.resize(N);
	C.resize(N);  D.resize(N);

	for (int i = 0; i < N; i++)
		cin >> A[i] >> B[i] >> C[i] >> D[i];
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			AB.push_back(A[i] + B[j]);
			CD.push_back(C[i] + D[j]);
		}
	}

	sort(AB.begin(), AB.end());
	sort(CD.begin(), CD.end(), greater<>());

	int m = 0;
	int n = 0;
	long long ans = 0;
	
	while (m < AB.size() && n < CD.size()) {
		int res = AB[m] + CD[n];
		if (res == 0) {
			long long cntAB, cntCD;
			for (int i = m; i < AB.size(); ++i) {
				if (AB[i] != AB[m]) break;
				cntAB = i - m + 1;
			}

			for (int i = n; i < CD.size(); ++i) {
				if (CD[i] != CD[n]) break;
				cntCD = i - n + 1;
			}
			ans += cntAB * cntCD;
			m += cntAB;
			n += cntCD;
		}
		else if (res < 0) m++;
		else if (res > 0) n++;
	}

	cout << ans;

	return 0;
}
/*
후기.
4000의 제곱은 160만이 아닌 1600만이다.
계산을 잘못해서 시간 초과/메모리 초과가...

추가로, 정렬된 배열에서 투 포인터를 사용하는데,
이 때 중복된 요소가 존재하는 경우 이에 대한 cnt 처리만
해주면 시간을 더 감소시킬 수 있다.

더해, 실무 및 코테에서 사용하는 알고리즘에서,
자료구조를 최소화하는 것이 최적화에 도움이 된다.
다음 3가지를 참조하자.
1. 같은 정보를 중복해서 또는 나누어 저장하지 말기
2. 가장 단순한 컨테이너부터 쓰기 (vector, array 등)
3. 재할당을 막아 낭비 줄이기: reserve() 한 번에 확보할 수 있다.
*/