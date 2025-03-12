from collections import deque
 
delta = [[0, 1], [1, 0], [0, -1], [-1, 0]]
 
 
# 서비스 제공이 가능한 집의 최대 개수를 출력합니다.
# 시작 위치 : DFS, 영역 확인 : BFS
def searching_area(size: int, cost: int):
    global answer
 
    for n in range(size * size):
        visited = [[0] * size for _ in range(size)]
 
        si, sj = n // size, n % size
        q = deque()
        q.append((si, sj))
        visited[si][sj] = 1
        house = 0
        k = 1
         
        # 서비스 영역 최대 반경을 size + 1 로 설정
        while len(q) != 0 and k <= 2 * size + 1:
            for _ in range(len(q)):
                i, j = q.popleft()
                if town[i][j] == 1:
                    house += 1
 
                for di, dj in delta:
                    ni, nj = i + di, j + dj
 
                    # ni, nj 가 영역 밖인 경우
                    if 0 > ni or ni >= size or 0 > nj or nj >= size:
                        continue
 
                    if visited[ni][nj] == 0:
                        visited[ni][nj] = 1
                        q.append((ni, nj))
 
            if house * cost - (k * k + (k - 1) * (k - 1)) >= 0:
                answer = max(house, answer)
 
            k += 1
 
 
T = int(input())
 
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    town = [list(map(int, input().split())) for _ in range(N)]
 
    answer = 0
 
    searching_area(N, M)
 
    print(f"#{tc} {answer}")