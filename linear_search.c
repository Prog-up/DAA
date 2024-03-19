#include <stdio.h>

int linear_search(int* a, int len, int x)
{
    for (int i = 0; i < len; i++)
        if (a[i] == x)
            return i;
    return -1;
}