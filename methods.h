#include "stdio.h"
#include "stdlib.h"

int fitness(int* tab, int size);

void one_flip(int** tab, int n);

void k_flip(int**tab, int n, int k);

int** one_point_crossover(int * tab1, int* tab2, int n);

int ** uniform_crossover(int* tab1, int* tab2, int n);

void generate_random_sols(int *** solutions, int n, int popSize);

int * roulette_wheel_selection(int ** solutions, int n, int popSize);

void replace(int *** solutions, int* child, int index, int n);

int * get_worst(int ** solution, int n, int popSize);

void first_algorithm(int popSize);

void print_tab(int* tab, int size);

void print_solutions(int ** solutions, int n, int popSize);

int isInto(int j, int* toRem, int rmsize);