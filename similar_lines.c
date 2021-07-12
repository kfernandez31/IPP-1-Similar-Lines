//
// Created by kacpe on 7/8/2021.
//

#include "similar_lines.h"

bool hasFracPart(long double num)
{
    int truncated = (int)num;
    return (num != truncated);
}

bool isLegalChar(char c) {
    return (c >= SPACE && c <= TILDE);
}

bool containsOnlyLegalChars(char *str) {
    for (uint i = 0; i < strlen(str); i++) {
        if (!isLegalChar(str[i])) {
            return false;
        }
    }
    return true;
}

bool containsOnlyWhiteSpace(char *str) {
    for (uint i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
            return false;
        }
    }
    return true;
}

bool wordEquals(Word *word1, Word *word2)
{
    if (word1->word_type != word2->word_type) {
        // incompatible types
        return false;
    }
    if (word1->word_type == NUM) {
        return numberEquals(&word1->u.number, &word2->u.number);
    }
    if (word1->word_type == NAN) {
        return strEquals(word1->u.nan, word2->u.nan);
    }
    fprintf(stderr, "Trying to compare words of unknown types\n");
    exit(EXIT_FAILURE);
}

bool strEquals(char *str1, char *str2)
{
    return (strcasecmp(str1, str2) == 0);
}

bool numberEquals(Number *num1, Number *num2) {
    if (num1->val_type != num2->val_type) {
        // return false, because due to our conversion of strings such as "21.0" to integers,
        // there is no chance for such a number to be equal to a double with a non-zero fractional part
        return false;
    }
    return (numbercmp(num1, num2) == 0);
}

/*int alphacmp(const void *alpha1, const void *alpha2)
{
    size_t len1 = strlen(alpha1);
    size_t len2 = strlen(alpha2);
    if (len1 == len2) {
        return strcmp(alpha1, alpha2);
    }
    uint smaller_len = (len1 <= len2)? len1 : len2;
    int res;

    for (uint i = 0; i < smaller_len; i++) {
        res = primcmp(alpha1 + i, alpha2 + i);
        // character at &alpha1[i] has higher ASCII code than character at &alpha2[i] does
        if (res > 0) {
            return 1;
        }
        // character at &alpha1[i] has lower ASCII code than character at &alpha2[i] does
        else if (res < 0) {
            return -1;
        }
    }

    return 0;
}*/

int numbercmp(const void *num1, const void *num2)
{
    void *val1 = NULL, *val2 = NULL;

    switch (((Number*)num1)->val_type) {
        case UNSIGNED_INT: {
            val1 = &((Number*)num1)->val._unsigned_int;
            val2 = &((Number*)num2)->val._unsigned_int;
            return primcmp(val1, val2);

        }
        case NEGATIVE_INT: {
            val1 = &((Number*)num1)->val._negative_int;
            val2 = &((Number*)num2)->val._negative_int;
            return primcmp(val1, val2);
        }
        case DOUBLE: {
            val1 = &((Number*)num1)->val._double;
            val2 = &((Number*)num2)->val._double;
            return primcmp((Number*)val1, (Number*)val2);
        }
        default: fprintf(stderr, "Comparing numbers of unknown types.\n");
        exit(EXIT_FAILURE);
    }
}

int cwcmp(const void *cw1, const void *cw2)
{
    Word *w1 = &((CountedWord*)cw1)->word;
    Word *w2 = &((CountedWord*)cw2)->word;

    if (w1->word_type != w2->word_type) {
        fprintf(stderr, "Comparing words of differing types.\n");
        exit(EXIT_FAILURE);
    }
    if (w1->word_type == NUM) {
        return numbercmp(&w1->u.number, &w2->u.number);
    }
    else /*if (w1->word_type == NAN)*/{
        return strcasecmp(w1->u.nan, w2->u.nan);
    }
}

/*int wordcmp(Word *word1, Word *word2)
{
    if (word1->word_type != word2->word_type) {
        // incompatible types
        fprintf(stderr, "Comparing incompatible word types.\n");
        return -1;
    }
    if (word1->word_type == NUM) {
        return numbercmp(&word1->u.number, &word2->u.number);
    }
    if (word1->word_type == NAN) {
        return alphacmp(word1->u.nan, word1->u.nan);
    }
    fprintf(stderr, "Trying to compare words of unknown types\n");
    exit(EXIT_FAILURE);
}*/

