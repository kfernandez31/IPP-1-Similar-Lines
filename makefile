CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
CPPFLAGS =
LDFLAGS  =
VPATH=src

.PHONY: all clean

all: similar_lines

similar_lines : main.o vector.o group_handling.o parsing_input.o printing_output.o vector.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c parsing_input.h group_handling.h printing_output.h
	$(CC) $(CFLAGS) -c $< $(CFLAGS)

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $< $(CFLAGS)

group_handling.o: group_handling.c group_handling.h vector.h
	$(CC) $(CFLAGS) -c $< $(CFLAGS)
printing_output.o: printing_output.c printing_output.h vector.h

parsing_input.o: parsing_input.c parsing_input.h vector.h
	$(CC) $(CFLAGS) -c $< $(CFLAGS)

clean:
	rm -f *.o similar_lines