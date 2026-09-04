.PHONY: all clean

CC ?= gcc

STAGING_DIR ?=

CFLAGS := -Wall -Wextra -g -std=c11

CPPFLAGS += \
    -Iinclude \
    -I../system_info/include \
    -I$(STAGING_DIR)/usr/include

SRC := $(wildcard src/*.c)

OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

TARGET := build/tuya-monitor-daemon

all: $(TARGET)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) \
		-L../system_info/build \
		-L$(STAGING_DIR)/usr/lib \
		-lsystem_info \
		-llink_core \
		-lmiddleware_implementation \
		-lplatform_port \
		-lutils_modules \
		-lubus \
		-lubox \
		-lblobmsg_json \
		-lpthread \
		-lm \
		-o $(TARGET)

clean:
	rm -rf build