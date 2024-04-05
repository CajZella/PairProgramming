//
// Created by Michelle on 2024-04-05.
//
#include<stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


double dfs(int* next_move, int flag, int op, int *status, int depth, int init_score1, int init_score2, double fa) { // flag: 1 for player 1, 2 for player 2
    // op = 0: max, op = 1: min
    double weights[4] = {0.7, 0.0, 0.2, 0.2};
    int depths = 7;
    int status_cpy[14];
    memcpy(status_cpy, status, sizeof(status_cpy));
    double res = op == 0 ? -1e9 : 1e9;
    for (int i = 0; i < 6; i++) {
        int pos = flag == 1 ? i : i + 7;
        if (status[pos] == 0) continue;
        int stones = status[pos]; status[pos] = 0;
        while (stones > 0) {
            pos = (pos + 1) % 14;
            if (pos == 6 && flag == 2 || pos == 13 && flag == 1) continue;
            status[pos]++; stones--;
        }
        if (status[pos] == 1 && status[12 - pos] > 0 && ((pos >= 1 && pos <= 6 && flag == 1) || (pos >= 8 && pos <= 13 && flag == 2)))
            status[flag == 1 ? 6 : 13] += status[12 - pos] + 1, status[12 - pos] = status[pos] = 0;
        int sum1 = 0, sum2 = 0, sum1_ = 0;
        for (int j = 0; j < 6; j++) {
            sum1 += status[j];
            sum2 += status[j + 7];
            sum1_ += status_cpy[j];
        }
        int next_flag = (pos == 6 && flag == 1 || pos == 13 && flag == 2) ? flag : 3 - flag;
        if (depth + 1 == depths || sum1 == 0 || sum2 == 0) {
            // calculate the features
            double features[4];
            features[0] = status[6] - init_score1 - (status[13] - init_score2);
            features[1] = sum1 - sum2;
            features[2] = sum1_ - sum1 + status[6] - init_score1;
            features[3] = next_flag == flag && flag == 1 ? 50 : (next_flag == flag && flag == 2 ? -50 : 0);
            // 归一化
            double sum = 0, target = 0;
            for (int j = 0; j < 4; j++)
                features[j] = exp(features[j]), sum += features[j];
            for (int j = 0; j < 4; j++)
                features[j] /= sum, target += features[j] * weights[j];
            if (op == 0) {
                if (res < target) res = target, *next_move = depth == 0 ? i : *next_move;
                if (res >= fa) return res;
            } else {
                if (res > target) res = target, *next_move = depth == 0 ? i : *next_move;
                if (res <= fa) return res;
            }
            memcpy(status, status_cpy, sizeof(status_cpy));
            continue;
        }
        if (op == 1) {
            double t = dfs(next_move, next_flag, flag == next_flag ? 1 : 0, status, depth + 1, init_score1, init_score2, res);
            memcpy(status, status_cpy, sizeof(status_cpy));
            if (res > t) res = t, *next_move = depth == 0 ? i : *next_move;
            if (res <= fa) break;
        } else {
            double t = dfs(next_move, next_flag, flag == next_flag ? 0 : 1, status, depth + 1, init_score1, init_score2, res);
            memcpy(status, status_cpy, sizeof(status_cpy));
            if (res < t) res = t, *next_move = depth == 0 ? i : *next_move;
            if (res >= fa) break;
        }
    }
    return res;
}
int mancala_operator(int flag, int *status) {
    int next_move = 0;
    dfs(&next_move, flag, flag == 1 ? 0 : 1, status, 0, status[6], status[13], flag == 1 ? 1e9 : -1e9);
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