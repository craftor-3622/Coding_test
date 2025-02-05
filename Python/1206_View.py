# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV134DPqAA8CFAYh&categoryId=AV134DPqAA8CFAYh&categoryType=CODE&problemTitle=View&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1

for test_case in range(1, 11):
    N = int(input())
    building_list = list(map(int, input().split()))
    amount = 0

    for idx in range(2, N - 2):
        maximum_height = 0
        for i in [idx - 2, idx - 1, idx + 1, idx + 2]:
            if building_list[i] > maximum_height:
                maximum_height = building_list[i]
                
        if building_list[idx] > maximum_height:
            amount += building_list[idx] - maximum_height
    
    print(f'#{test_case} {amount}')
