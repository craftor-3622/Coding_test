# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE&problemTitle=%EC%A4%84%EA%B8%B0&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 소요시간 : 8시간, 33/50, 세포 interaction에서 버그가 자주 난다...

import sys
# from pprint import pprint

sys.stdin = open("sample_input.txt", "r")

# 빈 공간인 경우 0, cell이 죽은 경우 X, 살아 있는 경우 [sleep, active, born]로 표시
# born은 지금 막 태어난 상태를 말합니다. 생성 시 1이며, 1시간 싸이클이 끝난 경우 0으로 설정

# delta 변수명은 자기 스타일대로 구성할 수 있습니다.(del, dxy, delta 등등)
dxy = [[0, 1], [1, 0], [0, -1], [-1, 0]]


# 디버그용 cell_map 출력
# i, j의 범위를 조정할 수 있습니다.
def print_cell_map(cell_info, time: int = 0):
    for i in range(150 - (time // 2) - (time % 2),
                   150 + N + (time // 2) + (time % 2)):
        for j in range(150 - (time // 2) - (time % 2),
                       150 + M + (time // 2)  + (time % 2)):
            if cell_info[i][j] == 0:
                print(' .', end='')
            elif cell_info[i][j] == 'X':
                print(' X', end='')
            else:
                print(f' {cell_info[i][j][1]}', end='')
        print()
    print()


# 1시간마다 cell_map 을 업데이트합니다.
def spend_time(cell_map, init_l: int, init_w: int, time: int):
    for i in range(150 - (time // 2), 150 + init_l + (time // 2)):
        for j in range(150 - (time // 2), 150 + init_w + (time // 2)):
            if cell_map[i][j] in (0, 'X'):
                continue
            elif cell_map[i][j][2] == 0:
                if cell_map[i][j][0] == 0 and cell_map[i][j][1] != 0:
                    split_cell(cell_map, i, j)
                    cell_map[i][j][1] -= 1
                elif cell_map[i][j][0] != 0:
                    cell_map[i][j][0] -= 1
                

    for i in range(150 - (time // 2) - (time % 2),
                   150 + init_l + (time // 2) + (time % 2)):
        for j in range(150 - (time // 2) - (time % 2),
                       150 + init_w + (time // 2) + (time % 2)):
            if cell_map[i][j] not in (0, 'X'):
                cell_map[i][j][2] = 0
            if cell_map[i][j] == [0, 0, 0]:
                cell_map[i][j] = 'X'
            
            
# 세포 활성화 시 분열하여 주변 빈 공간으로 확산합니다.
def split_cell(cell_map, pos_y: int, pos_x: int):
    for dy, dx in dxy:
        ni, nj = pos_y + dy, pos_x + dx
        lifetime = cell_map[pos_y][pos_x][1]
        new_cell = [lifetime, lifetime, 1]

        if cell_map[ni][nj] == 0:
            cell_map[ni][nj] = new_cell
            cell_map[ni][nj][2] = 1
        elif (cell_map[ni][nj] not in (0, 'X') and
              cell_map[ni][nj][0] == cell_map[ni][nj][1] and
              cell_map[ni][nj][1] != 0 and
              cell_map[ni][nj][2] == 1):
            cell_map[ni][nj] = merge_cell(cell_map[ni][nj], new_cell)


# 막 생성된 세포 2개 중 가장 높은 생명력을 가진 세포로 출력합니다.
def merge_cell(cell_1: list, cell_2: list):
    if cell_1[1] > cell_2[2]:
        return cell_1
    else:
        return cell_2


# K 시간이 지난 뒤 살아있는 cell의 개수를 계산합니다.
def calculate_cell(cell_map, init_l: int, init_w: int, time: int) -> int:
    amount_cell = 0
    for i in range(150 - (time // 2), 150 + init_l + (time // 2)):
        for j in range(150 - (time // 2), 150 + init_w + (time // 2)):
            if type(cell_map[i][j]) is list:
                amount_cell += 1

    return amount_cell



T = int(input())

for test_case in range(1, T + 1):
    N, M, K = map(int, input().split())

    field = [[0] * (300 + M) for _ in range(300 + N)]

    # cell_map 을 입력받습니다.
    for y in range(N):
        row_input = list(map(int, input().split()))
        for x in range(M):
            if row_input[x] != 0:
                field[150 + y][150 + x] \
                    = [row_input[x]] * 2 + [0]

    # K 시간 후 field 상태를 출력합니다.
    for t in range(K):
        spend_time(field, N, M, t)

    print_cell_map(field, t)

    cell_num = calculate_cell(field, N, M, K)

    print(f'#{test_case} {cell_num}')
    
