CC = gcc
CFLAGS = -DINCL_TERMBOX -Wextra -Wall -Werror -std=c11 -pedantic -O2
TARGETS = options.o ui.o command.o plot.o parser.o debug.o 
LIBRARIES = -lm -lncurses -ltermbox
TEST = false

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

termplot.o: src/termplot.c
	$(CC) $(CFLAGS) -c -o $@ $<

test.o: test/test.c
	$(CC) $(CFLAGS) -c -o $@ $<

termplot: $(TARGETS) termplot.o
	$(CC) $(LIBRARIES) $(TARGETS) termplot.o -o $@

testbin: $(TARGETS) test.o
	$(CC) $(LIBRARIES) $(TARGETS) test.o -o $@

test: testbin
	./testbin

clean:
	rm -f test.o $(TARGETS) debug.out termplot testbin

