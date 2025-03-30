# https://www.acmicpc.net/problem/1922
# Prim
import sys
import heapq

sys.stdin = open("sample_input.txt", "r")


def prim(start):
    pq = list()
    result = 0

    heapq.heappush(pq, (0, start))
    link = -1

    while pq:
        dist, now = heapq.heappop(pq)

        if visited[now]:
            continue

        visited[now] = 1
        link += 1

        result += dist

        if link == N - 1:
            break

        for next in range(1, N + 1):
            if visited[next] == 1:
                continue

            next_dist = computers[now][next]
            
            heapq.heappush(pq, (next_dist, next))

    return result

N = int(input())
M = int(input())

# 인접 행렬
computers = [[float('inf')] * (N + 1) for _ in range(N + 1)]
visited = [0] * (N + 1)

for _ in range(M):
    a, b, cost = map(int, input().split())
    computers[a][b] = computers[b][a] = cost

answer = prim(1)

print(answer)