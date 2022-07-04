#ifndef __GROUP_HANDLING_H__
#define __GROUP_HANDLING_H__

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "line_structures.h"


/*
 * Creates groups of similar lines based on the LineSet instance created by getLines().
 * Example of line contents that will lead to a group being created:
 * {{9, abc}, {abc, 0x09}, {011, ABC}, {.9e1, aBc}, {ABc, 09}}
 */
void generateGroups(LineSet *ls);

/**
 * Returns true if a true value is returned by comparing both number's values using "==".
 * Since numbers that return false in hasFracPart() are converted integers, no doubles will ever return true when
 * compared to an integer with this function.
 */
bool numberEquals(const Number *num1, const Number *num2);


/**
 * Sorting function for both multisets of a line.
 */
void sortMultisets(Line *line);

#endif //__GROUP_HANDLING_H__
