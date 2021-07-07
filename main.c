#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Structures.h"

void foo() {
    // TODO: numeracja linijek od 1-ki
    char *line_as_str = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line_as_str, &len, stdin)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line_as_str, nread, 1, stdout);
        //printf("nread = %d, len = %d", nread, len);
    }
}

int main(void) {
    LineSet *ls = getLines();
    GroupSet *gs = generateGroups(*ls);

    sortGroups(gs);
    printGroups(*gs);
    printErrorMessages(*ls);

    //foo();
    return 0;
}


/*
char getcharBetter()
{
    int c;
    do
    {
        c = getchar();
    } while(isspace(c));

    return (char)c;
}*/
