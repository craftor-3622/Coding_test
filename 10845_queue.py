queue = []

# queue 삽입
def push(component: int) -> None:
    global queue
    queue.append(component)

# queue 빼내기
def pop() -> None:
    global queue
    print(queue[0])
    queue = queue[1:]

N = int(input())

for i in range(N):
    order = input().split(' ')
    if order[0] == 'push':
        intager = order[1]
        order = order[0]
        push(intager)
    elif order[0] == 'pop':
        pop()
