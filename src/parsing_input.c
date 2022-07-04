#include "parsing_input.h"

#ifndef CHECK_POINTER
#define CHECK_POINTER(ptr)  \
do {                    \
    if (ptr == NULL) {  \
        fprintf(stderr, "ERROR: Ran out of memory!\n"); \
        exit(EXIT_FAILURE);        \
    }                   \
} while (0)
#endif /*CHECK_POINTER*/

#define SPACE 32
#define TILDE 126



/**
 * Returns true if number is written in base 8, false otherwise.
 */
static bool isInOctalRepresentation(const char *str);

/**
 * Returns true if number is written in base 10, false otherwise.
 */
static bool isInDecimalRepresentation(const char *str);

/**
 * Returns true if number is written in base 16, false otherwise.
 */
static bool isInHexRepresentation(const char *str);

/**
 * Returns true on numbers containing anything non-zero in their fractional part, false otherwise.
 */
static inline bool hasFracPart(const long double num);

/**
 * Returns true on characters with ASCII codes 33-126 or white-space, false otherwise.
 * Words that are a result of further handling will not contain white-space,
 * as it's the split regex.
 */
static inline bool isLegalChar(const char c);

/**
 * Returns true if all characters of string return true on a call of isLegalChar(), false otherwise.
 */
static bool containsOnlyLegalChars(const char *str);

/**
 * Returns true if all characters of string return true on a call of isspace(), false otherwise.
 */
static bool containsOnlyWhiteSpace(const char *str);

/**
 * Initializes an instance of struct Word.
 * Always results in a NaN if unable to create a valid number in base 8/10/16.
 */
static void createWordFromString(Word *word, const char *str);

/**
 * Returns a non-negataive index from the numbersMultiset
 * if line contains queried number, -1 otherwise.
 */
static int indexOfNumber(vector_t *numbersMultiset, const Number *query);

/**
 * Returns a non-negataive index from the nansMultiset
 * if line contains queried number, -1 otherwise.
 */
static int indexOfNan(vector_t *nansMultiset, const char *query);

/**
 * Creates an instance of struct CountedWord, with count set initially to 1.
 */
static inline void createCountedWord(CountedWord *cw, const Word *w);

/*
 * Creates an instance of struct Line.
 * Its field words_multiset is non-NULL if and only if line_type is LEGAL.
 */
static void createLine(Line *line, char *str, const size_t line_num);

/**
 * Floor function for long doubles. Could be replaced by floorl() from <tgmath.h>,
 * but my compiler wouldn't let me use it (I don't know why).
 */
static long double myFloor(long double x);

/**
 * Returns true if "0x"/"0X" prefix takes up indices 0 and 1 of the string, false otherwise.
 */
static inline bool is0xStringPrefix(const char *str);


/**
 * Creates an illegal line with empty multisets, error status and no group membership.
 */
static inline void createIllegalLine(Line *line);

/**
 * Creates an ignored line with empty multisets and no group membership.
 */
static inline void createIgnoredLine(Line *line);

/**
 * Creates a legal line with at least one non-empty multiset and no group membership at first.
 */
static void createLegalLine(Line *line, char *str);

/**
 * Initializes a legal line, gives it ownership of its multisets.
 */
static void initLegalLine(Line *line, vector_t *nans, vector_t *nums);

/**
 * Creates a word based on a form of input equal to zero.
 */
static inline void createZero(Word *word);

/**
 * Creates a word based on a form of input equal to -INFTY
 */
static inline void createMinusInfty(Word *word);

/**
 * Creates a word based on a form of input equal to INFTY
 */
static inline void createPlusInfty(Word *word);

/**
 * Creates a number word based on a negative number, or (-)NAN in case of failure.
 */
static void createNegativeNumber(Word *word, const char *str);

/**
 * Creates a number word based on a positive number, or (+)NAN in case of failure.
 */
static void createPositiveNumber(Word *word, const char *str);

/**
 * Creates a number word based on an unsigned number, or NAN in case of failure.
 */
static void createUnsignedNumber(Word *word, const char *str);

/**
 * Creates a non-number word based on the default string "NAN"
 */
static inline void createNan(Word *word, const char *str);

