#include <stdlib.h>

int bocchi_shut_up(int flag, int *seq, int size)
{
    int a[7];
    for (int i = 0; i < 7; i++)
    {
        a[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        if (seq[i] / 10 == flag)
        {
            a[seq[i] % 10]++;
        }
    }
    int max_time = -1;
    int max_num = 0;
    for (int i = 1; i < 7; i++)
    {
        if (a[i] > max_time)
        {
            max_time = a[i];
            max_num = flag * 10 + i;
        }
        else if (a[i] == max_time)
        {
            max_num = 10;
        }
    }
    return max_num;
}

void *self_malloc(int len)
{
    return (void *)malloc(len * sizeof(int));
}

void self_free(int *ptr)
{
    free(ptr);
}