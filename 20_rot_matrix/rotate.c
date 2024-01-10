#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char mp[10][10]) {
    char newMp[10][10];
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            newMp[j][9 - i] = mp[i][j];
        }
    }
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            mp[i][j] = newMp[i][j];
        }
    }
}