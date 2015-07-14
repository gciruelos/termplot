CC = clang
CFLAGS = -Wall -Wextra -pedantic

TARGETS = termplot.o input.o ui_curses.o parser.o options.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(TARGETS)
	$(CC) -lm -lncurses $(TARGETS) -o termplot


clean:
	rm -f $(TARGETS) termplot


