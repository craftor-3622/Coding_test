T = int(input())

for test_case in range(1, T + 1):
    width = int(input())
    box_list = list(map(int, input().split()))
    maximum_distance = 0

    for i in range(width):
        count = 0
        for j in range(i + 1, width):
            if box_list[j] >= box_list[i]:
                count += 1

        distance = (width - 1) - i - count 
        if maximum_distance < distance:
            maximum_distance = distance

    print(f'#{test_case} {maximum_distance}')