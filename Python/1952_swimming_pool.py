# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE&problemTitle=%EC%88%98%EC%98%81%EC%9E%A5&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# fee_list 세부 내용
# 0 -> day, 1 -> month, 2 -> quarter, 3 -> year

# 월간 이용료까지 고려한 상황에서 3개월 이용료도 고려합니다.
# 재귀 함수로 dfs 구현하고, 최소합을 갖는 리스트 출력
def consider_quarter(old: list, quarter: int, banned: list) -> int:
    new = old
    point = False
    temp = []
    recursive = list(range(12))
    minimum = sum(old)

    for idx in range(len(banned)):
        if banned[idx] == 1:
            recursive.remove(idx)

    for i in recursive:
        temp = old.copy()
        temp[i] = quarter
        for j in range(i + 1, min(i+3, 12)):
            temp[j] = 0
        print(temp)

        if sum(temp) < minimum:
            point = i
            for idx in range(max(0, point - 2), min(point + 3, 12)):
                banned[idx] = 1
            print(banned)
            minimum = sum(temp)
            temp = consider_quarter(temp, quarter, banned)

    print(new)
    return new

# 가격표와 이용 계획을 토대로 최소 가격을 반환합니다.
def minimum_fee(schedule: list, fee_list: list) -> int:
    day = fee_list[0]
    month = fee_list[1]
    quarter = fee_list[2]
    year = fee_list[3]

    quarter_charged = [0] * 12
    total_cost_list = []
    
    # 일간 및 월간 이용료만 고려한 최소 금액을 계산합니다.
    for idx in range(len(schedule)):
        total_cost_list.append(schedule[idx] * day)

        if total_cost_list[idx] > month:
            total_cost_list[idx] = month

    # 3개월 이용료를 고려합니다.
    total_cost_list = consider_quarter(total_cost_list, quarter, quarter_charged)

    # 마지막으로, 연간 이용료를 고려합니다.
    total = min(sum(total_cost_list), year)

    return total

T = int(input())

for test_case in range(1, T + 1):

    fee_list = list(map(int, input().split()))
    schedule = list(map(int, input().split()))

    total_cost = minimum_fee(schedule, fee_list)

    print(f'#{test_case} {total_cost}')