#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    int c = 0;
    int freq[30] = {0};
    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            if (isupper(c)) {
                c = tolower(c);
            }
            freq[c - 'a'] ++;
        }
    }
    int pos = 0, maxE = 0;
    for (int i = 0; i < 26; i ++) {
        if (freq[i] > maxE) {
            maxE = freq[i];
            pos = i;
        }
    }
    pos = (pos + 22) % 26;
    printf("%d\n", pos);
    return EXIT_SUCCESS;
}