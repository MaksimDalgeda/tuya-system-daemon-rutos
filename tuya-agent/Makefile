.PHONY: all clean

CC := gcc

TUYA_SDK := $(abspath ../../tuya-iot-core-sdk-main)

CFLAGS := -Wall -Wextra -g -std=c11

CPPFLAGS := \
    -Iinclude \
    -I../system_info/include \
    -I$(TUYA_SDK)/include \
    -I$(TUYA_SDK)/interface \
	-I$(TUYA_SDK)/utils \
	-I$(TUYA_SDK)/examples/custom_protocol_basic_demo
    -D_POSIX_C_SOURCE=200809L

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
		-L$(TUYA_SDK)/build/lib \
		-lsystem_info \
		-llink_core \
		-lmiddleware_implementation \
		-lplatform_port \
		-lutils_modules \
		-lpthread \
		-lm \
		-Wl,-rpath,$(TUYA_SDK)/build/lib \
		-Wl,-rpath,'$$ORIGIN/../../system_info/build' \
		-o $(TARGET)

clean:
	rm -f build/*.o
	rm -f $(TARGET)