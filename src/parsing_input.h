#ifndef __PARSING_INPUT__
#define __PARSING_INPUT__


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <errno.h>
#include <math.h>
#include "line_structures.h"
#include "group_handling.h"


/*
 * Reads lines from standard input, converting each to an instance f struct Line, and adding them to an instance
 * of struct LineSet.
 */
void getLines(LineSet *ls);


#endif //__PARSING_INPUT__