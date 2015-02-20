#include "methods.h"


////////// ALGORITHMS/////////////////////////////////
//////////////////////////////////////////

void first_algorithm(int solSize, char* fileName){
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

	//generate_random_sols(&solutions, n, popSize);
	init_with_zero(&solutions, n, popSize);
	init_mat_hamming(&matHamming, solutions, n, popSize);
	//print_solutions(solutions, n, popSize);
	//printf("average_hamming = %f \n", average_hamming(matHamming, popSize));

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	while (cmp < 100000 && done == 0) {

		printf("%d \n", cmp);

		//printf("%d : average_hamming = %f \n", cmp, average_hamming(matHamming, popSize));

		//print_mat(matHamming, popSize);

		//print_solutions(matHamming, popSize, popSize);

		writeInFile(solutions, n, popSize, fileName, cmp, matHamming);
		rws = roulette_wheel_selection(solutions, n, popSize);

		children = one_point_crossover(solutions[rws[0]], solutions[rws[1]], n);

		worst = get_worst(solutions, n, popSize);

		replace(&solutions, children[0], worst[0], n);
		replace(&solutions, children[1], worst[1], n);

		probability = (float)rand()/(float)(RAND_MAX/1);
		if (probability <= acceptance) {
			one_flip(&solutions[worst[0]],n);
			one_flip(&solutions[worst[1]], n);
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




void bandit() {

}

