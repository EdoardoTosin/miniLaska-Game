#include <stdio.h>
#include <stdlib.h> /* For exit() */

void readFile(/*string* printFile*/)
{
    char printFile[100], c; /* Temporary declaration of printFile */

    FILE *fptr;
    /* Open file */
    fptr = fopen(printFile, "r");
    if (fptr == NULL) {
        exit(0);
    }
    /* Read contents from file */
    c = fgetc(fptr);
    while (c != EOF) {
        printf ("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
    return;
}
