# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE&problemTitle=%EC%9B%90%EC%9E%90&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 소요시간 1시간 10분
# Queue 로 풀긴 풀었는데... 이거 맞아요? (실행시간 7초, 허용 최대 시간 15초)

import sys
from collections import deque

atoms_list = deque()
boundary = 1000

sys.stdin = open("input.txt", "r")


def collide_atoms(limit: int) -> int:
    total = 0

    while len(atoms_list) != 0:
        current_dict = dict()

        for _ in range(len(atoms_list)):
            particle = atoms_list.pop()
            if particle[2] == 0:
                particle[1] += 0.5
            elif particle[2] == 1:
                particle[1] -= 0.5
            elif particle[2] == 2:
                particle[0] -= 0.5
            elif particle[2] == 3:
                particle[0] += 0.5

            pos = (particle[0], particle[1])
            direction = particle[2]
            k = particle[3]

            if not current_dict.get(pos, []):
                current_dict[pos] = [[direction, k]]
            else:
                current_dict[pos].append([direction, k])

        for position in current_dict:
            if len(current_dict[position]) > 1:
                for i in range(len(current_dict[position])):
                    total += current_dict[position][i][1]
            else:
                now_x, now_y = position
                if -limit <= now_x <= limit and -limit <= now_y <= limit:
                    direction, e = current_dict[position][0]
                    temp = [now_x, now_y, direction, e]
                    atoms_list.append(temp)

        current_dict.clear()

    return total


T = int(input())

for test_case in range(1, T + 1):
    N = int(input())

    # 원자 정보 입력 : x, y, dir, K
    for _ in range(N):
        atom = list(map(int, input().split()))
        if atom[0] == boundary and atom[2] == 3:
            continue
        if atom[0] == -boundary and atom[2] == 2:
            continue
        if atom[1] == boundary and atom[2] == 0:
            continue
        if atom[1] == -boundary and atom[2] == 1:
            continue
        else:
            atoms_list.append(atom)

    answer = collide_atoms(boundary)

    print(f'#{test_case} {answer}')

    pass
