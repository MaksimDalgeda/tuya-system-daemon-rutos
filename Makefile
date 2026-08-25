.PHONY: all run build-lib build-src clean clean-lib clean-src install uninstall

PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

all:
	$(MAKE) -C system_info
	$(MAKE) -C tuya-agent

run: all
	./tuya-agent/build/tuya-monitor-daemon

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
