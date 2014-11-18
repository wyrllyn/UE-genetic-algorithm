program: main.o methods.o print_methods.o
	gcc main.o methods.o print_methods.o -O3 -o program -std=c99

main.o: main.c 
	gcc -c main.c -o main.o -O3 -std=c99

methods.o: methods.c
	gcc -c methods.c -o methods.o -O3 -std=c99

print_methods.o: print_methods.c
	gcc -c print_methods.c -o print_methods.o -O3 -std=c99

clean:
	rm -rf *.o