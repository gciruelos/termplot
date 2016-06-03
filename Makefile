CC = gcc
WARNINGS = -Wall -Wextra -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual
CFLAGS = $(WARNINGS) -Werror -std=c11 -pedantic -O2 -ggdb
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

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

ui_impl.o: $(UI_IMPL)
	$(CC) $(CFLAGS) -c -o $@ $<

termplot.o: src/termplot.c
	$(CC) $(CFLAGS) -c -o $@ $<

test.o: test/test.c
	$(CC) $(CFLAGS) -c -o $@ $<

termplot: $(TARGETS) termplot.o
	$(CC) $(LIBRARIES) $(TARGETS) termplot.o -o $@

testbin:
testbin: $(TARGETS) test.o
	$(CC) $(LIBRARIES) $(TARGETS) test.o -o $@

test: testbin
	./testbin

clean:
	rm -f termplot.o test.o $(TARGETS) debug.out termplot testbin

