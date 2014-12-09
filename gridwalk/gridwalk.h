#ifndef GRIDWALK_H
#define GRIDWALK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


int max(int first, int second);

bool inBounds(int x, int y);

int visitCell(int x, int y);

int sumDigits(int x, int y);

int length();



#endif
