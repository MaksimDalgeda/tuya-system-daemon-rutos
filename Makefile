.PHONY: all run build-lib build-src clean clean-lib clean-src install uninstall

PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

all:
	$(MAKE) -C system_info
	$(MAKE) -C tuya-agent

TUYA_LIB := $(HOME)/Documents/Projects/tuya-iot-core-sdk-main/build/lib

run: all
	LD_LIBRARY_PATH=$(TUYA_LIB):$$LD_LIBRARY_PATH \
	./tuya-agent/build/tuya-monitor-daemon\
		--device-id 269be577b3e64f5dbd95js\
		--device-secret VBv8CcB8EdgffeLp\
		--product-id smw2jne5ohpmq8t1\
		#--daemon


build-lib:
	$(MAKE) -C system_info

build-src:
	$(MAKE) -C tuya-agent

clean:
	$(MAKE) -C system_info clean
	$(MAKE) -C tuya-agent clean

clean-lib:
	$(MAKE) -C system_info clean

clean-src:
	$(MAKE) -C tuya-agent clean

install: all
	install -d $(BINDIR)
	install -d $(LIBDIR)

	install -m 755 tuya-agent/build/tuya-monitor-daemon $(BINDIR)/
	install -m 755 system_info/build/libsystem_info.so $(LIBDIR)/

uninstall:
	rm -f $(BINDIR)/tuya-monitor-daemon
	rm -f $(LIBDIR)/libsystem_info.so
