#ifndef PRINT_H
#define PRINT_H

#include "bandit.h"


void print_tab(int* tab, int size);

void print_solutions(int ** solutions, int n, int popSize);

void print_mat(int ** mat, int popSize);

void writeInFile(int ** solutions, int n, int popSize, char* fileName, int cmp, int ** matHamming);

#endif