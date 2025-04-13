# https://www.acmicpc.net/problem/1753
# Dijkstra 예제

import sys
import heapq

sys.stdin = open('sample_input.txt', 'r')


def dijkstra(start, graph, dist):
    pq = list()

    heapq.heappush(pq, (0, start))
    dist[start] = 0

    while pq:
        now_dist, now = heapq.heappop(pq)

        if now_dist > dist[now]: continue

        for edge in graph[now]:
            next_node, edge_cost = edge

            next_cost = now_dist + edge_cost
            if next_cost >= dist[next_node]: continue
            dist[next_node] = next_cost
            heapq.heappush(pq, (next_cost, next_node))


V, E = map(int, input().split())
dist = [float('inf')] * (V + 1)
graph = [[] for _ in range(V + 1)]

K = int(input())

for _ in range(E):
    u, v, w = map(int, sys.stdin.readline().split())
    # end, cost
    graph[u].append((v, w))

dijkstra(K, graph, dist)

for i in range(1, V + 1):
    print('INF' if dist[i] == float('inf') else dist[i])
