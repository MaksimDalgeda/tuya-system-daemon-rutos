.PHONY: all clean

CC := gcc

CFLAGS := -Wall -Wextra -g -std=c11

CPPFLAGS := \
	-Iinclude \
	-I../system_info/include \
	-D_POSIX_C_SOURCE=200809L

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

TARGET := build/tuya-monitor-daemon

all: $(TARGET)

build/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) \
		-L../system_info/build \
		-lsystem_info \
		-Wl,-rpath,'$$ORIGIN/../../system_info/build' \
		-o $(TARGET)

clean:
	rm -f build/*.o build/tuya-monitor-daemon