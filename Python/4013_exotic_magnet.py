# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeV9sKkcoDFAVH&categoryId=AWIeV9sKkcoDFAVH&categoryType=CODE&problemTitle=&orderBy=INQUERY_COUNT&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=4
# 추후 class 항목을 배울 때, class를 이용해 다시 쓰는 것을 추천합니다.

# 10
# 2
# 0 0 1 0 0 1 0 0
# 1 0 0 1 1 1 0 1
# 0 0 1 0 1 1 0 0
# 0 0 1 0 1 1 0 1
# 1 1
# 3 -1

import sys

# 자석 기어가 시계방향으로 회전합니다.
def turn_gear(old_gear: list, dir: int) -> list:

    if dir == 1:
        new_gear = old_gear[-1:]
        new_gear.extend(old_gear[:-1])

    elif dir == -1:
        new_gear = old_gear[1:]
        new_gear.append(old_gear[0])

    return new_gear

# 인접한 자석 간 인력이 작용하는 지 나타냅니다.
def magnet_interaction(left_gear: list, right_gear: list) -> bool:
    if left_gear[2] != right_gear[-2]:
        return True
    else:
        return False

def Force_rotation(pos: int, dir: int, link: list) -> list:
    temp = [0, 0, 0, 0]
    temp[pos - 1] = dir

    # 왼쪽 link 확인
    for left in range(pos - 1, 0, -1):
        if True:
            pass

    # 오른쪽 link 확인
    for right in range(pos - 1, 3):

        pass

    return temp


def get_score(gear_plate: list) -> int:
    sum = 0
    for idx in range(4):
        sum += gear_plate[idx][0] * (2**idx)

    return sum


# T = int(input())

# for test_case in range(T):
#     pass

K = int(input())

magnet_plate = []

for i in range(4):
    gear = list(map(int, sys.stdin.readline().split()))
    magnet_plate.append(gear)

print(get_score(magnet_plate))

for count in range(K):
    magnet_num, direction = map(int, sys.stdin.readline().split())
    gear_linked = []

    for idx in range(3):
        gear_linked.append(magnet_interaction(
            magnet_plate[idx], magnet_plate[idx + 1]))
    
    spin = Force_rotation(magnet_num, direction, gear_linked)

    for num in range(4):
        pass
        


    


# print(get_score(magnet_plate))

for idx in range(4):
    print(magnet_plate[idx])