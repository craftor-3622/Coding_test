# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeV9sKkcoDFAVH&categoryId=AWIeV9sKkcoDFAVH&categoryType=CODE&problemTitle=&orderBy=INQUERY_COUNT&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=4
# 추후 class 항목을 배울 때, class를 이용해 다시 쓰는 것을 추천합니다.
# 소요 시간 : 8시간

# 자석 기어가 회전합니다.
def turn_gear(old_gear: list, dir: int) -> list:

    if dir > 0:
        new_gear = old_gear[-1:]
        new_gear.extend(old_gear[:-1])
    elif dir < -0:
        new_gear = old_gear[1:]
        new_gear.append(old_gear[0])
    else:
        new_gear = old_gear

    return new_gear

# 인접한 자석 간 인력이 작용하는 지 나타냅니다.
def magnet_interaction(left_gear: list, right_gear: list) -> bool:
    if left_gear[2] != right_gear[-2]:
        return True
    else:
        return False

# 기어 작용 시 판에 놓인 4개의 기어가 어떻게 회전하는지 리스트로 나타냅니다.
def Force_rotation(pos_num: int, dir: int, link: list) -> list:
    spin = [0, 0, 0, 0]
    Forced_gear_index = pos_num - 1

    # 왼쪽 link 확인
    left = Forced_gear_index
    while left > 0 and link[left - 1]:
        left -= 1

    # 오른쪽 link 확인
    right = Forced_gear_index
    while right < 3 and link[right]:
        right += 1

    for idx in range(left, right + 1):
        if (Forced_gear_index - idx) % 2 == 0:
            spin[idx] = dir
        else:
            spin[idx] = -dir

    return spin

# 점수를 반환합니다.
def get_score(gear_plate: list) -> int:
    sum = 0
    for idx in range(4):
        sum += gear_plate[idx][0] * (2**idx)

    return sum


T = int(input())

for test_case in range(T):

    K = int(input())

    magnet_plate = []
    new_magnet_plate = []

    for i in range(4):
        gear = list(map(int, input().split()))
        magnet_plate.append(gear)

    for count in range(K):
        magnet_num, direction = map(int, input().split())
        gear_linked = []
        spin = []

        for idx in range(3):
            gear_linked.append(magnet_interaction(
                magnet_plate[idx], magnet_plate[idx + 1]))

        spin = Force_rotation(magnet_num, direction, gear_linked)

        for idx in range(4):
            magnet_plate[idx] = turn_gear(magnet_plate[idx], spin[idx])

    print(f'#{test_case} {get_score(magnet_plate)}')

'''
후기
회전을 표현할 수 있는 다양한 방법을 생각해보자.
처음에는 기어간의 상호작용을 재귀 함수로 표현해보려고 했으나,
중간에 구현 에러나기가 너무 쉬웠음. 유지 보수도 별로인 부분이 발생.
그래서 조작 시 움직이는 기어 전체의 왼쪽·오른쪽 포인터으로 구현 시도했더니 바로 풀림.

재귀 함수를 왜 쓸까? - 조건에 따라 조건 반복 구현이 쉽다.
단점은? - 시간 복잡도 평균 O(n!), 메모리 과다 사용 -> memoization 활용하여 시간 및 공간 절약
그럼 왜 오래 걸렸을까? - 기어 회전은 1회성인데, 이거를 재귀 함수로 표현하려 했기에 문제가 발생.
따라서 이건 문제 파악도 어려웠으나, 그 해결 과정을 정하는 것도 어렵게 구현하려다 문제 발생.

기준 조건 - 조건 발동 시, 반복적인가?
-> 맞다면 재귀 함수 고려 or 반복문, 아닌 경우 배열, 그래프 등 활용
'''