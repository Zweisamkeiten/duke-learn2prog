#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
    // outfileName is input + ".counts", so add 7 to its length
    // add 1 more ofr '\0'
    char * outFileName = malloc((strlen(inputName) + 7 + 1) * sizeof(*outFileName));
    strcpy(outFileName, inputName);
    strcat(outFileName, ".counts");
    return outFileName;
}
