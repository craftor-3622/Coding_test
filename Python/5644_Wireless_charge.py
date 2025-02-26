import sys
from itertools import product

# 이동 리스트
move = [[0, 0], [0, -1], [1, 0], [0, 1], [-1, 0]]

sys.stdin = open("input.txt", "r")

T = int(input())


def available_bc(player_cur: list, player_list: list, bc_list: list):
    global A
    x_p, y_p = player_cur

    for i in range(1, A+1):
        x_bc, y_bc, distance, amt = bc_list[i]
        if abs(x_p - x_bc) + abs(y_p - y_bc) <= distance:
            player_list.append(i)

    return player_list


# 플레이어의 움직임을 나타내는 함수입니다.
def move_player(player_pos: list, move_val: int):
    x, y = player_pos
    dx, dy = move[move_val]
    player_pos[0] = x + dx
    player_pos[1] = y + dy


# 현재 A, B의 위치로부터 충전 가능한 BC의 리스트를 받아 두 사용자의 초당 최대 충전량 합을 반환합니다.
def max_charge(a_bc: list, b_bc: list, bc_list: list) -> int:
    available_list = product(a_bc, b_bc)
    charge_amt = 0

    for bc_point in available_list:
        # A와 B의 충전 BC가 같은 경우
        if bc_point[0] == bc_point[1]:
            temp = bc_list[bc_point[0]][3]
        else:
            temp = bc_list[bc_point[0]][3] + bc_list[bc_point[1]][3]
        charge_amt = max(charge_amt, temp)

    return charge_amt


for test_case in range(1, T + 1):
    N = 10
    M, A = map(int, input().split())
    player_A, player_B = [1, 1], [10, 10]
    answer = 0

    user_a_move = list(map(int, input().split()))
    user_b_move = list(map(int, input().split()))
    battery_chargers = [None] * (A + 1)
    battery_chargers[0] = [0, 0, 0, 0]

    for i in range(1, A + 1):
        # x, y, 충전 범위, 처리량
        BC_info = list(map(int, input().split()))
        battery_chargers[i] = BC_info

    for t in range(M):
        bc_list_a = available_bc(player_A, [0], battery_chargers)
        bc_list_b = available_bc(player_B, [0], battery_chargers)
        answer += max_charge(bc_list_a, bc_list_b, battery_chargers)

        move_player(player_A, user_a_move[t])
        move_player(player_B, user_b_move[t])

    bc_list_a = available_bc(player_A, [0], battery_chargers)
    bc_list_b = available_bc(player_B, [0], battery_chargers)
    answer += max_charge(bc_list_a, bc_list_b, battery_chargers)

    print(f'#{test_case} {answer}')
