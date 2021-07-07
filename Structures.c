//
// Created by kacpe on 7/1/2021.
//

#include "Structures.h"

#include <stdio.h>
#include <stdlib.h>
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

bool wordEquals(Word *word1, Word *word2)
{
    if (word1->word_type != word2->word_type) {
        // incompatible types
        return false;
    }
    if (word1->word_type == NUM) {
        return numberEquals(&word1->u.number, &word2->u.number);
    }
    if (word1->word_type == ALPHA) {
        return alphaEquals(word1->u.alpha, word1->u.alpha);
    }
    fprintf(stderr, "Trying to compare words of unknown types");
    exit(0);
}

bool alphaEquals(char *alpha1, char *alpha2)
{
    return strcasecmp(alpha1, alpha2);
}

bool numberEquals(Number *num1, Number *num2) {
    if (num1->val_type != num2->val_type) {
        // return false, because due to our conversion of strings such as "21.0" to integers,
        // there is no chance for such a number to be equal to a double with a non-zero fractional part
        return false;
    }
    return (numbercmp(num1, num2) == 0);
}

int alphacmp(const void *alpha1, const void *alpha2)
{
    uint len1 = strlen(alpha1);
    uint len2 = strlen(alpha2);
    uint smaller_len = (len1 <= len2)? len1 : len2;

    int res;
    for (uint i = 0; i < smaller_len; i++) {
        //TODO: przerobić wszytkie int i na uint i ;)
        res = primcmp(alpha1 + i, alpha2 + i);
        // character at &alpha1[i] has higher ASCII code than character at &alpha2[i] does
        if (res > 0) {
            return 1;
        }
        // character at &alpha1[i] has lower ASCII code than character at &alpha2[i] does
        else if (res < 0) {
            return -1;
        }
    }
    if (len1 < len2) {
        // alpha1 is initial substring of alpha2
        return 1;
    }
    if (len1 > len2) {
        // alpha2 is initial substring of alpha1
        return -1;
    }
    // strings match completely
    return 0;
}

int numbercmp(const void *num1, const void *num2)
{
    void *val1 = NULL, *val2 = NULL;

    switch (((Number*)num1)->val_type) {
        case UNSIGNED: {
            val1 = &((Number*)num1)->val._unsigned_int;
            val2 = &((Number*)num2)->val._unsigned_int;
            return primcmp(val1, val2);
            //TODO: czy to sprawdza wskazniki czy ich zawartosc?

        }
        case NEGATIVE: {
            val1 = &((Number*)num1)->val._negative_int;
            val2 = &((Number*)num2)->val._negative_int;
            return primcmp(val1, val2);
        }
        case DOUBLE: {
            val1 = &((Number*)num1)->val._double;
            val2 = &((Number*)num2)->val._double;
            return primcmp((Number*)val1, (Number*)val2);
        }
        default: fprintf(stderr, "Comparing numbers of unknown types.\n");
    }
}

int wordcmp(Word *word1, Word *word2)
{
    if (word1->word_type != word2->word_type) {
        // incompatible types
        fprintf(stderr, "Comparing incompatible word types.\n");
        return -1;
    }
    if (word1->word_type == NUM) {
        return numbercmp(&word1->u.number, &word2->u.number);
    }
    if (word1->word_type == ALPHA) {
        return alphacmp(word1->u.alpha, word1->u.alpha);
    }
    fprintf(stderr, "Trying to compare words of unknown types\n");
    exit(0);
    //TODO: czy więcej takich errorów dowalić w innych funkcjach?
}

bool WWCEquals(WordWithCount *wwc1, WordWithCount *wwc2)
{
    return (wordEquals(&wwc1->word, &wwc2->word) && wwc1->num_occurrences == wwc2->num_occurrences);
}

Line *createLine(char *line_as_str, uint line_num)
{
    Line *line = malloc(sizeof(Line)); //TODO: działa?
    line->line_num = line_num;

    // no need to create a multiset in the three cases below, since line contents are to be omitted
    if (!containsOnlyLegalChars(line_as_str)) {
        line->line_type = ILLEGAL;
        line->nums_multiset = NULL;
        line->alphas_multiset = NULL;
        return line;
    }
    if (line_as_str[0] == '#') {
        line->line_type = COMMENT;
        line->nums_multiset = NULL;
        line->alphas_multiset = NULL;
        return line;
    }
    if (containsOnlyWhiteSpace(line_as_str)) {
        line->line_type = EMPTY;
        line->nums_multiset = NULL;
        line->alphas_multiset = NULL;
        return line;
    }

    scv_vector *nums = scv_new(sizeof(WordWithCount), 1);
    scv_vector *alphas = scv_new(sizeof(WordWithCount), 1);
    int idx;
    //TODO: czy ta capacity ma znaczenie? Na co ją ustawić (na coś trzeba...)

    // splits string at first white-space regex
    char *ptr = strtok(line_as_str, " ");
    while (ptr != NULL) {
        Word w;
        // creates word from current substring
        createWordFromString(&w, line_as_str);
        if (w.word_type == ALPHA) {
            idx = indexOfWord(alphas, &w);       //TODO: ten ampersand to tu jest okej i wgl?
            if (idx == -1) {
                // word wasn't found - add it to the multiset
                WordWithCount *wwc = createWordWithCount(w);
                scv_push_back(alphas, wwc);
            }
            else {
                // word was found - increment its occurrences
                WordWithCount *wwc = GET_ITEM(WordWithCount, alphas, idx);
                wwc->num_occurrences++;
            }
        }
        else /*if(w.word_type == NUM)*/ {
            idx = indexOfWord(nums, &w);       //TODO: ten ampersand to tu jest okej i wgl?
            if (idx == -1) {
                // word wasn't found - add it to the multiset
                WordWithCount *wwc = createWordWithCount(w);
                scv_push_back(nums, wwc);
            }
            else {
                // word was found - increment its occurrences
                WordWithCount *wwc = GET_ITEM(WordWithCount, nums, idx);
                wwc->num_occurrences++;
            }
        }
        // advances the pointer to next white-space
        ptr = strtok(NULL, " ");
    }
    scv_shrink_to_fit(alphas);
    scv_shrink_to_fit(nums);
    line->line_type = LEGAL;
    line->alphas_multiset = alphas;
    line->nums_multiset = nums;
    return line;
}

