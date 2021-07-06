//
// Created by kacpe on 7/1/2021.
//

#include "Structures.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>


#define EXCLAMATION_MARK 33
#define TILDE 126
#define ZERO 48
#define SEVEN 55
#define NINE 57
#define A 65
#define F 70


bool hasFracPart(long double num)
{
    int truncated = (int)num;
    return (num != truncated);
}

bool isLegalChar(char c) {
    return (c >= EXCLAMATION_MARK && c <= TILDE);
}

bool containsOnlyLegalChars(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isLegalChar(str[i])) {
            return false;
        }
    }
    return true;
}

bool containsOnlyWhiteSpace(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
            return false;
        }
    }
    return true;
}

void printGroups(uint **group_arr)
{
    for (int i = 0; i < ARRAY_SIZE(group_arr); i++) {
        for (int j = 0; j < ARRAY_SIZE(group_arr[i]); i++) {
            printf("%val ", group_arr[i][j]);
        }
        printf("\n");
    }
}

bool wordcmp(Word word1, Word word2)
{
    if (word1.word_type != word2.word_type) {
        // incompatible types
        return false;
    }
    if (word1.word_type == NUM) {
        return numbercmp(word1.u.number, word2.u.number);
    }
    if (word1.word_type == ALPHA) {
        return strcasecmp(word1.u.alpha, word1.u.alpha);
    }
}

bool numbercmp(Number num1, Number num2) {
    if (num1.val_type != num2.val_type) {
        // Floaty postaci 21.0 są przerabiane wcześniej na inty, stąd sprawdzenie tego typu ma sens.
        return false;
    }
    switch (num1.val_type) {
        case UNSIGNED: return (num1.val._unsigned_int == num2.val._unsigned_int);
        case NEGATIVE: return (num1.val._negative_int == num2.val._negative_int);
        case DOUBLE: return (num1.val._double == num2.val._double);
    }
}

Line* createLine(char *line_as_str)
{
    Line *line = malloc(sizeof(Line)); //TODO: działa?

    // no need to create a multiset in the three cases below, since line contents are to be omitted
    if (!containsOnlyLegalChars(line_as_str)) {
        line->line_type = ILLEGAL;
        return line;
    }
    if (line_as_str[0] == '#') {
        line->line_type = COMMENT;
        return line;
    }
    if (containsOnlyWhiteSpace(line_as_str)) {
        line->line_type = EMPTY;
        return line;
    }

    scv_vector *multiset = scv_new(sizeof(WordWithCount), 1);
    //TODO: czy ta capacity ma znaczenie? Na co ją ustawić (na coś trzeba...)

    // splits string at first white-space regex
    char *ptr = strtok(line_as_str, " ");
    while (ptr != NULL) {
        Word w;
        // creates word from current substring
        createWordFromString(&w, line_as_str) ;

        int idx = indexOfWord(multiset, w);
        if (idx == -1) {
            // word wasn't found - add it to the multiset
            WordWithCount *wwc = createWordWithCount(w);
            scv_push_back(multiset, wwc);
        }
        else {
            // word was found - increment its occurrences
            WordWithCount *wwc = GET_ITEM(WordWithCount, multiset, idx);
            wwc->num_occurrences++;
        }
        // advances the pointer to next white-space
        ptr = strtok(NULL, " ");
    }
    scv_shrink_to_fit(multiset);
    line->line_type = LEGAL;
    return line;
}

size_t indexOfWord(scv_vector *v, Word query)
{
    for (int i = 0; i < scv_size(v); i++) {
        Word w = (GET_ITEM(WordWithCount, v, i))->word;

        if (wordcmp(query, w)) {
            return i;
        }
    }
    return -1;
}

WordWithCount* createWordWithCount(Word w) {
    WordWithCount *wwc = malloc(sizeof(WordWithCount));
    wwc->word = w;
    wwc->num_occurrences = 1;
    return wwc;
}

void createWordFromString(Word *word, char *str)
{
    // We may have encountered a negative number
    if (str[0] == '-') {
        if (isDecimal(str)) {
            word->u.number.val_type = NEGATIVE;
            word->u.number.val._negative_int = strtoll(str, NULL, DECIMAL);
        }
        else if (isDouble(str) && !isNan(str)) {
            long double ld = strtold(str, NULL);
            if (hasFracPart(ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = ld;
            }
            else {
                // Number looks like 5.0, 81.00000, etc.
                word->u.number.val_type = NEGATIVE;
                word->u.number.val._negative_int = ld;
            }
        }
    }
    else {
        if (isOctal(str)) {
            word->u.number.val_type = UNSIGNED;
            word->u.number.val._unsigned_int = strtoull(str, NULL, OCTAL);
        }
        if (isHex(str)) {
            word->u.number.val_type = UNSIGNED;
            word->u.number.val._unsigned_int = strtoull(str, NULL, HEX);
        }
    }

    // Couldn't convert given word to any type of number - set it to NaN
    word->word_type = ALPHA;
    word->u.alpha = str;
}

bool isDouble(char *str)
{
    int len;
    float ignore;
    int ret = sscanf(str, "%f %n", &ignore, &len);
    return (ret && len == strlen(str));
}

bool isDecimal(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!(str[i] >= ZERO && str[i] <= NINE)) {
            return false;
        }
    }
    return true;
}

bool isNan(char *str) {
    return strcasecmp(str, "NaN");
}

bool isOctal(char *str) {
    if (str[0] != '0') {
        return false;
    }
    for (int i = 0; i < strlen(str); i++) {
        if (!(str[i] >= ZERO && str[i] <= SEVEN)) {
            return false;
        }
    }
    return true;
}

bool isHex(char *str) {
    if (strlen(str) < 2) {
        // string can't contain prefix "0x"/"0X" because it's too short
        return false;
    }
    if (strlen(str) == 2) {
        // string is interpreted as 0, because strtoull will interpret it as such
        return true;
    }
    for (int i = 2; i < strlen(str); i++) {
        if (!((str[i] >= ZERO && str[i] <= SEVEN) || (str[i] >= A && str[i] <= F))) {
            return false;
        }
    }
    return true;
}

void printErrorMessages(scv_vector *lines)
{
    for (int i = 0; i < scv_size(lines); i++) {
        Line *l = GET_ITEM(Line, lines, i);
        if (l->line_type == ILLEGAL) {
            printf("ERROR %d", l->line_num);
            // TODO: wiadomo, że to ma być do pliku
        }
    }
}

void sortGroups(Group *group) {

}