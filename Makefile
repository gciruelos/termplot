ifndef $(CC)
	CC = gcc
endif
WARNINGS = -Wall -Wextra -Werror -Wshadow -Wstrict-prototypes -Wpointer-arith \
					 -Wcast-qual
OPT_FLAGS = -O2 -flto --fast-math
CFLAGS = $(WARNINGS) -Werror -std=c99 -pedantic
LFLAGS = -lm
TEST_DIR = test/
SRC_DIR = src/
UI_SRC_DIR = $(SRC_DIR)ui/
OBJ_DIR = obj/
TEST_OBJ_DIR = $(OBJ_DIR)test/
SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(addprefix $(OBJ_DIR),$(notdir $(SRCS:.c=.o)))
TEST_SRCS = $(wildcard $(TEST_DIR)*.c)
TEST_OBJS = $(addprefix $(TEST_OBJ_DIR),$(notdir $(TEST_SRCS:.c=.o)))
UI_IMPL = 
EXECUTABLE = termplot
TEST_EXECUTABLE = testbin
MKDIR_P = mkdir -p

ifndef $(USE_NCURSES)
  TERMBOX = false
else
	TERMBOX = true
endif

ifeq ($(TERMBOX), true)
	CFLAGS+=-DINCL_TERMBOX
	SRCS+=src/ui/ui_termbox.c
	LFLAGS+=-ltermbox
else
	SRCS+=src/ui/ui_ncurses.c
	LFLAGS+=-lncurses
endif

.PHONY: all clean debug travis

all: $(OBJ_DIR) $(EXECUTABLE)

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(EXECUTABLE) $(TEST_EXECUTABLE)

debug: OPT_FLAGS = -ggdb -O2
debug: all

travis: all test

$(OBJ_DIR):
	${MKDIR_P} $@
	
$(TEST_OBJ_DIR):
	${MKDIR_P} $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -o $@ $<

$(OBJ_DIR)%.o: $(UI_SRC_DIR)%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -o $@ $<

$(OBJ_DIR)%.o: $(TESD_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(OBJS)
	$(CC) $(OPT_FLAGS) $^ -o $@ $(LFLAGS)

$(TEST_OBJ_DIR)%.o: $(TEST_DIR)%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -o $@ $<

$(TEST_EXECUTABLE): OBJS := $(filter-out obj/termplot.o, $(OBJS))
$(TEST_EXECUTABLE): $(OBJS) $(TEST_OBJS)
	$(CC) $(OPT_FLAGS) $(OBJS) $(TEST_OBJS) -o $@ $(LFLAGS)


test: $(TEST_OBJ_DIR)
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

