# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE&problemTitle=%EC%88%98%EC%98%81%EC%9E%A5&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# DP + 누적합

T = int(input())
 
for test_case in range(1, T + 1):
    day, month, quarter, year = map(int, input().split())
    day_list = list(map(int, input().split()))
    sub_total = [0] * 13
 
    sub_total[1] = min(day_list[0] * day, month)
    sub_total[2] = min(sub_total[1] + day_list[1] * day, sub_total[1] + month)
    for n in range(3, 13):
        sub_total[n] = min(sub_total[n - 1] + day_list[n - 1] * day,
                           sub_total[n - 3] + quarter, sub_total[n - 1] + month)
 
    sub_total[12] = min(sub_total[12], year)
 
    print(f"#{test_case} {sub_total[12]}")