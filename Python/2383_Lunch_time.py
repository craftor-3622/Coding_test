# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl&categoryId=AV5-BEE6AK0DFAVl&categoryType=CODE&problemTitle=2383&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 소요시간 : 1시간 45분
# 완전 탐색(itertools 활용 못하면 꽤 힘듦) + queue 활용

import sys
from collections import deque
from itertools import product

sys.stdin = open("sample_input.txt")

# 먼저 people_list 에 있는 사람들에서 먼저 돌린 후,
# 각 입력에 따라 stair1, 2를 1 cycle (1분)마다 돌리기
# 돌리는 순: stair1, 2 -> people_list
# 최종적으로 people_list, stair1, stair2 가 모두 비어야 함

# 계단은 항상 2개이며, FIFO 식으로 작동
stair1 = deque()
stair2 = deque()
people_waiting = deque()


# 특정 케이스에서 걸리는 시간을 계산하는 함수입니다.
def calculate_time(use_info: list, stairs: list, people_list: list):
    
    for i in range(len(people_list)):
        people_waiting.append(people_list[i].copy())
    minute = 0

    # 케이스에 따른 추가 정보 설정
    for n in range(people):
        px, py = people_waiting[n][0], people_waiting[n][1]

        if use_info[n] == 1:
            s1x, s1y = stairs[0][0], stairs[0][1]
            people_waiting[n][2] = 1
            people_waiting[n][3] = abs(px - s1x) + abs(py - s1y)
        else:
            s2x, s2y = stairs[1][0], stairs[1][1]
            people_waiting[n][2] = 2
            people_waiting[n][3] = abs(px - s2x) + abs(py - s2y)

    # 실행 시작
    while len(people_waiting) != 0 or len(stair1) != 0 or len(stair2) != 0:
        using_stair()
        waiting_stair(stairs)

        minute += 1
    
    return minute


# 계단 이용 전까지의 상황을 처리하는 함수입니다.
def waiting_stair(st_info: list):
    n = len(people_waiting)
    for i in range(n):
        people = people_waiting.popleft()

        if people[3] >= 0:
            people[3] -= 1

        if people[3] == -1 and people[2] == 1 and len(stair1) < 3:
            people[3] = st_info[0][2]
            stair1.append(people)
        elif people[3] == -1 and people[2] == 2 and len(stair2) < 3:
            people[3] = st_info[1][2]
            stair2.append(people)
        else:
            people_waiting.append(people)


# 계단 이용 중인 상황을 처리하는 함수입니다.
def using_stair():
    n1 = len(stair1)
    n2 = len(stair2)

    for _ in range(n1):
        p = stair1.popleft()
        p[3] -= 1

        if p[3] > 0:
            stair1.append(p)

    for _ in range(n2):
        p = stair2.popleft()
        p[3] -= 1

        if p[3] > 0:
            stair2.append(p)


T = int(input())

for tc in range(1, T + 1):
    # 방 한 변의 길이
    N = int(input())

    # 방의 기본 정보를 담는 변수들
    floor_info = list()
    stair_info = list()
    people = 0
    people_list = list()

    # 입력 처리
    for i in range(N):
        floor_info.append(list(map(int, input().split())))
        for j in range(N):
            if floor_info[i][j] == 1:
                people_list.append([i, j, 0, 0])
                people += 1
            elif floor_info[i][j] >= 2:
                stair_info.append([i, j, floor_info[i][j]])

    # 해당 변수는 사람 수에 따른 계단 이용하는 모든 경우의 수를 가집니다.
    stair_cases = list(product(*((1, 2) for _ in range(people))))

    # 각 케이스 별 소요 시간을 계산하고, 최소 시간을 도출합니다.
    answer = 60
    
    for case in stair_cases:
        result = calculate_time(case, stair_info, people_list)
        answer = min(result, answer)

    print(f'#{tc} {answer}')