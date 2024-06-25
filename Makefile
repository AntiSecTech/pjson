CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -ljansson
TARGET = pjson
SRC = pjson.c
CONFIG = pjson.json
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
CONFDIR = /etc

all: compile

compile: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

install: $(TARGET) $(TARGET).1 $(CONFIG)
	@if [ -e $(BINDIR)/$(TARGET) ]; then \
		echo "$(TARGET) already exists in $(BINDIR). Installation aborted."; \
	else \
		ln -s -r $(TARGET) $(BINDIR); \
		echo "$(TARGET) installed to $(BINDIR)/"; \
	fi
	@if [ -e $(CONFDIR)/$(CONFIG) ]; then \
		echo "$(CONFIG) already exist in $(CONFDIR). Installation aborted."; \
	else \
		ln -s -r $(CONFIG) $(CONFDIR); \
		echo "$(CONFIG) installed to $(CONFDIR)/"; \
	fi

uninstall:
	@if [ ! -e $(BINDIR)/$(TARGET) ]; then \
		echo "$(TARGET) does not exist in $(BINDIR). Nothing to uninstall."; \
	else \
		rm $(BINDIR)/$(TARGET); \
		echo "$(TARGET) removed from $(BINDIR)/"; \
	fi
	@if [ ! -e $(CONFDIR)/$(CONFIG) ]; then \
		echo "$(CONFIG) does not exist in $(CONFDIR). Nothing to uninstall."; \
	else \
		rm $(CONFDIR)/$(CONFIG); \
		echo "$(CONFIG) removed from $(CONFDIR)/"; \
	fi

clean:
	rm -f $(TARGET)

.PHONY: all compile install uninstall clean
