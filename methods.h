#ifndef METHOD_H
#define METHOD_H

#include "print_methods.h"

void first_algorithm(int solSize, char* fileName, int select, int cross, int mut, int insert, int count);
void write_fitness_per_iteration(int* fit, int size, int pop, int select, int cross, int mut, int insert, int count);

#endif