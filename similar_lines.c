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
    fprintf(stderr, "ERROR: Trying to compare words of unknown types\n");
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

int cwNumbercmp(const void *cw1, const void *cw2)
{
    Word w1 = ((CountedWord*)cw1)->word;
    Word w2 = ((CountedWord*)cw2)->word;
    return numbercmp(&w1.u.number, &w2.u.number);
}

int numbercmp(const Number *num1, const Number *num2)
{
    if (num1->val_type == num2->val_type) {
        return sameTypecmp(num1, num2);
    }
    if (num1->val_type != num2->val_type) {
        return diffTypecmp(num1, num2);
    }
    fprintf(stderr, "ERROR: Trying to compare numbers of unknown types\n");
    exit(EXIT_FAILURE);
}

int cwNancmp(const void *cw1, const void *cw2)
{
    Word w1 = ((CountedWord*)cw1)->word;
    Word w2 = ((CountedWord*)cw2)->word;

    return strcasecmp(w1.u.nan, w2.u.nan);
}

bool cwEquals(CountedWord *cw1, CountedWord *cw2)
{
    return (wordEquals(&cw1->word, &cw2->word) && cw1->num_occurrences == cw2->num_occurrences);
}

void createLine(Line *input, char *line_as_str, size_t line_num)
{
    line_as_str[strcspn(line_as_str, "\n")] = '\0';

    input->line_num = line_num;

    //TODO: co tu miałem na myśli?
    // second condition is there to be able to prevent the program from stopping when passing a line with ''
    // (empty char) and to just treat such line as illegal

    // no need to create a multiset in the three cases below, since line contents are to be omitted
    if (!containsOnlyLegalChars(line_as_str) || line_as_str == NULL) {
        input->line_type = ILLEGAL;
        input->nums_multiset = NULL;
        input->strings_multiset = NULL;
        return;
    }
    if (line_as_str[0] == '#') {
        input->line_type = COMMENT;
        input->nums_multiset = NULL;
        input->strings_multiset = NULL;
        return;
    }
    if (containsOnlyWhiteSpace(line_as_str)) {
        input->line_type = EMPTY;
        input->nums_multiset = NULL;
        input->strings_multiset = NULL;
        return;
    }

    scv_vector *temp1 = scv_new(sizeof(CountedWord), INIT_CAP);
    scv_vector *temp2 = scv_new(sizeof(CountedWord), INIT_CAP);
    if (temp1 == NULL || temp2 == NULL){
        fprintf(stderr, "ERROR: Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    scv_vector *nums = temp1;
    scv_vector *strings = temp2;

    // cutting string to its first white-space regex occurrence
    Word w;
    char *ptr = strtok(line_as_str, " ");
    while (ptr != NULL) {
        int idx;
        // creates word from current substring
        createWordFromString(&w, ptr);

        if (w.word_type == NAN) {
            idx = indexOfWord(strings, &w);

            if (idx == NOT_FOUND) {
                // word wasn't found - add it to the multiset
                CountedWord *cw = createCountedWord(w);
                if (scv_push_back(strings, cw) != SCV_OK){
                    fprintf(stderr, "Error during pushback\n");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                // word was found - increment its occurrences
                CountedWord *cw = GET_ITEM(CountedWord, strings, idx);
                cw->num_occurrences++;
            }
        }
        else {
            idx = indexOfWord(nums, &w);

            if (idx == NOT_FOUND) {
                // word wasn't found - add it to the multiset
                CountedWord *cw = createCountedWord(w);

                if (scv_push_back(nums, cw) != SCV_OK){
                    fprintf(stderr, "Error during pushback\n");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                // word was found - increment its occurrences
                CountedWord *cw = GET_ITEM(CountedWord, nums, idx);
                cw->num_occurrences++;
            }
        }
        // advances the pointer to content after next white-space
        ptr = strtok(NULL, " ");
    }
    scv_shrink_to_fit(strings);
    scv_shrink_to_fit(nums);
    input->line_type = LEGAL;
    input->strings_multiset = strings;
    input->nums_multiset = nums;
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
        fprintf(stderr, "ERROR: Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    cw = temp;

    cw->word = w;
    cw->num_occurrences = 1;
    return cw;
}

void createWordFromString(Word *word, char *str)
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
            return;
        }

        if (!isDigit(str[1])) {
            word->word_type = NAN;
            word->u.nan = str;
            return;
        }

        if (isOctalInteger(str + 1) || isHexInteger(str + 1)) {
            word->word_type = NAN;
            word->u.nan = str;
            return;
        }

        word->word_type = NUM;

        if (isDecimalInteger(str + 1)) {
            word->u.number.val_type = NEGATIVE_INT;
            errno = 0;
            res_ll = strtoll(str, &endptr, DECIMAL);

            if (res_ll == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid long long int
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ll == LLONG_MAX || res_ll == LLONG_MIN) && errno == ERANGE) {
                // number over/underflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            word->u.number.val._negative_int = res_ll;
            return;
        }

        if (isDouble(str)) {
            errno = 0;
            res_ld = strtold(str, &endptr);

            if (res_ld == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid long double
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ld == LDBL_MAX || res_ld == LDBL_MIN) && errno == ERANGE) {
                // number over/underflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            if (hasFracPart(res_ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = res_ld;
                return;
            }

            // Number looks like -5.0, -81.00000, etc. Treat it as an integer
            word->u.number.val_type = NEGATIVE_INT;
            word->u.number.val._negative_int = res_ld;
            return;
        }
    }

    else if (str[0] == '+' && strlen(str) > 1) {
        if (strEquals(str, "+NaN")) {
            word->word_type = NAN;
            word->u.nan = "NaN";
            return;
        }

        if (!isDigit(str[1])) {
            word->word_type = NAN;
            word->u.nan = str;
            return;
        }

        if (isOctalInteger(str + 1) || isHexInteger(str + 1)) {
            word->word_type = NAN;
            word->u.nan = str;
            return;
        }

        if (strlen(str) > 1 && isDecimalInteger(str + 1)) {
            word->u.number.val_type = UNSIGNED_INT;

            errno = 0;
            res_ull = strtoull(str, &endptr, DECIMAL);
            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid unsigned long long
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ull == ULLONG_MAX) && errno == ERANGE) {
                // number overflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            word->u.number.val._unsigned_int = res_ull;
            return;
        }

        if (isDouble(str)) {
            errno = 0;
            res_ld = strtold(str, &endptr);

            if (res_ld == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid long double
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ld == LDBL_MAX || res_ld == LDBL_MIN   ) && errno == ERANGE) {
                // number over/underflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            if (hasFracPart(res_ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = res_ld;
                return;
            }
            // Number looks like -5.0, -81.00000, etc. Treat it as an integer
            word->u.number.val_type = UNSIGNED_INT;
            word->u.number.val._unsigned_int = res_ld;
            return;
        }
    }

    else {
        if (strEquals(str, "NaN")) {
            word->word_type = NAN;
            word->u.nan = "NaN";
            return;
        }

        word->word_type = NUM;

        if (isOctalInteger(str)) {
            word->u.number.val_type = UNSIGNED_INT;
            errno = 0;
            res_ull = strtoull(str, &endptr, OCTAL);

            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid unsigned long long
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ull == ULLONG_MAX) && errno == ERANGE) {
                // number oveflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            word->u.number.val._unsigned_int = res_ull;
            return;
        }

        if (isHexInteger(str)) {
            word->u.number.val_type = UNSIGNED_INT;

            errno = 0;
            res_ull = strtoull(str, &endptr, HEX);
            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid unsigned long long
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ull == ULLONG_MAX) && errno == ERANGE) {
                // number oveflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            word->u.number.val._unsigned_int = res_ull;
            return;
        }

        if (isDecimalInteger(str)) {
            word->u.number.val_type = UNSIGNED_INT;

            errno = 0;
            res_ull = strtoull(str, &endptr, DECIMAL);
            if (res_ull == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid unsigned long long
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ull == ULLONG_MAX) && errno == ERANGE) {
                // number oveflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            word->u.number.val._unsigned_int = res_ull;
            return;
        }

        if (isDouble(str)) {
            errno = 0;
            res_ld = strtold(str, &endptr);
            if (res_ld == 0 && (errno != 0 || endptr == str)) {
                // input is not a valid long double
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }
            if ((res_ld == LDBL_MAX || res_ld == LDBL_MIN) && errno == ERANGE) {
                // number over/underflows range
                word->word_type = NAN;
                word->u.nan = str;
                return;
            }

            if (hasFracPart(res_ld)) {
                // Number contains something non-zero anywhere after "."
                word->u.number.val_type = DOUBLE;
                word->u.number.val._double = res_ld;
                return;
            }
            // Number looks like -5.0, -81.00000, etc. Treat it as an integer
            word->u.number.val_type = UNSIGNED_INT;
            word->u.number.val._unsigned_int = res_ld;
            return;
        }
    }

    // Couldn't convert given word to any type of number - set it to NaN
    word->word_type = NAN;
    word->u.nan = str;
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

