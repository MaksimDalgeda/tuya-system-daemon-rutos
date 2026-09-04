.PHONY: all run build-lib build-src clean clean-lib clean-src install uninstall

PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

all:
	$(MAKE) -C system_info
	$(MAKE) -C tuya-agent

TUYA_LIB := $(HOME)/Documents/Projects/tuya-iot-core-sdk-main/build/lib

clean:
	$(MAKE) -C system_info clean
	$(MAKE) -C tuya-agent clean
