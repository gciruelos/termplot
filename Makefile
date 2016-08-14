CC = gcc
WARNINGS = -Wall -Wextra -Wshadow -Wstrict-prototypes -Wpointer-arith \
					 -Wcast-qual
CFLAGS = $(WARNINGS) -Werror -std=c11 -pedantic -O2 --fast-math -pg -ggdb
TARGETS = options.o ui.o ui_impl.o command.o plot.o parser.o debug.o 
UI_IMPL = 
LIBRARIES = -lm
TERMBOX = true

ifeq ($(TERMBOX), true)
	CFLAGS+=-DINCL_TERMBOX
	UI_IMPL=src/ui/ui_termbox.c
	LIBRARIES+=-ltermbox
else
	UI_IMPL=src/ui/ui_ncurses.c
	LIBRARIES+=-lncurses
endif

all: termplot

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

ui_impl.o: $(UI_IMPL)
	$(CC) $(CFLAGS) -c -o $@ $<

termplot.o: src/termplot.c
	$(CC) $(CFLAGS) -c -o $@ $<

parser_test.o: test/parser_test.c
	$(CC) $(CFLAGS) -c -o $@ $<

termplot: $(TARGETS) termplot.o
	$(CC) $(LIBRARIES) $(TARGETS) -pg termplot.o -o $@

parser_test:
parser_test: $(TARGETS) parser_test.o
	$(CC) $(LIBRARIES) $(TARGETS) -pg parser_test.o -o $@

test: parser_test
	./parser_test

clean:
	rm -f termplot.o parser_test.o $(TARGETS) debug.out termplot parser_test

