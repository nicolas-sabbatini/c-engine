CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -pthread -Ivendors
LDFLAGS = -lGL -ldl -lm -lX11 -lasound -lXi -lXcursor

SRCDIR = src
TARGETDIR = target
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(TARGETDIR)/%.o,$(SRCS))
BIN_NAME = engine

RELEASE ?= 0
ifeq ($(RELEASE), 0)
    CFLAGS += -g -O0 -DDEBUG -D_DEBUG
else
    CFLAGS += -O3
endif

.PHONY: all clean compile_flags

# Default
all: compile_flags run

run: $(BIN_NAME)
	./bin/$^

$(BIN_NAME): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(BINDIR)/$@

$(TARGETDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $^ -o $@

clean:
	rm -fr $(TARGETDIR)/* $(BINDIR)/* compile_flags.txt

compile_flags:
	@echo $(CFLAGS) | tr ' ' '\n' > compile_flags.txt
	@echo $(LDFLAGS) | tr ' ' '\n' >> compile_flags.txt

set_up:
	git submodule init
	git submodule update --remote
