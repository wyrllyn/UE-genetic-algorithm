#include "methods.h"


//main
int main (int argc, char** argv){
/*	int n = 10; // size of a solution
	int popSize = 5;
	int ** solutions;

	generate_random_sols(&solutions, n, popSize);

	print_solutions(solutions, n, popSize);

	int * rws = roulette_wheel_selection(solutions, n, popSize);
	printf("chosen index 1 : %d, index 2 : %d \n",rws[0], rws[1]);*/

	first_algorithm(5);




	// shows fitness for each solution
/*	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}*/
	//k_flip(&solutions[0], n, 5);

	//print_solutions(solutions, n, popSize);

	//int* solution = malloc(sizeof(int) * n);

	//TODO : free method

	return 0;
}