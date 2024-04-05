//
// Created by Michelle on 2024-04-05.
//
#include<stdlib.h>
#include <string.h>
#include <math.h>

double weights[4] = {0.5, 0.3, 0.1, 0.1};
int depths = 8;
double dfs(int flag, int op, int *status, int depth, int init_score1, int init_score2) { // flag: 1 for player 1, 2 for player 2
    // op = 0: max, op = 1: min
    double res = op == 0 ? -1e9 : 1e9;
    for (int i = 0; i < 6; i++) {
        int pos = flag == 1 ? i : i + 7;
        if (status[pos] == 0) continue;
        int status_cpy[14];
        memcpy(status_cpy, status, sizeof(status_cpy));
        int stones = status[pos]; status[pos] = 0;
        while (stones > 0) {
            pos = (pos + 1) % 14;
            if (pos == 6 && flag == 2 || pos == 13 && flag == 1) continue;
            status[pos]++; stones--;
        }
        if (depth + 1 == depths) {
            // calculate the features
            int features[4];
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
            if (op == 0)
                res = res > target ? res : target;
            else
                res = res < target ? res : target;
            continue;
        }

    }
}
int mancala_operator(int flag, int *status) {

}