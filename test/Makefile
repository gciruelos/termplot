CC = clang
FLAGS = -Wextra -Wall -O0 -ggdb -pedantic
TARGETS = options.o ui.o command.o plot.o parser.o debug.o


test.o: test.c
	$(CC) $(CFLAGS) -c -o $@ $<


all: test.o
	mv test.o ../test.o
	cd .. && $(CC) -lm -lncurses  test.o $(TARGETS) -o testbin



