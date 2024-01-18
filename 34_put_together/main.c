#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Can't read file.");
        return NULL;
    }
    counts_t * newCount = createCounts();
    char * line = NULL;
    size_t len = 0;
    while(getline(&line, &len, fp) >= 0) {
        char * cur = calloc(strlen(line), sizeof(char));
        strncpy(cur, line, strlen(line) - 1);
        addCount(newCount, lookupValue(kvPairs, cur));
        free(cur);
        free(line);
        line = NULL;
    }
    free(line);
    fclose(fp);
    return newCount;
}

int main(int argc, char ** argv) {
    if (argc <= 1) {
        perror("Invalid arg count.");
        return EXIT_FAILURE;
    }
    kvarray_t * kv = readKVs(argv[1]);
    if (kv == NULL) {
        return EXIT_FAILURE;
    }
    for(int i = 2; i < argc; i ++) {
        counts_t * count = countFile(argv[i], kv);
        if (count == NULL) {
            return EXIT_FAILURE;
        }
        char * newName = computeOutputFileName(argv[i]);
        FILE *fp = fopen(newName, "w");
        if (fp == NULL) {
            perror("Can't write file.");
            return EXIT_FAILURE;
        }
        printCounts(count, fp);
        fclose(fp);
        free(newName);
        freeCounts(count);
    }
    freeKVs(kv);
    return EXIT_SUCCESS;
}
