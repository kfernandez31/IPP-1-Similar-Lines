#include "parsing_input.h"
#include "group_handling.h"
#include "printing_output.h"

int main(void) {
    LineSet ls;

    getLines(&ls);
    generateGroups(&ls);

    printGroups(&ls);
    printErrorMessages(&ls);

    freeLineSet(&ls);

    exit(EXIT_SUCCESS);
}
