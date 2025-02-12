# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq
# 공사 영역 확인은 완전 탐색으로 경우의 수 모두 확인하고(N은 작으니까), 경로 길이는 BFS 로 푸는 문제
# 소요시간: 40분, 테스트 개수 : 50/51
# 틀린 이유 : 깎기 전의 봉우리를 기준으로 시작점이 결정되어야 한다. (문제 설명이 너무 애매하게 되어 있었다)
# 최종 소요시간: 1시간

import sys                              # input.txt에서 입력을 받기 위한 패키지
from pprint import pprint               # 2차원 배열 가독성을 위한 출력 함수
from collections import deque           # DFS에서 활용할 Queue 모듈

sys.stdin = open("input.txt", "r")

delta = [[0, 1], [1, 0], [0, -1], [-1, 0]]
Pathfinder = deque()


# bfs 탐색으로 후보 영역의 특정 시작 지점에서 가장 긴 등산로의 길이를 계산합니다.
def bfs_trail(area: list, length: int, start_i: int, start_j: int) -> int:

    path = 0
    Pathfinder.append([start_i, start_j])

    while len(Pathfinder) > 0:

        for _ in range(len(Pathfinder)):
            i, j = Pathfinder.popleft()

            for di, dj in delta:
                ni, nj = i + di, j + dj

                if 0 <= ni < length and 0 <= nj < length:
                    if area[ni][nj] < area[i][j]:
                        Pathfinder.append([ni, nj])

        path += 1

    return path


# 해당 영역에서 가능한 포인터 리스트를 반환합니다.
def start_point(area: list, length: int):
    max_height = 0
    max_idx_list = []

    for i in range(length):
        for j in range(length):
            if area[i][j] > max_height:
                max_height = area[i][j]
                max_idx_list.clear()
                max_idx_list.append([i, j])
            elif area[i][j] == max_height:
                max_idx_list.append([i, j])

    return max_idx_list


# 후보 영역에서 가능한 시작 지점들에서 시작해 가장 긴 길이를 반환합니다.
def longest_length(area: list, length: int, idx_list: list):

    height_list = []

    for position in idx_list:
        height_list.append(bfs_trail(area, length, *position))

    return max(height_list)


# 공사했을 때 가능한 경우의 수를 모두 출력합니다.
def available_field(origin: list, length: int, depth: int) -> list:
    available_list = list()
    available_list.append(origin)

    for i in range(length):
        for j in range(length):
            for k in range(1, depth + 1):
                temp = [origin[row].copy() for row in range(length)]
                temp[i][j] -= k
                available_list.append(temp)

    return available_list


T = int(input())

for test_case in range(1, T + 1):
    N, K = map(int, input().split())

    # 2차 배열 (2차원 공간이니까)
    mountain = [list(map(int, input().split())) for _ in range(N)]
    # 3차 배열 (mountain 에서 공사했을 때 가능한 모든 부지를 출력한 리스트)
    area_list = available_field(mountain, N, K)
    # 시작 지점은 공사 전을 기준으로 설정해야 한다(문제 상황)
    entrance = start_point(mountain, N)
    height_nomi = []

    # 모든 후보 부지에서 가능한 등산로 길이 리스트가 반환됩니다.
    for nomi in area_list:
        height_nomi.append(longest_length(nomi, N, entrance))

    result = max(height_nomi)

    print(f'#{test_case} {result}')
