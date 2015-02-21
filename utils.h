#ifndef UTILS_H
#define UTILS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

int fitness(int* tab, int size);

void generate_random_sols(int *** solutions, int n, int popSize);

void init_with_zero(int *** solutions, int n, int popSize);

void init_mat_hamming(int *** mat, int ** sol, int n, int popSize);

void update_mat_hamming(int *** mat, int ** sol, int newi, int newj, int n, int popSize);

int hamming(int * sol1, int * sol2, int n);

float average_hamming(int ** mat, int popSize);

void one_flip(int** tab, int n);

void k_flip(int**tab, int n, int k);

void bit_flip(int** tab, int n);

int** one_point_crossover(int * tab1, int* tab2, int n);

int ** uniform_crossover(int* tab1, int* tab2, int n);

int * roulette_wheel_selection(int ** solutions, int n, int popSize);

int * tourn(int ** solution, int n, int popSize);

int * randParents(int popSize);

int * get_oldest(int * age, int popSize);

void replace(int *** solutions, int* child, int index, int n);

int * get_worst(int ** solution, int n, int popSize);

int * best(int ** solutions, int n, int popSize);

int isInto(int j, int* toRem, int rmsize);

#endif