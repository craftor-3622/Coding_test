# https://swexpertacademy.com/main/talk/solvingClub/problemSubmitHistory.do?contestProbId=AZIyCYJ6p30DFAQP&solveclubId=AZTP1QzqXnbHBIRD&problemBoxTitle=%2803.21%29++%EB%AC%B8%EC%A0%9C%ED%92%80%EC%9D%B43&problemBoxCnt=9&probBoxId=AZVkSAOaDQXHBINE

import sys

sys.stdin = open("input.txt", "r")

direction = [[0, 1], [1, 0], [0, -1], [-1, 0]]


def dfs(now: int, pos: tuple, d: int, cur_k: int):
    global N, field, visited, answer

    i, j = pos

    if cur_k < 0:
        return
    elif field[i][j] == "Y":
        answer = min(answer, now)
        return
    elif now > answer:
        return

    else:
        for nd in range(4):
            di, dj = direction[nd]
            ni, nj = i + di, j + dj
            cost = 1 + min(abs(d - nd), 4 - abs(d - nd))

            if 0 <= ni < N and 0 <= nj < N:
                if visited[ni][nj] != 0:
                    continue
                visited[ni][nj] = now + cost
                if field[ni][nj] == "T":
                    dfs(visited[ni][nj], (ni, nj), nd, cur_k - 1)
                else:
                    dfs(visited[ni][nj], (ni, nj), nd, cur_k)
                visited[ni][nj] = 0


T = int(input())

for tc in range(1, T + 1):
    N, K = map(int, input().strip().split())
    field = [list(input().strip()) for _ in range(N)]
    visited = [[0] * N for _ in range(N)]
    answer = 21e8
    si = sj = 0

    for i in range(N):
        for j in range(N):
            if field[i][j] == "X":
                visited[i][j] = 1
                si, sj = i, j
                break

    dfs(0, (si, sj), 3, K)
    if answer == 21e8:
        answer = -1

    print(f"#{tc} {answer}")
