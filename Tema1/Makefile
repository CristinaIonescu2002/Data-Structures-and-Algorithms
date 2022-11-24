FLAGS = -lm -g -std=c11
CC = gcc

all: tema1

build: tema1

tema1: tema1.o
	$(CC) -o $@ $^ $(FLAGS)

tema1.o: tema1.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f tema1 *.o

run: tema1
	./tema1 --c < ex.txt

memcheck:
	valgrind --leak-check=full -s --error-exitcode=2 ./tema1 --c < ex.txt
