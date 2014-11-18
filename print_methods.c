#include "print_methods.h"

void print_tab(int* tab, int size){
	for (int i = 0; i < size; i++){
		printf("%d", tab[i]);
	}
	printf("\n");
}


// print solutions // verification method
void print_solutions(int ** solutions, int n, int popSize) {
	for (int i = 0; i < popSize; i++) {
		printf(" solution %d : ", i);
		for (int j = 0; j < n ; j++){
			printf("%d", solutions[i][j]);
		}
		printf("\n");
	}
}