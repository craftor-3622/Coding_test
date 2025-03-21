# https://school.programmers.co.kr/learn/courses/30/lessons/214289
# DP (Bottom-up)

MAX_TEMP_RANGE = 50
PHASE_SHIFT = 10

def solution(temperature, t1, t2, a, b, onboard):
    N = len(onboard)
    
    cost = [[float("inf")] * N for _ in range(MAX_TEMP_RANGE + 1)]
    cost[temperature + PHASE_SHIFT][0] = 0
    
    up = a if temperature < t1 else 0
    go = b
    down = a if temperature > t2 else 0
    
    for time in range(1, N):
        for cur_tem in range(MAX_TEMP_RANGE + 1):
            if cur_tem == 0:
                next_up = float("inf")
            else:
                next_up = cost[cur_tem - 1][time - 1] + up
            
            if cur_tem == temperature + PHASE_SHIFT:
                next_go = cost[cur_tem][time - 1]
            else:
                next_go = cost[cur_tem][time - 1] + go
            
            if cur_tem == MAX_TEMP_RANGE:
                next_down = float("inf")
            else:
                next_down = cost[cur_tem + 1][time - 1] + down
    
            if cur_tem > temperature + PHASE_SHIFT and down:
                next_up = float("inf")
            if cur_tem < temperature + PHASE_SHIFT and up:
                next_down = float("inf")
    
            cost[cur_tem][time] = min(next_up, next_go, next_down)
        
            if onboard[time] and (cur_tem < t1 + PHASE_SHIFT or cur_tem > t2 + PHASE_SHIFT):
                cost[cur_tem][time] = float("inf")

    answer = float("inf")
    for t in range(MAX_TEMP_RANGE + 1):
        answer = min(answer, cost[t][N-1])
    
    return answer