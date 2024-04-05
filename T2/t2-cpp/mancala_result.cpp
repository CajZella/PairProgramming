//
// Created by Michelle on 2024-04-05.
//
#include<iostream>
#include<cstdio>
#include <emscripten/emscripten.h>
using namespace std;
#define EXTERN extern "C"

EXTERN EMSCRIPTEN_KEEPALIVE int32_t mancala_result(int32_t flag, int32_t* seq, int32_t size) {
    int32_t cnt[15] = {0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0};
    int32_t cur_player = flag, end = 0;
    for (int32_t i = 0; i < size; i++) {
        int32_t player = seq[i] / 10, pos = seq[i] % 10, score_pos = player == 1 ? 7 : 14;
        if (player != cur_player) // not the current player
            return 30000 + i;
        pos = player == 1 ? pos : pos + 7;
        if (cnt[pos] == 0) // invalid move
            return 30000 + i;
        int32_t stones = cnt[pos]; cnt[pos] = 0;
        while (stones > 0) {
            pos = pos % 14 + 1;
            if (pos == 21 - score_pos) // skip the opponent's score position
                continue;
            cnt[pos]++;
            stones--;
        }
        if (cnt[pos] == 1 && cnt[14 - pos] > 0) {
            cnt[score_pos] += cnt[14 - pos] + 1;
            cnt[14 - pos] = cnt[pos] = 0;
        }
        int32_t player1_sum = 0, player2_sum = 0;
        for (int32_t j = 1; j <= 6; j++) {
            player1_sum += cnt[j];
            player2_sum += cnt[j + 7];
        }
        if (player1_sum == 0) {
            cnt[14] += player2_sum, end = i;
            break;
        } if (player2_sum == 0) {
            cnt[7] += player1_sum, end = i;
            break;
        }
        if (pos == score_pos) // extra turn
            cur_player = player;
        else
            cur_player = 3 - player;
    }
    if (end < size - 1) // game end but not end
        return 30000 + end + 1;
    if (end) // game end
        return 15000 + cnt[7 * flag] - cnt[7 * (3 - flag)];
    return 20000 + cnt[7 * flag]; // game not end
}
int main() {
    int32_t flag, seq[100], size;
    cin >> flag >> size;
    for (int32_t i = 0; i < size; i++)
        cin >> seq[i];
    printf("%d\n", mancala_result(flag, seq, size));
    return 0;
}