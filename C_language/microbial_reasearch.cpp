#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define MAX_Q 55
#define MAX_N 20

int gN, gQ;
int count[MAX_Q] = { 0, };
int board[MAX_N][MAX_N] = { 0, };

int flag[MAX_Q] = { 0, };
vector<pair<int, int>> form[MAX_Q];

set<int> graph[MAX_Q];

int del[4][2] = {{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }};

struct Node {
    int num;
    int cnt;

    bool operator<(Node right) const {
        if (cnt < right.cnt) return true;
        if (cnt > right.cnt) return false;

        if (num > right.num) return true;
        if (num < right.num) return false;

        return false;
    }
};

// 디버그용 출력
void printBoard() {
    for (int i = gN - 1; i >= 0; --i) {
        for (int j = 0; j < gN; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int n = 1; n <= gQ; ++n) cout << count[n] << " ";
    cout << endl;
    for (int n = 1; n <= gQ; ++n) cout << flag[n] << " ";
    cout << endl << endl;
}

// 디버그용 출력 22222
void printGraph(int num) {
    for (int i = 1; i <= num; ++i) {
        if (flag[i] == 0) continue;
        for (int n: graph[i]) cout << n << " ";
        cout << endl;
    }
    cout << endl;
}

// 미생물 투입
void putCell(int num) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    flag[num] = 1;
    count[num] = (r2 - r1) * (c2 - c1);

    for (int i = c1; i < c2; ++i) {
        for (int j = r1; j < r2; ++j) {
            if (board[i][j] != 0) --count[board[i][j]];
            board[i][j] = num;
        }
    }
}

// 필드 검사
void checkCell() {
    int visited[MAX_N][MAX_N] = { 0, };
    queue<pair<int, int>> q;
    int si, sj, oi, oj, ni, nj;
    pair<int, int> now;
    int num, cnt;

    for (int n = 1; n <= gQ; ++n) form[n].clear();

    for (int j = 0; j < gN; ++j) {
        for (int i = 0; i < gN; ++i) {
            if (board[i][j] == 0 || flag[board[i][j]] == 0) continue;
            if (visited[i][j] != 0) continue;
            num = board[i][j];

            si = i; sj = j;
            q.push({ i, j });
            cnt = 0;

            while (!q.empty()) {
                now = q.front(); q.pop();
                oi = now.first; oj = now.second;

                if (oi < 0 || oi >= gN || oj < 0 || oj >= gN) continue;
                if (visited[oi][oj] != 0) continue;

                form[num].push_back({ oi - si, oj - sj });
                visited[oi][oj] = 1;
                cnt++;

                for (auto d : del) {
                    ni = oi + d[0]; nj = oj + d[1];

                    if (ni < 0 || ni >= gN || nj < 0 || nj >= gN) continue;
                    if (visited[ni][nj] != 0) continue;

                    if (board[ni][nj] != num) continue;
                    q.push({ ni, nj });
                }
            }

            if (cnt != count[num]) {
                flag[num] = 0;
                form[num].clear();
            }
        }
    }
}

// 미생물 이동
void moveCell() {
    int newBoard[MAX_N][MAX_N] = { 0, };
    priority_queue<Node> pq;

    for (int n = 1; n <= gQ; ++n)
        if (flag[n] == 1) pq.push({n, count[n]});

    int now_num;
    int flag1;

    while (!pq.empty()) {
        now_num = pq.top().num; pq.pop();

        int si = -1;
        int sj = -1;

        //선 검사
        for (int j = 0; j < gN; ++j) {
            for (int i = 0; i < gN; ++i) {
                flag1 = 1;
                for (auto node : form[now_num]) {
                    int ni = i + node.first;
                    int nj = j + node.second;

                    if (ni < 0 || ni >= gN || nj < 0 || nj >= gN) { flag1 = 0; break; }
                    if (newBoard[ni][nj] != 0 && newBoard[ni][nj] != now_num) { flag1 = 0; break; }
                }
                if (flag1 == 1) { si = i; sj = j; break; }
            }
            if (flag1 == 1) break;
        }

        if (si == -1) {
            flag[now_num] = 0;
            form[now_num].clear();
            continue;
        }

        // 후 입력
        for (auto node : form[now_num])
            newBoard[si + node.first][sj + node.second] = now_num;
    }

    // 결과 대입
    for (int i = 0; i < gN; i++)
        for (int j = 0; j < gN; j++)
            board[i][j] = newBoard[i][j];
}

// 그래프 갱신
void newGraph() {
    for (int n = 1; n <= gQ; ++n) graph[n].clear();

    // 인접 연산
    int visited[MAX_N][MAX_N] = { 0, };
    queue<pair<int, int>> q;
    pair<int, int> now;

    for (int j = 0; j < gN; ++j) {
        for (int i = 0; i < gN; ++i) {
            if (board[i][j] == 0 || flag[board[i][j]] == 0) continue;
            if (visited[i][j] != 0) continue;

            q.push({ i, j });

            while (!q.empty()) {
                now = q.front();  q.pop();
                int oi = now.first;
                int oj = now.second;

                if (visited[oi][oj] != 0) continue;
                visited[oi][oj] = 1;

                for (auto d : del) {
                    int ni = oi + d[0];
                    int nj = oj + d[1];
                    
                    if (ni < 0 || ni >= gN || nj < 0 || nj >= gN) continue;
                    if (visited[ni][nj] != 0) continue;
                    if (board[ni][nj] == 0) continue;
                    
                    if (board[ni][nj] != board[oi][oj]) {
                        graph[board[ni][nj]].insert(board[oi][oj]);
                        graph[board[oi][oj]].insert(board[ni][nj]);
                    }
                    q.push({ ni, nj });
                }
            }
        }
    }
}

// 실험 결과 기록
int result() {
    int ans = 0;

    for (int n = 1; n <= gQ; ++n)
        for (int next: graph[n])
            ans += count[n] * count[next];

    return ans / 2;
}

int main() {
    cin >> gN >> gQ;

    for (int n = 1; n <= gQ; ++n) {
        putCell(n);
        // printBoard();

        checkCell();
        moveCell();
        newGraph();

        cout << result() << endl;
        // cout << endl;

        // printBoard();
        // printGraph(n);
    }

    return 0;
}

/*
후기.

1. 인접 방식이어서 dfs가 가능할 수도 있겠다 생각은 했었는데, bfs만으로 되지 않을까 싶었다.
그러나 풀고 나서 보니, 계산 안정성에서는 이 방식이 맞는 것 같다.
디버깅, 기록 정보 등 여러 방면에서 이 graph 방식도 염두해야 할 것 같다.

2. 무방향 graph에 대한 연산 방식을 너무 어렵게 생각한듯.
구현만 잘하면 2번씩 중복 연산한 거라, 그냥 전체 순회 돌리고 절반으로 나누면 간단한 문제였는데,
오히려 visited를 사용해서 로직이 꼬인 것 같다.
*/
