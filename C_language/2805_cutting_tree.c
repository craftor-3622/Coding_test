// https://www.acmicpc.net/problem/2805

# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>

int compare(const int* a, const int* b) {
    return (*a) - (*b);
}

int main() {
    // freopen("input.txt", "r", stdin);

    int N, M;
    scanf("%d %d", &N, &M);

    int* tree_list = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &tree_list[i]);
    }

    qsort(tree_list, N, sizeof(int), compare);

    int left = 0;
    int right = tree_list[N - 1];
    int middle;
    long int length_sum;

    while (right - left != 1) {
        length_sum = 0;
        
        middle = (left + right) / 2;

        for (int i = 0; i < N; i++) {
            if (tree_list[i] > middle) length_sum += (tree_list[i] - middle);
        }

        if (length_sum >= M) {
            left = middle;
        }
        else {
            right = middle;
        }
    }

    printf("%d\n", left);

    free(tree_list);

    return 0;
}

// 정렬 후 이진 탐색
// 소요 시간 : 30분, long int와 int의 범위는 다르다.
/* 여담 :
매개변수 탐색은 이진 탐색과 동일한 알고리즘 구조를 가지고 있지만,
한 가지 다른 특징은 배열이 꼭 정렬되어 있지 않아도 된다.
왜냐하면 초기 설정이 동일하다면 length_sum의 값 변화는
정렬이나 비정렬이나 동일하기 때문.
거기다 최소값을 기준으로 명제 참 거짓이 일관성을 띄기에
비정렬이어도 크게 상관 없다.
따라서 여기서 더 최적화할 수 있다면 n log n 이 아니라
log n까지도 바라볼 수 있는 문제다.
*/