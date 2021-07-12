//
// Created by kacpe on 7/8/2021.
//

#ifndef IPP_MALE_ZADANIE_SIMILAR_LINES_H
#define IPP_MALE_ZADANIE_SIMILAR_LINES_H

#define SPACE 32
#define EXCLAMATION_MARK 33
#define TILDE 126
#define ZERO 48
#define SEVEN 55
#define NINE 57
#define A 65
#define F 70
/*#define CHECK_PTR(ptr) do { if(ptr == NULL) exit(1); } while(0)*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "structures.h"

/*
 * Returns true if str is same as "NaN" regardless of case, false otherwise.
 */
bool strEqualsWithNaN(char *str);

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
bool isOctalInteger(char *str);

/*
 * Returns true if number is written in base 10, false otherwise.
 */
bool isDecimalInteger(char *str);

/*
 * Returns true if number is written in base 16, false otherwise.
 */
bool isHexInteger(char *str);

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
bool strEquals(char *str1, char *str2);

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
int numbercmp(const void *num1, const void *num2);

/*
 * Function to compare two instances of CountedWord -
 * it compares strings according to alphanumeric precedence,
 * and number according to their value. Doesn't put into account
 * the occurrences field of the struct.
 */
int cwcmp(const void *cw1, const void *cw2);

/* U    N   U   S   E   D
 * Function to compare two words,
 * in order to sort them later on.
 *//*
int wordcmp(Word *word1, Word *word2);*/

/*
 * Compares CountedWord instances of both types: number or NaN.
 */
bool cwEquals(CountedWord *cw1, CountedWord *cw2);

/*
 * Initializes an instance of struct Word.
 * Always results in a NaN if unable to create a valid number in base 8/10/16.
 */
int createWordFromString(Word *word, char *str);

/*
 * Returns a non-negataive index if line contains queried word, -1 otherwise.
 */
size_t indexOfWord(scv_vector *v, Word *query);

/*
 * Creates an instance of struct CountedWord, with count set initially to 1.
 */
CountedWord* createCountedWord(Word w);

/*
 * Creates an instance of struct Line.
 * Its field words_multiset is non-NULL if and only if line_type is LEGAL.
 */
Line *createLine(char *line_as_str, size_t line_num);

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
void sortStrings(Line *line);

/*
 * Sorting function for a numbers multiset (in ascending order).
 */
void sortNums(Line *line);

/*
 * Generic function to compare two primitive types (i.e. int, float, char) and their derivatives,
 * in order to sort them later on.
 * Naturally, floating point number comparison is precision-dependent.
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

/* U    N   U   S   E   D
 * Reads the next character, omitting any white-space before it.
 */
/*char getcharBetter();*/

/*
 * Returns true if all elements (of type CountedWord) of both vectors return true on cwEquals(),
 * false otherwise.
 */
bool vectorEquals(scv_vector *v1, scv_vector *v2);

/*
 * Returns true if character belongs to set {'0', '1',...'9'}, false otherwise
 */
bool isDigit(char c);

/*
 * Calls getline(), removes the newline character in the line and replaces it with '\0'.
 */
ssize_t my_getline(char **_lineptr, size_t *_n);

/*
 * Prints all strings in strings.
 */
void printStrings(Line line);

#endif //IPP_MALE_ZADANIE_SIMILAR_LINES_H
