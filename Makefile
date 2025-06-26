# Compiler and flags
CC      := gcc

CFLAGS  := -Wall -Wextra -O2

LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files and target
SRCFILE := main.c attaque.c mouvement.c utility.c
SRCPATH := src/
SRC     := $(addprefix $(SRCPATH),$(SRCFILE))
OBJDIR  := bin
OBJ     := $(SRCFILE:%.c=$(OBJDIR)/%.o)
TARGET  := 1v1GDN

# Default target
all: $(TARGET)

# Ensure bin directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files into bin/
$(OBJDIR)/%.o: $(SRCPATH)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build target from object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ)

git:
	@read -p "Commit message: " msg; \
	git add *; \
	git commit -m "$$msg"; \
	git push


# Phony targets
.PHONY: all clean git
