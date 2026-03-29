# Compiler and flags
CC := gcc
CFLAGS := -g -O0
LDFLAGS := 

# Directories
TARGET_DIR := bin

# Target
TARGET := $(TARGET_DIR)/shell

# Files
CFILES := $(wildcard *.c)
# $(VAR:old=new)
#OFILES := $(CFILES:.c=.o)
# $(patsubst pattern,replacement,text) In text, replace every word matching pattern with replacement.
OFILES := $(patsubst %.c, $(TARGET_DIR)/%.o, $(CFILES))

all: $(TARGET_DIR) $(TARGET)

$(TARGET_DIR):
	mkdir $(TARGET_DIR)

# $@ means the name of the current target, $^ means all the dependencies of the current target
$(TARGET): $(OFILES)
	$(CC) -o $@ $^

# $< means get me the first dependency, best for one file one object
$(TARGET_DIR)/%.o: %.c | $(TARGET_DIR)
	$(CC) -c -o $@ $< $(CFLAGS) 

clean:
	rm -rf $(TARGET_DIR)
