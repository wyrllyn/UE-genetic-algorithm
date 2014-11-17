program: main.o methods.o
	gcc main.o methods.o -O3 -o program -std=c99

main.o: main.c 
	gcc -c main.c -o main.o -O3 -std=c99

methods.o: methods.c
	gcc -c methods.c -o methods.o -O3 -std=c99

clean:
	rm -rf *.o