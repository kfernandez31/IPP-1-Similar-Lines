//
// Created by kacpe on 7/8/2021.
//

#include "test.h"


TEST TEST_isNan()
{
    printf("=== Testing strEqualsWithNaN() ===\n");
    bool res;
    char *str;

    str = "nan";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "NAN";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "Nan";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "nAn";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "naN";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "NaN";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "NAn";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "nAN";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);

    str = "nANa";
    res = strEqualsWithNaN(str);
    printf("%s : %d\n", str, res);
}

TEST TEST_isDouble()
{
    printf("=== Testing isDouble() ===\n");
    bool res;
    char *str;

    str = "nan";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "NAN";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "Nan";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "nAn";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "naN";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "NaN";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "NAn";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "nAN";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "nANa";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "nAN123";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "123";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "123.45";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "123.4f";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "0.25";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = ".33";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "-1E-1";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "INF";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "-INF";
    res = isDouble(str);
    printf("%s : %d\n", str, res);

    str = "+inf";
    res = isDouble(str);
    printf("%s : %d\n", str, res);
}

TEST TEST_hasFracPart()
{
    printf("=== Testing hasFracPart() ===\n");
    bool res;
    char *str;
    long double ld;

    str = "nan";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "hehexd";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "NAN";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "Nan";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "nAn";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "naN";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "NaN";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "NAn";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "nAN";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "nANa";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "nAN123";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "123";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "123.45";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "123.4f";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "0.25";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = ".33";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "-1E-1";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "INF";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "-INF";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "+inf";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);

    str = "10e6";
    ld = strtold(str, NULL);
    res = hasFracPart(ld);
    printf("%s : %d\n", str, res);
}

TEST TEST_isOctal()
{
    printf("=== Testing isOctalInteger() ===\n");
    bool res;
    char *str;
    long double ld;

    str = "nan";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "hehexd";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "NAN";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "NaN";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "123";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "123.45";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "123.4f";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0.25";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = ".33";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-1E-1";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "INF";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-INF";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "+inf";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "10e6";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0177";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0001";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "42";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-1";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "+123";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-0";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-02";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0X0001";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0x0001";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0XABC";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0xABC";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "10000000000000000";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0xFFFFFFFFFFFFFFFF";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "18446744073709551615";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "18446744073709551616";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "01777777777777777777777";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "02000000000000000000000";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0";
    res = isOctalInteger(str);
    printf("%s : %d\n", str, res);
}

TEST TEST_isDecimal()
{
    printf("=== Testing isDecimalInteger() ===\n");
    bool res;
    char *str;
    long double ld;

    str = "nan";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "hehexd";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "NAN";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "NaN";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "123";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "123.45";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "123.4f";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0.25";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = ".33";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-1E-1";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "INF";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-INF";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "+inf";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "10e6";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0177";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0001";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "42";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-1";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "+123";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-0";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "-02";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0X0001";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0x0001";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0XABC";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0xABC";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "10000000000000000";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0xFFFFFFFFFFFFFFFF";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "18446744073709551615";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "18446744073709551616";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "01777777777777777777777";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "02000000000000000000000";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);

    str = "0";
    res = isDecimalInteger(str);
    printf("%s : %d\n", str, res);
}

TEST TEST_isHex()
{
    printf("=== Testing isHexInteger() ===\n");
    bool res;
    char *str;
    long double ld;

    str = "nan";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "hehexd";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "NAN";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "NaN";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "123";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "123.45";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "123.4f";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0.25";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = ".33";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "-1E-1";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "INF";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "-INF";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "+inf";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "10e6";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0177";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0001";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "42";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "-1";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "+123";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "-0";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "-02";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0X0001";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0x0001";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0XABC";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0xABC";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "10000000000000000";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0xFFFFFFFFFFFFFFFF";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "18446744073709551615";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "18446744073709551616";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "01777777777777777777777";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "02000000000000000000000";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);

    str = "0";
    res = isHexInteger(str);
    printf("%s : %d\n", str, res);
}

TEST TEST_isLegalChar()
{
    printf("=== Testing isLegalChar() ===\n");
    bool res;
    char c;

    c = '0';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);

    c = '~';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);

    c = 'A';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);

    c = 'á';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);

    c = 'ƒ';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);
}

TEST TEST_containsOnlyLegalChars()
{
    printf("=== Testing containsOnlyLegalChars() ===\n");
    bool res;
    char *c;

    c = "0~";
    res = containsOnlyLegalChars(c);
    printf("%s : %d\n", c, res);

    c = "~á";
    res = containsOnlyLegalChars(c);
    printf("%s : %d\n", c, res);

    c = "ƒá";
    res = containsOnlyLegalChars(c);
    printf("%s : %d\n", c, res);
}

