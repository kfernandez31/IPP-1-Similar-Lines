//
// Created by kacpe on 7/1/2021.
//

#ifndef IPP_MALE_ZADANIE_STRUCTURES_H
#define IPP_MALE_ZADANIE_STRUCTURES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "scv.h"

#define GET_ITEM(TYPE,vector,index) (TYPE*)scv_at(vector, index)
//#define ARRAY_SIZE(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define ARRAY_SIZE(_Array) (sizeof(_Array) / sizeof((_Array)[0]))

typedef enum Base
{
    OCTAL = 8,
    DECIMAL = 10,
    HEX = 16
} BASE; // TODO: capslock


/*
 * - COMMENT if line.as_text starts with "#",
 * - EMPTY if line.as_text is composed only of white-space,
 * - LEGAL/ILLEGAL based on the legality of words in a given line.
 */
typedef enum LineType
{
    //TODO: właściwie to EMPTY/COMMENT mogłyby być chyba tym samym
    EMPTY = 0,
    COMMENT = 1,
    LEGAL = 2,
    ILLEGAL = 3
} LineType;

typedef enum WordType
{
    ALPHA = 0,
    NUM = 1,
} WordType;

typedef enum ValType
{
    UNSIGNED = 0,
    NEGATIVE = 1,
    DOUBLE = 2,
} ValType;

typedef struct Number
{
    ValType val_type;
    union {
        long long unsigned _unsigned_int;
        long long int _negative_int;
        long double _double;
    } val;
} Number;

typedef struct Word
{
    WordType word_type;
    union {
        char* alpha;
        Number number;
    } u;
} Word;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// represents a set entry - holds a word along with its occurrences in the set
typedef struct WordWithCount
{
    Word word;
    uint num_occurrences;
} WordWithCount;

typedef struct Group
{
    uint *lines;
    size_t num_lines;
} Group;


// "kompiluję z flagą, która to optymalizuje" //TODO: poczytaj o tym :pp
typedef struct GroupSet
{
    Group *groups;
    size_t num_groups;
} GroupSet;


// Instead of using an array in the structs below,
// I'll use a vector, to keep the number of allocations logarithmic
typedef struct Line
{
    char *as_text;
    LineType line_type;
    uint line_num;
    scv_vector *words_multiset;
} Line;

typedef struct LineSet
{
    scv_vector *lines;
} LineSet;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Returns true if str is same as "NaN" irregardless of case.
 */
bool isNan(char *str);

/*
 * Returns true if str represents a double.
 * Handles all kinds of doubles, i.e: 0.25, .33, -1E-1, INF, -INF, 21.37, etc.
 * Actually, the function also handles NaN (written irregardless of case), but according to the assignment,
 * I'll treat NaN as a non-number in createWordFromString().
 */
bool isDouble(char *str);

/*
 * Returns true if number is written in base 8, false otherwise.
 */
bool isOctal(char *str);

/*
 * Returns true if number is written in base 10, false otherwise.
 */
bool isDecimal(char *str);

/*
 * Returns true if number is written in base 16, false otherwise.
 */
bool isHex(char *str);

/*
 * Returns true on numbers containing anything non-zero in their fractional part, false otherwise.
 */
bool hasFracPart(long double num);

/*
 * Returns true on characters with ASCII codes 33-126, false otherwise.
 * There won't be any words containing white-space, since we split lines at " ", hence no handling of code 32.
 */
bool isLegalChar(char c);

/*
 * Returns true if all characters of string return true on a call of isLegalChar(), false otherwise.
 */
bool containsOnlyLegalChars(char *str);

/*
 * Returns true if all characters of string return true on a call of isspace(), false otherwise.
 */
bool containsOnlyWhiteSpace(char *str);

/*
 * Returns true if a true value is returned by comparing both number's values using "==".
 * Since numbers that return false in hasFracPart() are converted integers, no doubles will ever return true when
 * compared to an integer with this function.
 */
bool numbercmp(Number num1, Number num2);

/*
 * A wrapper for comparing words; be it number-words or nan-words.
 */
bool wordcmp(Word word1, Word word2);

/*
 * Initializes an instance of struct Word.
 * Always results in a NaN if unable to create a valid number in base 8/10/16.
 */
void createWordFromString(Word *word, char *str);

/*
 * Returns a non-negataive index if line contains queried word, -1 otherwise.
 */
size_t indexOfWord(scv_vector *v, Word query);

/*
 * Creates an instance of struct WordWithCount, with count set initially to 1.
 */
WordWithCount* createWordWithCount(Word w);

/*
 * Creates an instance of struct Line.
 * Its field words_multiset is non-NULL if and only if line_type is LEGAL.
 */
Line* createLine(char *line_as_str);

/*
 * Prints into a file which lines contained illegal characters.
 */
void printErrorMessages(scv_vector *lines);

/*void printGroups(GroupSet set);
void printGroup(Group *group);

Line* createLineVector(FILE file);    //creates an array of Lines for the entire file
uint* createGroupVector(FILE file);    //creates an array of indices of a group
scv_vector* createVector(FILE file);//creates uint[] for a Group*/

void sortGroups(Group *group);


#endif //IPP_MALE_ZADANIE_STRUCTURES_H
