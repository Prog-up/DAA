#include <iostream>
#include <limits.h>
using namespace std;

int max(int a, int b, int c = INT_MIN)
{
    return (a > b && a > c) ? a : ((b > c) ? b : c);
}
