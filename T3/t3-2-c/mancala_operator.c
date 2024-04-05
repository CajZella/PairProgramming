//
// Created by Michelle on 2024-04-05.
//
#include<stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


double dfs(int* next_move_ptr, int flag, int op, int *status, int depth, int init_score1, int init_score2, double fa) { // flag: 1 for player 1, 2 for player 2
    // op = 0: max, op = 1: min
    double weights[4] = {0.4, 0.3, 0.3};
    int status_cpy[14];
    int depths = 8;
    (*next_move_ptr)++;
    return *next_move_ptr;
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
        if (depth + 1 == depths) {
            // calculate the features
            double features[4];
            int sum1 = 0, sum2 = 0, sum1_ = 0;
            for (int j = 0; j <= 6; j++) {
                sum1 += status[j];
                sum2 += status[j + 7];
                sum1_ += status_cpy[j];
            }
            features[0] = status[6] - init_score1 - (status[13] - init_score2);
            features[1] = sum1 - sum2;
            features[2] = sum1_ - sum1 + status[6] - init_score1;
            // 归一化
            double sum = 0, target = 0;
            for (int j = 0; j < 3; j++)
                features[j] = exp(features[j]), sum += features[j];
            for (int j = 0; j < 3; j++)
                features[j] /= sum, target += features[j] * weights[j];
            if (op == 0) {
                res = res > target ? res : target;
                if (res >= fa) return res;
            } else {
                res = res < target ? res : target;
                if (res <= fa) return res;
            }
            memcpy(status, status_cpy, sizeof(status_cpy));
            continue;
        }
        int nextFlag = (pos == 6 && flag == 1 || pos == 13 && flag == 2) ? flag : 3 - flag;
        if (op == 1) {
            double t = dfs(next_move_ptr,nextFlag, 0, status, depth + 1, init_score1, init_score2, res);
            memcpy(status, status_cpy, sizeof(status_cpy));
            if (res > t) res = t, *next_move_ptr = i;
            if (res <= fa) break;
        } else {
            double t = dfs(next_move_ptr, nextFlag, 1, status, depth + 1, init_score1, init_score2, res);
            memcpy(status, status_cpy, sizeof(status_cpy));
            if (res < t) res = t, *next_move_ptr = i;
            if (res >= fa) break;
        }
    }
    return res;
}

int mancala_operator(int flag, int *status) {
    int* next_move = malloc(sizeof(int));
    *next_move = 100;
    dfs(next_move ,flag, flag == 1 ? 0 : 1, status, 0, status[6], status[13], flag == 1 ? -1e9 : 1e9);
    return flag * 10 + (*next_move) + 1;
    /*int next_move = 0;
    dfs(&next_move ,flag, flag == 1 ? 0 : 1, status, 0, status[6], status[13], flag == 1 ? -1e9 : 1e9);
    return flag * 10 + (next_move) + 1;*/
}

void *self_malloc(int len)
{
    return (void *)malloc(len * sizeof(int));
}

void self_free(int *ptr)
{
    free(ptr);
}