bool isDigit(char c)
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
    if (strlen(str) < strlen("0x")) {
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

/*void sortGroups(GroupSet *gs)
{
    qsort(gs->groups->data, scv_size(gs->groups), sizeof(Group), groupcmp);
}*/

void sortMultisets(Line *line)
{
    qsort(line->nums_multiset->data, scv_size(line->nums_multiset), sizeof(CountedWord), cwNumbercmp);
    qsort(line->strings_multiset->data, scv_size(line->strings_multiset), sizeof(CountedWord), cwNancmp);
}

int sameTypecmp(const Number *num_a, const Number *num_b)
{
    if (num_a->val_type != num_b->val_type) {
        fprintf(stderr, "ERROR: Trying to compare numbers of differing types\n");
        exit(EXIT_FAILURE);
    }

    switch (num_a->val_type) {
        case UNSIGNED_INT:
            if (num_a->val._unsigned_int < num_b->val._unsigned_int) {
                return -1;
            }
            if (num_a->val._unsigned_int > num_b->val._unsigned_int) {
                return 1;
            }
            return 0;
        case NEGATIVE_INT:
            if (num_a->val._negative_int < num_b->val._negative_int) {
                return -1;
            }
            if (num_a->val._negative_int > num_b->val._negative_int) {
                return 1;
            }
            return 0;
        case DOUBLE:
            if (num_a->val._double < num_b->val._double) {
                return -1;
            }
            if (num_a->val._double > num_b->val._double) {
                return 1;
            }
            return 0;
    }
}

int diffTypecmp(const Number *num_a, const Number *num_b)
{
    if (num_a->val_type == UNSIGNED_INT && num_b->val_type == NEGATIVE_INT) {
        return 1;
    }

    if (num_a->val_type == UNSIGNED_INT && num_b->val_type == DOUBLE) {
        if ((long double)num_a->val._unsigned_int > LDBL_MAX || (long double)num_a->val._unsigned_int > num_b->val._double) {
            return 1;
        }
        if ((long double)num_a->val._unsigned_int < LDBL_MIN || (long double)num_a->val._unsigned_int < num_b->val._double) {
            return -1;
        }
        else return 0;
    }

    if (num_a->val_type == NEGATIVE_INT && num_b->val_type == UNSIGNED_INT) {
        return -1;
    }

    if (num_a->val_type == NEGATIVE_INT && num_b->val_type == DOUBLE) {
        if ((long double)num_a->val._negative_int > LDBL_MAX || (long double)num_a->val._negative_int > num_b->val._double) {
            return 1;
        }
        if ((long double)num_a->val._negative_int < LDBL_MIN || (long double)num_a->val._negative_int < num_b->val._double) {
            return -1;
        }
        else return 0;
    }

    if (num_a->val_type == DOUBLE && num_b->val_type == UNSIGNED_INT) {
        if (num_a->val._double < 0 || (long double)num_b->val._unsigned_int > LDBL_MAX) {
            return -1;
        }
        if (num_a->val._double > (long double)num_b->val._unsigned_int) {
            return 1;
        }
        else return 0;
    }

    if (num_a->val_type == DOUBLE && num_b->val_type == NEGATIVE_INT) {
        if (num_a->val._double >= 0 || (long double)num_a->val._negative_int < LDBL_MIN || num_a->val._double > (long double)num_b->val._negative_int) {
            return 1;
        }
        if (num_a->val._double < (long double)num_b->val._negative_int) {
            return -1;
        }
        else return 0;
    }

    fprintf(stderr, "ERROR: Trying to compare numbers of unknown/same types\n");
    exit(EXIT_FAILURE);
}

int my_memcmp(const void *a, const void *b) {
    return memcmp(a, b, VAR_SIZE_8_BYTES);
}

/*int groupcmp(const void *a, const void *b) {
    Group *g_a = (Group*)a;
    Group *g_b = (Group*)b;

    uint *index_a = scv_at(g_a->lines, 0);
    uint *index_b = scv_at(g_b->lines, 0);

    if (index_a == NULL || index_b == NULL) {
        fprintf(stderr, "Cannot compare with empty group\n");
        exit(EXIT_FAILURE);
    }
*//*    int comp =  memcmp(scv_at(((Group*)a)->lines, 0), scv_at(((Group*)a)->lines, 0), sizeof(uint));

    if (comp < 0) {
        return -1;
    }
    if (comp > 0) {
        return -1;
    }
    return 0;*//*

    if (*index_a < *index_b) {
        return -1;
    }
    if (*index_a > *index_b) {
        return 1;
    }
    return 0;
}*/

void printGroups(GroupSet *gs)
{
    Group *group = NULL;
    // TODO: wiadomo, że to ma być do pliku
    for (uint i = 0; i < scv_size(gs->groups); i++) {
        group = GET_ITEM(Group, gs->groups, i);
        printGroup(group);
    }
}

void printGroup(Group *g)
{
    // TODO: wiadomo, że to ma być do pliku
    for (uint i = 0; i < scv_size(g->lines); i++) {
        printf("%u ", *GET_ITEM(uint, g->lines, i));
    }
    printf("\n");
}

void getLines(LineSet *ls)
{
    scv_vector *temp = scv_new(sizeof(Line), INIT_CAP);
    if (temp == NULL){
        fprintf(stderr, "ERROR: Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    ls->lines = temp;

    uint line_index = 1;
    char *line_as_str = NULL;
    size_t len = 0;
    ssize_t nread;


    while ((nread = getline(&line_as_str, &len, stdin)) != -1) {
        Line line;
        if (nread != strlen(line_as_str)) {
            createLine(&line, NULL, line_index++);
        }
        else {
            createLine(&line, line_as_str, line_index++);
        }
        if (scv_push_back(ls->lines, &line) != SCV_OK){
            fprintf(stderr, "Error during pushback\n");
            exit(EXIT_FAILURE);
        }
    }
}

void generateGroups(GroupSet *gs, LineSet *ls)
{
    scv_vector *temp1 = scv_new(sizeof(Group), INIT_CAP);
    if (temp1 == NULL){
        fprintf(stderr, "ERROR: Ran out of memory!\n");
        exit(EXIT_FAILURE);
    }
    gs->groups = temp1;


    for (uint i = 0; i < scv_size(ls->lines); i++) {
        Line *line_i = GET_ITEM(Line, ls->lines, i);

        if (!line_i->belongs_to_group) {
            // create new cur_group based on current line, add current line to it
            //TODO: czy tu potrzebny malloc()... dwukrotnie ?

            Group *cur_group = NULL;
            Group *temp2 = malloc(sizeof(Group));
            if (temp2 == NULL) {
                fprintf(stderr, "ERROR: Ran out of memory!\n");
                exit(EXIT_FAILURE);
            }
            cur_group = temp2;

            scv_vector *temp3 = scv_new(sizeof(uint*), INIT_CAP);
            if (temp3 == NULL) {
                fprintf(stderr, "ERROR: Ran out of memory!\n");
                exit(EXIT_FAILURE);
            }
            cur_group->lines = temp3;

            if (scv_push_back(cur_group->lines, &line_i->line_num) != SCV_OK) {
                fprintf(stderr, "Error during pushback\n");
                exit(EXIT_FAILURE);
            }

            for (uint j = i + 1; j < scv_size(ls->lines); j++) {
                Line *line_j = GET_ITEM(Line, ls->lines, j);

                bool res1 = line_j != NULL;
                bool res2 = areLinesEqual(line_i, line_j);
                //TODO: jebie się na j=5
                bool res3 = !line_j->belongs_to_group;

/*                if (line_j != NULL && areLinesEqual(line_i, line_j) && !line_j->belongs_to_group) {
                    if (scv_push_back(cur_group->lines, &line_j->line_num) != SCV_OK) {
                        fprintf(stderr, "Error during pushback\n");
                        exit(EXIT_FAILURE);
                    }
                    line_j->belongs_to_group = true;
                }*/

                if (res1) {
                    if (res2) {
                        if (res3) {
                            if (scv_push_back(cur_group->lines, &line_j->line_num) != SCV_OK) {
                                fprintf(stderr, "Error during pushback\n");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                    line_j->belongs_to_group = true;
                }
            }
            line_i->belongs_to_group = true;

            // add current group to groupset
            if (scv_push_back(gs->groups , cur_group) != SCV_OK) {
                fprintf(stderr, "Error during pushback\n");
                exit(EXIT_FAILURE);
            }
        }
        // in case we didn't find matching lines, the cur_group will be a singleton
        // i.e. all lines are in some sort of cur_group - with oneself or with others
    }
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

ssize_t my_getline(char **_lineptr, size_t *_n)
{
    //TODO: zrobić to obcinanie tutaj
    ssize_t lineSize =  getline(_lineptr, _n, stdin);
    //*_lineptr[strcspn(*_lineptr, "\n")] = '\0';
    return lineSize;
}

void printNans(Line *line)
{
    char *str = NULL;
    CountedWord *cw = NULL;

    for (int i = 0 ; i < scv_size(line->strings_multiset); i++) {
        cw = GET_ITEM(CountedWord, line->strings_multiset, i);
        str = cw->word.u.nan;
        printf("%s | %zu\n", str, cw->num_occurrences);
    }
}

void printNumbers(Line *line)
{
    Number num;
    CountedWord *cw = NULL;

    for (int i = 0 ; i < scv_size(line->nums_multiset); i++) {
        cw = GET_ITEM(CountedWord, line->nums_multiset, i);
        num = cw->word.u.number;

        switch (num.val_type) {
            case UNSIGNED_INT:
                printf("%llu | %zu\n", num.val._unsigned_int, cw->num_occurrences);
                break;
            case NEGATIVE_INT:
                printf("%lli | %zu\n", num.val._negative_int, cw->num_occurrences);
                break;
            case DOUBLE:
                printf("%Lf | %zu\n", num.val._double, cw->num_occurrences);
                break;
        }
    }
}

bool areLinesEqual(Line *l1, Line *l2)
{
    return (vectorEquals(l1->strings_multiset, l2->strings_multiset) &&
    vectorEquals(l1->nums_multiset, l2->nums_multiset));
}