# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE&problemTitle=%EC%B0%A8%EB%9F%89&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
# 소요시간 : 4시간 +
# 소감 : Queue 가 사람을 화나게 하는 방법

import sys
from collections import deque


class CustomerInfo:
    def __init__(self, number, t_k):
        self.number = number
        self.eta = t_k
        self.reception_num = 0
        self.receive_time = 0
        self.repair_num = 0
        self.repair_time = 0

    def __lt__(self, other):
        return self.number > other.number

    def __str__(self):
        return f'{self.number}, {self.reception_num}, {self.repair_num}'


def wait_to_receive(before: deque, port_a: list):
    wait_line = len(before)

    for _ in range(wait_line):
        visitor = before.popleft()
        if visitor.eta > 0:
            visitor.eta -= 1
        if visitor.eta == 0:
            for i in range(len(port_a)):
                if port_a[i] is None:
                    index = port_a.index(None)
                    visitor.reception_num = index + 1
                    visitor.receive_time = a_list[index]
                    port_a[index] = visitor
                    break
            else:
                before.append(visitor)
        else:
            before.append(visitor)


def receive_to_mid(port_a: list, after: deque):
    # 동시에 처리가 완료된 고객을 처리하는 리스트입니다.
    temp = deque()

    for i in range(len(port_a)):
        if port_a[i] is not None:
            visitor = port_a[i]
            visitor.receive_time -= 1
            if visitor.receive_time == 0:
                temp.append(visitor)
                port_a[i] = None

    for i in range(len(temp) - 1):
        min_idx, min_num = i, temp[i]
        for j in range(i, len(temp)):
            if temp[j] < min_num:
                min_idx = j
                min_num = temp[j]
        temp[i], temp[min_idx] = temp[min_idx], temp[i]

    for _ in range(len(temp)):
        person = temp.popleft()
        after.append(person)


def mid_to_repair(before: deque, port: list):
    wait_line = len(before)

    for _ in range(wait_line):
        visitor = before.popleft()

        for i in range(len(port)):
            if port[i] is None:
                index = port.index(None)
                visitor.repair_num = index + 1
                visitor.repair_time = b_list[index]
                port[index] = visitor
                break
        else:
            before.append(visitor)


def repair_to_result(port: list, after: list):
    # 동시에 처리가 완료된 고객을 처리하는 리스트입니다.

    for i in range(len(port)):
        if port[i] is not None:
            visitor = port[i]
            visitor.repair_time -= 1
            if visitor.repair_time == 0:
                after.append(visitor)
                port[i] = None


sys.stdin = open("input.txt", "r")

T = int(input())

for test_case in range(1, T + 1):
    N, M, K, A, B = map(int, input().split())

    # 접수 시간 입력 - 접수처 : a_list, 정비소 : b_list
    a_list = list(map(int, input().split()))
    b_list = list(map(int, input().split()))

    # 고객 도착 정보(K개)
    T_visitor_list = list(map(int, input().split()))

    # 대기줄, 접수줄, 정비줄, 결과줄 생성 (queue)
    wait = deque()
    receiving = [None] * N
    mid = deque()
    repairing = [None] * M
    result = list()

    for i in range(K):
        customer = CustomerInfo(i + 1, T_visitor_list[i])
        wait.append(customer)

    time = 0

    while True:
        time += 1
        # 모두 처리한 경우
        if len(result) == K:
            break

        repair_to_result(repairing, result)
        receive_to_mid(receiving, mid)
        mid_to_repair(mid, repairing)
        wait_to_receive(wait, receiving)

        wait, receiving, mid, repairing, result

    answer = 0
    people = 0
    for i in range(K):
        visitor = result[i]
        if visitor.reception_num == A and visitor.repair_num == B:
            answer += visitor.number
            people += 1

    if people == 0:
        answer = -1

    print(answer)
