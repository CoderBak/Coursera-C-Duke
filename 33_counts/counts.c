#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
    counts_t * newCount = malloc(sizeof(counts_t));
    newCount->size = 0;
    newCount->unknown_cnt = 0;
    newCount->counts = NULL;
    return newCount;
}

void addCount(counts_t * c, const char * name) {
    if (name == NULL) {
        c->unknown_cnt ++;
        return;
    }
    for(int i = 0; i < c->size; i ++) {
        if (!strcmp(name, c->counts[i].id)) {
            c->counts[i].cnt ++;
            return;
        }
    }
    c->counts = realloc(c->counts, (c->size + 1) * sizeof(one_count_t));
    c->counts[c->size].id = calloc(strlen(name) + 1, sizeof(char));
    strncpy(c->counts[c->size].id, name, strlen(name));
    c->counts[c->size ++].cnt = 1;
}

void printCounts(counts_t * c, FILE * outFile) {
    for(int i = 0; i < c->size; i ++) {
        fprintf(outFile, "%s: %d\n", c->counts[i].id, c->counts[i].cnt);
    }
    if (c->unknown_cnt != 0) {
        fprintf(outFile, "<unknown> : %d\n", c->unknown_cnt);
    }
}

void freeCounts(counts_t * c) {
    for(int i = 0; i < c->size; i ++) {
        free(c->counts[i].id);
    }
    free(c->counts);
    free(c);
}