/**
 * Checks whether the string represents a simple negative number corner case
 * for further simpler conversion.
 */
static bool isNegativeNumberCornerCase(Word *word, const char *str);

/**
 * Checks whether the string represents a simple unsigned number corner case
 * for further simpler conversion.
 */
static bool isUnsignedNumberCornerCase(Word *word, const char *str);

/**
 * Checks whether the string represents a negative integer corner case
 * for further simpler conversion.
 */
static bool isNegativeIntegerCase(Word *word, const char *str);

/**
 * Checks whether the string represents a positive integer
 * for further simpler conversion.
 */
static bool isPositiveIntegerCase(Word *word, const char *str);

/**
 * Checks whether the string represents an unsigned integer
 * for further simpler conversion.
 */
static bool isUnsignedIntegerCase(Word *word, const char *str);

/**
 * Processes an unsigned octal integer which it'll store in word.
 */
static void parseUnsignedOctal(Word *word, const char *str);

/**
 * Processes an unsigned decimal integer which it'll store in word.
 */
static void parseUnsignedDecimal(Word *word, const char *str);

/**
 * Processes an unsigned hex integer which it'll store in word.
 */
static void parseUnsignedHex(Word *word, const char *str);

/**
 * Attempts to extract a negative long double from the source string.
 */
static void considerNegativeDoubleCase(Word *word, const char *str);

/**
 * Attempts to extract a positive long double from the source string.
 */
static void considerPositiveDoubleCase(Word *word, const char *str);

/**
 * Attempts to extract a long double from the source string.
 */
static void considerUnsignedDoubleCase(Word *word, const char *str);


static long double myFloor(long double x)
{
    long double xcopy = (x < 0)? -1 * x : x;
    int zeros = 0;
    long double n = 1;

    while (xcopy > n * 10) {
        n *= 10;
        zeros++;
    }
    for (xcopy -= n; zeros != -1; xcopy -= n) {
        if (xcopy < 0) {
            xcopy += n;
            n /= 10;
            --zeros;
        }
    }
    xcopy += n;

    if (x < 0) {
        if (xcopy == 0) {
            return x;
        }
        else {
            return x - (1 - xcopy);
        }
    }
    else {
        return x - xcopy;
    }
}

static inline bool hasFracPart(const long double num)
{
    return num - myFloor(num) != 0;
}

static inline bool isLegalChar(const char c) {
    return ((c >= SPACE && c <= TILDE) || isspace(c));
}

static bool containsOnlyLegalChars(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isLegalChar(str[i])) {
            return false;
        }
    }
    return true;
}

static bool containsOnlyWhiteSpace(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
            return false;
        }
    }
    return true;
}

static inline void createIllegalLine(Line *line)
{
    line->line_type = ILLEGAL;
    line->numbersMultiset = NULL;
    line->nansMultiset = NULL;
    line->group_num = NO_GROUP;
}

static inline void createIgnoredLine(Line *line)
{
    line->line_type = IGNORED;
    line->numbersMultiset = NULL;
    line->nansMultiset = NULL;
    line->group_num = NO_GROUP;
}

static void initLegalLine(Line *line, vector_t *nans, vector_t *nums)
{
    VectorShrinkToFit(nans);
    VectorShrinkToFit(nums);
    line->line_type = LEGAL;
    line->nansMultiset = nans;
    line->numbersMultiset = nums;
    line->group_num = NO_GROUP;
}


