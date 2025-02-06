T = int(input())

for test_case in range(1, T + 1):
    
    K, N, M = map(int, input().split())

    Stop_number = list(map(int, input().split()))

    can_stop = 1
    arrive = 0
    point = 0

    while point != N:
        for move in range(K, 0, -1):
            if (point + move) in Stop_number or (point + move) == N:
                point += move
                arrive += 1
                break
        else:
            can_stop = 0
            break
    
    if can_stop == 0:
        print(f'#{test_case} 0')
    # 도착 지점은 충전 횟수에 포함되지 않습니다.
    else:
        print(f'#{test_case} {arrive - 1}')
