#include<iostream>
#include <stdlib.h>
using namespace std;

int seq[100] = {11,21,16,21,12,16,14,21,16,15,21,16,13,21,16,14,26,11,22,11,21,16,12,26,24,11,26,25,11,26,23,11,26,24,16,12,21,16,14,21,16,15,22,11,23,11,24};

int mancala_result(int flag, int *seq, int size)
{
    int cnt[15] = {0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0};
    int cur_player = flag, end = 0;
    for (int i = 0; i < size; i++)
    {
        int player = seq[i] / 10, pos = seq[i] % 10, score_pos = player == 1 ? 7 : 14;
        if (player != cur_player) // not the current player
            return 30000 + i;
        pos = player == 1 ? pos : pos + 7;
        if (cnt[pos] == 0) // invalid move
            return 30000 + i;
        int stones = cnt[pos];
        cnt[pos] = 0;
        while (stones > 0)
        {
            pos = pos % 14 + 1;
            if (pos == 21 - score_pos) // skip the opponent's score position
                continue;
            cnt[pos]++;
            stones--;
        }
        if (cnt[pos] == 1 && cnt[14 - pos] > 0 && pos != score_pos && pos != 21 - score_pos)
        {
            cnt[score_pos] += cnt[14 - pos] + 1;
            cnt[14 - pos] = cnt[pos] = 0;
        }
        int player1_sum = 0, player2_sum = 0;
        for (int j = 1; j <= 6; j++)
        {
            player1_sum += cnt[j];
            player2_sum += cnt[j + 7];
        }
        if (player1_sum == 0)
        {
            cnt[14] += player2_sum, end = i;
            break;
        }
        if (player2_sum == 0)
        {
            cnt[7] += player1_sum, end = i;
            break;
        }
        if (pos == score_pos) // extra turn
            cur_player = player;
        else
            cur_player = 3 - player;
        printf("0: %d ", cnt[14]);
        for (int i = 1; i <= 13; i++)
            printf("%d: %d ", i, cnt[i]);
        printf("\n");
    }
    if (end && end < size - 1) // game end but not end
        return 30000 + end;
    if (end) // game end
        return 15000 + cnt[7 * flag] - cnt[7 * (3 - flag)];
    return 20000 + cnt[7 * flag]; // game not end
}

int main() {
    cout<<mancala_result(1,seq,77)<<endl;
}