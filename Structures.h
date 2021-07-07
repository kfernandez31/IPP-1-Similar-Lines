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
    //TODO: zmień nazwę na "nan"
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
    scv_vector *lines;
} Group;


// "kompiluję z flagą, która to optymalizuje" //TODO: poczytaj o tym :pp
//TODO: czy zostawiamy te vectory czy gdzieś zmienić na dynamiczne tablice?
typedef struct GroupSet
{
    scv_vector *groups;
} GroupSet;


// Instead of using an array in the structs below,
// I'll use a vector, to keep the number of allocations logarithmic
typedef struct Line
{
    LineType line_type;
    uint line_num;
    scv_vector *nums_multiset;
    scv_vector *alphas_multiset;
    bool belongs_to_group;
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
 * Returns true if both strings are identical, ignoring case.
 */
bool alphaEquals(char *alpha1, char *alpha2);

/*
 * Returns true if a true value is returned by comparing both number's values using "==".
 * Since numbers that return false in hasFracPart() are converted integers, no doubles will ever return true when
 * compared to an integer with this function.
 */
bool numberEquals(Number *num1, Number *num2);

/*
 * Returns true if both words are of the same type and have matching strings/number values,
 * false otherwise.
 */
bool wordEquals(Word *word1, Word *word2);

/*
 * Function to compare two instances of struct Number,
 * in order to sort them later on.
 */
int alphacmp(const void *alpha1, const void *alpha2);

/*
 * Function to compare two strings,
 * in order to sort them later on.
 */
int numbercmp(const void *num1, const void *num2);

/*
 * Function to compare two words,
 * in order to sort them later on.
 */
int wordcmp(Word *word1, Word *word2);

/*
 * Compares WordWithCount instances of both types: number or NaN.
 */
bool WWCEquals(WordWithCount *wwc1, WordWithCount *wwc2);

/*
 * Initializes an instance of struct Word.
 * Always results in a NaN if unable to create a valid number in base 8/10/16.
 */
void createWordFromString(Word *word, char *str);

/*
 * Returns a non-negataive index if line contains queried word, -1 otherwise.
 */
uint indexOfWord(scv_vector *v, Word *query);

/*
 * Creates an instance of struct WordWithCount, with count set initially to 1.
 */
WordWithCount* createWordWithCount(Word w);

/*
 * Creates an instance of struct Line.
 * Its field words_multiset is non-NULL if and only if line_type is LEGAL.
 */
Line *createLine(char *line_as_str, uint line_num);

/*
 * Prints into a file which lines contained illegal characters.
 */
void printErrorMessages(LineSet ls);

/*
 * Sorting function for groups (in ascending order).
 */
void sortGroups(GroupSet *gs);

/*
 * Sorting function for a NaN multiset (in alphanumeric order).
 */
void sortAlphas(scv_vector *alphas);

/*
 * Sorting function for a numbers multiset (in ascending order).
 */
void sortNums(scv_vector *nums);

/*
 * Generic function to compare two primitive types (i.e. int, float, char) and their derivatives,
 * in order to sort them later on.
 */
int primcmp(const void *a, const void *b);


/*
 * Function to compare two groups,
 * in order to sort them later on.
 */
int groupcmp(const void *a, const void *b);


/*
 * Prints all groups in gs.
 */
void printGroups(GroupSet gs);

/*
 * Prints a single group.
 */
void printGroup(Group g);

/*
 * Reads lines from standard input, converting each to an instance of struct Line, and adding them to an instance
 * of struct LineSet.
 */
LineSet* getLines();

/*
 * Creates groups of similar lines based on the LineSet instance created by getLines().
 * Example of line contents that will lead to a group being created:
 * {{9, abc}, {abc, 0x09}, {011, ABC}, {.9e1, aBc}, {ABc, 09}}
 */
GroupSet* generateGroups(LineSet ls);

/*
 * Reads the next character, omitting any white-space before it.
 */
char getcharBetter();

/*
 * Returns true if all elements (of type WordWithCount) of both vectors return true on WWCEquals(),
 * false otherwise.
 */
bool vectorEquals(scv_vector *v1, scv_vector *v2);

#endif //IPP_MALE_ZADANIE_STRUCTURES_H