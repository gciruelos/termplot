CC = clang
CFLAGS = -Wextra -Wall -g -pedantic

TARGETS = termplot.o options.o ui.o command.o plot.o parser.o debug.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(TARGETS)
	$(CC) -lm -lncurses $(TARGETS) -o termplot


clean:
	rm -f $(TARGETS) debug.out termplot


