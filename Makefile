CC = gcc
FLAGS = -Wextra -Wall -O3 -pedantic

TARGETS = options.o ui.o command.o plot.o parser.o debug.o 
MAIN = termplot.o
TEST = test.o

test.o: test/test.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


all: $(MAIN) $(TARGETS)
	$(CC) -lm -lncurses  $(MAIN) $(TARGETS) -o termplot

test: $(TEST) $(TARGETS)
	$(CC) -lm -lncurses  $(TEST) $(TARGETS) -o testbin

clean:
	rm -f $(MAIN) $(TEST) $(TARGETS) debug.out termplot testbin

