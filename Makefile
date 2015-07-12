CC = gcc
CFLAGS = -pedantic

TARGETS = termplot.o ui_curses.o options.o

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

all: $(TARGETS)
	gcc -lncurses $(TARGETS) -o termplot


clean:
	rm -f $(TARGETS) termplot


