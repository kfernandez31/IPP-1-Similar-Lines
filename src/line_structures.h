#ifndef __LINE_STRUCTURES_H__
#define __LINE_STRUCTURES_H__

#include <stdbool.h>
#include <strings.h>
#include "vector.h"

#define NOT_FOUND -1
#define NO_GROUP -1

#define INIT_OCCURRENCES 1
#define EXAMPLE_IN_TOTAL_NUM_LINES 26


/*
 * Enum for the base in which an integer is represented.
 */
typedef enum Base
{
    OCTAL = 8,
    DECIMAL = 10,
    HEX = 16
} BASE;


/*
 * - IGNORED - line represents a comment (starting with "#") or is empty
 * - LEGAL/ILLEGAL - based on the legality of words in a given line.
 */
typedef enum LineType
{
    IGNORED,
    LEGAL,
    ILLEGAL
} LineType;

/*
 * Used for indicating whether the word is a number or not.
 */
typedef enum WordType
{
    NAN_e,
    NUM_e,
} WordType;

/*
 * Used to distinguish what type of number a Number struct is holding.
 */
typedef enum ValType
{
    UNSIGNED_INT,
    NEGATIVE_INT,
    DOUBLE
} ValType;

/*
 * Struct representing the contents of a word that is a number.
 */
typedef struct Number
{
    ValType val_type;
    union {
        long long unsigned _unsigned_int;
        long long int _negative_int;
        long double _double;
    } val;
} Number;

/*
 * Struct that represents a word.
 */
typedef struct Word
{
    WordType word_type;
    union {
        char* nan;
        Number number;
    } u;
} Word;

// Struct that represents a multiset entry - holds a word along with its occurrences in the multiset.
typedef struct CountedWord
{
    Word word;
    size_t num_occurrences;
} CountedWord;

/*
 * Struct representing a line.
 */
typedef struct Line
{
    LineType line_type;
    size_t line_num;
    vector_t *numbersMultiset;
    vector_t *nansMultiset;
    int group_num;
} Line;

/*
 * Struct holding all the provided lines in its vector (lines).
 */
typedef struct LineSet
{
    int highest_group_num; //todo: set this!
    vector_t *lines;
} LineSet;


/**
 * Returns true if both strings are identical, ignoring case.
 */
static inline bool strEquals(const char *str1, const char *str2)
{
    return (strcasecmp(str1, str2) == 0);
}

#endif //__LINE_STRUCTURES_H__