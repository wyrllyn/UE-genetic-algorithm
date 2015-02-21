#include "methods.h"

int cmp_max = 500000;

////////// ALGORITHMS/////////////////////////////////
//////////////////////////////////////////

void first_algorithm(int solSize, char* fileName, int select, int cross, int mut, int insert, int count){
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

	//for replacement
	int * age= (int*)malloc(sizeof(int) * popSize);
	for (int i = 0; i < popSize; i++) age[i] = 0;

	init_with_zero(&solutions, n, popSize);
	init_mat_hamming(&matHamming, solutions, n, popSize);

	//best fitness for each iteration
	int* trace = (int*) malloc(sizeof(int) * cmp_max);

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	while (cmp < cmp_max && done == 0) {

		writeInFile(solutions, n, popSize, fileName, cmp, matHamming);
		switch(select) {
			case 1:
				rws = tourn(solutions, n, popSize);
				break;
			case 2:
				rws = best(solutions, n, popSize);
				break;
			case 3 :
				rws = randParents(popSize);
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
				worst = get_oldest(age, popSize);
				//update old
				for(int i = 0; i < popSize ; i++) age[i]++;
				age[worst[0]] = 0;
				age[worst[1]] = 0;
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
		

		int tmp_best = 0;
		for (int i = 0; i < popSize; i++) {
			int tmp_fit = fitness(solutions[i], n);
			if (tmp_fit > tmp_best) tmp_best = tmp_fit;
			if (tmp_fit == n) {
				done = 1;
				break;
			}
		}
		trace[cmp] = tmp_best;
		cmp++;

	}
	writeInFile(solutions, n, popSize, fileName, cmp, matHamming);
//	print_solutions(solutions, n, popSize);

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	if (cmp == cmp_max) printf("MAXIMAL ITERATION NUMBER REACHED\n");

	//for (int i = 0; i < cmp; i++) printf("%d : best = %d\n",i, trace[i]);
	write_fitness_per_iteration(trace, cmp, popSize, select, cross, mut, insert, count);

}

void write_fitness_per_iteration(int* fit, int size, int pop, int select, int cross, int mut, int insert, int count) {
	FILE* file = NULL;
	char* name = (char*)malloc(sizeof(char) * 10);
	name = "res_fit.txt";

	file = fopen(name, "a");

	if(file != NULL) {
		fprintf(file,"# %d %d %d %d %d %d \n", pop, select, cross, mut, insert, count);
		for (int i = 0; i < size; i++) {
			fprintf(file, "%d %d\n", i, fit[i]);
		}
		fclose(file);
	}
}

float calculate_entropy() {
	float toReturn;


	return toReturn; 
}


