#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
    const char * const * p1 = vp1;
    const char * const * p2 = vp2;
    return strcmp(*p1, *p2);
}

//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
    qsort(data, count, sizeof(char *), stringOrder);
    for(size_t i = 0; i < count; i ++) {
        printf("%s", data[i]);
    }
}

void work(FILE *fp) {
    char ** lines = NULL;
    char * line = NULL;
    size_t len = 0, cnt = 0;
    while(getline(&line, &len, fp) >= 0) {
        lines = realloc(lines, (cnt + 1) * sizeof(*lines));
        lines[cnt ++] = line;
        line = NULL;
    }
    free(line);
    sortData(lines, cnt);
    for(size_t i = 0; i < cnt; i ++) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char ** argv) {
    FILE *fp;
    if (argc == 1) {
        fp = stdin;
        if (fp == NULL) {
            perror("Can't read file.");
            return EXIT_FAILURE;
        }
        work(fp);
        fclose(fp);
    } else {
        for(int i = 1; i <= argc - 1; i ++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror("Can't read file.");
                return EXIT_FAILURE;
            }
            work(fp);
            fclose(fp);
        }
    }
    return EXIT_SUCCESS;
}
