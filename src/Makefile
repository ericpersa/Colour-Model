#makefile project milestone 1

CC = gcc
CFLAGS = -Wall -std=c11

#normal targets

test_load: test_load.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@

test_range: test_range.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

test_value: test_value.o pigment.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

#phony targets

.PHONY: clean package

clean: test_load test_value test_range
	rm -f test_load test_value test_range *.o

package: *.c *.h makefile
	tar -czvf cmpt201_project01_EP_JL.tar.gz *.c *.h makefile
