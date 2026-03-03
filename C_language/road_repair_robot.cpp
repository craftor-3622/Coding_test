// https://www.codetree.ai/ko/frequent-problems/hsat/problems/road-repair-robot/description
#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<long long> positions;
int ans;

int main() {
    cin >> N >> K;

    positions.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> positions[i];
    }

    int left = 1;
    int right = positions[N - 1] - positions[0] + 1;
    ans = positions[N - 1] - positions[0] + 1;

    int mid = (left + right) / 2;
    int cnt;
    while (left < right) {

        cnt = 0;
        int i = 0;
        int j = 0;
        while (i < N) {
            while (j < N && positions[j] < positions[i] + mid)
                j++;
            cnt++;
            i = j;
        }

        if (cnt > K) left = mid + 1;
        else if (cnt <= K) {
            right = mid;
            ans = mid;
        }

        mid = (left + right) / 2;
    }

    cout << ans;

    return 0;
}
