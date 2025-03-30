# https://www.acmicpc.net/problem/1922
# Kruskal
import sys

sys.stdin = open("sample_input.txt", "r")


def find(x):
    if x != parent[x]:
        parent[x] = find(parent[x])
    return parent[x]


def union(x, y):
    rx, ry = find(x), find(y)

    if rx != ry:
        if rank[rx] > rank[ry]:
            parent[ry] = rx
        elif rank[rx] < rank[ry]:
            parent[rx] = ry
        else:
            parent[ry] = rx
            rank[rx] += 1


def kruskal():
    result = 0

    for i in range(M):
        x, y, c = graph[i]
        if find(x) != find(y):
            union(x, y)
            result += c

    return result


N = int(input())
M = int(input())

# 인접 리스트
graph = []
parent = [i for i in range(N + 1)]
rank = [1] * (N + 1)

for _ in range(M):
    a, b, cost = map(int, input().split())
    graph.append((a, b, cost))

graph.sort(key=lambda x:x[2])

print(kruskal())