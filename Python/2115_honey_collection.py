# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu&categoryId=AV5V4A46AdIDFAWu&categoryType=CODE&problemTitle=%EB%B2%8C%EA%BF%80&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# DFS로 푸는 것이 정석이지만, 범위가 적어 조합도 가능.
# 소요시간 : 1시간 조금 안됨
import sys

sys.stdin = open("input.txt", "r")


# 추출한 리스트에서 채취 가능한 조합을 선택합니다. (M = 5 기준 최대 32가지)
def maximum_price(row_list: list, length: int, max_amount: int):
    honey_set_amount = 2 ** length
    available_list = []

    # 해당 코드 블록은 조건을 만족하는 벌통 부분 집합을 추가합니다.
    for num in range(honey_set_amount):
        temp = []
        for k in range(length):
            if num & (1 << k):
                temp.append((row_list[k]))
        if sum(temp) <= max_amount:
            available_list.append(temp)

    return available_list


# 일꾼이 수확 가능한 리스트 중 최대 값을 출력합니다.
def maximum_earnings(honey_list: list) -> int:
    price = 0

    for honeys in honey_list:
        temp = 0
        for item in honeys:
            temp += item ** 2
        price = max(price, temp)

    return price


T = int(input())

for test_case in range(1, T + 1):
    N, M, C = map(int, input().split())

    field = [list(map(int, input().split())) for _ in range(N)]
    # 해당 변수는 첫 번째 일꾼과의 영역 침범을 방지하기 위한 변수입니다.
    ban = [[0] * N for _ in range(N)]

    max_i, max_j = 0, 0

    # 첫 번째 일꾼이 채취합니다. 각 영역에서 채취 가능한 벌통 집합을 완전 탐색하여
    # 최대 판매 가격을 구하고, 가장 수익이 잘나는 영역 및 가격을 반환합니다.
    worker1_max = 0
    for i in range(N):
        for j in range(N - M + 1):
            worker1_list = maximum_price(field[i][j:j + M], M, C)
            worker1_earn = maximum_earnings(worker1_list)
            if worker1_max < worker1_earn:
                worker1_max = worker1_earn
                max_i, max_j = i, j

    # 채취가 끝났다면, 해당 영역은 이제 두 번째 일꾼이 채취할 수 없습니다.
    for j in range(max(0, max_j - M + 1), min(N, max_j + M)):
        ban[max_i][j] = 1

    # 두 번째 일꾼이 채취합니다. ban 값이 1인 경우 채취할 수 없습니다.
    worker2_max = 0
    for i in range(N):
        for j in range(N - M + 1):
            if ban[i][j] == 0:
                worker2_list = maximum_price(field[i][j:j + M], M, C)
                worker2_earn = maximum_earnings(worker2_list)
                worker2_max = max(worker2_max, worker2_earn)

    result = worker1_max + worker2_max

    print(f'#{test_case} {result}')
