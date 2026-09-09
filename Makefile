.PHONY: all clean run sdk

CC := gcc

TUYA_SDK := $(abspath sdk)
SDK_BUILD_DIR := $(TUYA_SDK)/build

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

sdk: $(SDK_BUILD_DIR)/Makefile
	$(MAKE) -C $(SDK_BUILD_DIR)

$(SDK_BUILD_DIR)/Makefile:
	@mkdir -p $(SDK_BUILD_DIR)
	cd $(SDK_BUILD_DIR) && cmake ..

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): sdk $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ) \
		-L$(SDK_BUILD_DIR)/lib \
		-llink_core \
		-lmiddleware_implementation \
		-lplatform_port \
		-lutils_modules \
		-lpthread \
		-lm \
		-Wl,-rpath,$(SDK_BUILD_DIR)/lib \
		-o $@

run: all
	LD_LIBRARY_PATH=$(SDK_BUILD_DIR)/lib:$$LD_LIBRARY_PATH \
	./$(TARGET) \
		--device-id 2630971166afe6a35f7yph \
		--device-secret uUQgkqABDcHHKzUi \
		--product-id l3ydtvg3stqqf7io \
		--daemon

clean:
	rm -rf build

clean-all:
	rm -rf build
	rm -rf $(SDK_BUILD_DIR)

clean-sdk:
	rm -rf $(SDK_BUILD_DIR)