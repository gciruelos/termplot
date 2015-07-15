CC = clang
CFLAGS = -g -pedantic

TARGETS = termplot.o command.o ui_curses.o plot.o parser.o options.o debug.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(TARGETS)
	$(CC) -lm -lncurses $(TARGETS) -o termplot


clean:
	rm -f $(TARGETS) termplot


