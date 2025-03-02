// https://www.acmicpc.net/problem/16926
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

void rotatematrix(std::vector<std::vector<int>>& matrix, int H, int W, int start) {
    if (H - 2 * start > 0 && W - 2 * start > 0) {
        std::queue<int> temp = {};

        for (int j = start + 1; j < W - start; j++) temp.push(matrix[start][j]);
        for (int i = start + 1; i < H - start; i++) temp.push(matrix[i][W - 1 - start]);

        for (int j = W - 2 - start; j >= start; j--) temp.push(matrix[H - 1 - start][j]);
        for (int i = H - 2 - start; i >= start; i--) temp.push(matrix[i][start]);

        matrix[start][start] = temp.front();
        temp.pop();

        for (int j = start + 1; j < W - start; j++) { matrix[start][j] = temp.front(); temp.pop(); }
        for (int i = start + 1; i < H - start; i++) { matrix[i][W - 1 - start] = temp.front(); temp.pop(); }

        for (int j = W - 2 - start; j >= start; j--) { matrix[H - 1 - start][j] = temp.front(); temp.pop(); }
        for (int i = H - 2 - start; i >= start + 1; i--) { matrix[i][start] = temp.front(); temp.pop(); }

        rotatematrix(matrix, H, W, start + 1);
    }
}


int main() {
    freopen("input.txt", "r", stdin);

    int N, M, R;
    std::cin >> N >> M >> R;

    std::vector<std::vector<int>> A(N, std::vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> A[i][j];
        }
    }

    for (int n = 0; n < R; n++) rotatematrix(A, N, M, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << A[i][j] << ' ';
        }
        if (i != N - 1) { std::cout << std::endl; }
    }
    
    return 0;
}