## BUILD SETTINGS ##


# Enables debugging symbols (gdb)
# y/n
DEBUG := n

# Specify whether the libraries should be linked statically or not
# y/n
STATIC := n

# The optimization level for the compilation
# n/s/1..3
OPT_L := n



## VARIABLES ##


# Output variables
EXEC := pnc
OUT_DIR := out

# Variables describing the architecture of the project directory
INC_DIR := inc
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR := obj
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


# Documentation specific variables
DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc


# The compiler to use
CC := gcc
# Compilation flags
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded -I$(INC_DIR) $$(sdl2-config --cflags)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif
# The libraries to link
LDLIBS := -lm -llog -larray -lSDL2_ttf
ifeq ($(STATIC),y)
	LDLIBS += $$(sdl2-config --static-libs)
else
	LDLIBS += $$(sdl2-config --libs)
endif
# Linkage flags
LDFLAGS :=



## RULES ##


# All rule names that do not refer to files
.PHONY: all clean distclean doc cleandoc


# The default rule (the one called when make is invoked without arguments)
all: $(EXEC)

# Linkage
$(EXEC): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(CC) -o$(OUT_DIR)/$(EXEC) $(OBJ) $(LDFLAGS) $(LDLIBS)

# Filewise compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -o$@ -c $< $(CFLAGS)


# Remove object files
clean:
	rm -rf $(OBJ_DIR)

# Reset project to initial state
distclean: clean cleandoc
	rm -rf $(OUT_DIR)


# (Re)generate doc
doc: $(DOC_CFG) cleandoc
	$(DOC_PRG) $(DOC_CFG)

# Remove doc directory
cleandoc:
	rm -rf $(DOC_DIR)
