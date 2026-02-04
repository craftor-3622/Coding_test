// https://www.acmicpc.net/problem/1644
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define SQRT_MAX_N 2000

vector<bool> isPrime;
vector<int> primes;

void primeSet(int sqrt_n) {
	isPrime[2] = true;
	for (int i = 1; i < sqrt_n * sqrt_n / 2; i++) isPrime[2 * i + 1] = true;
	for (int i = 3; i <= sqrt_n; i++) {
		if (isPrime[i]) {
			for (int x = i * i; x < sqrt_n * sqrt_n; x += 2 * i)
				isPrime[x] = false;
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int N;
	cin >> N;
	isPrime.resize(SQRT_MAX_N * SQRT_MAX_N + 1, false);
	primeSet(min(N, SQRT_MAX_N));

	for (int i = 2; i <= N; i++)
		if (isPrime[i]) primes.push_back(i);

	int sum = 0;
	int ans = 0;
	int l = 0;
	for (int r = 0; r < primes.size(); r++) {
		sum += primes[r];
		while (sum > N)
			sum -= primes[l++];
		if (sum == N) ans++;
	}

	cout << ans;

	return 0;
}