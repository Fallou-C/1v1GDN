# Compiler and flags
CC      := gcc

CFLAGS  := -Wall -Wextra -O2

LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files and target
SRC     := main.c
OBJDIR  := bin
OBJ     := $(OBJDIR)/main.o
TARGET  := 1v1GDN

# Default target
all: $(TARGET)

# Ensure bin directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object file into bin/
$(OBJ): $(SRC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build target from object file
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets
.PHONY: all clean
