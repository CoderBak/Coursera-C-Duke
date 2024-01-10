#include <stdlib.h>
#include <assert.h>

unsigned power (unsigned x, unsigned y);

void test (unsigned x, unsigned y, unsigned exp) {
    assert(power(x, y) == exp);
}

int main(void) {
    test(0, 0, 1);
    test(1, 0, 1);
    test(0, 1, 0);
    test(2, 2, 4);
    test(10, 3, 1000);
    test(2, 0, 1);
    test(2, 31, 2147483648);
    return EXIT_SUCCESS;
}