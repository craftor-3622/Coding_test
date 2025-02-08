// https://www.acmicpc.net/problem/2805
// 정렬 후 이진 탐색 (qsort 함수 만세)
// 소요 시간 : 30분, long int와 int의 범위는 다르다 (근데 항상 까먹는다)

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