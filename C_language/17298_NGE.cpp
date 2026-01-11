// https://www.acmicpc.net/problem/17298
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

vector<int> stack;
vector<int> arr;
vector<int> nge;

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	arr.resize(N);
	nge.resize(N);

	for (int i = 0; i < N; i++) cin >> arr[i];

	for (int i = N - 1; i >= 0; i--) {
		while (!stack.empty()) {
			if (stack.back() > arr[i]) break;
			stack.pop_back();
		}

		if (stack.empty()) nge[i] = -1;
		else nge[i] = stack.back();
		stack.push_back(arr[i]);
	}

	for (int i = 0; i < N; i++) cout << nge[i] << " ";

	return 0;
}
/*
후기...?
때로는 단순하면서도 효율적인 자료구조 몇 개가
시간 복잡도를 극적으로 개선할 수도 있다.
대신, 자료구조의 특성을 활용하기 좋게 사용해야 한다.
*/