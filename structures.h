//
// Created by kacpe on 7/1/2021.
//

#ifndef IPP_MALE_ZADANIE_STRUCTURES_H
#define IPP_MALE_ZADANIE_STRUCTURES_H

#include "scv.h"

#define GET_ITEM(TYPE,vector,index) (TYPE*)scv_at(vector, index)

typedef enum Base
{
    OCTAL = 8,
    DECIMAL = 10,
    HEX = 16
} BASE;


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
    NAN_e = 0,
    NUM_e = 1,
} WordType;

typedef enum ValType
{
    UNSIGNED_INT = 1,
    NEGATIVE_INT = 2,
    DOUBLE = 4,

} ValType;

typedef struct Number
{
    ValType val_type;
    union {
        //TODO: zmienić to na long (?), chyba jeden typ wystarczy
        long long unsigned _unsigned_int;
        long long int _negative_int;
        long double _double;
    } val;
} Number;

typedef struct Word
{
    WordType word_type;
    union {
        char* nan;
        Number number;
    } u;
} Word;

// represents a set entry - holds a word along with its occurrences in the set
typedef struct CountedWord
{
    Word word;
    size_t num_occurrences;
} CountedWord;

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
    scv_vector *numbersMultiset;
    scv_vector *nansMultiset;
    //TODO: "jak będziesz miał powyżej 120 alokacji na example.c, to ci utną punkty"
    bool belongs_to_group;
} Line;

typedef struct LineSet
{
    scv_vector *lines;
} LineSet;

#endif //IPP_MALE_ZADANIE_STRUCTURES_H