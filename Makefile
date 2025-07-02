# Compiler and flags
CC      := gcc

CFLAGS  := -Wall -Wextra -O2

LDFLAGS := -lraylib -lm -lpthread -ldl -lrt -lX11 -lGL

# Source files and target
SRCFILE := main.c attaque.c mouvement.c utility.c
SRCPATH := src/
SRC     := $(addprefix $(SRCPATH),$(SRCFILE))
OBJDIR  := bin
OBJ     := $(addprefix $(OBJDIR)/,$(SRCFILE:.c=.o))
TARGET  := 1v1GDN

# Windows build settings
WIN_CC := x86_64-w64-mingw32-gcc
WIN_LDFLAGS := -lraylib -lm -lpthread 
WIN_OBJDIR := bin_win
WIN_OBJ := $(addprefix $(WIN_OBJDIR)/,$(SRCFILE:.c=.o))

# Default target
all: $(TARGET)

# Ensure bin directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files into bin/
$(OBJDIR)/%.o: $(SRCPATH)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build target from object files (Linux)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS)  $^ -o $@ $(LDFLAGS)

# Windows build (creates 1v1GDN.exe in bin/) flemme faut recompiler raylib pour windows
win: CFLAGS += -DPLATFORM_DESKTOP
win: LDFLAGS := $(WIN_LDFLAGS)
win: $(WIN_OBJDIR) $(WIN_OBJ)
	$(WIN_CC) $(CFLAGS) $(WIN_OBJ) -I"../raylib/src" -L"../raylib/src" -o $(WIN_OBJDIR)/$(TARGET).exe $(LDFLAGS)
$(WIN_OBJDIR):
	mkdir -p $(WIN_OBJDIR)

$(WIN_OBJDIR)/%.o: $(SRCPATH)%.c | $(WIN_OBJDIR)
	$(WIN_CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ) $(TARGET).exe $(WIN_OBJ)

git:
	@read -p "Commit message: " msg; \
	git add *; \
	git commit -m "$$msg"; \
	git push


# Phony targets
.PHONY: all clean git win