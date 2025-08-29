CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread -Ivendors
LDFLAGS = -lGL -ldl -lm -lX11 -lasound -lXi -lXcursor

TARGETDIR = target
BINDIR = bin
BIN_NAME = engine

RELEASE ?= 0
ifeq ($(RELEASE), 0)
    CFLAGS += -ggdb -O0 -DDEBUG -D_DEBUG
else
    CFLAGS += -O3
endif

# Default
$(BINDIR)/$(BIN_NAME): src/main.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) src/main.c $(LDFLAGS) -o $@

run: $(BINDIR)/$(BIN_NAME)
	./$^

all: compile_flags.txt run

clean:
	rm -fr $(BINDIR)/* compile_flags.txt

compile_flags.txt:
	@echo $(CFLAGS) | tr ' ' '\n' > compile_flags.txt
	@echo $(LDFLAGS) | tr ' ' '\n' >> compile_flags.txt

set_up:
	git submodule init
	git submodule update --remote

.PHONY: all clean
