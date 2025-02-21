# 소요 시간 : 8시간... (2주에 걸쳐 풀이 끗)
# BFS(벽돌 파괴) + DFS(완전 탐색) + 스택(벽돌 정리) (backtracking은 선택사항)
import sys
from collections import deque

sys.stdin = open("input.txt", "r")
destroyer = deque()
delta = [[0, 1], [1, 0], [0, -1], [-1, 0]]


# 지정된 횟수만큼 공을 던져 최소가 나오는 값을 완전 탐색으로 출력합니다.
def drop_ball(cur_map: list, cur: int, length: int, width: int):
    global answer

    if cur == 0:
        result = get_score(cur_map, length, width)
        answer = min(result, answer)
    elif answer != 0:
        for j in range(width):
            temp = [cur_map[i].copy() for i in range(length)]
            destroy_blocks(temp, j, length, width)
            gravity(temp, length, width)
            drop_ball(temp, cur-1, length, width)


# 공에 의한 폭발 및 연쇄 폭발을 처리하는 함수입니다.
def destroy_blocks(map_info: list, sj: int, length: int, width: int):
    si = 0
    for i in range(length):
        if map_info[i][sj] != 0:
            si = i
            break

    init_blast = map_info[si][sj]
    destroyer.append([si, sj, init_blast])
    map_info[si][sj] = 0

    while len(destroyer) != 0:
        i, j, blast = destroyer.popleft()
        for di, dj in delta:
            for c in range(blast):
                ni, nj = i + c * di, j + c * dj
                if 0 <= ni < length and 0 <= nj < width:
                    if map_info[ni][nj] != 0:
                        post_blast = map_info[ni][nj]
                        map_info[ni][nj] = 0
                        destroyer.append([ni, nj, post_blast])


# 블럭이 깨진 후 중력이 작용하는 상황을 처리하는 함수입니다.
def gravity(map_info: list, length: int, width: int):
    blocks = list()
    for j in range(width):
        for i in range(length):
            if map_info[i][j] != 0:
                blocks.append(map_info[i][j])
                map_info[i][j] = 0

        k = length - 1
        while len(blocks) != 0:
            map_info[k][j] = blocks.pop()
            k -= 1


# 시행이 모두 종료된 이후 남은 블럭의 개수를 반환합니다.
def get_score(map_info: list, length: int, width: int):
    cnt = 0

    for i in range(length):
        for j in range(width):
            if map_info[i][j] != 0:
                cnt += 1

    return cnt


T = int(input())

for test_case in range(1, T+1):
    N, W, H = map(int, input().split())
    game_board = [list(map(int, input().split())) for _ in range(H)]
    answer = W * H

    drop_ball(game_board, N, H, W)

    print(f'#{test_case} {answer}')
