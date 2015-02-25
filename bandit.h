#ifndef BANDIT_H
#define BANDIT_H
#include "utils.h"
#include <math.h>
#include <stdio.h>

int* ActionMax(float* E, int sizeE);
int choix_uniforme(int nba);
int tirage_aleatoire(float* proba, int sizeP);
int UCB1(float* R, int sizeR, int iter, int* Actions, int sizeA);
int roulette_adaptative(float* R, int sizeR, float ** Proba, int sizeP, float Pmin);
int adaptive_pursuit(float* R, int sizeR, float** Proba, float Pmin, float alpha);
int choice(int n, float ** proba, float ** R, int ** Actions, int method, int iter);
int max(float* R, int sizeR);


#endif