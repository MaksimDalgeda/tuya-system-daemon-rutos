.PHONY: all clean run

CC := gcc

TUYA_SDK := $(abspath sdk)

CFLAGS := -Wall -Wextra -g -std=c11

CPPFLAGS := \
    -Isystem_info/include \
    -Ituya-agent/include \
    -I$(TUYA_SDK)/include \
    -I$(TUYA_SDK)/interface \
    -I$(TUYA_SDK)/utils \
    -I$(TUYA_SDK)/examples/custom_protocol_basic_demo

SYSTEM_INFO_SRC := $(wildcard system_info/src/*.c)
TUYA_AGENT_SRC := $(wildcard tuya-agent/src/*.c)

SRC := \
    $(SYSTEM_INFO_SRC) \
    $(TUYA_AGENT_SRC)

OBJ := $(patsubst %.c,build/%.o,$(SRC))

TARGET := build/tuya-monitor-daemon

all: $(TARGET)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) \
		-L$(TUYA_SDK)/build/lib \
		-llink_core \
		-lmiddleware_implementation \
		-lplatform_port \
		-lutils_modules \
		-lpthread \
		-lm \
		-Wl,-rpath,$(TUYA_SDK)/build/lib \
		-o $@

run: all
	LD_LIBRARY_PATH=$(TUYA_SDK)/build/lib:$$LD_LIBRARY_PATH \
	./$(TARGET) \
		--device-id 2630971166afe6a35f7yph \
		--device-secret uUQgkqABDcHHKzUi \
		--product-id l3ydtvg3stqqf7io\
		--daemon

clean:
	rm -rf build