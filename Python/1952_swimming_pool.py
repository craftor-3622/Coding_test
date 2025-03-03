# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE&problemTitle=%EC%88%98%EC%98%81%EC%9E%A5&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 최종 3트, 총 소요시간 8시간
# DFS + Backtracking을 활용하여 구현
# 실제 최적 방법은 누적합을 이용한 DP 문제

def minimum_fee(mid_cal: list, ban: list, thr_month: int, start: int):
    if sum(ban) == M:
        return
 
    else:
        temp = list(mid_cal.copy())
        temp2 = list(ban.copy())
 
        left = max(0, start - 2)
        right = min(M, start + 3)
 
        # 가능한 경우
        if sum(mid_cal[start:right]) == 0:
            ban[start] = 1
        elif temp2[start] == 0:
            temp[start] = thr_month
            for j in range(start + 1, right):
                temp[j] = 0
 
            for j in range(left, right):
                temp2[j] = 1
            fee_cases.append(temp)
            for i in range(M):
                minimum_fee(temp, temp2, thr_month, i)
 
 
T = int(input())
M = 12      # 1년은 12달
 
for tc in range(1, T + 1):
 
    day, month, quarter, year = map(int, input().split())
    swimming_plan = list(map(int, input().split()))
    fee_cost = [day * swimming_plan[i] for i in range(M)]
    used_quarter = [0] * M
    fee_cases = list()
 
    for idx in range(M):
        fee_cost[idx] = min(fee_cost[idx], month)
    result = sum(fee_cost)
 
    for i in range(M):
        minimum_fee(fee_cost, used_quarter, quarter, i)
 
    for case in fee_cases:
        result = min(sum(case), result)
    result = min(result, year)
 
    print(f'#{tc} {result}')
    