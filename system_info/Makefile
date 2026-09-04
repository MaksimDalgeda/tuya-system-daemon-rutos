.PHONY: all clean

CC ?= gcc
AR ?= ar

CFLAGS += -Wall -Wextra -Werror
CPPFLAGS += -Iinclude

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

TARGET := build/libsystem_info.a

all: $(TARGET)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -rf build