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
	// i represents index into population
	// j represents index into solution i
	for (int i = 0; i < popSize; i++){
		for (int j = 0; j < n; j++) {
			(*solutions)[i][j] = rand() % 2;
		}
	}
}

void init_with_zero(int *** solutions, int n, int popSize) {
	*solutions = (int**)malloc(sizeof(int*) * popSize);
	for (int i = 0; i < n; i++) {
		(*solutions)[i] = (int*)malloc(sizeof(int)*n);
	}
	// i represents index into population
	// j represents index into solution i
	for (int i = 0; i < popSize; i++){
		for (int j = 0; j < n; j++) {
			(*solutions)[i][j] = 0;
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

void bit_flip(int** tab, int n){
	float randVal = 0;
	float proba = 1/n;
	for (int i = 0; i < n; i++){
		randVal = (float)rand()/(float)(RAND_MAX/1);
		if (randVal <= proba) {
			if ((*tab)[i] == 0){
				(*tab)[i] = 1;
			}
			else {
				(*tab)[i] = 0;
			}
		}
	}
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

	if (total == 0) {
		toReturn[0] = rand() % popSize;
		toReturn[1] = rand() % popSize;
		return toReturn;
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


// select 3 randomly and chose de best (return 2)
int * tourn(int ** solution, int n, int popSize){
	int nbr = 4;

	int * toReturn = (int*)malloc(sizeof(int) * 2);
	int * tmp = (int*)malloc(sizeof(int)*nbr);
	int tmpRand = 0;
	int cmp = 0;
	while(cmp < nbr) {
		tmpRand = rand() % popSize;
		if (isInto(tmpRand, tmp, cmp) == 0){
			tmp[cmp] = tmpRand;
			cmp++;
		}
	}
	int val = tmp[0];
	int index = 0;
	for (int i = 1; i < nbr; i++) {
		if (tmp[i] < val) {
			index = i;
			val = tmp[i];
		}
	}

	cmp = 0;
	for (int i = 0; i < nbr; i++) {
		if (i != index) {
			toReturn[cmp] = tmp[i];
			cmp++;
		}
	}
	free(tmp);
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

void init_mat_hamming(int *** mat, int ** sol, int n, int popSize) {
	(*mat) = (int**) malloc(sizeof(int *) * popSize);
	for (int i = 0; i < popSize; i++) {
		(*mat)[i] = (int*)malloc(sizeof(int) * popSize);
	}
	
	for (int i = 0; i < popSize; i++) {
		for (int j = i; j < popSize; j++) {
			(*mat)[i][j] = hamming(sol[i], sol[j], n);
		}
	}
}

void update_mat_hamming(int *** mat, int ** sol, int newi, int newj, int n, int popSize){
	for (int i = 0; i < popSize; i++) {
		(*mat)[i][newj] = hamming(sol[i], sol[newj], n);
		(*mat)[newj][i] = hamming(sol[i], sol[newj], n);
		(*mat)[i][newi] = hamming(sol[i], sol[newi], n);
		(*mat)[newi][i] = hamming(sol[i], sol[newi], n);
	}
}

int hamming(int * sol1, int * sol2, int n) {
	int toReturn = 0;
	for (int i = 0; i < n ;i++) {
		if (sol1[i] != sol2[i]){
			toReturn++;
		}
	}
	//printf("hamming %d\n", toReturn);
	return toReturn;
}

float average_hamming(int ** mat, int popSize) {
	float toReturn = 0;
	int cmp = 0;
	for (int i = 0; i < popSize; i++) {
		for (int j = i; j < popSize; j++){
			toReturn += mat[i][j];
			cmp++;
		}
	}

	//printf("average_hamming %f\n", toReturn );
	toReturn /= cmp;

	return toReturn;
}

///////////////////////////////////////////
//////////////////////////////////////////

void first_algorithm(int popSize, char* fileName){
	int ** solutions;
	int n = 10;

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
	print_solutions(solutions, n, popSize);
	printf("average_hamming = %f \n", average_hamming(matHamming, popSize));

	for (int i = 0; i < popSize; i++) {
		printf("i = %d : fitness = %d \n", i, fitness(solutions[i], n));
	}

	while (cmp < 1000 && done == 0) {

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


// return 0 if false, 1 if true
int isInto(int j, int* toRem, int rmsize) {
	for (int i = 0; i < rmsize; i++) {
		if (toRem[i] == j){
			return 1;
		}
	}
	return 0;
}

// moyenne

void writeInFile(int ** solutions, int n, int popSize, char* fileName, int cmp, int ** matHamming) {
	FILE* file = NULL;
	FILE * file2 = NULL;
	FILE * file3 = NULL;
	char * line = (char*)malloc(sizeof(char) * strlen(fileName));
	char * lineBest = (char*) malloc(sizeof(char) * (strlen(fileName)+5));
	char * lineH = (char*) malloc(sizeof(char) * (strlen(fileName)+5));
	
	strcpy(line, fileName);
	strcpy(lineBest, fileName);
	strcat(lineBest, "bf");
	strcpy(lineH, fileName);
	strcat(lineH, "ham");

	if (cmp > 0) {
		file = fopen(line, "a");
		file2 = fopen(lineBest, "a");
		file3 = fopen(lineH, "a");
	}
	else {
		file = fopen(line, "w");
		file2 = fopen(lineBest, "w");
		file3 = fopen(lineH, "w");
	}

	float fit = 0;
	int bf = 0;
	for (int i = 0; i < popSize; i++) {
		fit += fitness(solutions[i], n);
		if (fitness(solutions[i],n) > bf) {
			bf = fitness(solutions[i],n);
		}
	}
	fit /= popSize;

	if (file != NULL){
		fprintf(file,"%f", fit);
		fprintf(file, "\n");
		fclose(file);
	}
	if (file2 != NULL) {
		fprintf(file2,"%d", bf);
		fprintf(file2, "\n");
		fclose(file2);
	}
	if (file3 != NULL) {
		fprintf(file3,"%f", average_hamming(matHamming, popSize) );
		fprintf(file3, "\n");
		fclose(file3);
	}
	else {
		printf("error with 2nd file \n");
	}


	free(line);
	free(lineBest);
}