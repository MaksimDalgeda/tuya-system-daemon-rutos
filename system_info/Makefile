.PHONY: all clean

CC := gcc

CFLAGS := -Wall -Wextra -Werror -fPIC
CPPFLAGS := -Iinclude

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

TARGET := build/libsystem_info.so

all: $(TARGET)

build/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

clean:
	rm -f build/*.o build/*.so