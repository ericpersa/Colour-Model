#makefile project milestone 2
# ID BOX: Eric Persa 3123945
# ID BOX : Jenna Leaw 3147578

CC = gcc
CFLAGS = -Wall -std=c11
VPATH = ../bin ../obj 

#normal targets

test_load: test_load.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o ../obj
	- mv test_load ../bin

test_range: test_range.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	- mv *.o ../obj
	- mv test_range ../bin

test_range_debug: test_range.o pigment.o
	$(CC) $(CFLAGS) $^ -g -o $@ -lm
	- mv *.o ../obj

test_value: test_value.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o ../obj
	- mv test_value ../bin

test_colour: test_colour.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o ../obj
	- mv test_colour ../bin

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

#phony targets

.PHONY: clean package

clean: test_load test_value test_range test_range_debug
	rm -f ../bin/test_load ../bin/test_value ../bin/test_range ../obj/*.o test_range_debug

package: *.c *.h makefile
	tar -czvf cmpt201_project01_EP_JL.tar.gz *.c *.h makefile
