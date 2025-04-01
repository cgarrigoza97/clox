CC = gcc
CFLAGS = -Wall -I.
TARGET = clox
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	del /Q $(TARGET).exe $(OBJS)