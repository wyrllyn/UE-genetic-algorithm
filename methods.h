#ifndef METHOD_H
#define METHOD_H

#include "print_methods.h"
#include "bandit.h"

void first_algorithm(int solSize, char* fileName, int select, int cross, int mut, int insert, int count);
void write_fitness_per_iteration(int* fit, int size, int pop, int select, int cross, int mut, int insert, int count);
void auto_algo(int solSize, char* fileName, int method) ;
int max(float* R, int sizeR);

#endif