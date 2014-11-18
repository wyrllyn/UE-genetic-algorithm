#ifndef METHOD_H
#define METHOD_H

#include "print_methods.h"

int fitness(int* tab, int size);

void one_flip(int** tab, int n);

void k_flip(int**tab, int n, int k);

int** one_point_crossover(int * tab1, int* tab2, int n);

int ** uniform_crossover(int* tab1, int* tab2, int n);

void generate_random_sols(int *** solutions, int n, int popSize);

int * roulette_wheel_selection(int ** solutions, int n, int popSize);

int * tourn(int ** solution, int n, int popSize);

void replace(int *** solutions, int* child, int index, int n);

int * get_worst(int ** solution, int n, int popSize);

void first_algorithm(int popSize, char* fileName);

int isInto(int j, int* toRem, int rmsize);

void writeInFile(int ** solutions, int n, int popSize, char* fileName);

#endif