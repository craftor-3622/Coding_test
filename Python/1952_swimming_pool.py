# fee_list 세부 내용
# 0 -> day, 1 -> month, 2 -> quarter, 3 -> year

# 월간 이용료까지 고려한 상황에서 3개월 이용료도 고려해본다.
# 2번 이상도 적용될 수 있다!
def consider_quarter(cost_list: list, quarter: int) -> list:
    new_cost_list = cost_list
    temp2 = cost_list.copy()
    
    for n in range(4):
        for i in range(12):
            temp1 = temp2.copy()
            temp1[i] = quarter
            for j in range(i + 1, min(i+3, 12)):
                temp1[j] = 0
                print(temp1)
            if sum(temp1) < sum(new_cost_list):
                new_cost_list = temp1
        temp2 = new_cost_list.copy()
        

    print(new_cost_list)

    return new_cost_list

# 가격표와 이용 계획을 토대로 최소 가격을 반환합니다.
def minimum_fee(schedule: list, fee_list: list) -> int:
    day = fee_list[0]
    month = fee_list[1]
    quarter = fee_list[2]
    year = fee_list[3]

    total_cost_list = []
    
    # 일간 및 월간 이용료만 고려한 최소 금액을 계산합니다.
    for idx in range(len(schedule)):
        total_cost_list.append(schedule[idx] * day)

        if total_cost_list[idx] > month:
            total_cost_list[idx] = month

    # 3개월 이용료를 고려합니다.
    total_cost_list = consider_quarter(total_cost_list, quarter)

    # 마지막으로, 연간 이용료를 고려합니다.
    total = min(sum(total_cost_list), year)

    return total

# T = int(input())
T = 1
for test_case in range(1, T + 1):

    fee_list = list(map(int, input().split()))
    schedule = list(map(int, input().split()))

    total_cost = minimum_fee(schedule, fee_list)

    print(f'#{test_case} {total_cost}')