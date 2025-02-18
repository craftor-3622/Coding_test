# dfs + backtracking

import sys

sys.stdin = open("input.txt", "r")


def dfs(selection: int, length: int, penalty: int, total: int, current: int = 0):
    global answer

    if current == length:
        if answer < total:
            answer = total
    else:
        if current == 0:
            dfs(1, length, penalty, soil_a[current], current + 1)
            dfs(2, length, penalty, soil_b[current], current + 1)
        else:
            if selection == 1:
                dfs(1, length, penalty, total + soil_a[current] - penalty, current + 1)
                if soil_a[current] - 2 * P <= soil_b[current]:
                    dfs(2, length, penalty, total + soil_b[current], current + 1)
            elif selection == 2:
                if soil_b[current] - 2 * P <= soil_a[current]:
                    dfs(1, length, penalty, total + soil_a[current], current + 1)
                dfs(2, length, penalty, total + soil_b[current] - penalty, current + 1)


T = int(input())

for test_case in range(1, T + 1):

    N, P = map(int, input().split())

    soil_a = list(map(int, input().split()))
    soil_b = list(map(int, input().split()))

    answer = 0
    dfs(1, N, P, 0)

    print(f'#{test_case} {answer}')
