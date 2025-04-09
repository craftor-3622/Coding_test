# https://www.acmicpc.net/problem/1806
# 누적합 기초 문제
import sys

N, S = map(int, input().split())
num_list = list(map(int, sys.stdin.readline().split()))
subtotal = [0] * (N + 1)

for i in range(N):
    subtotal[i+1] = subtotal[i] + num_list[i]

answer = float('inf')
left = 0
right = 1

while right <= N:
    total = subtotal[right] - subtotal[left]

    if total >= S:
        answer = min(answer, right - left)
        left += 1
    elif total < S:
        right += 1

print(0 if answer == float('inf') else answer)
