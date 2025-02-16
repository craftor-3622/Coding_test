# 완전 탐색(조합)
import sys

sys.stdin = open("sample_input.txt", "r")


# 가능한 약품 위치 조합으로부터 공정 후 최소 두께를 리스트에 추가하는 함수입니다.
def film_processing(map_info: list[list], length: int, width: int, num: int):
    combination(process_position, length, num)

    for _ in range(len(processed_list)):
        case = processed_list.pop()

        temp = [map_info[i].copy() for i in range(length)]
        for i in range(length):
            if case[i] is not None:
                for j in range(width):
                    temp[i][j] = case[i]
        
        result = min_thickness(temp, length, width)
        thickness_list.append(result)


# 약품을 처리할 row의 번호 조합을 생성하는 함수입니다.
def combination(old: list, length: int, number: int, start: int = 0):
    temp = old.copy()
    if number == 0:
        processed_list.append(temp)
    else:
        for i in range(start, length):
            if temp[i] is None:
                for c in range(2):
                    temp[i] = c
                    combination(temp, length, number - 1, i + 1)
                temp[i] = None


# 필름의 최소 두께를 계산하는 함수입니다.
def min_thickness(map_info: list[list], length: int, width: int) -> list:
    result = length

    for j in range(width):
        depth = 1
        column_max = 0

        for i in range(length - 1):
            if map_info[i][j] == map_info[i+1][j]:
                depth += 1
            else:
                column_max = max(column_max, depth)
                depth = 1
        
        column_max = max(column_max, depth)
        result = min(column_max, result)

    return result


# 현재 필름에서 조건을 만족하는 최소 공정 회수를 반환하는 함수입니다.
def minimum_processing_num(map_info: list[list], length: int, width: int, thread: int):
    temp = [map_info[i].copy() for i in range(length)]
    current_low = min_thickness(temp, length, width)

    # 지금 상태가 조건을 만족하면, 후속 공정 없이 바로 사용 가능합니다.
    if current_low >= thread:
        return 0
    
    # 아닌 경우, 공정 횟수를 1씩 증가시키면서 조건을 만족하는 지 확인합니다.
    else:
        for n in range(1, thread + 1):
            thickness_list.clear()
            film_processing(map_info, length, width, n)
            if max(thickness_list) >= thread:
                return n


T = int(input())

for tc in range(1, T + 1):
    D, W, K = map(int, input().split())

    film = [list(map(int, input().split())) for _ in range(D)]
    process_position = [None] * D
    thickness_list = list()           # 약품 처리가 끝난 후의 두께를 모은 리스트입니다.
    processed_list = list()           # 약품 처리하는 위치 조합을 모은 리스트입니다.

    answer = minimum_processing_num(film, D, W, K)

    print(f'#{tc} {answer}')
