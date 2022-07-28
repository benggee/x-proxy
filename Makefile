CC=gcc
# Binary name
TARGET=xproxy

BUILDDIR=build
SRCDIR=src .
INCLUDEDIR=src
CFLAGS=$(patsubst %,-I%, $(INCLUDEDIR))

# Find all .C files
SOURCES=$(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))

# Header files
INCLUDES=$(foreach dir,$(INCLUDEDIR), $(wildcard $(dir)/*.h))

# Build all .O files
OBJECTS=$(patsubst %.c,$(BUILDDIR)/%.o, $(notdir $(SOURCES)))
VPATH=$(SRCDIR)

.PHONY: clean build 

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ && cp -rf $(BUILDDIR)/xproxy ./

# Create directory before comipling
$(BUILDDIR)/%.o:%.c $(INCLUDES) | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) xproxy

build:
	mkdir -p $(BUILDDIR)
