#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y) {
    if (y == 0) {
        return 1;
    }
    unsigned r = y / 2;
    unsigned ans = power(x, r);
    ans = ans * ans;
    return (y % 2 == 1) ? ans * x : ans;
}