# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu&categoryId=AV5VwAr6APYDFAWu&categoryType=CODE&problemTitle=%EB%94%94%EC%A0%80%ED%8A%B8+%EC%B9%B4%ED%8E%98&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 소요시간 : 1시간
# 이론상 O(n^6)의 시간 복잡도. n = 20에 탈출 조건, 연관식 등이 있어 체감상 O(n^4) 정도.
# 별개로 하드 코딩 부분이 있어서 손 볼 부분도 많음.

import sys

sys.stdin = open("input.txt", "r")


# 시작 좌표와 두 길이가 주어지면, 가능한 trail 을 반환합니다.
def add_trail(area: list, size: int, left: int, right: int) -> int:
    length = 0
    find = 0

    for i in range(size - left - right):
        for j in range(left, size - right):
            start_i, start_j = i, j
            trail = []
            flag = 1

            for _ in range(right):
                if flag == 0:
                    break
                di, dj = [1, 1]
                i += di
                j += dj
                item = area[i][j]
                if item in trail:
                    flag = 0
                    break
                else:
                    trail.append(item)

            for _ in range(left):
                if flag == 0:
                    break
                di, dj = [1, -1]
                i += di
                j += dj
                item = area[i][j]
                if item in trail:
                    flag = 0
                    break
                else:
                    trail.append(item)

            for _ in range(right):
                if flag == 0:
                    break
                di, dj = [-1, -1]
                i += di
                j += dj
                item = area[i][j]
                if item in trail:
                    flag = 0
                    break
                else:
                    trail.append(item)

            for _ in range(left):
                if flag == 0:
                    break
                di, dj = [-1, 1]
                i += di
                j += dj
                item = area[i][j]
                if item in trail:
                    flag = 0
                    break
                else:
                    trail.append(item)

            i, j = start_i, start_j
            if flag == 1:
                length = (left + right) * 2
                find = 1
                break
        if find == 1:
            break

    return length


# 가능한 디저트 동산의 길이를 출력하는 함수입니다.
def dessert_trail(area: list, size: int):
    # 마름모의 평행하지 않은 서로 다른 한변의 길이합의 최대 크기는 size - 1 입니다.
    max_length = size - 1
    trail_length = 0

    # 시작 좌표 지정
    for left_dia in range(1, max_length):
        for right_dia in range(1, max_length + 1 - left_dia):
            length = add_trail(area, size, left_dia, right_dia)
            trail_length = max(trail_length, length)

    return trail_length


T = int(input())

for test_case in range(1, T + 1):
    N = int(input())

    store_area = [list(map(int, input().split())) for _ in range(N)]
    trail_list = []

    result = dessert_trail(store_area, N)

    if result == 0:
        answer = -1
    else:
        answer = result

    print(f'#{test_case} {answer}')
