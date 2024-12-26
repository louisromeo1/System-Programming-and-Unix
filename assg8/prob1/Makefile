CC = gcc
CFLAGS = -Wall -g
OBJ = shortestPaths.o

shortestPaths: $(OBJ)
	$(CC) $(CFLAGS) -o shortestPaths $(OBJ)

shortestPaths.o: shortestPaths.c
	$(CC) $(CFLAGS) -c shortestPaths.c

clean:
	rm -f $(OBJ) shortestPaths