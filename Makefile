CC = clang
CFLAGS = -fmax-errors=5 -Wall -pedantic

TARGETS = termplot.o input.o ui_curses.o plot.o parser.o options.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(TARGETS)
	$(CC) -lm -lncurses $(TARGETS) -o termplot


clean:
	rm -f $(TARGETS) termplot


