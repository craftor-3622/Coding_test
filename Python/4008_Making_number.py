# 소요시간 : 1시간 30분
# DFS를 통한 연산자 경우의 수 완전 탐색인데, 중복을 허용하는 순열에서 힘든 부분이 발생.

import sys

sys.stdin = open("input.txt", "r")


# 입력받은 숫자 및 연산자를 바탕으로 결과를 반환합니다.
def calculation(num_list: list, op_list: list):
    result = num_list[0]

    for i in range(N - 1):
        if op_list[i] == 0:
            result = result + num_list[i + 1]
        elif op_list[i] == 1:
            result = result - num_list[i + 1]

        elif op_list[i] == 2:
            result = result * num_list[i + 1]

        elif op_list[i] == 3:
            result = int(result / num_list[i + 1])

    return result


# 가능한 연산자 순서를 모두 계산합니다.
def operator_case(old: list, op_count: list, cur_i: int):
    current = old.copy()
    if cur_i == len(current):
        operators_list.append(current)
    else:
        for n in range(4):
            if op_count[n] != 0:
                current[cur_i] = n
                op_count[n] -= 1
                operator_case(current, op_count, cur_i + 1)
                op_count[n] += 1


T = int(input())

for test_case in range(1, T + 1):
    N = int(input())
    operator_count = list(map(int, input().split()))
    integer_list = list(map(int, input().split()))

    op_pos = [None] * (N - 1)
    operators_list = []

    # 가능한 모든 연산자 경우의 수를 operator_list 에 저장합니다.
    operator_case(op_pos, operator_count, 0)

    # 초기값 설정
    min_result = max_result = calculation(integer_list, operators_list[0])

    # 모든 케이스를 검사해 최대 최소 결과를 계산합니다.
    for case in operators_list:
        temp = calculation(integer_list, case)
        max_result = max(temp, max_result)
        min_result = min(temp, min_result)

    answer = max_result - min_result

    print(f'#{test_case} {answer}')
