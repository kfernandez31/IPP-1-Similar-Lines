#include "printing_output.h"

/**
 * Prints all strings in line.nansMultiset. Used for debugging purposes.
 */
static void printNans(const Line *line);

/**
 * Prints all strings in line.numbers_multiset. Used for debugging purposes.
 */
static void printNumbers(const Line *line);

/**
 * Prints both multisets of a line. Used for debugging purposes.
 */
static void printLineContents(const Line *line);



static void printNans(const Line *line)
{
    char *str = NULL;
    CountedWord *cw = NULL;

    for (size_t i = 0 ; i < line->nansMultiset->size; i++) {
        cw = GET_ITEM(CountedWord, line->nansMultiset, i);
        str = cw->word.u.nan;
        printf("%s | %zu\n", str, cw->num_occurrences);
    }
}

static void printNumbers(const Line *line)
{
    Number num;
    CountedWord *cw = NULL;

    for (size_t i = 0 ; i < line->numbersMultiset->size; i++) {
        cw = GET_ITEM(CountedWord, line->numbersMultiset, i);
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

static void printLineContents(const Line *line)
{
    printf("=== PRINTING MULTISETS OF LINE %zu ===\n", line->line_num);
    if (line->line_type == LEGAL) {
        printNans(line);
        printNumbers(line);
    }
    else if (line->line_type == IGNORED) {
        printf("##IGNORED##\n");
    }
    else if (line->line_type == ILLEGAL) {
        printf("--ILLEGAL--\n");
    }
}

void printGroups(LineSet *ls)
{
    for (int i = 0; i <= ls->highest_group_num; i++) {
        int first_idx = 0;
        for (int j = 0; j < (int) ls->lines->size; j++) {
            Line *line_j = GET_ITEM(Line, ls->lines, j);

            if (line_j->group_num == i) {
                fprintf(stdout, "%zu", line_j->line_num);
                first_idx = j;
                break;
            }
        }
        for (int j = first_idx + 1; j < (int)ls->lines->size; j++) {
            Line *line_j = GET_ITEM(Line, ls->lines, j);

            if (line_j->group_num == i) {
                fprintf(stdout, " %zu", line_j->line_num);
            }
        }
        fprintf(stdout, "\n");
    }
}

void printErrorMessages(const LineSet *ls)
{
    vector_t *lines = ls->lines;
    for (size_t i = 0; i < lines->size; i++) {
        Line *l = GET_ITEM(Line, lines, i);

        if (l->line_type == ILLEGAL) {
            fprintf(stderr, "ERROR %zu\n", l->line_num);
        }
    }
}

void freeLineSet(LineSet *ls)
{
    for (size_t i = 0; i < ls->lines->size; i++) {
        Line *line = GET_ITEM(Line, ls->lines, i);

        VectorDestroy(line->numbersMultiset);

        if (line->nansMultiset != NULL) {
            for (size_t j = 0; j < line->nansMultiset->size; j++) {
                CountedWord *counted_nan = GET_ITEM(CountedWord, line->nansMultiset, j);
                free(counted_nan->word.u.nan);
            }
        }
        VectorDestroy(line->nansMultiset);
    }
    VectorDestroy(ls->lines);
}

void printLines(const LineSet *ls)
{
    for (size_t i = 0; i < ls->lines->size; i++) {
        Line *l = GET_ITEM(Line, ls->lines, i);
        printLineContents(l);
    }
}