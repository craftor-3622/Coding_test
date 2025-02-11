# https://www.acmicpc.net/problem/12927

switch_dict = {
    'N': 0,
    'Y': 1,
}

arr = list(input())
switch_list = [switch_dict[item] for item in arr]
N = len(switch_list)
answer = -1
count = 0

for i in range(N):
    if switch_list[i] != 0:
        for n in range(i, N, i + 1):
            switch_list[n] = (switch_list[n] + 1) % 2
        count += 1

    if 1 not in switch_list:
        answer = count
        break

print(answer)
