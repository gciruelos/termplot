CC = gcc
CFLAGS = -Wextra -Wall -Werror -std=c11 -pedantic -O2

TARGETS = termplot.o options.o ui.o command.o plot.o parser.o debug.o 

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(MAIN) $(TARGETS)
	$(CC) -lm -lncurses  $(MAIN) $(TARGETS) -o termplot

test: $(TARGETS)
	cd test && make all

clean:
	rm -f test.o $(TARGETS) debug.out termplot testbin

