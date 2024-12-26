CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

TARGET = mymake

SRCS = mymake.c parser.c graph.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c mymake.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean