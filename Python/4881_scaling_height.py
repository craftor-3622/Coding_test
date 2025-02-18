import sys

sys.stdin = open("input.txt", "r")


def dfs(tree: dict, now: int):
    global know_cnt
    visited[now] = 1

    for higher in tree.get(now, []):
        if visited[higher] == 0:
            know_cnt += 1
            dfs(tree, higher)


T = int(input())

for test_case in range(1, T + 1):
    N = int(input())
    M = int(input())

    higher_dict = dict()
    lower_dict = dict()

    answer = 0

    for _ in range(M):
        a, b = map(int, input().split())
        if not higher_dict.get(a, False):
            higher_dict[a] = [b]
        else:
            higher_dict[a].append(b)
        if not lower_dict.get(b, False):
            lower_dict[b] = [a]
        else:
            lower_dict[b].append(a)

    for i in range(1, N + 1):
        know_cnt = 0
        visited = [0] * (N + 1)
        dfs(higher_dict, i)
        dfs(lower_dict, i)
        if know_cnt == N - 1:
            answer += 1

    print(f'#{test_case} {answer}')