TEST TEST_containsOnlyWhiteSpace()
{
    printf("=== Testing containsOnlyWhiteSpace() ===\n");
    bool res;
    char *c;

    c = "0~";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);

    c = "~á";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);

    c = "ƒá";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);

    c = "";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);

    c = " ";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);

    c = "\t \n kk";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);

    c = "\t \n kk";
    res = containsOnlyWhiteSpace(c);
    printf("%s : %d\n", c, res);
}

TEST TEST_alphaEquals()
{
    printf("=== Testing strEquals() ===\n");
    bool res;
    char *c1, *c2;

    c1 = "0~";
    c2 = "~0";
    res = strEquals(c1, c2);
    printf("%s %s : %d\n", c1, c2, res);

    c1 = "~á";
    c2 = "~á";
    res = strEquals(c1, c2);
    printf("%s %s : %d\n", c1, c2, res);

    c1 = "AbC";
    c2 = "Abc";
    res = strEquals(c1, c2);
    printf("%s %s : %d\n", c1, c2, res);
}

TEST TEST_numberEquals()
{
    printf("=== Testing numberEquals() ===\n");
    bool res;

    Number *n1 = NULL, *n2 = NULL;
    Number *temp1 = malloc(sizeof(Number));
    Number *temp2 = malloc(sizeof(Number));
    if (temp1 == NULL || temp2 == NULL) {
        fprintf(stderr, "Ran out of memory!\n");
        exit(1);
    }
    n1 = temp1;
    n2 = temp2;

    n1->val_type = DOUBLE;
    n1->val._double = 5.5;
    n2->val_type = DOUBLE;
    n2->val._double = 20000.0;
    res = numberEquals(n1, n2);
    //res = primcmp(&n1->val._double, &n2->val._double);
    printf("res = %d\n", res);

    n1->val_type = NEGATIVE_INT;
    n1->val._negative_int = -55;
    n2->val_type = NEGATIVE_INT;
    n2->val._negative_int = -20000;
    res = numberEquals(n1, n2);
    //res = primcmp(&n1->val._negative_int, &n2->val._negative_int);
    printf("res = %d\n", res);

    n1->val_type = UNSIGNED_INT;
    n1->val._unsigned_int = 55;
    n2->val_type = UNSIGNED_INT;
    n2->val._unsigned_int = 20000;
    res = numberEquals(n1, n2);
    //res = primcmp(&n1->val._unsigned_int, &n2->val._unsigned_int);
    printf("res = %d\n", res);

    n1->val_type = DOUBLE;
    n1->val._double = 55;
    n2->val_type = UNSIGNED_INT;
    n2->val._unsigned_int = 55;
    res = numberEquals(n1, n2);
    //res = primcmp(&n1->val._double, &n2->val._double);
    printf("res = %d\n", res);


    n1->val_type = DOUBLE;
    n1->val._double = 55.67;
    n2->val_type = DOUBLE;
    n2->val._double = 55.67;
    res = numberEquals(n1, n2);
    //res = primcmp(&n1->val._double, &n2->val._double);
    printf("res = %d\n", res);

    free(n1);
    free(n2);
}

TEST TEST_wordEquals()
{
    printf("=== Testing wordEquals() ===\n");
    bool res;
    Word w1, w2;

    w1.word_type = NUM;
    w2.word_type = NUM;
    w1.u.number.val_type = DOUBLE;
    w2.u.number.val_type = DOUBLE;
    w1.u.number.val._double = 5.5;
    w2.u.number.val._double = 20000.01;
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NUM;
    w2.word_type = NUM;
    w1.u.number.val_type = NEGATIVE_INT;
    w2.u.number.val_type = DOUBLE;
    w1.u.number.val._double = 5.5;
    w2.u.number.val._double = 5.5;
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NUM;
    w2.word_type = NAN;
    w1.u.number.val_type = DOUBLE;
    w1.u.number.val._double = 5.5;
    w2.u.nan = "witam";
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NAN;
    w2.word_type = NAN;
    w1.u.nan = "siema";
    w2.u.nan = "hej";
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NAN;
    w2.word_type = NAN;
    w1.u.nan = "dziendobry";
    w2.u.nan = "DziEndobRy";
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);
}

