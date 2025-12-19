// https://www.acmicpc.net/problem/20055
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <deque>
using namespace std;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N, K;
	cin >> N >> K;

	deque<int> active;
	deque<int> sleep;
	deque<int> robots;

	// 초기 벨트 상태 입력
	int a;
	for (int i = 0; i < N; ++i) {
		cin >> a;
		active.push_back(a);
	}

	for (int i = 0; i < N; ++i) {
		cin >> a;
		sleep.push_front(a);
	}

	int time = 0;
	int now_k = 0;
	int num_robots;
	while (now_k < K) {
		++time;

		// 1단계 - 벨트 회전
		int unmount_pos = active.back(); active.pop_back();
		int mount_pos = sleep.front(); sleep.pop_front();

		sleep.push_back(unmount_pos);
		active.push_front(mount_pos);

		num_robots = robots.size();
		for (int r = 0; r < num_robots; ++r) ++robots[r];
		if (num_robots && robots.back() == N - 1) robots.pop_back();

		// 2단계 - 로봇 이동
		num_robots = robots.size();
		for (int r = num_robots - 1; r >= 0; --r) {
			if (active[robots[r] + 1]) {
				if (r == num_robots - 1) {
					++robots[r];
					active[robots[r]]--;
					if (active[robots[r]] == 0)
						++now_k;
				}
				else if (robots[r] + 1 < robots[r + 1]) {
					++robots[r];
					active[robots[r]]--;
					if (active[robots[r]] == 0)
						++now_k;
				}
			}
		}
		if (num_robots && robots[num_robots - 1] == N - 1) robots.pop_back();

		// 3단계 - 로봇 mount
		if (active[0]) {
			robots.push_front(0);
			--active[0];
			if (active[robots[0]] == 0)
				++now_k;
		}
	}

	cout << time << endl;

	return 0;
}
/*
후기.
지금처럼 queue 처럼 보이는 자료구조에서 인덱스 접근이 안되기에,
deque를 활용해 상태를 바꾸는 로직은 합리적임.

다만, 문제를 다시 분석해보면 이 시뮬레이션은 실제 데이터가 이동하는 구조가 아니라,
기준 인덱스의 변화로 해석할 수 있는 문제임을 알 수 있다.
벨트 위 내구도의 순서는 회전 과정에서도 뒤섞이지 않고 그대로 유지되기 때문이다.

즉, 벨트를 고정된 상태로 두고, 기준 위치(start)와 로봇의
활동 상태만을 변화시키는 방식으로도 문제를 해결할 수 있다.
이와 같은 관점에서는 헤드 연산 비용이 상대적으로 큰 deque 대신,
아래처럼 vector와 인덱스 연산을 이용한 구현이 더 간결하고 직관적이다.

vector<int> belt;
vector<bool> robot;
int start;
*/