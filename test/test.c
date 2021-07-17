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

    str = "NAN_e";
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

    str = "NAN_e";
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

/*    c = 'á';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);

    c = 'ƒ';
    res = isLegalChar(c);
    printf("%c : %d\n", c, res);*/
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
    //res = my_memcmp(&n1->val._double, &n2->val._double);
    printf("res = %d\n", res);

    n1->val_type = NEGATIVE_INT;
    n1->val._negative_int = -55;
    n2->val_type = NEGATIVE_INT;
    n2->val._negative_int = -20000;
    res = numberEquals(n1, n2);
    //res = my_memcmp(&n1->val._negative_int, &n2->val._negative_int);
    printf("res = %d\n", res);

    n1->val_type = UNSIGNED_INT;
    n1->val._unsigned_int = 55;
    n2->val_type = UNSIGNED_INT;
    n2->val._unsigned_int = 20000;
    res = numberEquals(n1, n2);
    //res = my_memcmp(&n1->val._unsigned_int, &n2->val._unsigned_int);
    printf("res = %d\n", res);

    n1->val_type = DOUBLE;
    n1->val._double = 55;
    n2->val_type = UNSIGNED_INT;
    n2->val._unsigned_int = 55;
    res = numberEquals(n1, n2);
    //res = my_memcmp(&n1->val._double, &n2->val._double);
    printf("res = %d\n", res);


    n1->val_type = DOUBLE;
    n1->val._double = 55.67;
    n2->val_type = DOUBLE;
    n2->val._double = 55.67;
    res = numberEquals(n1, n2);
    //res = my_memcmp(&n1->val._double, &n2->val._double);
    printf("res = %d\n", res);

    free(n1);
    free(n2);
}

TEST TEST_wordEquals()
{
    printf("=== Testing wordEquals() ===\n");
    bool res;
    Word w1, w2;

    w1.word_type = NUM_e;
    w2.word_type = NUM_e;
    w1.u.number.val_type = DOUBLE;
    w2.u.number.val_type = DOUBLE;
    w1.u.number.val._double = 5.5;
    w2.u.number.val._double = 20000.01;
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NUM_e;
    w2.word_type = NUM_e;
    w1.u.number.val_type = NEGATIVE_INT;
    w2.u.number.val_type = DOUBLE;
    w1.u.number.val._double = 5.5;
    w2.u.number.val._double = 5.5;
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NUM_e;
    w2.word_type = NAN_e;
    w1.u.number.val_type = DOUBLE;
    w1.u.number.val._double = 5.5;
 /*   w2.u.nan = "witam";*/
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NAN_e;
    w2.word_type = NAN_e;
/*    w1.u.nan = "siema";
    w2.u.nan = "hej";*/
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);

    w1.word_type = NAN_e;
    w2.word_type = NAN_e;
/*    w1.u.nan = "dziendobry";
    w2.u.nan = "DziEndobRy";*/
    res = wordEquals(&w1, &w2);
    printf("res = %d\n", res);
}

TEST TEST_cwEquals()
{
    printf("=== Testing cwEquals() ===\n");
    bool res;
    CountedWord cw1, cw2;

    cw1.word.word_type = NUM_e;
    cw2.word.word_type = NUM_e;
    cw1.word.u.number.val_type = DOUBLE;
    cw2.word.u.number.val_type = DOUBLE;
    cw1.word.u.number.val._double = 5.5;
    cw2.word.u.number.val._double = 666.666;
    cw1.num_occurrences = 15;
    cw2.num_occurrences = 20;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    cw1.word.word_type = NAN_e;
    cw2.word.word_type = NAN_e;
/*    cw1.word.u.nan = "dziendobry";
    cw2.word.u.nan = "DziEndobRy";*/
    cw1.num_occurrences = 0;
    cw2.num_occurrences = 1;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    cw1.word.word_type = NUM_e;
    cw2.word.word_type = NUM_e;
    cw1.word.u.number.val_type = DOUBLE;
    cw2.word.u.number.val_type = DOUBLE;
    cw1.word.u.number.val._double = 5.5;
    cw2.word.u.number.val._double = 666.666;
    cw1.num_occurrences = 15;
    cw2.num_occurrences = 15;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    cw1.word.word_type = NAN_e;
    cw2.word.word_type = NAN_e;
/*    cw1.word.u.nan = "dziendobry";
    cw2.word.u.nan = "DziEndobRy";*/
    cw1.num_occurrences = 0;
    cw2.num_occurrences = 0;
    res = cwEquals(&cw1, &cw2);
    printf("res = %d\n", res);

    Word w1, w2;
    createWordFromString(&w1, "21e3");
    createWordFromString(&w2, "21000");
/*
    CountedWord *cwptr1 = createCountedWord(NULL, w1, 0);
    CountedWord *cwptr2 = createCountedWord(NULL, w2, 0);
    res = cwEquals(cwptr1, cwptr2);*/
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
    //ssize_t strSize = my_getline(&str, &len);
    str[strcspn(str, "\n")] = '\0';
    Line line;
    createLine(&line, str, 1);
    printNans(&line);

    int x = 3;
}
TEST TEST_vectorEquals()
{
    char arr1[] = "0xABC siemka O3rhue2bVp13 0XFFFFFF 16777215 01777 1023.0";
    char arr2[] = "2748 SiEmKa o3RhUe2bvP13 16777.215E3 1677721500E-2 1023 0x3FF";
    char arr3[] = "2748 16777.215E3 1677721500E-2 1023 1023 1023 0x3FF";
    char arr4[] = "2748 16777.215E3 1677721500E-2 1677721500E-2 1023 1023 0x3FF 0x3FF";

    Line line1;
    createLine(&line1, arr1, 1);
    Line line2;
    createLine(&line2, arr2, 1);
    Line line3;
    createLine(&line3, arr3, 1);
    Line line4;
    createLine(&line4, arr4, 1);
    bool res;

    res = vectorEquals(line1.numbersMultiset, line2.numbersMultiset);
    printf("%d\n", res);
    res = vectorEquals(line1.numbersMultiset, line1.nansMultiset);
    printf("%d\n", res);
    res = vectorEquals(line1.nansMultiset, line2.nansMultiset);
    printf("%d\n", res);
    res = vectorEquals(line2.nansMultiset, line3.nansMultiset);
    printf("%d\n", res);
    res = vectorEquals(line2.nansMultiset, line4.nansMultiset);
    printf("%d\n", res);

    //printNans(line1.nansMultiset);
}