TEST TEST_cwEquals()
{
    printf("=== Testing cwEquals() ===\n");
    bool res;
    CountedWord cw1, cw2;

    cw1.word.word_type = NUM;
    cw2.word.word_type = NUM;
    cw1.word.u.number.val_type = DOUBLE;
    cw2.word.u.number.val_type = DOUBLE;
    cw1.word.u.number.val._double = 5.5;
    cw2.word.u.number.val._double = 666.666;
    cw1.num_occurrences = 15;
    cw2.num_occurrences = 20;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    cw1.word.word_type = NAN;
    cw2.word.word_type = NAN;
    cw1.word.u.nan = "dziendobry";
    cw2.word.u.nan = "DziEndobRy";
    cw1.num_occurrences = 0;
    cw2.num_occurrences = 1;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    cw1.word.word_type = NUM;
    cw2.word.word_type = NUM;
    cw1.word.u.number.val_type = DOUBLE;
    cw2.word.u.number.val_type = DOUBLE;
    cw1.word.u.number.val._double = 5.5;
    cw2.word.u.number.val._double = 666.666;
    cw1.num_occurrences = 15;
    cw2.num_occurrences = 15;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    cw1.word.word_type = NAN;
    cw2.word.word_type = NAN;
    cw1.word.u.nan = "dziendobry";
    cw2.word.u.nan = "DziEndobRy";
    cw1.num_occurrences = 0;
    cw2.num_occurrences = 0;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    Word w1, w2;
    createWordFromString(&w1, "21e3");
    createWordFromString(&w2, "21000");

    CountedWord *cwptr1 = createCountedWord(w1);
    CountedWord *cwptr2 = createCountedWord(w2);
    res = cwEquals(cwptr1, cwptr2);
    printf("res = %d\n", res);
}

TEST TEST_createWordFromString()
{
    printf("=== Testing createWordFromString() ===\n");
    Word w;
    char *str;

    str = "01777";
    createWordFromString(&w, str); // ok

    str = ".33";
    createWordFromString(&w, str); // ok

    str = "104";
    createWordFromString(&w, str); // ok

    str = "+104";
    createWordFromString(&w, str); // ok

    str = "-104";
    createWordFromString(&w, str);  // ok

    str = "+104.05";
    createWordFromString(&w, str);  // ok

    str = "+104.0";
    createWordFromString(&w, str);  // ok

    str = "-104.05";
    createWordFromString(&w, str);  // ok

    str = "siema";
    createWordFromString(&w, str); // ok

    str = "123wololo456";
    createWordFromString(&w, str); // ok

    str = "10EE4";
    createWordFromString(&w, str); // ok

    str = "10E4";
    createWordFromString(&w, str); // ok

    str = "NaN";
    createWordFromString(&w, str); // ok

    str = "+nan";
    createWordFromString(&w, str); // ok

    str = "-NAN";
    createWordFromString(&w, str); // ok

    str = "INF";
    createWordFromString(&w, str); // ok

    str = "-INF";
    createWordFromString(&w, str); // ok

    str = "+inf";
    createWordFromString(&w, str); // ok

    str = "10e-1";
    createWordFromString(&w, str); // ok

    str = "2.45e-6";
    createWordFromString(&w, str); // ok

    str = "0x";
    createWordFromString(&w, str); // ok

    str = "0X";
    createWordFromString(&w, str); // ok

    str = "-0XFF";
    createWordFromString(&w, str); // ok

    str = "+0XFF";
    createWordFromString(&w, str); // ok

    str = "--1.04";
    createWordFromString(&w, str); // ok

    str = "--1";
    createWordFromString(&w, str); // ok

    int debug = 45;
}

TEST TEST_createLine()
{
/*    printf("Please enter a line:\n");
    char *str = NULL;
    size_t len = 0;
    ssize_t strSize = my_getline(&str, &len);
    str[strcspn(str, "\n")] = '\0';

    printf("You entered %s, which has %zu chars.\n", str, strSize - 1);
    printf("%lu\n", strlen(str));
    free(str);*/

    char *str = NULL;
    size_t len = 0;
    ssize_t strSize = my_getline(&str, &len);
    str[strcspn(str, "\n")] = '\0';
    Line *line = createLine(str, 1);
    printStrings(*line);

    int x = 3;
}
TEST TEST_vectorEquals()
{
    char arr1[] = "0xABC siemka O3rhue2bVp13 0XFFFFFF 16777215 01777 1023.0";
    char arr2[] = "2748 SiEmKa o3RhUe2bvP13 16777.215E3 1677721500E-2 1023 0x3FF";
    char arr3[] = "2748 16777.215E3 1677721500E-2 1023 1023 1023 0x3FF";
    char arr4[] = "2748 16777.215E3 1677721500E-2 1677721500E-2 1023 1023 0x3FF 0x3FF";

    Line *line1 = createLine(arr1, 1);
    Line *line2 = createLine(arr2, 2);
    Line *line3 = createLine(arr2, 3);
    Line *line4 = createLine(arr2, 4);
    bool res;

    res = vectorEquals(line1->nums_multiset, line2->nums_multiset);
    printf("%d\n", res);
    res = vectorEquals(line1->nums_multiset, line1->strings_multiset);
    printf("%d\n", res);
    res = vectorEquals(line1->strings_multiset, line2->strings_multiset);
    printf("%d\n", res);
    res = vectorEquals(line2->strings_multiset, line3->strings_multiset);
    printf("%d\n", res);
    res = vectorEquals(line2->strings_multiset, line4->strings_multiset);
    printf("%d\n", res);

    //printStrings(line1->strings_multiset);
}


