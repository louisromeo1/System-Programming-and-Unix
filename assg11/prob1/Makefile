CC = gcc
CFLAGS = -Wall -g

all: bacon

bacon: bacon.o graph.o queue.o
	$(CC) $(CFLAGS) -o bacon bacon.o graph.o queue.o

bacon.o: bacon.c graph.h queue.h
	$(CC) $(CFLAGS) -c bacon.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f *.o bacon