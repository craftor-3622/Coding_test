from collections import deque
 
# delta 정의. 0부터 3까지 동, 남, 서, 북
delta = [[0, 1], [1, 0], [0, -1], [-1, 0]]
# pipe 연결 상태 정의. 0부터 3까지 동, 남, 서, 북
pipes = [
    [0, 1, 0, 1, 1, 1, 0, 0],
    [0, 1, 1, 0, 0, 1, 1, 0],
    [0, 1, 0, 1, 0, 0, 1, 1],
    [0, 1, 1, 0, 1, 0, 0, 1],
]
 
 
def bfs(start: tuple, time: int):
    q = deque()
    visited = [[0] * M for _ in range(N)]
    hour = 1
    length = 0
 
    # 초기값 입력
    si, sj = start
    q.append(start)
    length += 1
    visited[si][sj] = 1
 
    while len(q) != 0 and hour < time:
 
        # queue 관점에서 1시간 : q에 있는 모든 요소를 처리하고, 입력받을 수 있는 모든 요소를 받는다.
        for _ in range(len(q)):
            i, j = q.popleft()
 
            # delta list 로 받지 않고 수로 받습니다.
            # delta 와 pipe 의 direction 을 맞춰 코드 가독성을 높이고자 함.
            for d in range(4):
                ni, nj = i + delta[d][0], j + delta[d][1]
                if 0 <= ni < N and 0 <= nj < M:
                    # 한 번도 방문하지 않았거나, 파이프가 연결된 경우
                    if (visited[ni][nj] == 0 and pipes[(d + 2) % 4][tunnel[ni][nj]] == 1
                            and pipes[d][tunnel[i][j]] == 1):
                        q.append((ni, nj))
                        visited[ni][nj] = 1
                        length += 1
 
        hour += 1
 
    return length
 
 
T = int(input())
 
for tc in range(1, T + 1):
    N, M, R, C, L = map(int, input().split())
 
    tunnel = [list(map(int, input().split())) for _ in range(N)]
 
    answer = bfs((R, C), L)
 
    print(f"#{tc} {answer}")