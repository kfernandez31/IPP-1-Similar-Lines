#include "group_handling.h"

/**
 * Returns index of the group that was created last in the line set.
 */
static void setHighestGroupNumber(LineSet *ls);

/**
 * Returns true if both lines' multisets are equal, false otherwise.
 */
static inline bool areLinesEqual(const Line *l1, const Line *l2);

/**
 * Compares CountedWord instances of both types: number or NaN.
 */
static inline bool cwEquals(const CountedWord *cw1, const CountedWord *cw2);

/**
 * Returns true if all elements (of type CountedWord) of both vectors return true on cwEquals(),
 * false otherwise.
 */
static bool vectorEquals(vector_t *v1, vector_t *v2);

/**
 * Returns true if both words are of the same type and have matching strings/number values,
 * false otherwise.
 */
static bool wordEquals(const Word *word1, const Word *word2);

/**
 * Function to compare two instances of CountedWord that hold
 * an instance of struct Number according to their numerical
 * values.
 */
static int cwNumbercmp(const void *cw1, const void *cw2);

/**
 * Function to compare two instances of struct Number
 * based on their value.
 */
static int numbercmp(const Number *num1, const Number *num2);

/**
 * Function to compare two instances of CountedWord that hold
 * an string according to their alphanumeric precedence in ASCII.
 */
static int cwNancmp(const void *cw1, const void *cw2);

/**
 * Function to compare two numbers of same val_type.
 */
static int sameTypecmp(const Number *num_a, const Number *num_b);

/**
 * Function to compare two numbers of different val_type.
 */
static int diffTypecmp(const Number *num_a, const Number *num_b);

static int sameTypecmp(const Number *num_a, const Number *num_b)
{
    if (num_a->val_type != num_b->val_type) {
        fprintf(stderr, "ERROR: Trying to compare numbers of differing types\n");
        exit(EXIT_FAILURE);
    }

    switch (num_a->val_type) {
        case UNSIGNED_INT:
            if (num_a->val._unsigned_int < num_b->val._unsigned_int) {
                return -1;
            }
            if (num_a->val._unsigned_int > num_b->val._unsigned_int) {
                return 1;
            }
            return 0;
        case NEGATIVE_INT:
            if (num_a->val._negative_int < num_b->val._negative_int) {
                return -1;
            }
            if (num_a->val._negative_int > num_b->val._negative_int) {
                return 1;
            }
            return 0;
        case DOUBLE:
            if (num_a->val._double < num_b->val._double) {
                return -1;
            }
            if (num_a->val._double > num_b->val._double) {
                return 1;
            }
            return 0;
        default:
            fprintf(stderr, "ERROR: Trying to compare numbers of unknown types\n");
            exit(EXIT_FAILURE);
    }
}

static int diffTypecmp(const Number *num_a, const Number *num_b)
{
    if (num_a->val_type == UNSIGNED_INT && num_b->val_type == NEGATIVE_INT) {
        return 1;
    }
    else if (num_a->val_type == UNSIGNED_INT && num_b->val_type == DOUBLE) {
        if ((long double)num_a->val._unsigned_int > LDBL_MAX || (long double)num_a->val._unsigned_int > num_b->val._double) {
            return 1;
        }
        else if ((long double)num_a->val._unsigned_int < LDBL_MIN || (long double)num_a->val._unsigned_int < num_b->val._double) {
            return -1;
        }
    }
    else if (num_a->val_type == NEGATIVE_INT && num_b->val_type == DOUBLE) {
        if ((long double)num_a->val._negative_int > LDBL_MAX || (long double)num_a->val._negative_int > num_b->val._double) {
            return 1;
        }
        else if ((long double)num_a->val._negative_int < LDBL_MIN || (long double)num_a->val._negative_int < num_b->val._double) {
            return -1;
        }
    }
    else if (num_a->val_type == NEGATIVE_INT && num_b->val_type == UNSIGNED_INT) {
        return -1 * diffTypecmp(num_b, num_a);
    }
    else if (num_a->val_type == DOUBLE && num_b->val_type == UNSIGNED_INT) {
        return -1 * diffTypecmp(num_b, num_a);
    }
    else if (num_a->val_type == DOUBLE && num_b->val_type == NEGATIVE_INT) {
        return -1 * diffTypecmp(num_b, num_a);
    }
    return 0;
}

