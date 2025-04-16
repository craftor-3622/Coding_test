# https://www.acmicpc.net/problem/2042
import sys

sys.stdin = open("input.txt", "r")
input = sys.stdin.readline


def build(node, start, end):
    if start == end:
        tree[node] = array[start]
        return

    mid = (start + end) // 2
    build(node * 2, start, mid)
    build(node * 2 + 1, mid + 1, end)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


def query(node, start, end, left, right):
    if end < left or start > right:
        return 0
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right)


def update(node, start, end, idx, value):
    if idx < start or idx > end:
        return
    if start == end:
        tree[node] = value
        return

    mid = (start + end) // 2
    update(node * 2, start, mid, idx, value)
    update(node * 2 + 1, mid + 1, end, idx, value)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


N, M, K = map(int, input().split())

tree = [0] * (4 * N)
array = [int(input()) for _ in range(N)]
results = list()
build(1, 0, N - 1)

for _ in range(M + K):
    a, b, c = map(int, input().split())
    if a == 1:
        update(1, 0, N - 1, b - 1, c)
    elif a == 2:
        results.append(str(query(1, 0, N - 1, b - 1, c - 1)))

print('\n'.join(results))
