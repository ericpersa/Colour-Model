#makefile project milestone 1

CC = gcc
CFLAGS = -Wall -std=c11

#normal targets

test_load: test_load.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)
