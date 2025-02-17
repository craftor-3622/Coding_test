# https://www.acmicpc.net/problem/7569
# 소요시간 : 40분, bfs 3차원 그래프 문제 (2차원의 확장)

import sys
from collections import deque

sys.stdin = open("sample_input.txt", "r")

# dx, dy, dz
delta3D = [[0, 1, 0], [1, 0, 0], [0, 0, 1], [0, -1, 0], [-1, 0, 0], [0, 0, -1]]
Pathfinder = deque()


def bfs(length, width, height):
    count = -1

    while len(Pathfinder) != 0:
        count += 1
        for n in range(len(Pathfinder)):
            i, j, k = Pathfinder.popleft()
            for di, dj, dk in delta3D:
                ni, nj, nk = i + di, j + dj, k + dk
                if 0 <= ni < length and 0 <= nj < width and 0 <= nk < height:
                    if warehouse[nk][ni][nj] == 0 and visited[nk][ni][nj] == 0:
                        Pathfinder.append([ni, nj, nk])
                        warehouse[nk][ni][nj] = 1
                        visited[nk][ni][nj] = 1

    return count


M, N, H = map(int, input().split())

warehouse = [[[None] for _ in range(N)] for _ in range(H)]
visited = [[[0] * M for _ in range(N)] for _ in range(H)]
day = 0

for k in range(H):
    for i in range(N):
        warehouse[k][i] = list(map(int, input().split()))
        for j in range(M):
            if warehouse[k][i][j] == 1:
                Pathfinder.append([i, j, k])
                visited[k][i][j] = 1

result = bfs(N, M, H)

blank = 0
for k in range(H):
    for i in range(N):
        for j in range(M):
            if warehouse[k][i][j] == 0:
                blank += 1

result = -1 if blank != 0 else result

print(result)


