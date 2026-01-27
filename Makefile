CC = clang
CFLAGS = -Wall -Wextra -std=c23 -pedantic
DFLAGS =
LDFLAGS = -Llibs/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RELEASE ?= 0
ifeq ($(RELEASE), 0)
    CFLAGS += -g -O0 -fsanitize=address -fno-omit-frame-pointer
    DFLAGS += -DDEBUG -D_DEBUG
else
    CFLAGS += -O3
endif

SRC = $(shell find src -name "*.c")
OBJ = $(SRC:src/%.c=objects/%.o)

# Default
bin/main: $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DFLAGS) $^ $(LDFLAGS) -o $@

objects/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

compile_flags.txt:
	@echo $(CFLAGS) | tr ' ' '\n' > compile_flags.txt
	@echo $(LDFLAGS) | tr ' ' '\n' >> compile_flags.txt
	@echo $(DFLAGS) | tr ' ' '\n' >> compile_flags.txt

run: bin/main
	./$^

all: compile_flags.txt run

clean:
	rm -fr bin objects

clean-all:
	rm -fr bin objects compile_flags.txt

.PHONY: all clean compile_flags.txt run
