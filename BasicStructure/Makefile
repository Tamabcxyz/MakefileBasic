#should be link 
build: my_lib.o main.o
	gcc my_lib.o main.o -o main

#don't need to link so should use -c option in gcc
my_lib.o:
	gcc -c my_lib.c -o my_lib.o

#don't need to link so should use -c option in gcc
main.o:
	gcc -c main.c -o main.o

execute:
	./main

clean:
	rm -rf *.o
	rm -rf main