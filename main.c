#include "methods.h"


//main
int main (int argc, char** argv){

	int sizePop = 100;
	int select = 2;
	int cross = 1;
	int mut = 1;
	int insert = 1;
	int count = 20;
	if (argc > 1) sizePop = atoi(argv[1]);
	if (argc > 2) select = atoi(argv[2]);
	if (argc > 3) cross = atoi(argv[3]);
	if (argc > 4) mut = atoi(argv[4]);
	if (argc > 5) insert = atoi(argv[5]);
	if (argc > 6) count = atoi(argv[6]);

	
	first_algorithm(sizePop, "trace.txt", select, cross, mut, insert, count);


	return 0;
}