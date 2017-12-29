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
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded
ifeq ($(STATIC),y)
	LDLIBS := -Wl,-dn -llog -larray -lSDL2 -Wl,-dy -lSDL2_ttf -lm -ldl -lasound \
	          -lpthread -lpulse -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi \
	          -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client \
	          -lwayland-cursor -lxkbcommon
else
	LDLIBS := -llog -larray -lSDL2 -lSDL2_ttf -lm
endif
LDFLAGS := -I$(INC_DIR)

.PHONY: all clean distclean doc cleandoc

all: $(EXEC)

$(EXEC): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(CC) -o$(OUT_DIR)/$(EXEC) $(OBJ_DIR)/*.o $(CFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -o$@ -c $< $(LDFLAGS) $(CFLAGS)


clean:
	rm -rf $(OBJ_DIR)/

distclean: clean cleandoc
	rm -rf $(OUT_DIR)/


doc: $(DOC_CFG)
	$(DOC_PRG) $(DOC_CFG)

cleandoc:
	rm -rf $(DOC_DIR)