bool cwEquals(CountedWord *cw1, CountedWord *cw2)
{
    return (wordEquals(&cw1->word, &cw2->word) && cw1->num_occurrences == cw2->num_occurrences);
}

Line *createLine(char *line_as_str, size_t line_num)
{
    line_as_str[strcspn(line_as_str, "\n")] = '\0';
    //TODO: ogarnąć to (komentarz niżej)

    Line *line = NULL;
    Line *temp1 = malloc(sizeof(Line));
    if (temp1 == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    line = temp1;
    line->line_num = line_num;

/*    char *s = NULL;
    strcpy(s, line_as_str);
    s[strcspn(s, "\n")] = '\0';
    if (strEquals(s, line_as_str)) {
        // line didn't end with '\n', so strcspn didn't modify it
        line->line_type = ILLEGAL;
        line->nums_multiset = NULL;
        line->strings_multiset = NULL;
        return line;
    }
    else line_as_str = s;*/

    // no need to create a multiset in the three cases below, since line contents are to be omitted
    if (!containsOnlyLegalChars(line_as_str) || line_as_str == NULL) {
        // second condition is there to be able to prevent the program from stopping when passing a line with ''
        // (empty char) and to just treat such line as illegal
        line->line_type = ILLEGAL;
        line->nums_multiset = NULL;
        line->strings_multiset = NULL;
        return line;
    }
    if (line_as_str[0] == '#') {
        line->line_type = COMMENT;
        line->nums_multiset = NULL;
        line->strings_multiset = NULL;
        return line;
    }
    if (containsOnlyWhiteSpace(line_as_str)) {
        line->line_type = EMPTY;
        line->nums_multiset = NULL;
        line->strings_multiset = NULL;
        return line;
    }

    line = temp1;
    line->line_num = line_num;

    scv_vector *temp2 = scv_new(sizeof(CountedWord), INIT_CAP);
    scv_vector *temp3 = scv_new(sizeof(CountedWord), INIT_CAP);
    if (temp2 == NULL || temp3 == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    scv_vector *nums = temp2;
    scv_vector *strings = temp3;

    // cutting string to its first white-space regex occurrence
    Word w;
    int idx;
    char *ptr = strtok(line_as_str, " ");
    while (ptr != NULL) {
        // creates word from current substring
        createWordFromString(&w, ptr);

        if (w.word_type == NAN) {
            idx = indexOfWord(strings, &w);
            if (idx == -1) {
                // word wasn't found - add it to the multiset
                CountedWord *cw = createCountedWord(w);
                scv_push_back(strings, cw);
            }
            else {
                // word was found - increment its occurrences
                CountedWord *cw = GET_ITEM(CountedWord, strings, idx);
                cw->num_occurrences++;
            }
        }
        else /*if(w.word_type == NUM)*/ {
            idx = indexOfWord(nums, &w);
            if (idx == -1) {
                // word wasn't found - add it to the multiset
                CountedWord *cw = createCountedWord(w);
                scv_push_back(nums, cw);
            }
            else {
                // word was found - increment its occurrences
                CountedWord *cw = GET_ITEM(CountedWord, nums, idx);
                cw->num_occurrences++;
            }
        }
        // advances the pointer to next white-space
        ptr = strtok(NULL, " ");
    }
    scv_shrink_to_fit(strings);
    scv_shrink_to_fit(nums);
    line->line_type = LEGAL;
    line->strings_multiset = strings;
    line->nums_multiset = nums;
    return line;
}

size_t indexOfWord(scv_vector *v, Word *query)
{
    for (uint i = 0; i < scv_size(v); i++) {
        Word w = (GET_ITEM(CountedWord, v, i))->word;

        if (wordEquals(query, &w)) {
            return i;
        }
    }
    return NOT_FOUND;
}

CountedWord* createCountedWord(Word w) {
    CountedWord *cw = NULL;
    CountedWord *temp = malloc(sizeof(CountedWord));
    if (temp == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    cw = temp;

    cw->word = w;
    cw->num_occurrences = 1;
    return cw;
}

int createWordFromString(Word *word, char *str)
//TODO: zachowanie gdy podaje się  na wejściu coś poza zakres
//TODO: czy octale i hexy mogą mieć "+" ?
//TODO: czy 01777 traktować jako octal czy decimal?
{
    // This function doesn't call containsOnlyLegalChars(), because createLineFromString() does it beforehand.
    long double res_ld;
    long long int res_ll;
    unsigned long long res_ull;
    char *endptr = NULL;

/*    if (*endptr != '\0') {
        // TODO: wtedy linijka, która zawiera to słowo ma ERROR
        return -1;
    }*/

    if (str[0] == '-' && strlen(str) > 1) {
        if (strEquals(str, "-NaN")) {
            word->word_type = NAN;
            word->u.nan = "-NaN";
            return SUCCESS;
        }

        if (!isDigit(str[1])) {
            word->word_type = NAN;
            word->u.nan = str;
        }

        if (isOctalInteger(str + 1) || isHexInteger(str + 1)) {
            word->word_type = NAN;
            word->u.nan = str;
            return SUCCESS;
        }

        word->word_type = NUM;

        if (isDecimalInteger(str + 1)) {
            word->u.number.val_type = NEGATIVE_INT;
            errno = 0;
            res_ll = strtoll(str, &endptr, DECIMAL);

            if (res_ll == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid long long int
                return FAILURE;
            }
            word->u.number.val._negative_int = res_ll * -1;
            return SUCCESS;
        }

        if (isDouble(str)) {
            errno = 0;
            res_ld = strtold(str, &endptr);

            if (res_ld == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid long double
                return FAILURE;
            }

            if (hasFracPart(res_ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = res_ld;
            }

            else {
                // Number looks like -5.0, -81.00000, etc. Treat it like an integer
                word->u.number.val_type = NEGATIVE_INT;
                word->u.number.val._negative_int = res_ld;
            }
            return SUCCESS;
        }
    }

    else if (str[0] == '+' && strlen(str) > 1) {
        if (strEquals(str, "+NaN")) {
            word->word_type = NAN;
            word->u.nan = "NaN";
            return SUCCESS;
        }

        if (isOctalInteger(str + 1) || isHexInteger(str + 1)) {
            word->word_type = NAN;
            word->u.nan = str;
            return SUCCESS;
        }

        if (strlen(str) > 1 && isDecimalInteger(str + 1)) {
            word->u.number.val_type = UNSIGNED_INT;
            errno = 0;
            res_ull = strtoull(str, &endptr, DECIMAL);
            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid unsigned long long
                return FAILURE;
            }
            word->u.number.val._unsigned_int = res_ull;
            return SUCCESS;
        }

        if (isDouble(str)) {
            errno = 0;
            res_ld = strtold(str, &endptr);

            if (res_ld == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid long double
                return FAILURE;
            }

            if (hasFracPart(res_ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = res_ld;
            }
            else {
                // Number looks like -5.0, -81.00000, etc. Treat it like an integer
                word->u.number.val_type = UNSIGNED_INT;
                word->u.number.val._unsigned_int = res_ld;
            }
            return SUCCESS;
        }
    }

    else {
        if (strEquals(str, "NaN")) {
            word->word_type = NAN;
            word->u.nan = "NaN";
            return SUCCESS;
        }

        word->word_type = NUM;

        if (isOctalInteger(str)) {
            word->u.number.val_type = UNSIGNED_INT;
            errno = 0;
            res_ull = strtoull(str, &endptr, OCTAL);

            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid unsigned long long
                return FAILURE;
            }
            word->u.number.val._unsigned_int = res_ull;
            return SUCCESS;
        }

        if (isHexInteger(str)) {
            word->u.number.val_type = UNSIGNED_INT;
            errno = 0;
            res_ull = strtoull(str, &endptr, HEX);

            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid unsigned long long
                return FAILURE;
            }
            word->u.number.val._unsigned_int = res_ull;
            return SUCCESS;
        }

        if (isDecimalInteger(str)) {
            word->u.number.val_type = UNSIGNED_INT;
            errno = 0;
            res_ull = strtoull(str, &endptr, DECIMAL);

            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid unsigned long long
                return FAILURE;
            }
            word->u.number.val._unsigned_int = res_ull;
            return SUCCESS;
        }

        if (isDouble(str)) {
            errno = 0;
            res_ld = strtold(str, &endptr);

            if (res_ld == 0 && (errno != 0 || endptr == str)) {
                //Error: input is not a valid long double
                return FAILURE;
            }

            if (hasFracPart(res_ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = res_ld;
            }
            else {
                // Number looks like -5.0, -81.00000, etc. Treat it like an integer
                word->u.number.val_type = UNSIGNED_INT;
                word->u.number.val._unsigned_int = res_ld;
            }
            return SUCCESS;
        }
    }

    // Couldn't convert given word to any type of number - set it to NaN
    word->word_type = NAN;
    word->u.nan = str;
    return SUCCESS;
}

bool isDouble(char *str)
{
    int len;
    float ignore;
    int ret = sscanf(str, "%f %n", &ignore, &len);
    return (ret && len == strlen(str));
}

bool isDecimalInteger(char *str) {
    for (uint i = 0; i < strlen(str); i++) {
        if (!isDigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isDigit(char c) //TODO: a co robi funkcja isdigit() ?
{
    return (c >= ZERO && c <= NINE);
}

bool strEqualsWithNaN(char *str) {
    return (strcasecmp(str, "NaN") == 0);
}

bool isOctalInteger(char *str) {
    if (str[0] != '0' || str[0] == '-') {
        return false;
    }

    //TODO: tak zostawić czy walnąć define ze strlenem górnego zakresu w octalu?
    if ((strlen(str) > 1 && str[1] - '0' >= 2) || strlen(str) > strlen("07777777777777777777777")) {
        // given number exceeds long long double range, treat it as NaN
        //TODO: traktować jako NaN czy jako INF?
        return false;
    }

    for (uint i = 0; i < strlen(str); i++) {
        if (!(str[i] >= ZERO && str[i] <= SEVEN)) {
            return false;
        }
    }
    return true;
}

bool isHexInteger(char *str) {
    if (strlen(str) < 2) {
        // string can't contain prefix "0x"/"0X" because it's too short
        return false;
    }
    if (strcasecmp(str, "0x") == 0) {
        // string is interpreted as 0, because strtoull will interpret it as such
        return true;
    }
    if (str[0] != '0' || !(str[1] == 'x' || str[1] == 'X')) {
        // no "0x"/"0X" prefix
        return false;
    }

    for (int i = 2; i < strlen(str); i++) {
        if (!((str[i] >= ZERO && str[i] <= SEVEN) || (str[i] >= A && str[i] <= F))) {
            return false;
        }
    }
    return true;
}

void printErrorMessages(LineSet ls)
{
    scv_vector *lines = ls.lines;
    for (uint i = 0; i < scv_size(lines); i++) {
        Line *l = GET_ITEM(Line, lines, i);
        if (l->line_type == ILLEGAL) {
            printf("ERROR %u\n", l->line_num);
            // TODO: wiadomo, że to ma być do pliku
        }
    }
}

void sortGroups(GroupSet *gs)
{
    Group *group = NULL;
    for (uint i = 0; i < scv_size(gs->groups); i++) {
        group = GET_ITEM(Group, gs->groups, i);
        qsort(group, scv_size(group->lines), sizeof(uint), primcmp);
        //TODO: coo?
    }
    qsort(gs->groups, scv_size(gs->groups), sizeof(Group), groupcmp);
}

void sortStrings(Line *line)
{
    scv_vector **strings_with_count = &line->strings_multiset;
    // TODO: czy wystarczy cast, czy muszę robić osobną funkcję na voidach? (odkomentować alphacmp())
    qsort(line->strings_multiset, scv_size(line->strings_multiset), sizeof(CountedWord), cwcmp);
}

void sortNums(Line *line)
{
    //qsort(line, scv_size(line), sizeof(Number), numbercmp);
}

int primcmp(const void *a, const void *b) {
    return memcmp(a, b, sizeof(a));
}

int groupcmp(const void *a, const void *b) {
    return primcmp(&((Group *)a)->lines[0], &((Group *)b)->lines[0]);
}

void printGroups(GroupSet gs)
{
    Group *group = NULL;
    // TODO: wiadomo, że to ma być do pliku
    for (uint i = 0; i < scv_size(gs.groups); i++) {
        group = GET_ITEM(Group, gs.groups, i);
        printGroup(*group);
    }
}

void printGroup(Group g)
{
    // TODO: wiadomo, że to ma być do pliku
    for (uint i = 0; i < scv_size(g.lines); i++) {
        printf("%u ", *GET_ITEM(uint, g.lines, i));
    }
    printf("\n");
}

LineSet* getLines()
{
    LineSet *ls = NULL;
    LineSet *temp1 = malloc(sizeof(LineSet));
    if (temp1 == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    ls = temp1;

    scv_vector *temp2 = scv_new(sizeof(Line), INIT_CAP);
    if (temp2 == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    ls->lines = temp2;

    Line *line = NULL;
    uint i = 1;

    char *line_as_str = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line_as_str, &len, stdin)) != -1) {
        if (nread != strlen(line_as_str)) {
            line = createLine(NULL, i++);
        }
        else {
            line = createLine(line_as_str, i++);
        }
        scv_push_back(ls->lines, line);
    }
    return ls;
}

GroupSet* generateGroups(LineSet ls)
{
    GroupSet *gs = NULL;
    GroupSet *temp1 = malloc(sizeof(GroupSet));
    if (temp1 == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    gs = temp1;

    scv_vector *temp2 = scv_new(sizeof(Group), INIT_CAP);
    if (temp1 == NULL){
        fprintf(stderr, "Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    gs->groups = temp2;

    Group *group = NULL;
    Line *line_i = NULL, *line_j = NULL;

    for (uint i = 0; i < scv_size(ls.lines); i++) {
        line_i = GET_ITEM(Line, ls.lines, i);
        if (!line_i->belongs_to_group) {
            // create new group based on current line, add current line to it
            Group *temp3 = malloc(sizeof(Group));
            if (temp3 == NULL){
                fprintf(stderr, "Ran out of memory!\n");
                exit(EXIT_FAILURE);
            }
            group = temp3;

            scv_vector *temp4 = scv_new(sizeof(uint), INIT_CAP);
            if (temp4 == NULL){
                fprintf(stderr, "Ran out of memory!\n");
                exit(EXIT_FAILURE);
            }
            group->lines = temp4;

            scv_push_back(group->lines, &line_i->line_num);

            for (int j = i; j < scv_size(ls.lines); j++) {
                line_j = GET_ITEM(Line, ls.lines, j);
                if (vectorEquals(line_i->strings_multiset, line_j->strings_multiset) && vectorEquals(line_i->nums_multiset, line_j->nums_multiset)) {
                    // Lines contain identical multisets of Numbers and NaNs
                    scv_push_back(group->lines, &line_j->line_num);
                    line_j->belongs_to_group = true;
                }
            }
        }
        // in case we didn't find matching lines, the group will be a singleton
        // i.e. all lines are in some sort of group - with oneself or with others
        line_i->belongs_to_group = true;
    }
    sortGroups(gs);
    return gs;
}

bool vectorEquals(scv_vector *v1, scv_vector *v2)
{
    if (scv_size(v1) != scv_size(v2)) {
        return false;
    }
    CountedWord *cw1 = NULL, *cw2 = NULL;

    for (uint i = 0; i < scv_size(v1); i++) {
        cw1 = GET_ITEM(CountedWord, v1, i);
        cw2 = GET_ITEM(CountedWord, v2, i);
        if (!cwEquals(cw1, cw2)) {
            return false;
        }
    }
    return true;
}

/*char getcharBetter()
{
    int c;
    do
    {
        c = getchar();
    } while(isspace(c));

    return (char)c;
}*/

ssize_t my_getline(char **_lineptr, size_t *_n)
{
    //TODO: zrobić to obcinanie tutaj
    ssize_t lineSize =  getline(_lineptr, _n, stdin);
    //*_lineptr[strcspn(*_lineptr, "\n")] = '\0';
    return lineSize;
}

void printStrings(Line line)
{
    char *str = NULL;
    CountedWord *cw = NULL;

    for (int i = 0 ; i < scv_size(line.strings_multiset); i++) {
        cw = GET_ITEM(CountedWord, line.strings_multiset, i);
        str = cw->word.u.nan;
        printf("%s %zu\n", str, cw->num_occurrences);
    }
}