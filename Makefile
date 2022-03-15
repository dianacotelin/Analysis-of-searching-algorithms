CC = gcc
CFLAGS = -g -Wall
DEPS = algo.h
OBJ = algo.o algo2.c

build: algo.o algo2.o

run-best:
	./algo2

run-p1:
	./algo

run-p2:
	./algo2

algo.o: algo.c
	gcc algo.c -o algo $(CFLAGS)

algo2.o: algo.c
	gcc algo2.c -o algo2 $(CFLAGS)

clean:
	rm -rf *.o algo algo2
