CC = gcc
CFLAGS = -Wall -g
OBJS = main.o parser.o graph.o utils.o
TARGET = mymake2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c parser.h graph.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h graph.h utils.h
	$(CC) $(CFLAGS) -c parser.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)
