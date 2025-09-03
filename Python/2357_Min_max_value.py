# segment tree - 구간 query 문제

import sys

input = sys.stdin.readline


def build(node, start, end):
    if start == end:
        tree[node] = (arr[start], arr[start])
        return

    mid = (start + end) // 2
    build(2 * node, start, mid)
    build(2 * node + 1, mid + 1, end)
    tree[node] = (min(tree[2 * node][0], tree[2 * node + 1][0]),
                  max(tree[2 * node][1], tree[2 * node + 1][1]))


def query(node, start, end, left, right):
    if start > right or end < left:
        return float('inf'), float('-inf')
    elif left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    left_query = query(2 * node, start, mid, left, right)
    right_query = query(2 * node + 1, mid + 1, end, left, right)
    return min(left_query[0], right_query[0]), max(left_query[1], right_query[1])


N, M = map(int, input().split())

arr = list()
tree = [0] * (4 * N)

for _ in range(N):
    element = int(input())
    arr.append(element)

build(1, 0, N - 1)

for _ in range(M):
    a, b = map(int, input().split())
    min_val, max_val = query(1, 0, N - 1, a - 1, b - 1)
    print(min_val, max_val)
