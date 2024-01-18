#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


char ** readLines(size_t * length, FILE *fp) {
    // Read lines from the file.
    // Need to free after using the data.
    // Return the line count.
    char ** lines = NULL;
    char * line = NULL;
    size_t len = 0, cnt = 0;
    while(getline(&line, &len, fp) >= 0) {
        lines = realloc(lines, (cnt + 1) * sizeof(*lines));
        lines[cnt ++] = line;
        line = NULL;
    }
    free(line);
    *length = cnt;
    return lines;
}

kvarray_t * split(char ** lines, size_t cnt) {
    kvarray_t * lst = malloc(sizeof(kvarray_t));
    lst->pairs = malloc(cnt * sizeof(kvpair_t));
    for(size_t i = 0; i < cnt; i ++) {
        char * cur = lines[i];
        size_t pos = -1;
        for(size_t j = 0; j < strlen(cur); j ++) {
            if (cur[j] == '=') {
                pos = j;
                break;
            }
        }
        if (pos == -1) {
            perror("Invalid format.");
            return NULL;
        }
        lst->pairs[i].key = calloc(pos + 1, sizeof(char));
        lst->pairs[i].value = calloc(strlen(cur) - pos - 1, sizeof(char));
        strncpy(lst->pairs[i].key, cur, pos);
        strncpy(lst->pairs[i].value, cur + pos + 1, strlen(cur) - pos - 2);
    }
    lst->size = cnt;
    return lst;
}

kvarray_t * readKVs(const char * fname) {
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Can't read file.");
        return NULL;
    }
    size_t cnt = 0;
    char ** lines = readLines(&cnt, fp);
    kvarray_t * lst = split(lines, cnt);
    for(int i = 0; i < cnt; i ++) {
        free(lines[i]);
    }
    free(lines);
    fclose(fp);
    return lst;
}

void freeKVs(kvarray_t * pairs) {
    for(int i = 0; i < pairs->size; i ++) {
        free(pairs->pairs[i].key);
        free(pairs->pairs[i].value);
    }
    free(pairs->pairs);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    for(size_t i = 0; i < pairs->size; i ++) {
        printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    for (int i = 0; i < pairs->size; i ++) {
        if (!strcmp(pairs->pairs[i].key, key)) {
            return pairs->pairs[i].value;
        }
    }
    return NULL;
}
