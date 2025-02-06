# import sys
from pprint import pprint

# sys.stdin = open("input.txt", "r")

# 1시간마다 cell map을 업데이트합니다.
def time_step(map_data: list[list], length: int, width: int) -> None:
    for i in range(length):
        for j in range(width):
            if map_data[i][j] in (0, 'X'):
                continue
            elif map_data[i][j][0] > 0:
                map_data[i][j][0] -= 1
            elif map_data[i][j][1] > 0:
                split_cell(map_data, i, j)
                map_data[i][j][1] -= 1
            if map_data[i][j][1] == 0:
                map_data[i][j] = 'X'

def split_cell(map_data: list[list], i: int, j: int) -> None:
    for di, dj in ([1, 0], [-1, 0], [0, 1], [0, -1]):
        if map_data[i + di][j + dj] == 0:
            map_data[i + di][j + di] = [map_data[i][j][1], map_data[i][j][1]]
        elif (type(map_data[i + di][j + dj]) is list and
            map_data[i + di][j + dj][0] == map_data[i + di][j + dj][1]):
            map_data[i + di][j + di] = merge_cell(
                map_data[i + di][j + di], map_data[i][j])
                    

def merge_cell(cell_1: list, cell_2: list) -> list:
    if cell_1[1] > cell_2[1]:
        return cell_1
    else:
        return cell_2

T = 1

for test_case in range(1, T + 1):
    
    N, M, K = map(int, input().split())

    cell_map = []
    for i in range(300 + N):
        cell_map.append([0] * (300 + M))

    for i in range(N):
        row_cell_list = list(map(int, input().split()))
        for j in range(M):
            if row_cell_list[j] != 0:
                cell_map[150 + i][150 + j] = [row_cell_list[j], row_cell_list[j]]

    # 디버그용 cell map 출력
    for i in range(145, 155 + N):
        for j in range(145, 155 + M):
            if cell_map[i][j] == 0:
                print(' .', end='')
            elif cell_map[i][j] == 'X':
                print(' X', end='')
            else:
                print(f' {cell_map[i][j][1]}', end='')
        print()
    print()

    for t in range(K):
        time_step(cell_map, 300 + N, 300 + M)
    
    # 디버그용 cell map 출력
    for i in range(145, 155 + N):
        for j in range(145, 155 + M):
            if cell_map[i][j] == 0:
                print(' .', end='')
            elif cell_map[i][j] == 'X':
                print(' X', end='')
            else:
                print(f' {cell_map[i][j][1]}', end='')
        print()
    print()

