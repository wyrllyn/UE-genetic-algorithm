#include "methods.h"
#include "time.h"

// evaluation function
int fitness(int* tab, int size){
	int res = 0;
	for (int i = 0; i < size; i++) {
		if (tab[i] == 1) {
			res++;
		}
	}
	return res;
}

void generate_random_sols(int *** solutions, int n, int popSize) {
	*solutions = (int**)malloc(sizeof(int*) * popSize);
	for (int i = 0; i < n; i++) {
		(*solutions)[i] = (int*)malloc(sizeof(int)*n);
	}
	srand(time(NULL));
	// i represents index into population
	// j represents index into solution i
	for (int i = 0; i < popSize; i++){
		for (int j = 0; j < n; j++) {
			(*solutions)[i][j] = rand() % 2;
		}
	}
}

void one_flip(int** tab, int n) {
	int index = rand() % n;
	int toChange = (*tab)[index];
	if (toChange == 0) {
		(*tab)[index] = 1;
	}
	else {
		(*tab)[index] = 0;
	}
}

void k_flip(int**tab, int n, int k){
	int * index = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) {
		index[i] = -1;
	}
	int tmp = -1;
	if (k > n) {
		printf("error, k > n is not ok \n");
	}
	else {
		for (int i = 0; i < k; i++) {
			tmp = -1;
			while(isInto(tmp, index, n) == 1 || tmp < 0){
				tmp = rand() % n;
			}
			index[i] = tmp;
			printf("i = %d, tmp = %d \n", i, tmp);
		}
		for (int j = 0; j < k ; j++) {
			tmp = (*tab)[index[j]];
			if (tmp == 0) {
				(*tab)[index[j]] = 1;
			}
			else {
				(*tab)[index[j]] = 0;
			}
		}
	}

	free(index);
}


//generates 2 children
int** one_point_crossover(int * tab1, int* tab2, int n){
	int index = rand() % n;
	int** children = (int**)malloc(sizeof(int*)*2);
	for (int i = 0; i < 2; i++){
		children[i] = (int*)malloc(sizeof(int)*n);
	}
	for (int i = 0; i < n; i++) {
		if (i < index) {
			children[0][i] = tab1[i];
			children[1][i] = tab2[i];
		}
		else {
			children[0][i] = tab2[i];
			children[1][i] = tab1[i];
		}
	}
	return children;
}

int ** uniform_crossover(int* tab1, int* tab2, int n) {
	int** children = (int**)malloc(sizeof(int*)*2);
	for (int i = 0; i < 2; i++){
		children[i] = (int*)malloc(sizeof(int)*n);
	}

	int * mask = (int*)malloc(sizeof(int) * n);
	for (int j = 0; j < n; j++) {
		mask[j] = rand() % 2;
	}

	for (int i = 0; i < n; i++) {
		if (mask[i] == 0) {
			children[0][i] = tab1[i];
			children[1][i] = tab2[i];
		}
		else {
			children[0][i] = tab2[i];
			children[1][i] = tab1[i];
		}
	}
	return children;
}

// returns index (2) of future parents
int * roulette_wheel_selection(int ** solutions, int n, int popSize) {
	int * toReturn = (int*)malloc(sizeof(int) * 2);
	float * probability = (float*)malloc(sizeof(float) * popSize);
	int total = 0;

	for (int i = 0; i < popSize; i++) {
		probability[i] = fitness(solutions[i], n);
		total+= probability[i];
	}
	for (int i = 0; i < popSize; i++) {
		probability[i]/=total;
	}

	float tmp = 0;
	for (int i = 0; i < popSize; i++) {
		tmp += probability[i];
	}
	//modification

	float firstRand = (float)rand()/(float)(RAND_MAX/1);
	tmp = 0;
	for (int i = 0; i < popSize; i++) {
		tmp += probability[i];
		if (firstRand < tmp){
			toReturn[0] = i;
			break;
		}
	}
	toReturn[1] = toReturn[0];
	while(toReturn[1] == toReturn[0]) {
		firstRand = (float)rand()/(float)(RAND_MAX/1);
		tmp = 0;
		for (int i = 0; i < popSize; i++) {
			tmp += probability[i];
			if (firstRand < tmp){
				toReturn[1] = i;
				break;
			}
		}
	}

	return toReturn;
}

////////////////////////////////////////
// REPLACEMENT STEADY-STATE TYPE ////////

void replace(int *** solutions, int* child, int index, int n) {
	for (int i = 0; i < n; i++){
		(*solutions)[index][i] = child[i];
	}
}

// returns index of solutions with the lowest fitness value / 2
int * get_worst(int ** solution, int n, int popSize){
	int tmp = n*10;
	int inter = 0;
	int * toReturn = (int*)malloc(sizeof(int) * 2);
	toReturn[0] = -1;
	toReturn[1] = -1;
	for (int i = 0; i < popSize; i++){
		inter = fitness(solution[i], n);
		if (inter < tmp) {
			tmp = inter;
			toReturn[0] = i;
		}
	}
	tmp = n*10;
	for (int i = 0; i < popSize; i++){
		inter = fitness(solution[i], n);
		if (inter < tmp && i != toReturn[0]) {
			tmp = inter;
			toReturn[1] = i;
		}
	}
	return toReturn;
}

///////////////////////////////////////////
//////////////////////////////////////////

void first_algorithm(int popSize){
	int ** solutions;
	int n = 10;

	int * rws;
	int * worst;
	int ** children;

	int cmp = 0;

	int done = 0;

	float probability;
	float acceptance = 0.5;

	generate_random_sols(&solutions, n, popSize);
	print_solutions(solutions, n, popSize);

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	while (cmp < 10000 && done == 0) {

		rws = roulette_wheel_selection(solutions, n, popSize);

	//	print_tab(solutions[rws[0]], n);
	//	print_tab(solutions[rws[1]], n);

		children = one_point_crossover(solutions[rws[0]], solutions[rws[1]], n);

	//	print_tab(children[0], n);
	//	print_tab(children[1], n);

		worst = get_worst(solutions, n, popSize);
		//printf("%d and %d \n", worst[0], worst[1]);

		replace(&solutions, children[0], worst[0], n);
		replace(&solutions, children[1], worst[1], n);

		probability = (float)rand()/(float)(RAND_MAX/1);
		if (probability < acceptance) {
			one_flip(&solutions[worst[0]], n);
			one_flip(&solutions[worst[1]], n);
		}

		cmp++;

		for (int i = 0; i < popSize; i++) {
			if (fitness(solutions[i], n) == n) {
				done = 1;
				break;
			}
		}
	}

	print_solutions(solutions, n, popSize);

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	printf("cmp = %d\n", cmp );

}

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

// return 0 if false, 1 if true
int isInto(int j, int* toRem, int rmsize) {
	for (int i = 0; i < rmsize; i++) {
		if (toRem[i] == j){
			return 1;
		}
	}
	return 0;
}