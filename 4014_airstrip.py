# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE&problemTitle=%ED%99%9C%EC%A3%BC%EB%A1%9C&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1

# 활주로가 건설할 지형의 최대 높이를 출력합니다.
def cliff_height(line: list) -> int:
    height = 0
    for idx in range(len(line) - 1):
        temp = abs(line[idx] - line[idx + 1])

        if (height < temp):
            height = temp

    return height

# 절벽의 위치 정보를 알려줍니다. + 값인 경우 오르막, - 값인 경우 내리막을 나타냅니다.
def cliff_position(line: list) -> list:
    cliff_pos = []
    for idx in range(len(line) - 1):
        difference = line[idx + 1] - line[idx]
        cliff_pos.append(difference)
    
    return cliff_pos

# 설치할 경사로가 충분히 긴 지 검사합니다.
def isLongEnough(cliff_line: list, ramp_length: int) -> bool:
    ## 오르막 경사를 검사합니다.
    for i in range((ramp_length - 1), len(cliff_line)):
        for j in range(i - (ramp_length - 1), i):
            if (cliff_line[i] > 0 and cliff_line[j] != 0):
                return False
    # 내리막 경사를 검사합니다.
    for i in range(0, len(cliff_line) - (ramp_length - 1)):
        for j in range(i + 1, i + ramp_length):
            if (cliff_line[i] < 0 and cliff_line[j] != 0):
                return False

    return True

# 설치할 경사로가 지형 내에 있는지 검사합니다.
def is_inline(cliff_line: list, ramp_length: int):
    for idx in range(len(cliff_line)):
        # 경사로가 너무 왼쪽에 있으면 안됩니다.
        if (cliff_line[idx] >= 1
            and idx < ramp_length - 1):
            return False
        # 경사로가 너무 오른쪽에 있어서도 안됩니다.
        elif (cliff_line[idx] <= -1
              and idx >= len(cliff_line) - (ramp_length - 1)):
            return False

    # 이상 없습니다.
    else:
        return True

# 활주로가 중복으로 건설되었는지를 체크합니다.
def build_stack(cliff_line: list, ramp_length: int):
    N = len(cliff_line) + 1

    build_area = [0 for i in range(N)]

    # 중복과 상관없이 경사로가 설치되는 area에 +1을 합니다.
    for i in range(len(cliff_line)):
        if cliff_line[i] > 0 and i - ramp_length >= 0:
            for j in range(i - ramp_length + 1, i + 1):
                build_area[j] = build_area[j] + 1

        if cliff_line[i] < 0 and i + 1 + ramp_length <= N:
            for j in range(i + 1, i + 1 + ramp_length):
                build_area[j] = build_area[j] + 1

    # 중복으로 건설된 경우(2 이상), False를 출력합니다.
    for stack in build_area:
        if stack >= 2:
            return False
    else:
        return True
    

# 활주로가 건설 가능한지 여부를 체크합니다.
def isBuilt(line: list, ramp_length: int) -> bool:
    # 해당 변수는 지형 간 높이 차를 계산해 리스트로 나타낸 값입니다.
    cliff_line = cliff_position(line)

    # height is too much // 절벽 높이가 너무 높습니다.
    if cliff_height(line) > 1:
        return False
    # Out of Bound // 경사로가 영역 밖을 벗어났습니다.
    elif not is_inline(cliff_line, ramp_length):
        return False
    # ramp Shortage // 경사로가 너무 짧습니다.
    elif not isLongEnough(cliff_line, ramp_length):
        return False
    # ramp OverStack // 경사로가 중복되었습니다.
    elif not build_stack(cliff_line, ramp_length):
        return False
    # No error // 이상 없습니다.
    else:
        return True

# 영역내의 라인들을 모두 검사하여 가능한 경우의 수를 출력합니다.
def count_airstrip(line_list: list, ramp_length: int) -> int:
    count = 0
    
    for line in line_list:
        if isBuilt(line, ramp_length):
            count += 1

    return count

# 테스트 케이스 수를 입력받습니다.
T = int(input())

for test_case in range(1, T + 1):

    # 지형의 2차원 리스트입니다.
    area = []
    # 활주로를 만들 1차원 지형의 리스트입니다.
    airstrip_line = []

    # 지형의 크기와 경사로의 길이를 입력받습니다.
    N, X = tuple(map(int, input().split()))

    # 가로 줄과 세로줄을 입력받아, 활주로가 될 수 있는 라인을 리스트로 정리합니다.
    for i in range(N):
        row = tuple(map(int, input().split()))
        airstrip_line.append(row)
        area.append(row)

    # zip 사용 시, *를 사용해 unpacking 해주어야 한다.
    for column in zip(*area):
        airstrip_line.append(column)
        
    print(f'#{test_case} {count_airstrip(airstrip_line, X)}')