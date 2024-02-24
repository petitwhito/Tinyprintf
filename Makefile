CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wvla -pedantic -g -fsanitize=address
LDLIBS=-lcriterion
LDFLAGS=-fsanitize=address

TESTNAME=tests/testsuite.c src/tinyprintf.c

all: src/tinyprintf.o

src/tinyprintf.o: src/tinyprintf.c
	$(CC) $(CFLAGS) -c -o src/tinyprintf.o src/tinyprintf.c $(LDLIBS) $(LDFLAGS)

tests/testsuite.o: tests/testsuite.c
	$(CC) $(CFLAGS) -c -o tests/testsuite.o tests/testsuite.c $(LDLIBS) $(LDFLAGS)

check: tests/testsuite.o src/tinyprintf.c
	$(CC) $(CFLAGS) $(TESTNAME) -o res $(LDLIBS) $(LDFLAGS)
	./res

clean:
	$(RM) res src/tinyprintf.o tests/testsuite.o