uint indexOfWord(scv_vector *v, Word *query)
{
    for (int i = 0; i < scv_size(v); i++) {
        Word w = (GET_ITEM(WordWithCount, v, i))->word;

        if (wordEquals(query, &w)) {
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

void printErrorMessages(LineSet ls)
{
    scv_vector *lines = ls.lines;
    for (int i = 0; i < scv_size(lines); i++) {
        Line *l = GET_ITEM(Line, lines, i);
        if (l->line_type == ILLEGAL) {
            printf("ERROR %d\n", l->line_num);
            // TODO: wiadomo, że to ma być do pliku
        }
    }
}

void sortGroups(GroupSet *gs) {
    Group *group = NULL;
    for (int i = 0; i < scv_size(gs->groups); i++) {
         group = GET_ITEM(Group, gs->groups, i);
        qsort(group, scv_size(group->lines), sizeof(uint), primcmp);
    }
    qsort(gs->groups, scv_size(gs->groups), sizeof(Group), groupcmp);
}

void sortAlphas(scv_vector *alphas)
{
    qsort(alphas, scv_size(alphas), sizeof(char*), alphacmp);
}

void sortNums(scv_vector *nums)
{
    qsort(nums, scv_size(nums), sizeof(Number), numbercmp);
}

int primcmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int groupcmp(const void *a, const void *b) {
    return primcmp(&((Group *)a)->lines[0], &((Group *)b)->lines[0]);
}

void printGroups(GroupSet gs)
{
    Group *group = NULL;
    // TODO: wiadomo, że to ma być do pliku
    for (int i = 0; i < scv_size(gs.groups); i++) {
        group = GET_ITEM(Group, gs.groups, i);
        printGroup(*group);
    }
}

void printGroup(Group g)
{
    // TODO: wiadomo, że to ma być do pliku
    for (int i = 0; i < scv_size(g.lines); i++) {
        printf("%u ", *GET_ITEM(uint, g.lines, i));
    }
    printf("\n");
}

LineSet* getLines()
{
    LineSet *ls = calloc(1, sizeof(LineSet));
    //TODO: co z tą capacity?
    scv_vector *vect = scv_new(sizeof(Line), 1);

    Line *line = NULL;
    uint i = 1;

    char *line_as_str = NULL;
    size_t len = 0;
    ssize_t nread;

/*    while ((nread = getline(&line_as_str, &len, stdin)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line_as_str, nread, 1, stdout);
    }*/

    while ((nread = getline(&line_as_str, &len, stdin)) != -1) {
        line = createLine(line_as_str, i++);
        scv_push_back(vect, line);
    }

    ls->lines = vect;
    return ls;
}

GroupSet* generateGroups(LineSet ls)
{
    GroupSet *gs = malloc(sizeof(GroupSet));
    gs->groups = scv_new(sizeof(Group), 1);
    //TODO: czy w końcu capacity ma znaczenie?
    Group *group = NULL;
    Line *line_i = NULL, *line_j = NULL;

    for (int i = 0; i < scv_size(ls.lines); i++) {
        line_i = GET_ITEM(Line, ls.lines, i);
        if (!line_i->belongs_to_group) {
            // create new group based on current line, add current line to it
            group = malloc(sizeof(Group));
            group->lines = scv_new(sizeof(uint), 1);
            scv_push_back(group->lines, &line_i->line_num);

            for (int j = 0; j < scv_size(ls.lines); j++) {
                line_j = GET_ITEM(Line, ls.lines, j);
                if (
                        vectorEquals(line_i->alphas_multiset, line_j->alphas_multiset) &&
                        vectorEquals(line_i->nums_multiset, line_j->nums_multiset)) {
                    // Lines contain identical multisets of Numbers and NaNs
                    scv_push_back(group->lines, &line_j->line_num);
                    line_j->belongs_to_group = true;
                }
            }
        }
        // in case we didn't find matching lines, the group will be a singleton
        // i.e. all lines are in some sort of group - with oneself or with others
        line_i->belongs_to_group = true;
    }
    sortGroups(gs);
    return gs;
}

bool vectorEquals(scv_vector *v1, scv_vector *v2)
{
    if (scv_size(v1) != scv_size(v2)) {
        return false;
    }
    WordWithCount *wwc1 = NULL;
    WordWithCount *wwc2 = NULL;
    for (int i = 0; i < scv_size(v1); i++) {
        wwc1 = GET_ITEM(WordWithCount, v1, i);
        wwc2 = GET_ITEM(WordWithCount, v2, i);
        if (!WWCEquals(wwc1, wwc2)) {
            return false;
        }
    }
    return true;
}

char getcharBetter()
{
    int c;
    do
    {
        c = getchar();
    } while(isspace(c));

    return (char)c;
}