TEST TEST_sortMultisets()
{
    //TODO: dziś koniecznie do ogarnięcia funkcje sortujące

    char arr[] = "zak 0xABC siemka waeuiufhwevw tryt x sieeeaafaf O3rhue2bVp13 1023 tryteyrt zakfmefo 0XFFFFFF xxxxxxxxxx 16777215 01777 1023.0 abcdef\n";
    //char arr[] = "0xABC 1023  0XFFFFFF 16777215 01777 1023.0 \n";
    //char arr[] = "123 465 8424 16777124 999 1023\n";
    //char arr[] = "1 -3 -3 -3 -3 -3 2 1 4 cb b aa\n";
    //char arr[] = "123 0xABC 123 1677721 9999 01777 1023.0\n";
    Line line;
    createLine(&line, arr, 1);

    printNans(&line);
    printNumbers(&line);

/*    CountedWord cw[100];
    memcpy(cw,&line.numbersMultiset,scv_size(line.numbersMultiset));*/

/*    Number num0 = (GET_ITEM(CountedWord, line.numbersMultiset, 0))->word.u.number;
    Number num1 = (GET_ITEM(CountedWord, line.numbersMultiset, 1))->word.u.number;
    Number num2 = (GET_ITEM(CountedWord, line.numbersMultiset, 2))->word.u.number;
    Number num3 = (GET_ITEM(CountedWord, line.numbersMultiset, 3))->word.u.number;
    Number num4 = (GET_ITEM(CountedWord, line.numbersMultiset, 4))->word.u.number;
    Number num5 = (GET_ITEM(CountedWord, line.numbersMultiset, 5))->word.u.number;

    int comp_res;

    comp_res = numbercmp(&num1, &num1);
    comp_res = numbercmp(&num1, &num2);
    comp_res = numbercmp(&num1, &num3);
    comp_res = numbercmp(&num4, &num5);
    comp_res = numbercmp(&num5, &num2);
    comp_res = numbercmp(&num3, &num1);*/


    unsigned si = scv_size(line.numbersMultiset);

    sortMultisets(&line);
    printf("\n=== SORTED ===\n");
    printNans(&line);
    printNumbers(&line);
}
TEST TEST_sortNums()
{

}

TEST TEST_generateGroups()
{
    LineSet *ls = malloc(sizeof(LineSet));
    ls->lines = scv_new(sizeof(Line), INIT_CAP);

    GroupSet gs;
    char arr1[] = "0xABC siemka O3rhue2bVp13 0XFFFFFF 16777215 01777 1023.0";
    char arr2[] = "2748 SiEmKa o3RhUe2bvP13 16777.215E3 1677721500E-2 1023 0x3FF";
    char arr3[] = "zak 0xABC siemka waeuiufhwevw tryt x sieeeaafaf O3rhue2bVp13 tryteyrt zakfmefo 0XFFFFFF xxxxxxxxxx 16777215 01777 1023.0 abcdef\n";
    char arr4[] = "2748 16777.215E3 1677721500E-2 1023 1023 1023 0x3FF";
    char arr5[] = "2748 16777.215E3 1677721500E-2 1677721500E-2 1023 1023 0x3FF 0x3FF";

    Line line1;
    createLine(&line1, arr1, 1);
    Line line2;
    createLine(&line2, arr2, 2);
    Line line3;
    createLine(&line3, arr3, 3);
    Line line4;
    createLine(&line4, arr4, 4);
    Line line5;
    createLine(&line5, arr5, 5);

    scv_push_back(ls->lines, &line1);
    scv_push_back(ls->lines, &line2);
    scv_push_back(ls->lines, &line3);
    scv_push_back(ls->lines, &line4);
    scv_push_back(ls->lines, &line5);
    scv_shrink_to_fit(ls->lines);

    generateGroups(&gs, ls);
    printGroups(&gs);

    //sortGroups(&gs);
    //printf("\n=== SORTED ===\n");
    //printGroups(&gs);
}

