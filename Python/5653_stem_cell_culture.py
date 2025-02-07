# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE&problemTitle=%EC%A4%84%EA%B8%B0&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1

# import sys
# from pprint import pprint

# sys.stdin = open("input.txt", "r")

# delta 변수명은 자기 스타일대로 구성할 수 있습니다.(del, dxy, delta 등등)
dxy = [[0, 1], [1, 0], [0, -1], [-1, 0]]


# 디버그용 cell_map 출력
# i, j의 범위를 조정할 수 있습니다.
def print_cell_map(cell_info, time: int = 0):
    for i in range(150 - (time // 2), 150 + N + (time // 2)):
        for j in range(150 - (time // 2), 150 + M + (time // 2)):
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
            if cell_map[i][j] == 0:
                continue
            elif cell_map[i][j][0] != 0:
                cell_map[i][j][0] -= 1
            elif cell_map[i][j][1] != 0:

                cell_map[i][j][1] -= 1
            if cell_map[i][j] == [0, 0]:
                cell_map[i][j] = 'X'


# 세포 활성화 시 분열하여 주변 빈 공간으로 확산합니다.
def split_cell(cell_map, pos_y: int, pos_x: int):
    for dx, dy in dxy:
        ni, nj = pos_y + dy, pos_x + dx
        if cell_map[ni][nj] == 0:
            cell_map[ni][nj] =[cell_map[pos_y][pos_x]] * 2
        elif (cell_map[ni][nj] not in (0, 'X') and
              cell_map[ni][nj][0] == cell_map[ni][nj][1]):
            merge_cell(cell_map[ni][nj], cell_map[pos_y][pos_x])

            pass

    pass


# 막 생성된 세포 2개 중 가장 생명력 융합합니다.
def merge_cell(cell_1, cell_2):
    pass


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
                    = [row_input[x]] * 2

    print_cell_map(field)

    for t in range(K):
        spend_time(field, N, M, t)
        print_cell_map(field, t)
