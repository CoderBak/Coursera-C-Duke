#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

size_t maxSeq(int * array, size_t n);

int a[100];
void test(int * array, size_t size, size_t exp) {
    printf("Current Test: ");
    for(size_t i = 0; i < size; i += 1) {
        a[i] = array[i];
        printf("%d ", a[i]);
    }
    size_t calc = maxSeq(a, size);
    printf("-> Get: %zu Exp: %zu\n", calc, exp);
    assert(calc == exp);
    memset(a, 0, sizeof(a));
}
int main(void) {
    int test1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
    test(test1, 10, 4);
    int test2[] = {0};
    test(test2, 0, 0);
    int test3[] = {1, 2, 2, 2, 2, 2};
    test(test3, 6, 2);
    int test4[] = {1, 2, 3, 1, 2, 3, 4};
    test(test4, 7, 4);
    int test5[] = {-1, 0, 1, -2, 0, 1, 2};
    test(test5, 7, 4);
    int test6[] = {0};
    test(test6, 1, 1);
    int test7[] = {1, 2};
    test(test7, 2, 2);
    int test8[] = {1, -2};
    test(test8, 2, 1);
    return EXIT_SUCCESS;
}