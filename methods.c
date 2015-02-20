#include "methods.h"


////////// ALGORITHMS/////////////////////////////////
//////////////////////////////////////////

void first_algorithm(int solSize, char* fileName, int select, int cross, int mut, int insert){
	int ** solutions;
	int n = solSize;

	int popSize = 10;

	int * rws;
	int * worst;
	int ** children;

	int ** matHamming;

	int cmp = 0;
	int done = 0;
	float probability;
	float acceptance = 0.5;

	srand(time(NULL));

	init_with_zero(&solutions, n, popSize);
	init_mat_hamming(&matHamming, solutions, n, popSize);

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	while (cmp < 100000 && done == 0) {

		writeInFile(solutions, n, popSize, fileName, cmp, matHamming);
		switch(select) {
			case 1:
				rws = roulette_wheel_selection(solutions, n, popSize);
				break;
			case 2:
				//best
				break;
			case 3 :
				//rand
				break;
		}

		switch(cross) {
			case 1:
				children = one_point_crossover(solutions[rws[0]], solutions[rws[1]], n);
				break;
			case 2:
				children = uniform_crossover(solutions[rws[0]], solutions[rws[1]], n);
				break;
		}

		switch(insert) {
			case 1:
				worst = get_worst(solutions, n, popSize);
				break;
			case 2:
				//age
				break;
		}

		replace(&solutions, children[0], worst[0], n);
		replace(&solutions, children[1], worst[1], n);

		probability = (float)rand()/(float)(RAND_MAX/1);
		if (mut != 0 && probability <= acceptance) {
			switch(mut) {
				case 1:
					one_flip(&solutions[worst[0]],n);
					one_flip(&solutions[worst[1]], n);
					break;
				case 2:
					k_flip(&solutions[worst[0]],n,3);
					k_flip(&solutions[worst[1]], n,3);
					break;
				case 3:
					k_flip(&solutions[worst[0]],n,5);
					k_flip(&solutions[worst[1]], n,5);
					break;
				case 4:
					bit_flip(&solutions[worst[0]],n);
					bit_flip(&solutions[worst[1]], n);
					break;
			}

		}

		update_mat_hamming(&matHamming, solutions, worst[0], worst[1], n, popSize);
		cmp++;

		for (int i = 0; i < popSize; i++) {
			if (fitness(solutions[i], n) == n) {
				done = 1;
				break;
			}
		}
	}
	writeInFile(solutions, n, popSize, fileName, cmp, matHamming);
	print_solutions(solutions, n, popSize);

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}
	

	printf("cmp = %d\n", cmp );

}

float calculate_entropy() {
	float toReturn;


	return toReturn; 
}


