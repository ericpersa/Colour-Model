# ID BOX: Eric Persa 3123945
# ID BOX : Jenna Leew 3147578

#makefile  module 2 - in main
CC = gcc
CFLAGS = -Wall -std=c11

VPATH = src bin obj

#normal targets

paintProgram: paintProgram.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o obj
	- mv paintProgram bin

test_load: test_load.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o obj
	- mv test_load bin

test_range: test_range.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	- mv *.o obj
	- mv test_range bin
	
test_value: test_value.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o obj
	- mv test_value bin

test_palette: test_palette.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@
	- mv *.o obj
	- mv test_palette bin

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

#phony targets

.PHONY: clean package

clean: test_load test_value test_range
	- rm -f bin/test_load bin/test_value bin/test_range  bin/paintProgram
	- rm -f obj/*.o

package:
	tar -czvf cmpt201_project02_EP_JL.tar.gz src/*.c src/*.h src/Makefile obj/ignore.txt data/*.dat bin/ignore.txt Makefile README.md
