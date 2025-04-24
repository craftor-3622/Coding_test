# https://www.acmicpc.net/problem/6549
# Stack 풀이
import sys

sys.stdin = open("sample_input.txt", "r")

while True:
    test_case = list(map(int, sys.stdin.readline().split()))

    N = test_case[0]
    if N == 0:
        break

    h_list = test_case[1:]
    stack = list()
    answer = 0

    for h in h_list:
        if not stack or stack[-1][0] <= h:
            stack.append((h, 1))
        else:
            rec_w = 0
            while stack and stack[-1][0] > h:
                height, width = stack.pop()
                rec_w += width
                answer = max(answer, height * rec_w)
                
            stack.append((h, rec_w + 1))

    rec_w = 0
    while stack:
        height, width = stack.pop()
        rec_w += width
        answer = max(answer, height * rec_w)

    print(answer)