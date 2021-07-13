#include <stdio.h>
#include <string.h>
#include "test/test.h"
#include "similar_lines.h"

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
    //TEST_isNan();     // test passed
    //TEST_isDouble();      // test passed
    //TEST_hasFracPart();       // test passed
    //TEST_isLegalChar();     // test passed
    //TEST_containsOnlyLegalChars();     // test passed
    //TEST_containsOnlyWhiteSpace();     // test passed
    //TEST_alphaEquals();       // test passed
    //TEST_numberEquals();       // test passed
    //TEST_wordEquals();      // test passed
    // alphacmp() działa, numbercmp() też
    //TEST_cwEquals();     // test passed

    //TEST_isOctal();       // test passed
    //TEST_isDecimal();       // test passed
    //TEST_isHex();       // test passed
    //TEST_vectorEquals(); // test passed
    // TEST_sortMultisets();    // test passed

    //TEST_createWordFromString();    // test passed (?)
    //TEST_createLine();    // test passed (?)
    // hasFracPart(), isDouble(), isLegalChar(), createCountedWord(), indexOfWord() też

    //TEST_generateGroups();
    TEST_printErrorMessages();

    return 0;
    //TODO: funkcja do kasowania elementów vect, i samego vect
    // ogólnie dużo free()
}

/*
    LineSet ls;
    getLines(&ls);
    GroupSet gs;
    getGroups(&gs);

    sortGroups(gs);
    printGroups(*gs);

    printErrorMessages(*ls);
*/

/*    scv_vector *v = scv_new(sizeof(char), 0);

    char *str = "siemaneczkosiemaneczkosiemaneczkosiemaneczkosiemaneczkosiemaneczkosiemaneczkosiemaneczkosiemaneczko\0";

    for (int i = 0; i < strlen(str); i++) {
        scv_push_back(v, &str[i]);
    }
    scv_shrink_to_fit(v);*/

