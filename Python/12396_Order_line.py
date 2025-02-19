# https://school.programmers.co.kr/learn/courses/30/lessons/12936

def solution(n, k):
    global answer

    list_a = [i for i in range(1, n + 1)]
    answer = []
    permutation(k, n, n, list_a)

    return answer


def permutation(k, n, cur, target):
    global answer

    if cur == 1:
        answer.append(sum(target))

    if cur > 1:
        mod = (k - 1) // factorial(cur - 1)
        m = -1
        for i in range(n):
            if target[i] == 0:
                continue
            else:
                m += 1
                if m == mod:
                    answer.append(target[i])
                    target[i] = 0
                    permutation(k - mod * factorial(cur - 1), n, cur - 1, target)


def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n - 1)
