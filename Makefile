CC = gcc
CFLAGS = -Wall -Wextra -std=c23 -Ivendors -Ishader_out
DFLAGS = -DSOKOL_NO_DEPRECATED
LDFLAGS =
SHADERTYPE =

TARGET ?= linux
ifeq ($(TARGET), linux)
	LDFLAGS += -pthread -lGL -lEGL -ldl -lm -lX11 -lasound -lXi -lXcursor
	DFLAGS += -DSOKOL_GLCORE -DSOKOL_FORCE_EGL
	SHADERTYPE = glsl430
endif

RELEASE ?= 0
ifeq ($(RELEASE), 0)
    CFLAGS += -ggdb -O0
		DFLAGS += -DDEBUG -D_DEBUG
else
    CFLAGS += -O3
endif

# Default
bin/render: objects/main.o
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) $(DFLAGS) $^ -o $@

objects/%.o: src/main.c
	@mkdir -p objects
	$(CC) $(CFLAGS) $(LDFLAGS) $(DFLAGS) -c $^ -o $@

run: bin/render
	./$^

compile_flags.txt:
	@echo $(CFLAGS) | tr ' ' '\n' > compile_flags.txt
	@echo $(LDFLAGS) | tr ' ' '\n' >> compile_flags.txt
	@echo $(DFLAGS) | tr ' ' '\n' >> compile_flags.txt

set_up: compile_flags.txt
	@mkdir -p vendors
	wget -O vendors/sokol_app.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_app.h
	wget -O vendors/sokol_args.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_args.h
	wget -O vendors/sokol_audio.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_audio.h
	wget -O vendors/sokol_fetch.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_fetch.h
	wget -O vendors/sokol_gfx.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_gfx.h
	wget -O vendors/sokol_glue.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_glue.h
	wget -O vendors/sokol_log.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_log.h
	wget -O vendors/sokol_time.h https://raw.githubusercontent.com/floooh/sokol/master/sokol_time.h

compile_shader:
	@mkdir -p shader_out
	sokol-shdc --input shaders/main.glsl --output shader_out/main.c --slang $(SHADERTYPE) -f sokol

all: compile_flags.txt compile_shader run

clean:
	rm -fr bin objects compile_flags.txt shader_out

.PHONY: all clean set_up compile_flags.txt compile_shader
