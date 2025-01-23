# https://www.acmicpc.net/problem/10845

queue = []

# queue 삽입
def push(component: int) -> None:
    global queue
    queue.append(component)
    
# queue 빼내기
def pop() -> None:
    global queue
    if len(queue) == 0:
        print(-1)
    else:
        print(queue[0])
        queue = queue[1:]

# queue 크기
def size() -> None:
    global queue
    print(len(queue))

# queue 비어있음 여부
def empty() -> None:
    if len(queue) == 0:
        print(1)
    else:
        print(0)

# queue의 맨 앞 요소
def front() -> None:
    global queue
    if len(queue) == 0:
        print(-1)
    else:
        print(queue[0])
        
# queue의 맨 뒤 요소
def back() -> None:
    global queue
    if len(queue) == 0:
        print(-1)
    else:
        print(queue[len(queue) - 1])

N = int(input())

for i in range(N):
    order = input().split(' ')
    if order[0] == 'push':
        intager = order[1]
        push(intager)
    elif order[0] == 'pop':
        pop()
    elif order[0] == 'size':
        size()
    elif order[0] == 'empty':
        empty()
    elif order[0] == 'front':
        front()
    elif order[0] == 'back':
        back()
