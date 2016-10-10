ifndef $(CC)
	CC = gcc
endif
WARNINGS = -Wall -Wextra -Werror -Wshadow -Wstrict-prototypes -Wpointer-arith \
					 -Wcast-qual
OPT_FLAGS = -O2 -flto -ffast-math
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
EXECUTABLE = termplot
TEST_EXECUTABLE = testbin
MKDIR_P = mkdir -p
DEFAULT = termbox

all: $(DEFAULT)

ncurses: OBJS += obj/ui_ncurses.o
ncurses: LFLAGS += -lncurses
ncurses: $(OBJ_DIR) | obj/ui_ncurses.o $(EXECUTABLE)

termbox: CFLAGS += -DINCL_TERMBOX
termbox: OBJS += obj/ui_termbox.o
termbox: LFLAGS += -ltermbox
termbox: $(OBJ_DIR) | obj/ui_termbox.o $(EXECUTABLE)

.PHONY: all clean debug travis ncurses termbox

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(EXECUTABLE) $(TEST_EXECUTABLE)
	rm -r $(OBJ_DIR)

debug: OPT_FLAGS = -ggdb -O2
debug: termbox

travis: | ncurses test

$(OBJ_DIR):
	${MKDIR_P} $@
	
$(TEST_OBJ_DIR): $(OBJ_DIR)
	${MKDIR_P} $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -o $@ $<

$(OBJ_DIR)%.o: $(UI_SRC_DIR)%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -o $@ $<

$(TEST_OBJ_DIR)%.o: $(TEST_DIR)%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -o $@ $<

$(EXECUTABLE): $(OBJS)
	$(CC) $(OPT_FLAGS) $(OBJS) -o $@ $(LFLAGS)

# We test with ncurses.
$(TEST_EXECUTABLE): OBJS := $(filter-out obj/termplot.o obj/ui_termbox.o, \
	$(OBJS))
$(TEST_EXECUTABLE): $(OBJS) $(TEST_OBJS)
	$(CC) $(OPT_FLAGS) $(OBJS) $(TEST_OBJS) -o $@ $(LFLAGS)


test: $(TEST_OBJ_DIR) | $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

