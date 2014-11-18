#ifndef PRINT_H
#define PRINT_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void writeInFile(int ** solutions, int n, int popSize, char* fileName);

void print_tab(int* tab, int size);

void print_solutions(int ** solutions, int n, int popSize);

#endif