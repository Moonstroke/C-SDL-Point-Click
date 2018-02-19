# y/n.
# Enables debugging symbols (gdb)
DEBUG := n

# y/n.
# Specify whether the libraries should be linked statically or not
STATIC := n

# n/s/1..3
# The optimization level for the compilation
OPT_L := n



EXEC := pnc
OUT_DIR := out

INC_DIR := inc
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR := obj
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc



CC := gcc
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded -I$(INC_DIR) $$(sdl2-config --cflags)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif
LDLIBS := -lm -llog -larray -lSDL2_ttf
ifeq ($(STATIC),y)
	LDLIBS += $$(sdl2-config --static-libs)
else
	LDLIBS += $$(sdl2-config --libs)
endif
LDFLAGS :=

.PHONY: all clean distclean doc cleandoc

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(CC) -o$(OUT_DIR)/$(EXEC) $(OBJ) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -o$@ -c $< $(CFLAGS)


clean:
	rm -rf $(OBJ_DIR)

distclean: clean cleandoc
	rm -rf $(OUT_DIR)


doc: $(DOC_CFG) cleandoc
	$(DOC_PRG) $(DOC_CFG)

cleandoc:
	rm -rf $(DOC_DIR)
