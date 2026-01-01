// https://www.acmicpc.net/problem/7662
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct maxCmp {
	bool operator()(int left, int right) const {
		if (left < right) return true;
		if (left > right) return false;
		return false;
	}
};

struct minCmp {
	bool operator()(int left, int right) const {
		if (left > right) return true;
		if (left < right) return false;
		return false;
	}
};

priority_queue<int, vector<int>, maxCmp> maxHeap;
priority_queue<int, vector<int>, minCmp> minHeap;
map<int, int> Data;

#define MAX_N 100005

// 요소 추가
void addData(int val) {
	maxHeap.push(val);
	minHeap.push(val);

	if (Data.find(val) == Data.end()) Data[val] = 1;
	else ++Data[val];
}

// 요소 제거
void deleteData(int mod) {
	int now;
	switch (mod) {
	case 1:
		while (!maxHeap.empty()) {
			now = maxHeap.top();

			if (Data[now] == 0) {
				maxHeap.pop();
				continue;
			}
			else {
				maxHeap.pop();
				--Data[now];
				break;
			}
		}
		break;
	case -1:
		while (!minHeap.empty()) {
			now = minHeap.top();

			if (Data[now] == 0) {
				minHeap.pop();
				continue;
			}
			else {
				minHeap.pop();
				--Data[now];
				break;
			}
		}
		break;
	}
}

// 최대, 최소 출력
void output() {
	int maxVal, minVal;
	bool flag = false;

	int now;
	while (!maxHeap.empty()) {
		now = maxHeap.top();

		if (Data[now] > 0) {
			maxVal = now;
			flag = true;
			break;
		}

		maxHeap.pop();
	}

	while (!minHeap.empty() && flag) {
		now = minHeap.top();

		if (Data[now] > 0) {
			minVal = now;
			break;
		}

		minHeap.pop();
	}

	if (!flag) cout << "EMPTY" << "\n";
	else cout << maxVal << " " << minVal << "\n";
}

int main() {
	// 대용량 Input
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("sample_input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 0; tc < T; ++tc) {
		while (!maxHeap.empty()) maxHeap.pop();
		while (!minHeap.empty()) minHeap.pop();
		Data.clear();

		int K;
		cin >> K;

		for (int k = 0; k < K; ++k) {
			char order;
			int val;
			cin >> order >> val;

			switch (order) {
			case 'I':
				addData(val);
				break;
			case 'D':
				deleteData(val);
				break;
			}
		}

		output();
	}

	return 0;
}
/*
후기.
간단한 Type의 Max/Min Heap은 이렇게 정의하기 편리하다.

// Max Heap (기본값)
priority_queue<int, vector<int>, less<>> pq;
priority_queue<int> pq;

// Min Heap
priority_queue<int, vector<int>, greater<int>> pq;

==========================
별도로, 이번 문제는 Lazy Evaluation이 키포인트.
삭제 요청이 들어오면 바로 삭제하는 것이 아닌,
별도 유효 자료를 두어 관리하고 필요할 때만 연산을 수행하는 방식.

다만 이 부분은 구현 과정에서 실수가 발생할 확률이 높고,
자료구조 관리 로직과 비즈니스 로직이 섞이기 쉬워
실무에서는 여기에 단일 책임 원칙도 깨지기 쉽다.
그래서인지 체감 난이도가 어렵다고 느꼈음.
*/