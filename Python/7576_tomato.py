# https://www.acmicpc.net/problem/7576
# 평범한 DFS
# 소요시간 : 30분

import sys
from collections import deque

delta = [[0, 1], [1, 0], [0, -1], [-1, 0]]
Pathfinder = deque()


# bfs를 통해 토마토를 익힙니다. 탐색이 끝나면 빈 공간을 검사한 뒤 이에 맞게 출력합니다.
def bfs_warehouse(area: list, ban: list, length: int, width: int) -> int:
    blank = 0
    
    # 빈 공간을 검사하는 코드입니다.
    for i in range(length):
        for j in range(width):
            if area[i][j] == 1:
                Pathfinder.append([i, j])
            elif area[i][j] == 0:
                blank += 1

    day = 0
    if blank == 0:
        return day
    else:
        while True:
            k = len(Pathfinder)

            for _ in range(k):
                point = Pathfinder.popleft()
                i, j = point
                for di, dj in delta:
                    ni = i + di
                    nj = j + dj
                    if (0 <= ni < length and 0 <= nj < width and area[ni][nj] == 0 and ban[ni][nj] == 0):
                        area[ni][nj] = 1
                        ban[ni][nj] = 1
                        Pathfinder.append([ni, nj])

            if len(Pathfinder) == 0:
                break

            day += 1

        # 다시 한번 빈 공간을 검사합니다.
        blank = 0
        for i in range(length):
            for j in range(width):
                if area[i][j] == 0:
                    blank += 1

        if blank == 0:
            return day
        else:
            return -1


sys.stdin = open("sample_input.txt", "r")

M, N = map(int, input().split())

warehouse = [list(map(int, input().split())) for _ in range(N)]
visited = [[0] * M for _ in range(N)]

result = bfs_warehouse(warehouse, visited, N, M)

print(result)

