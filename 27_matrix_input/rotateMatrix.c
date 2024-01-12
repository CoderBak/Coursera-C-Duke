#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char mp[10][10]) {
    int newMp[10][10];
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

int main(int argc, char ** argv) {
    if (argc != 2) {
        perror("This program takes in exactly one file.");
        return EXIT_FAILURE;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Unable to read file.");
        return EXIT_FAILURE;
    }
    int buf[200] = {0}, c = 0, cnt = 0;
    while((c = fgetc(fp)) != EOF) {
        buf[cnt ++] = c;
        if (cnt % 11 == 0) {
            if (c != '\n') {
                perror("Invalid size.");
                return EXIT_FAILURE;
            }
        }
        if (cnt > 110) {
            perror("Invalid size.");
            return EXIT_FAILURE;
        }
    }
    if (cnt < 109) {
        perror("Invalid size.");
        return EXIT_FAILURE;
    }
    char mp[10][10] = {0};
    for(int i = 0; i < 10; i ++) {
        for(int j = 0; j < 10; j ++) {
            mp[i][j] = buf[11 * i + j];
        }
    }
    rotate(mp);
    for(int i = 0; i < 10; i ++) {
        for(int j = 0; j < 10; j ++) {
            printf("%c", mp[i][j]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
} 