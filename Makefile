# Compiler and flags
CC      := gcc

CFLAGS  := -Wall -Wextra -O2

LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files and target
SRC     := main.c attaque.c mouvement.c utility.c
OBJDIR  := bin
OBJ     := $(SRC:%.c=$(OBJDIR)/%.o)
TARGET  := 1v1GDN

# Default target
all: $(TARGET)

# Ensure bin directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files into bin/
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build target from object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ)

git:
	git pull

# Phony targets
.PHONY: all clean
