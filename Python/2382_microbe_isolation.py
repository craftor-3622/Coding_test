# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE&problemTitle=%EB%AF%B8%EC%83%9D%EB%AC%BC+%EA%B2%A9%EB%A6%AC&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 소요시간 : 1시간 40분분

# 군집이 약품 구역에 도달 했을 때 발동합니다.
def change_direction(microbe_hive: list) -> None:
    # 미생물 숫자 절반으로 감소
    microbe_hive[2] = microbe_hive[2] // 2
    # 방향 전환 : 상하(1, 2), 좌우(3, 4)
    if microbe_hive[3] % 2 == 1:    # 1, 3
        microbe_hive[3] += 1
    else:                           # 2, 4
        microbe_hive[3] -= 1

def complexing_hive(existed: list, new: list) -> None:
    amount = []
    direction = []

    if type(existed[2]) is int:
        amount.append(existed[2])
        direction.append(existed[3])
    else:
        for num in existed[2]:
            amount.append(num)
        for d in existed[3]:
            direction.append(d)
    amount.append(new[2])
    direction.append(new[3])
        
    existed[2] = amount
    existed[3] = direction
    
# 군집이 둘 이상 뭉쳤을 때 발동합니다.
def merge_hive(complex_hive: list) -> None:
    amount = sum(complex_hive[2])
    maximum = max(complex_hive[2])
    idx = complex_hive[2].index(maximum)

    complex_hive[2] = amount
    complex_hive[3] = complex_hive[3][idx]

# 1시간 마다 군집의 움직임을 적용합니다. 미생물 수가 0인 경우 소멸합니다.
def delta_time(hive_list: list, length: int) -> list:
    new_hive_list = []
    for unit in hive_list:
        if unit[3] == 1:
            unit[0] -= 1
        elif unit[3] == 2:
            unit[0] += 1
        elif unit[3] == 3:
            unit[1] -= 1
        else:         # 4
            unit[1] += 1

        if unit[0] in (0, length - 1) or unit[1] in (0, length - 1):
            change_direction(unit)
        
        if unit[2] <= 0:
            continue

        for moved_unit in new_hive_list:
            if moved_unit[0] == unit[0] and moved_unit[1] == unit[1]:
                complexing_hive(moved_unit, unit)
                break
        else:
            new_hive_list.append(unit)

    for unit in new_hive_list:
        if type(unit[2]) is list:
            merge_hive(unit)

    return new_hive_list

# 필드에 남아있는 미생물의 수를 계산합니다.
def amount_microbe(hive_list: list) -> int:
    sum = 0
    for unit in hive_list:
        sum += unit[2]

    return sum

T = int(input())

for test_case in range(1, T + 1):

    N, M, K = map(int, input().split())
    hive_list = []

    for unit in range(K):
        unit_info = list(map(int, input().split()))
        hive_list.append(unit_info)

    for time_step in range(M):
        hive_list = delta_time(hive_list, N)

    print(f'#{test_case} {amount_microbe(hive_list)}')
