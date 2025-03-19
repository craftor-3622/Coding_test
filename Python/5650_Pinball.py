# https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo
# 완전 탐색 + Delta 탐색 종결
import sys

sys.stdin = open("input.txt", "r")

# 동, 남, 서, 북
direction = [[0, 1], [1, 0], [0, -1], [-1, 0]]
# 벽면에 부딪혔을 때 바뀌는 방향
bound = {
    1: [2, 0, 3, 1],
    2: [2, 3, 1, 0],
    3: [1, 3, 0, 2],
    4: [3, 2, 0, 1],
    5: [2, 3, 0, 1],
}
wormhole = dict()


# 해당 게임판에서 최고 점수를 출력
def maximum_score():
    global answer, N, game_board

    for n in range(N * N):              # 무작위 위치
        for d in range(4):              # 무작위 방향
            if game_board[n // N][n % N] != 0:
                continue

            answer = max(answer, get_score((n // N, n % N), d))


# 임의의 지점 및 방향으로 시작했을 때 얻을 수 있는 점수
# 주의 : pos: tuple[int, int]은 3.7 버전에서 지원하지 않습니다.
# 런타임 에러 발생 시 tuple[int, int] 을 지우고 사용해 주세요.
def get_score(pos: tuple[int, int], dir_s: int):
    p, d = list(pos), dir_s
    score = 0

    while True:
        i, j = p
        di, dj = direction[d]
        ni, nj = i + di, j + dj

        # 벽 충돌 처리 코드
        if ni >= N or ni < 0 or nj >= N or nj < 0:
            ni, nj = i, j
            d = (d + 2) % 4
            score += 1

        # 블록 충돌 처리 코드
        if 1 <= game_board[ni][nj] <= 5:
            d = bound[game_board[ni][nj]][d]
            score += 1

        # 웜홀 처리 코드
        if game_board[ni][nj] >= 6:
            for hole_pos in wormhole[game_board[ni][nj]]:
                if hole_pos != [ni, nj]:
                    ni, nj = hole_pos
                    break

        # 게임 종료 처리 코드
        if game_board[ni][nj] == -1 or (ni, nj) == pos:
            break

        p = ni, nj

    return score


T = int(input())

for tc in range(1, T + 1):
    N = int(input())
    game_board = [list(map(int, input().split())) for _ in range(N)]
    wormhole.clear()
    answer = 0

    # 맵 초기화
    for i in range(N):
        for j in range(N):
            if game_board[i][j] <= 5:
                continue

            if game_board[i][j] not in wormhole:
                wormhole[game_board[i][j]] = [[i, j]]
            else:
                wormhole[game_board[i][j]].append([i, j])

    maximum_score()

    print(f"#{tc} {answer}")
