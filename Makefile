## PROJECT SETTINGS ##


# Project name
PROJECT_NAME := C_SDL-Point_Click


# Project directories
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := obj
OUT_DIR := out


# Documentation
DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc



## BUILD SETTINGS ##


# Enables debugging symbols (gdb)
# y/n
DEBUG := n

# Specify whether the libraries should be linked statically or not
# y/n
STATIC := n

# The optimization level for the compilation
# 0..3/s
OPTIM_LVL := 0



## VARIABLES ##


# Variables describing the architecture of the project directory
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


# Output executable
EXEC := $(OUT_DIR)/$(PROJECT_NAME)


# Preprocessor flags
CPPFLAGS := -I$(INC_DIR)
# Compilation flags
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded $$(sdl2-config --cflags) -O$(OPTIM_LVL)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif

# The libraries to link against
LDLIBS := -lm -lclog -lCODS -lSDL2_ttf
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
	$(CC) -o$(EXEC) $^ $(LDFLAGS) $(LDLIBS)

# Filewise compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -o$@ -c $< $(CPPFLAGS) $(CFLAGS)


# Remove object files
clean:
	@rm -rf $(OBJ_DIR)

# Reset project to initial state
distclean: clean cleandoc
	@rm -rf $(OUT_DIR)


# (Re)generate doc
doc: $(DOC_CFG)
	$(DOC_PRG) $(DOC_CFG)

# Remove doc directory
cleandoc:
	@rm -rf $(DOC_DIR)
