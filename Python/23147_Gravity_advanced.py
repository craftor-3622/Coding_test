# Gravity 문제 advanced
# 문제에 제시된 상황을 재현하는 것이 해당 코드의 목표입니다.

# 문제에선 N 으로 주어졌으나, 코드 관리 편의성을 위해 width 로 사용합니다.
width = int(input())

box_room = [[0] * width for _ in range(100)]

box_list = list(map(int, input().split()))

for j in range(width):
    for i in range(box_list[j]):
        box_room[i][j] = j + 1

box_room_rotate = list(map(list, zip(*box_room)))

# 출력용 코드입니다. 빈 공간인 경우 '.' 을 출력합니다.

# 회전 이전 상태를 출력합니다.
# 입력 값에 따라 i 범위를 조정할 수 있습니다.
temp = box_room[::-1]
for i in range(90, 100):
    for j in range(width):
        if temp[i][j] == 0:
            print('.', end=' ')
        else:
            print(temp[i][j], end=' ')
    print()

print()

# 회전 이후 상태를 출력합니다.
# 입력 값에 따라 j 범위를 조정할 수 있습니다.
for i in range(width):
    for j in range(10):
        if box_room_rotate[i][j] == 0:
            print('.', end=' ')
        else:
            print(box_room_rotate[i][j], end=' ')
    print()

print()

# 박스 중력 적용
gravity_applied_room = [[0] * 100 for _ in range(width)]

for j in range(100):
    item_count = 0
    for i in range(width - 1, -1, -1):
        if box_room_rotate[i][j] != 0:
            gravity_applied_room[(width - 1) - item_count][j] = box_room_rotate[i][j]
            item_count += 1

# 중력 적용 이후 상태를 출력합니다.
# 입력 값에 따라 j 범위를 조정할 수 있습니다.
for i in range(width):
    for j in range(10):
        if gravity_applied_room[i][j] == 0:
            print('.', end=' ')
        else:
            print(gravity_applied_room[i][j], end=' ')
    print()
