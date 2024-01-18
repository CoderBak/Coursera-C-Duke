#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
    char * newName = malloc(strlen(inputName) + 8);
    strcpy(newName, inputName);
    strcat(newName, ".counts");
    return newName;
}
