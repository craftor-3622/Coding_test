# https://swexpertacademy.com/main/code/problem/problemDetail.do?problemLevel=1&problemLevel=2&contestProbId=AZD8K_UayDoDFAVs&categoryId=AZD8K_UayDoDFAVs&categoryType=CODE&problemTitle=&orderBy=FIRST_REG_DATETIME&selectCodeLang=PYTHON&select-1=2&pageSize=10&pageIndex=1&problemLevel=1%2C2&&&&&&&&&

T = int(input())

for test_case in range(1, T + 1):
	
    A, B, N = map(int, input().split())
    
    count = 0
    
    while ((A <= N) and (B <= N)):
        if (A > B):
            B += A
        else:
            A += B
        count += 1
    
    print(count)
