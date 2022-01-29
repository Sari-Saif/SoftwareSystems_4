CC=gcc
AR=ar
FLAGS= -Wall -g

all: graph

graph: graph.o algo.o main.o
	$(CC) $(FLAGS) -o graph graph.o algo.o main.o

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

algo.o: algo.c algo.h graph.h
	$(CC) $(FLAGS) -c algo.c

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

clean:
	rm -f *.o *.a *.so graph