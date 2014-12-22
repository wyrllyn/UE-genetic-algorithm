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

void print_mat(int ** mat, int popSize){
	for (int i = 0; i < popSize; i++) {
		for (int j= 0; j < popSize; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

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