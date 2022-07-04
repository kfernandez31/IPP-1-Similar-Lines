#ifndef __PRINTING_OUTPUT_H__
#define __PRINTING_OUTPUT_H__

#include <stdlib.h>
#include <stdio.h>
#include "line_structures.h"

/*
 * Prints all groups in Ls.
 */
void printGroups(LineSet *ls);

/*
 * Prints into a file which lines contained illegal characters.
 */
void printErrorMessages(const LineSet *ls);

/*
 * Frees all the lines in a LineSet.
 */
void freeLineSet(LineSet *ls);

/*
 * Prints all lines of a LineSet. Used for debugging purposes.
 */
void printLines(const LineSet *ls);


#endif //__PRINTING_OUTPUT_H__
