// https://school.programmers.co.kr/learn/courses/30/lessons/42895
#include <cmath>
#include <set>

using namespace std;

int power(int base, int n) {
    if (n == 0) return 1;
    else return base * power(base, n - 1);
}

int solution(int N, int number) {
    set<int> dp[10];    // DP
    
    // 초기값 설정
    for (int i = 1; i < 9; i++) {
        int starter = 0;
        for (int j = 0; j < i; j++) {
            starter = starter * 10 + N;
        }
        dp[i].insert(starter);
    }
    
    // dp 연산
    for (int k = 2; k < 9; k++) {
        for (int i = 1; i < k; i++) {
            for (int left : dp[i]) {
                for (int right : dp[k - i]) {
                    dp[k].insert(left + right);
                    dp[k].insert(left - right);
                    dp[k].insert(left * right);
                    if (right != 0) dp[k].insert(left / right);
                }
            }
        }
    }
    
    int answer = -1;
    int search = 1;
    while (search < 9) {
        if (dp[search].find(number) != dp[search].end()) {
            answer = search;
            break;
        }
        
        search++;
    }

    return answer;
}

/*
후기

DP + 분할 정복.
비슷한 유형으로 행렬 문제가 있었는데, 이건 그거보다 3배는 어렵다...

한줄 평 - DP를 표현하는 방법은 무궁무진하다, 그리고 비효율적일 수도 있다.
*/