//
// Created by Michelle on 2024-04-05.
//
#include<stdlib.h>

int* mancala_board(int flag, int* seq, int size) {
    int* cnt = (int*)malloc(15 * sizeof(int));
    for (int i = 0; i < 15; i++)
        cnt[i] = (i == 6 || i == 13 || i == 14) ? 0 : 4;
    int cur_player, end = 0;
    for (int i = 0; i < size; i++) {
        int player = seq[i] / 10, pos = (player == 1) ? seq[i] % 10 - 1 : seq[i] % 10 + 6, score_pos = player == 1 ? 6 : 13;
        if (i == size - 1)
            if (flag != cur_player || !cnt[pos] || end) { // not the current player
                end = 2;
                break;
            }
        int stones = cnt[pos]; cnt[pos] = 0;
        while (stones > 0) {
            pos = (pos + 1) % 14;
            if (pos == 19 - score_pos) // skip the opponent's score position
                continue;
            cnt[pos]++;
            stones--;
        }
        if (cnt[pos] == 1 && cnt[12 - pos] > 0  && pos != 6 && pos != 13) {
            cnt[score_pos] += cnt[12 - pos] + 1;
            cnt[12 - pos] = cnt[pos] = 0;
        }
        int player1_sum = 0, player2_sum = 0;
        for (int j = 0; j < 6; j++) {
            player1_sum += cnt[j];
            player2_sum += cnt[j + 7];
        }
        if (player1_sum == 0) {
            cnt[13] += player2_sum, end = 1;
            break;
        } if (player2_sum == 0) {
            cnt[6] += player1_sum, end = 1;
            break;
        }
        if (pos == score_pos) // extra turn
            cur_player = player;
        else
            cur_player = 3 - player;
    }
    if (end == 1) { // game end
        if (cnt[6] == cnt[13])
            cnt[14] = 200;
        else
            cnt[14] = 200 + cnt[6] - cnt[13];
    } else if (end == 2) {// not valid
        if (flag == 1)
            cnt[14] = 200 + 2 * cnt[6] - 48;
        else
            cnt[14] = 200 + 48 - 2 * cnt[13];
    }
    return cnt;
}

void *self_malloc(int len)
{
    return (void *)malloc(len * sizeof(int));
}

void self_free(int *ptr)
{
    free(ptr);
}