TEST TEST_getLines()
{

}
TEST TEST_printGroupsAndErrorMessages()
{
    LineSet ls;
    ls.lines = scv_new(sizeof(Line), INIT_CAP);
    GroupSet gs;

    char s1[] = "9 abc\n";
    char s2[] = "abc 0x09\n";
    char s3[] = "011 ABC\n";
    char s4[] = ".9e1 aBc\n";
    char s5[] = "ABc 09\n";
    char s6[] = "# To jest komentarz.\n";
    char s7[] = "żółć\n";
    char s8[] = "\n";
    char s9[] = "9 9 abc\n";
    char s10[] = "9 abc abc\n";
    char s11[] = "9 abc ĘĄ\n";
    char s12[] = "9223372036854775807\n";
    char s13[] = "0x7fffffffffffffff\n";
    char s14[] = "0777777777777777777777\n";
    char s15[] = "-9223372036854775808\n";
    char s16[] = "9223372036854775808\n";
    char s17[] = "0x8000000000000000\n";
    char s18[] = "01000000000000000000000\n";
    char s19[] = "-1\n";
    char s20[] = "18446744073709551615\n";
    char s21[] = "0xffffffffffffffff\n";
    char s22[] = "01777777777777777777777\n";
    char s23[] = "-9000000000000000000\n";
    char s24[] = "-9e18\n";
    char s25[] = "18e18\n";
    char s26[] = "18000000000000000000";

    Line line1;
    createLine(&line1, s1, 1);
    Line line2;
    createLine(&line2, s2, 2);
    Line line3;
    createLine(&line3, s3, 3);
    Line line4;
    createLine(&line4, s4, 4);
    Line line5;
    createLine(&line5, s5, 5);
    Line line6;
    createLine(&line6, s6, 6);
    Line line7;
    createLine(&line7, s7, 7);
    Line line8;
    createLine(&line8, s8, 8);
    Line line9;
    createLine(&line9, s9, 9);
    Line line10;
    createLine(&line10, s10, 10);
    Line line11;
    createLine(&line11, s11, 11);
    Line line12;
    createLine(&line12, s12, 12);
    Line line13;
    createLine(&line13, s13, 13);
    Line line14;
    createLine(&line14, s14, 14);
    Line line15;
    createLine(&line15, s15, 15);
    Line line16;
    createLine(&line16, s16, 16);
    Line line17;
    createLine(&line17, s17, 17);
    Line line18;
    createLine(&line18, s18, 18);
    Line line19;
    createLine(&line19, s19, 19);
    Line line20;
    createLine(&line20, s20, 20);
    Line line21;
    createLine(&line21, s21, 21);
    Line line22;
    createLine(&line22, s22, 22);
    Line line23;
    createLine(&line23, s23, 23);
    Line line24;
    createLine(&line24, s24, 24);
    Line line25;
    createLine(&line25, s25, 25);
    Line line26;
    createLine(&line26, s26, 26);

    scv_push_back(ls.lines, &line1);
    scv_push_back(ls.lines, &line2);
    scv_push_back(ls.lines, &line3);
    scv_push_back(ls.lines, &line4);
    scv_push_back(ls.lines, &line5);
    scv_push_back(ls.lines, &line6);
    scv_push_back(ls.lines, &line7);
    scv_push_back(ls.lines, &line8);
    scv_push_back(ls.lines, &line9);
    scv_push_back(ls.lines, &line10);
    scv_push_back(ls.lines, &line11);
    scv_push_back(ls.lines, &line12);
    scv_push_back(ls.lines, &line13);
    scv_push_back(ls.lines, &line14);
    scv_push_back(ls.lines, &line15);
    scv_push_back(ls.lines, &line16);
    scv_push_back(ls.lines, &line17);
    scv_push_back(ls.lines, &line18);
    scv_push_back(ls.lines, &line19);
    scv_push_back(ls.lines, &line20);
    scv_push_back(ls.lines, &line21);
    scv_push_back(ls.lines, &line22);
    scv_push_back(ls.lines, &line23);
    scv_push_back(ls.lines, &line24);
    scv_push_back(ls.lines, &line25);
    scv_push_back(ls.lines, &line26);

    scv_shrink_to_fit(ls.lines);
    printLines(&ls);

    gs.groups = scv_new(sizeof(Group), INIT_CAP);
    generateGroups(&gs, &ls);
    printGroups(&gs);
    printErrorMessages(&ls);
}