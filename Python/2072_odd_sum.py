# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5QSEhaA5sDFAUq&categoryId=AV5QSEhaA5sDFAUq&categoryType=CODE&problemTitle=&orderBy=INQUERY_COUNT&selectCodeLang=PYTHON&select-1=&pageSize=10&pageIndex=1

int_array = input().split()
sum = 0

for i in range (10):
    if ((int(int_array[i-1]) % 2) == 1):
        sum = sum + int(int_array[i-1])

print(sum)