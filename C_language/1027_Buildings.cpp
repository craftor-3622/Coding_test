// https://www.acmicpc.net/problem/1027
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <array>
using namespace std;

vector<int> buildings;
vector<int> graph[50];

using Line = array<long long, 3>;

// 1차 함수 구하기 (ax + by + c = 0 -> [a, b, c[)])
Line getFunc(long long x1, long long y1, long long x2, long long y2) {
	return { y1 - y2, x2 - x1, x1 * y2 - y1 * x2 };
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	buildings.resize(N);

	for (int i = 0; i < N; i++) { 
		graph[i].clear();
		cin >> buildings[i];
	}

	bool flag = true;
	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			flag = true;
			Line cons = getFunc(i, buildings[i], j, buildings[j]);
			for (int k = i + 1; k < j; ++k) {
				long long res = cons[0] * k + cons[1] * buildings[k] + cons[2];
				if (res >= 0) { flag = false; break; }
			}
			if (flag) {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++) ans = max(ans, (int) graph[i].size());

	cout << ans;

	return 0;
}
/*
배경 지식을 가지는 문제에서,
C++의 객체 수명 규칙 이해에서 의의를 가지는 문제.

함수 내부의 지역 배열 주소를 반환하면서, 
로직과 무관하게 값이 변하는 현상이 발생.
이는 함수 종료 이후 스택 메모리가 재사용되거나,
다른 변수로 덮이면서 이상한 값이 나타나게 됨.

추가로 1차 함수의 a, b, c 같은 정적인 자료 구조는,
포인터 기반 전달 대신 std::array와 같은 STL이 적합하다.
c++ 수명 문제도 자유롭고, 헤드 크기도 거의 없어
단순 배열 형태의 데이터 전달에 안정적이다.
*/