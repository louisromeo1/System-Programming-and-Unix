CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = anagrams2

all: $(TARGET)

$(TARGET): anagrams2.o
	$(CC) $(CFLAGS) -o $(TARGET) anagrams2.o

anagrams2.o: anagrams2.c
	$(CC) $(CFLAGS) -c anagrams2.c

clean:
	rm -f anagrams2.o $(TARGET)

.PHONY: all clean