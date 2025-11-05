#include <string>
#include <vector>
#include <iostream>

#define OFFSET 600
#define MAX_DP_SIZE 1200

using namespace std;

int n, k;      // n은 2의 배수
vector<vector<int>> copy_dice;
int max_win_cnt;

vector<int> answer;

void dice_combination(int cur, int a, int b, vector<int> nowList, vector<int> table) {
    vector<int> next_table(MAX_DP_SIZE);
    
    // for (int i = OFFSET - 20; i < OFFSET + 21; ++i)
    //     cout << table[i] << " ";
    // cout << endl;
    
    if (cur == n) {
        int result = 0;
        for (int i = OFFSET + 1; i < MAX_DP_SIZE; ++i)
            result += table[i];
        if (result > max_win_cnt) {
            answer = nowList;
            max_win_cnt = result;
        }
        return;
    }
    
    if (a < k) {
        fill(next_table.begin(), next_table.end(), 0);
        for (int i = 0; i < MAX_DP_SIZE - 100; ++i)
            for (int j = 0; j < 6; ++j)
                next_table[i + copy_dice[a + b][j]] += table[i];
        nowList.push_back(cur + 1);
        dice_combination(cur + 1, a + 1, b, nowList, next_table);
        nowList.pop_back();
    }
    
    if (b < k) {
        fill(next_table.begin(), next_table.end(), 0);
        for (int i = 100; i < MAX_DP_SIZE; ++i)
            for (int j = 0; j < 6; ++j)
                next_table[i - copy_dice[a + b][j]] += table[i];
        dice_combination(cur + 1, a, b + 1, nowList, next_table);
    }
}

vector<int> solution(vector<vector<int>> dice) {
    answer.clear();
    
    copy_dice = dice;
    n = dice.size();
    k = n / 2;
    max_win_cnt = 0;
    
    vector<int> init;
    init.resize(MAX_DP_SIZE, 0);
    init[OFFSET] = 1;
    
    dice_combination(0, 0, 0, {}, init);
    
    return answer;
}
