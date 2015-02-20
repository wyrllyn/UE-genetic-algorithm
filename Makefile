program: main.o methods.o print_methods.o bandit.o utils.o
	gcc main.o methods.o print_methods.o bandit.o utils.o -O3 -o program -std=c99 -lm

main.o: main.c 
	gcc -c main.c -o main.o -O3 -std=c99 -lm

methods.o: methods.c print_methods.o
	gcc -c methods.c -o methods.o -O3 -std=c99 -lm

print_methods.o: print_methods.c bandit.o
	gcc -c print_methods.c -o print_methods.o -O3 -std=c99 -lm

bandit.o: bandit.c utils.o
	gcc -c bandit.c -o bandit.o -O3 -std=c99 -lm

utils.o: utils.c
	gcc -c utils.c -o utils.o -O3 -std=c99 -lm

clean:
	rm -rf *.o