static void createLegalLine(Line *line, char *str)
{
    vector_t *nums = VectorNew(sizeof(CountedWord), INIT_CAP);
    vector_t *nans = VectorNew(sizeof(CountedWord), INIT_CAP);
    CHECK_POINTER(nums); CHECK_POINTER(nans);

    char *ptr = strtok(str, " \t\v\f\r");   // cutting string to its first white-space regex occurrence
    while (ptr != NULL) {
        Word w;
        int nans_idx = indexOfNan(nans, ptr);

        if (nans_idx != NOT_FOUND) {
            CountedWord *cw = GET_ITEM(CountedWord, nans, nans_idx);
            cw->num_occurrences++;       // increment this NaN's occurrences
        }
        else {
            createWordFromString(&w, ptr);
            CountedWord cw;
            int nums_idx = indexOfNumber(nums, &w.u.number);

            if (nums_idx != NOT_FOUND) {
                CountedWord *cw_ptr = GET_ITEM(CountedWord, nums, nums_idx);
                cw_ptr->num_occurrences++;    // increment this number's occurrences
            }
            else if (w.word_type == NUM_e) {
                createCountedWord(&cw, &w);
                SAFE_PUSH(nums, &cw);    // add newly created number to nums
            }
            else if (w.word_type == NAN_e) {
                createCountedWord(&cw, &w);
                SAFE_PUSH(nans, &cw);    // add newly created NaN to nans
            }
        }
        ptr = strtok(NULL, " \t\v\f\r");      // advances the pointer to content after next white-space
    }
    initLegalLine(line, nans, nums);
}

static void createLine(Line *line, char *str, const size_t line_num)
{
    line->line_num = line_num;

    if (str == NULL) {
        createIllegalLine(line);
        return;
    }
    str[strcspn(str, "\n")] = '\0';

    if (str[0] == '#' || containsOnlyWhiteSpace(str)) {
        createIgnoredLine(line);
    }
    else if (!containsOnlyLegalChars(str)) {
        createIllegalLine(line);
    }
    else {
        createLegalLine(line, str);
    }
}

static int indexOfNumber(vector_t *numbersMultiset, const Number *query)
{
    for (int i = 0; i < (int)numbersMultiset->size; i++) {
        Word w = (GET_ITEM(CountedWord, numbersMultiset, i))->word;

        if (numberEquals(&w.u.number, query)) {
            return i;
        }
    }
    return NOT_FOUND;
}

static int indexOfNan(vector_t *nansMultiset, const char *query)
{
    for (int i = 0; i < (int)nansMultiset->size; i++) {
        Word w = (GET_ITEM(CountedWord, nansMultiset, i))->word;

        if (strEquals(w.u.nan, query)) {
            return i;
        }
    }
    return NOT_FOUND;
}

static inline void createCountedWord(CountedWord *cw, const Word *w) {
    cw->word = *w;
    cw->num_occurrences = INIT_OCCURRENCES;
}

static inline void createZero(Word *word)
{
    word->word_type = NUM_e;
    word->u.number.val_type = UNSIGNED_INT;
    word->u.number.val._unsigned_int = 0;
}

static inline void createMinusInfty(Word *word)
{
    word->word_type = NUM_e;
    word->u.number.val_type = DOUBLE;
    word->u.number.val._double = -INFINITY;
}

static inline void createPlusInfty(Word *word)
{
    word->word_type = NUM_e;
    word->u.number.val_type = DOUBLE;
    word->u.number.val._double = INFINITY;
}

static inline void createNan(Word *word, const char *str)
{
    word->word_type = NAN_e;
    word->u.nan = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(word->u.nan, str);
}

static bool isNegativeNumberCornerCase(Word *word, const char *str)
{
    if (strEquals(str, "-0")) {
        createZero(word);
        return true;
    }
    if (is0xStringPrefix(str + 1)) {
        createNan(word, str);    // only positive/unsigned numbers are to be treated as hex
        return true;
    }
    else return false;
}

static bool isNegativeIntegerCase(Word *word, const char *str)
{
    if (isInDecimalRepresentation(str + 1)) {
        char *endptr = NULL;
        errno = 0;
        long long int res_ll = strtoll(str, &endptr, DECIMAL);

        if ((res_ll == 0 && (/*errno != 0 || */endptr == str)) || (res_ll == LLONG_MIN/* && errno == ERANGE*/)) {
            createNan(word, str);    // input is not a valid long long int or underflows range
            return true;
        }
        else {
            word->word_type = NUM_e;
            word->u.number.val_type = NEGATIVE_INT;
            word->u.number.val._negative_int = res_ll;
            return true;
        }
    }
    return false;
}