static bool vectorEquals(vector_t *v1, vector_t *v2)
{
    if (v1->size != v2->size) {
        return false;
    }
    CountedWord *cw1 = NULL, *cw2 = NULL;

    for (size_t i = 0; i < v1->size; i++) {
        cw1 = GET_ITEM(CountedWord, v1, i);
        cw2 = GET_ITEM(CountedWord, v2, i);
        if (!cwEquals(cw1, cw2)) {
            return false;
        }
    }
    return true;
}

static bool wordEquals(const Word *word1, const Word *word2)
{
    if (word1->word_type != word2->word_type) {
        return false;    // incompatible types
    }
    if (word1->word_type == NUM_e) {

        return numberEquals(&word1->u.number, &word2->u.number);
    }
    if (word1->word_type == NAN_e) {
        return strEquals(word1->u.nan, word2->u.nan);
    }
    fprintf(stderr, "ERROR: Trying to compare words of unknown types\n");
    exit(EXIT_FAILURE);
}

static inline bool cwEquals(const CountedWord *cw1, const CountedWord *cw2)
{
    return wordEquals(&cw1->word, &cw2->word) && cw1->num_occurrences == cw2->num_occurrences;
}

static void setHighestGroupNumber(LineSet *ls) {
    int max = -1;
    for (int i = 0; i < (int)ls->lines->size; i++) {
        Line *line = GET_ITEM(Line, ls->lines, i);

        if (line->group_num > max) {
            max = line->group_num;
        }
    }
    ls->highest_group_num = max;
}

static inline bool areLinesEqual(const Line *l1, const Line *l2)
{
    return vectorEquals(l1->nansMultiset, l2->nansMultiset) && vectorEquals(l1->numbersMultiset, l2->numbersMultiset);
}

static int cwNumbercmp(const void *cw1, const void *cw2)
{
    Word w1 = ((CountedWord*)cw1)->word;
    Word w2 = ((CountedWord*)cw2)->word;
    return numbercmp(&w1.u.number, &w2.u.number);
}

static int numbercmp(const Number *num1, const Number *num2)
{
    if (num1->val_type == num2->val_type) {
        return sameTypecmp(num1, num2);
    }
    if (num1->val_type != num2->val_type) {
        return diffTypecmp(num1, num2);
    }
    fprintf(stderr, "ERROR: Trying to compare numbers of unknown types\n");
    exit(EXIT_FAILURE);
}

static int cwNancmp(const void *cw1, const void *cw2)
{
    Word w1 = ((CountedWord*)cw1)->word;
    Word w2 = ((CountedWord*)cw2)->word;

    return strcasecmp(w1.u.nan, w2.u.nan);
}



void generateGroups(LineSet *ls)
{
    int cur_group_idx = 0;

    for (size_t i = 0; i < ls->lines->size; i++) {
        Line *line_i = GET_ITEM(Line, ls->lines, i);

        if (line_i->line_type == LEGAL && line_i->group_num == NO_GROUP) {
            // line_i constitutes a new group
            line_i->group_num = cur_group_idx;

            for (size_t j = i + 1; j < ls->lines->size; j++) {
                Line *line_j = GET_ITEM(Line, ls->lines, j);

                // add any matching lines to line_i's group
                if (line_j->line_type == LEGAL && line_j->group_num == NO_GROUP && areLinesEqual(line_i, line_j)) {
                    line_j->group_num = cur_group_idx;
                }
            }
            cur_group_idx++;
        }
    }
    setHighestGroupNumber(ls);
}

bool numberEquals(const Number *num1, const Number *num2) {

    if (num1->val_type != num2->val_type) {
        return false;
    }
    return numbercmp(num1, num2) == 0;
}

void sortMultisets(Line *line)
{
    if (line->numbersMultiset != NULL) {
        qsort(line->numbersMultiset->items, line->numbersMultiset->size, sizeof(CountedWord), cwNumbercmp);
    }
    if (line->nansMultiset != NULL) {
        qsort(line->nansMultiset->items, line->nansMultiset->size, sizeof(CountedWord), cwNancmp);
    }
}