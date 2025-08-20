CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -pthread
LDFLAGS = -lGL -ldl -lm -lX11 -lasound -lXi -lXcursor

SRCDIR = src
TARGETDIR = target
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(TARGETDIR)/%.o,$(SRCS))
BIN_NAME = engine

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g -O0
else
    CFLAGS += -O3
endif

.PHONY: all clean

# Default
all: run

run: $(BIN_NAME)
	./bin/$^

$(BIN_NAME): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -v -o $(BINDIR)/$@

$(TARGETDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(TARGETDIR)
	$(CC) $(CFLAGS)  -c $^ -o $@

clean:
	rm -fr $(TARGETDIR)/* $(BINDIR)/*

