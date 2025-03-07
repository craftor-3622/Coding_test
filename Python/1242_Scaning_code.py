# 암호패턴
encoded_num = {
    "0001101": 0,
    "0011001": 1,
    "0010011": 2,
    "0111101": 3,
    "0100011": 4,
    "0110001": 5,
    "0101111": 6,
    "0111011": 7,
    "0110111": 8,
    "0001011": 9,
}

BINARY_COMP = 56            # 2진수 기준 가로 길이는 56의 배수
HEX_LENGTH_COMP = 14        # 16진수 기준 14의 배수
DECIMAL_NUM_CNT = 8
NUM_BIT_LENGTH = 7


# 16진수 Sample 로부터 늘어난 배수를 반환합니다.
# 검사 방법 : 56자리 문자열의 좌우 양단을 strip 한 후, bit 단위를 측정합니다.
def sampling(string: str):
    sample = bin(int(string, base=16))[2:]
    left = 0
    right = len(sample) - 1
    mul = 56
    unit = 0

# 길이 56 sample 문자열 좌우 strip
    while sample[0] == sample[left]:
        left += 1

    while sample[len(sample) - 1] == sample[right]:
        right -= 1

    sample = sample[left: right + 1]
    cur = sample[0]

    # 단위 길이 계산 -> 단위 길이의 최소값이 배수가 됩니다.
    for next_str in sample:
        if cur == next_str:
            unit += 1
        else:
            mul = min(mul, unit)
            cur = next_str
            unit = 1
    else:
        mul = min(mul, unit)
 
    return mul
 
 
# 삽입된 암호코드를 해독하는 함수입니다. 해독한 숫자는 조건에 따라 명령을 수행하며, 암호코드의 끝점을 반환합니다.
def code_reader(si: int, sj: int) -> tuple:
    global video
    global answer
 
    k = 1       # 가로 길이의 배수
    ni = si
    nj = sj - HEX_LENGTH_COMP
    num_list = list()
    b = 0
 
    # 암호 코드의 시작점은 직사각형 기준 북동쪽, 끝점은 남서쪽에 있습니다.
    # 세로 끝점을 확인합니다.
    while video[ni][sj] == video[si][sj]:
        ni += 1
 
    # Sampling : 배수(k)를 확인합니다. bit 가 몇 단위로 반복하는 지를 검사합니다.
    temp = "".join(video[si][nj:sj+1])
    k = sampling(temp)
    nj = sj - k * HEX_LENGTH_COMP
 
    # 코드가 16진수로 추가 암호화되면서 자리수가 밀렸을 수 있습니다. 이를 확인해줍니다.
    while not (int(video[si][sj], base=16) & 1 << b):
        b += 1
 
    # 자리수가 2칸 이상 밀린 경우, 차지하는 길이가 배수와 무관하게 1칸 더 깁니다. (2배수 기준 기존 28칸에서 29칸으로 증가)
    if b >= 2:
        nj -= 1
 
    encoded_binary = "".join(video[si][nj + 1:sj + 1])      # 코드 추출
    temp = str(bin(int(encoded_binary, base=16)))[2:]       # 16진수 -> 2진수
    bit_line = str(bin(int(temp, base=2) >> b))[2:]         # 밀린 자리수만큼 재조정
    code = bit_line.zfill(k * HEX_LENGTH_COMP * 4)[::k]     # 남은 자리만큼 채우기
 
    for n in range(DECIMAL_NUM_CNT):
        num_list.append(encoded_num[code[n*NUM_BIT_LENGTH:(n+1)*NUM_BIT_LENGTH]])
 
    # 조건을 확인한 후 출력 값을 계산합니다.
    if (sum(num_list[0::2]) * 3 + sum(num_list[1::2])) % 10 == 0:
        answer += sum(num_list)
 
    return ni, nj
 
 
# 검사 코드를 다시 검사하지 않게 구역을 칠하는 함수입니다.
def ban(si, ei, sj, ej):
    for i in range(si, ei):
        for j in range(sj, ej, -1):
            visited[i][j] = 1
 
 
T = int(input())
 
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    answer = 0
 
    video = [list(input()) for _ in range(N)]
    visited = [[0] * M for _ in range(N)]
 
    # 맨 뒤에 오는 자리수를 확인해줍니다.
    for j in range(M - 1, HEX_LENGTH_COMP - 1, -1):
        for i in range(N):
            if visited[i][j] == 0 and video[i][j] != "0":
                fi, fj = code_reader(i, j)
                ban(i, fi, j, fj)
 
    print(f"#{tc} {answer}")