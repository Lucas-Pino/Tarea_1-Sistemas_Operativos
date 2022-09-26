
default: tarea1
tarea1: linkedList.o main.o
	gcc -g -Wall -o tarea1 main.o linkedList.o
main.o: main.c linkedList.o
	gcc -g -Wall -c main.c
funciones.o: linkedList.c linkedList.h
	gcc -g -Wall -c linkedList.c
run: ./tarea1

clean:
	rm *.o
purge:
	rm tarea1