static void considerNegativeDoubleCase(Word *word, const char *str)
{
    char *endptr = NULL;
    errno = 0;
    long double res_ld = strtold(str, &endptr);    // attempt to create long double

    if (res_ld == -INFINITY || !isfinite(res_ld)) {
        createMinusInfty(word);
    }
    else if (res_ld == 0) {
        createZero(word);    // input is very small (say, -1e-5000), treat it as zero
    }
    else if (*endptr != '\0') {
        createNan(word, str);
    }
    else if (hasFracPart(res_ld) || res_ld < LLONG_MIN) {
        word->word_type = NUM_e;    // Number contains something non-zero after "." or is too small for a long long
        word->u.number.val_type = DOUBLE;
        word->u.number.val._double = res_ld;
    }
    else {
        word->word_type = NUM_e;   // Number can be represented as an integer
        word->u.number.val_type = NEGATIVE_INT;
        word->u.number.val._negative_int = res_ld;
    }
}

static void createNegativeNumber(Word *word, const char *str)
{
    if (!isNegativeNumberCornerCase(word, str)) {
        if (!isNegativeIntegerCase(word, str)) {
            considerNegativeDoubleCase(word, str);
        }
    }
}

static bool isPositiveIntegerCase(Word *word, const char *str)
{
    if (isInOctalRepresentation(str + 1)) {
        parseUnsignedOctal(word, str + 1);
        return true;
    }
    else if (is0xStringPrefix(str + 1)) {
        parseUnsignedHex(word, str);
        return true;
    }
    return false;
}

static void considerPositiveDoubleCase(Word *word, const char *str)
{
    errno = 0;
    char *endptr = NULL;
    long double res_ld = strtold(str, &endptr);    // attempt to create long double

    if (res_ld == INFINITY || !isfinite(res_ld)) {
        createPlusInfty(word);
    }
    else if (res_ld == 0) {
        createZero(word);    // input is very small (say, +1e-5000), treat it as zero
    }
    else {
        if (*endptr != '\0') {
            createNan(word, str);
        }
        else if (hasFracPart(res_ld) || res_ld > ULLONG_MAX) {
            word->word_type = NUM_e;    // There's something non-zero after '.' / overflow of the unsigned long long type
            word->u.number.val_type = DOUBLE;
            word->u.number.val._double = res_ld;
        }
        else {
            word->word_type = NUM_e;    // Number looks like -5.0, -81.00000, etc, can be represented as an integer
            word->u.number.val_type = UNSIGNED_INT;
            word->u.number.val._unsigned_int = res_ld;
        }
    }
}

static void createPositiveNumber(Word *word, const char *str)
{
    if (strEquals(str, "+NAN")) {
        createNan(word, "+NAN");
    }
    else if (!isUnsignedNumberCornerCase(word, str + 1)) {
        if (!isPositiveIntegerCase(word, str)) {
            considerPositiveDoubleCase(word, str);
        }
    }
}

static bool isUnsignedNumberCornerCase(Word *word, const char *str)
{
    if (strEquals(str, "INF") || strEquals(str, "INFTY") || strEquals(str, "INFINITY")) {
        createPlusInfty(word);
        return true;
    }
    return false;
}

static void parseUnsignedOctal(Word *word, const char *str)
{
    char *endptr = NULL;
    errno = 0;
    unsigned long long res_ull = strtoull(str, &endptr, OCTAL);

    if ((res_ull == 0 && (errno != 0 || endptr == str)) || (res_ull == ULLONG_MAX && errno == ERANGE)) {
        createNan(word, str);    // input is not a valid unsigned long long or overflows range
    }
    else {
        word->word_type = NUM_e;
        word->u.number.val_type = UNSIGNED_INT;
        word->u.number.val._unsigned_int = res_ull;
    }
}

static void parseUnsignedDecimal(Word *word, const char *str)
{
    char *endptr = NULL;
    errno = 0;
    unsigned long long res_ull = strtoull(str, &endptr, DECIMAL);

    if ((res_ull == 0 && (errno != 0 || endptr == str)) || (res_ull == ULLONG_MAX && errno == ERANGE)) {
        createNan(word, str);     // input is not a valid unsigned long long or overflows range
    }
    else {
        word->word_type = NUM_e;
        word->u.number.val_type = UNSIGNED_INT;
        word->u.number.val._unsigned_int = res_ull;
    }
}

