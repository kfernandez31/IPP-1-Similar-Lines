//
// Created by kacpe on 7/8/2021.
//

#ifndef IPP_MALE_ZADANIE_TEST_H
#define IPP_MALE_ZADANIE_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../similar_lines.h"

typedef void TEST;

TEST TEST_isNan();
TEST TEST_isDouble();
TEST TEST_hasFracPart();
TEST TEST_isOctal();
TEST TEST_isDecimal();
TEST TEST_isHex();
TEST TEST_isLegalChar();
TEST TEST_containsOnlyLegalChars();
TEST TEST_containsOnlyWhiteSpace();
TEST TEST_alphaEquals();
TEST TEST_numberEquals();
TEST TEST_wordEquals();
TEST TEST_cwEquals();
TEST TEST_createWordFromString();
TEST TEST_createLine();
TEST TEST_indexOfWord();
TEST TEST_vectorEquals();
TEST TEST_sortMultisets();

TEST TEST_generateGroups();
TEST TEST_printGroups();
TEST TEST_sortGroups();
TEST TEST_groupcmp();

//TODO: te funkcje zostały, reszta śmiga:

TEST TEST_getLines();
TEST TEST_printGroupsAndErrorMessages();
//////////////////////////////////////////

#endif //IPP_MALE_ZADANIE_TEST_H
