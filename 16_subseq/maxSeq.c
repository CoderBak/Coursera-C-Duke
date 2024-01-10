#include <stdio.h>
#include <stdlib.h>

size_t max(size_t x, size_t y) {
    return (x > y) ? x : y;
}

size_t maxFromStart(int * a, size_t n) {
    // returns the length of longest
    // increasing sequence from 0
    for (size_t i = 1; i < n; i ++) {
        if (a[i] <= a[i - 1]) {
            return i;
        }
    }
    return n;
}

size_t maxSeq(int * a, size_t n) {
    int maxL = 0;
    for (size_t i = 0; i < n; i ++) {
        maxL = max(maxL, maxFromStart(a + i, n - i));
    }
    return maxL;
}