static void parseUnsignedHex(Word *word, const char *str)
{
    char *endptr = NULL;
    errno = 0;
    unsigned long long res_ull;

    if (isInHexRepresentation(str + 2)) {
        res_ull = strtoull(str, &endptr, HEX);

        if (res_ull == ULLONG_MAX && errno == ERANGE) {
            createNan(word, str);    // number oveflows range
        }
        else {
            word->word_type = NUM_e;
            word->u.number.val_type = UNSIGNED_INT;
            word->u.number.val._unsigned_int = res_ull;
        }
    }
    else {
        createNan(word, str);    // nothing other than a hex number can have prefix "0x"/"0X", unless it's NAN
    }
}

static bool isUnsignedIntegerCase(Word *word, const char *str)
{
    if (str[0] == '0' && isInOctalRepresentation(str)) {
        parseUnsignedOctal(word, str);
        return true;
    }
    if (is0xStringPrefix(str)) {
        parseUnsignedHex(word, str);
        return true;
    }
    else if (isInDecimalRepresentation(str)) {
        parseUnsignedDecimal(word, str);
        return true;
    }
    else return false;
}

static void considerUnsignedDoubleCase(Word *word, const char *str)
{
    errno = 0;
    char *endptr = NULL;
    long double res_ld = strtold(str, &endptr);    // attempt to create long double

    if (res_ld == INFINITY || !isfinite(res_ld)) {
        createPlusInfty(word);
    }
    else if (res_ld == 0) {
        if (*endptr != '\0') {
            createNan(word, str);    // input is not a valid long double
        }
        else {
            createZero(word);    // input is very small (say, 1e-5000), treat it as zero
        }
    }
    else if (*endptr != '\0') {
        createNan(word, str);
    }
    else if (hasFracPart(res_ld) || res_ld > ULLONG_MAX) {
        word->word_type = NUM_e;  // Input contains something non-zero after "." / overflows the unsigned long long type
        word->u.number.val_type = DOUBLE;
        word->u.number.val._double = res_ld;
    }
    else {
        word->word_type = NUM_e;       // Number looks like -5.0, -81.00000, etc, can be represented as an integer
        word->u.number.val_type = UNSIGNED_INT;
        word->u.number.val._unsigned_int = res_ld;
    }
}

static void createUnsignedNumber(Word *word, const char *str)
{
    if (!isUnsignedNumberCornerCase(word, str)) {
        if (!isUnsignedIntegerCase(word, str)) {
            considerUnsignedDoubleCase(word, str);
        }
    }
}

static void createWordFromString(Word *word, const char *str)
{
    if (str[0] == '-' && strlen(str) > 1) {
        createNegativeNumber(word, str);
    }
    else if (str[0] == '+' && strlen(str) > 1) {
        createPositiveNumber(word, str);
    }
    else {
        createUnsignedNumber(word, str);
    }
}

static bool isInDecimalRepresentation(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

static bool isInOctalRepresentation(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]) || str[i] == '9') {
            return false;
        }
    }
    return true;
}

static bool isInHexRepresentation(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isxdigit(str[i])) {
            return false;
        }
    }
    return true;
}

static inline bool is0xStringPrefix(const char *str)
{
    return (str != NULL && strlen(str) > 1 && (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')));
}

void getLines(LineSet *ls)
{
    ls->lines = VectorNew(sizeof(Line), EXAMPLE_IN_TOTAL_NUM_LINES);
    CHECK_POINTER(ls->lines);

    size_t line_index = 1, len;
    char *lineptr = NULL;
    long long nread;

    errno = 0;
    while ((nread = getline(&lineptr, &len, stdin)) != -1) {
        CHECK_POINTER(lineptr);
        Line line;

        if ((size_t)nread != strlen(lineptr)) {
            createLine(&line, NULL, line_index++);       // illegal line - contains too many '\0' characters
        }
        else {
            createLine(&line, lineptr, line_index++);
            sortMultisets(&line);
        }
        SAFE_PUSH(ls->lines, &line);
    }

    if (lineptr != NULL) {
        free(lineptr);
    }
    if (nread == -1 && errno == ENOMEM) {
        exit(EXIT_FAILURE);
    }
}