TEST TEST_sortStrings()
{
/*    scv_vector *vect = scv_new(sizeof(char**), INIT_CAP);

    char *s1 = malloc(sizeof(char) * (strlen("aaaaaaaaa") + 1));
    strcpy(s1, "aaaaaaaaa");
    scv_push_back(vect, &s1);

    char *s2 = malloc(sizeof(char) * (strlen("bbbbbbbbb") + 1));
    strcpy(s2, "bbbbbbbbb");
    scv_push_back(vect, &s2);

    char *s3 = malloc(sizeof(char) * (strlen("ccccccccc") + 1));
    strcpy(s3, "ccccccccc");
    scv_push_back(vect, &s3);

    char *s4 = malloc(sizeof(char) * (strlen("ddddddddd") + 1));
    strcpy(s4, "ddddddddd");
    scv_push_back(vect, &s4);

    scv_shrink_to_fit(vect);
    */

/*    char a[] = "aaaaaaaa";
    char b[] = "bbbbbbbb";
    char c[] = "cccccccc";
    char d[] = "dddddddd";
    scv_push_back(vect, a);
    scv_push_back(vect, b);
    scv_push_back(vect, c);
    scv_push_back(vect, d);*/
//    scv_push_back(vect, "abcdef");
//    scv_push_back(vect, "kakfafak");
//    scv_push_back(vect, "tryteyrt");
//    scv_push_back(vect, "tryt");
//    scv_push_back(vect, "sieeeaafaf");
//    scv_push_back(vect, "zakfmefo");
//    scv_push_back(vect, "waeuiufhwevw");
//    scv_push_back(vect, "xxxxxxxxxx");
//    scv_push_back(vect, "zak");
/*    scv_shrink_to_fit(vect);
    printStrings(vect);*/

    //sortStrings(vect);
    //printStrings(vect);
    char arr[] = "zak 0xABC siemka waeuiufhwevw tryt x sieeeaafaf O3rhue2bVp13 tryteyrt zakfmefo 0XFFFFFF xxxxxxxxxx 16777215 01777 1023.0 abcdef\n";
    Line *line = createLine(arr, 1);
    printStrings(*line);

    sortStrings(line);
    printStrings(*line);
}
TEST TEST_sortNums()
{

}

TEST TEST_generateGroups()
{
    LineSet *ls = malloc(sizeof(LineSet));
    ls->lines = scv_new(sizeof(Line), INIT_CAP);

    GroupSet *gs = NULL;
    char arr1[] = "0xABC siemka O3rhue2bVp13 0XFFFFFF 16777215 01777 1023.0";
    char arr2[] = "2748 SiEmKa o3RhUe2bvP13 16777.215E3 1677721500E-2 1023 0x3FF";
    char arr3[] = "zak 0xABC siemka waeuiufhwevw tryt x sieeeaafaf O3rhue2bVp13 tryteyrt zakfmefo 0XFFFFFF xxxxxxxxxx 16777215 01777 1023.0 abcdef\n";
    char arr4[] = "2748 16777.215E3 1677721500E-2 1023 1023 1023 0x3FF";
    char arr5[] = "2748 16777.215E3 1677721500E-2 1677721500E-2 1023 1023 0x3FF 0x3FF";

    Line *l1 = createLine(arr1, 1);
    Line *l2 = createLine(arr2, 2);
    Line *l3 = createLine(arr3, 3);
    Line *l4 = createLine(arr4, 4);
    Line *l5 = createLine(arr5, 5);

    scv_push_back(ls->lines, l1);
    scv_push_back(ls->lines, l2);
    scv_push_back(ls->lines, l3);
    scv_push_back(ls->lines, l4);
    scv_push_back(ls->lines, l5);
    scv_shrink_to_fit(ls->lines);
    gs = generateGroups(*ls);
    printGroups(*gs);
}
TEST TEST_printGroups()
{

}
TEST TEST_groupcmp()
{

}
TEST TEST_sortGroups()
{

}
TEST TEST_getLines()
{

}
TEST TEST_printErrorMessages()
{

}