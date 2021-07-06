#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "Structures.h"


/*
 * Hex, szesnastkowe mogą mieć "-" (ale nie "+") przed sobą //TODO: niezgodne z treścią
 * zmiennoprzecinkowe i inty mogą mieć zarówno "+" jak i "-" przed sobą
 * Liczba spoza zakresu - traktowana jako INF/-INF (?)
 * +/-INF to liczba (int)
 *
 */
void test(char *str) {
    int len;
    float ignore;
    int ret = sscanf(str, "%f %n", &ignore, &len);
    printf("'%s'\t\t: %d\n", str, ret && len==strlen(str));
}

int main(void) {
    test("5.5");
    test("5.5 ");
    test(" 5.5 ");
    test("hello");
    test("123.ok");
    test("");
    test("-1E-1");
    test("INF");
    test("-INF");
    test("37363.6E3");
    test(".33");
    test("NAN");
    test("nan");
    test("NaN");
    test("nAn");
    test("nAnn");
    return 0;
}

/*
char getcharBetter()
{
    int c;
    do
    {
        c = getchar();
    } while(isspace(c));

    return (char)c;
}

// Creates an array of all non-white space characters read, returns to how many cards the input translates to.
int fillArray(int* array, const int size)
{
    char input = '\0';
    char readChars[MAX_DECK_SIZE * NUMBER_CHARS_LENGTH] = {'\0'};
    int read_chars_index = 0;
    int cards_count = 0;

    while((input = getcharBetter()) != EOF)
    {
        readChars[read_chars_index++] = input;
    }
    cards_count = read_chars_index / NUMBER_CHARS_LENGTH;

    for(int i = 0; i < size && i < cards_count; i++)
    {
        char buffer[NUMBER_CHARS_LENGTH + 1] = {'\0'};
        memcpy(buffer, &readChars[i * NUMBER_CHARS_LENGTH], NUMBER_CHARS_LENGTH);
        array[i] = atoi(buffer);
    }
    return cards_count;
}*/