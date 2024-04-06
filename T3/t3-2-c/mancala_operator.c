//
// Created by Michelle on 2024-04-05.
//
#include<stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int next_move = -1;
int *cur_status;
int depths = 10;
int weights[4] = {100, 10, 1};
int check_skip(int player, int pos) {
    return pos == 6 && player == 2 || pos == 13 && player == 1;
}
int check_eat(int player, int pos) {
    return cur_status[pos] == 1 && cur_status[12 - pos] > 0 && ((pos >= 0 && pos < 6 && player == 1) || (pos >= 7 && pos < 13 && player == 2));
}
int check_end() {
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 6; i++)
        sum1 += cur_status[i], sum2 += cur_status[i + 7];
    if (sum1 == 0) {
        cur_status[13] += sum2;
        for (int j = 7; j < 13; j++)
            cur_status[j] = 0;
        return 1;
    }
    if (sum2 == 0) {
        cur_status[6] += sum1;
        for (int j = 0; j < 6; j++)
            cur_status[j] = 0;
        return 1;
    }
    return 0;
}
int calc_feature(int next_player, int *pre_status) { // 求 player1
    int features;
    // 得分
    features = weights[0] * (cur_status[6] - cur_status[13]);
    // 下一步可能被取走的最大棋子数或者额外回合
    if (next_player == 1)
        features += weights[1] * 1;
    else {
        int status_cpy[14];
        memcpy(status_cpy, cur_status, sizeof(status_cpy));
        int max_taken_stones = 0;
        for (int i = 7; i < 13; i++) {
            int pos = i;
            if (cur_status[pos] == 0) continue;
            int stones = cur_status[pos]; cur_status[pos] = 0;
            while (stones > 0) {
                pos = (pos + 1) % 14;
                if (check_skip(2, i)) continue;
                cur_status[pos]++; stones--;
            }
            if (check_eat(2, pos) && max_taken_stones < cur_status[12 - pos])
                max_taken_stones = cur_status[12 - pos];
            memcpy(cur_status, status_cpy, sizeof(status_cpy));
        }
        features -= weights[1] * max_taken_stones;
    }
    // 得失棋子数
    int sum1 = 0, sum1_ = 0;
    for (int j = 0; j < 6; j++) {
        sum1 += cur_status[j];
        sum1_ += pre_status[j];
    }
    features += weights[2] * (sum1 - sum1_ + cur_status[6] - pre_status[6]);
    return features;
}
int dfs(int player, int op, int depth, int weight_by_father, int op_by_father) {
    int status_cpy[14];
    memcpy(status_cpy, cur_status, sizeof(status_cpy));
    int res = op == 0 ? -1e9 : 1e9;
    int score_pos = player == 1 ? 6 : 13;
    for (int i = 0; i < 6; i++) {
        int pos = player == 1 ? i : i + 7;
        if (cur_status[pos] == 0) continue;
        // 模拟落子
        int stones = cur_status[pos]; cur_status[pos] = 0;
        while (stones > 0) {
            pos = (pos + 1) % 14;
            if (check_skip(player, pos)) continue;
            cur_status[pos]++; stones--;
        }
        // 判断是否可以吃子
        if (check_eat(player, pos))
            cur_status[score_pos] += cur_status[12 - pos] + 1, cur_status[12 - pos] = cur_status[pos] = 0;
        // 判断游戏是否结束
        if (check_end()) {
            int features = weights[0] * (cur_status[6] - cur_status[13]);
            if (op == 0 && res < features || op == 1 && res > features)
                res = features, next_move = depth == 0 ? i : next_move;
            memcpy(cur_status, status_cpy, sizeof(status_cpy));
            continue;
        }
        // 判断是否额外回合
        int next_player = (pos == 6 && player == 1 || pos == 13 && player == 2) ? player : 3 - player;
        // 达到最大深度时求解特征向量
        if (depth == depths) {
            int features = calc_feature(next_player, status_cpy);
            if (op == 0 && res < features || op == 1 && res > features)
                res = features, next_move = depth == 0 ? i : next_move;
            memcpy(cur_status, status_cpy, sizeof(status_cpy));
            continue;
        }
        // 递归求解
        int t = dfs(next_player, player == next_player ? op : 1 - op, depth + 1, res, op);
        memcpy(cur_status, status_cpy, sizeof(status_cpy));
        if (op == 0 && res < t || op == 1 && res > t)
            res = t, next_move = depth == 0 ? i : next_move;
        if (op != op_by_father && (op == 0 && res >= weight_by_father || op == 1 && res <= weight_by_father))
            break;
    }
    return res;
}
int mancala_operator(int flag, int *status) {
    cur_status = status;
    dfs(flag, 1 - flag, 0, flag == 1 ? 1e9 : -1e9, flag);
    return flag * 10 + next_move + 1;
}

void *self_malloc(int len)
{
    return (void *)malloc(len * sizeof(int));
}

void self_free(int *ptr)
{
    free(ptr);
}