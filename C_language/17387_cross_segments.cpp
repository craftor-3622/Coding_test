// https://www.acmicpc.net/problem/17387
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

struct Coefficient {
	long long coX, coY, constant;
};

// 선분의 두 지점으로부터 계수 및 상수값을 구하는 함수
Coefficient get_variables(int x1, int y1, int x2, int y2) {
	if (x1 == x2) return { 1, 0, -x1 };
	if (y1 == y2) return { 0, 1, -y1 };

	// 계수 값을 먼저 작성한 뒤, 대입하는 방식으로 상수 계산
	long long a = y1 - y2;
	long long b = x2 - x1;
	long long c = (a * x1 + b * y1) * (-1);
	return { a, b, c };
}

int get_pos(Coefficient var, int x, int y) {
	if (var.coX * x + var.coY * y + var.constant > 0) return 1;
	if (var.coX * x + var.coY * y + var.constant < 0) return -1;
	return 0;
}

bool check_segment(int cx, int cy, int x1, int y1, int x2, int y2) {
	if (y1 == y2) {
		if (cx >= x1 && cx <= x2) return true;
		if (cx <= x1 && cx >= x2) return true;
		return false;
	}
	else {
		if (cy >= y1 && cy <= y2) return true;
		if (cy <= y1 && cy >= y2) return true;
		return false;
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	Coefficient var1 = get_variables(x1, y1, x2, y2);

	int x3, y3, x4, y4;
	cin >> x3 >> y3 >> x4 >> y4;
	Coefficient var2 = get_variables(x3, y3, x4, y4);

	int pos1 = get_pos(var2, x1, y1);
	int pos2 = get_pos(var2, x2, y2);

	int pos3 = get_pos(var1, x3, y3);
	int pos4 = get_pos(var1, x4, y4);

	if (pos1 * pos2 == -1 && pos3 * pos4 == -1) cout << 1;
	else if (pos1 == 0 && check_segment(x1, y1, x3, y3, x4, y4)) cout << 1;
	else if (pos2 == 0 && check_segment(x2, y2, x3, y3, x4, y4)) cout << 1;
	else if (pos3 == 0 && check_segment(x3, y3, x1, y1, x2, y2)) cout << 1;
	else if (pos4 == 0 && check_segment(x4, y4, x1, y1, x2, y2)) cout << 1;
	else cout << 0;

	return 0;
}
/*
후기.
어찌보면, 자주 나오는 그래프 기반 문제보다 더 어려운 문제라고 생각했다.
문제의 본질은 좌표 값을 구하는 것이 아니라,
두 선분의 상대적인 위치 관계를 판정하는 것이 핵심이었다.
특히 공선, 끝점 접촉처럼 특이 케이스가 오히려 문제의 정답을 결정한다는 점에서,
예외 처리를 나중에 덧붙이는 방식이 위험하다는 것을 느끼게 되었다.

실무에서는 대부분의 문제에서 정확한 값 자체보다 조건 충족 여부가 더 중요하다.
이 문제 역시 교차점 좌표를 계산하는 것이 아니라,
교차 여부라는 불리언 판정을 먼저 안정적으로 처리하는 것이 핵심이었다.
(교차 여부 판정과 교차점 계산은 서로 다른 책임이다.)

그래서 앞으로의 개발에서도 아래 두 가지는 반드시 나눠 처리하는 것이 좋다고 생각한다.
- 조건을 만족하는가?
- 조건을 만족한다면 그 결과값은 어떻게 되는가?
*/