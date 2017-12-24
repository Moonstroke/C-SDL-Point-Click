# y/n.
# Specify whether the libraries should be linked statically or not
STATIC := y

# n/s/1..3
# The optimization level for the compilation
OPT_L := n

CC := gcc
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded
ifeq ($(STATIC),y)
	LDLIBS := -Wl,-dn -llog -lSDL2 -Wl,-dy -lm -ldl -lasound -lpthread -lpulse \
	          -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss \
	          -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon
else
	LDLIBS := -llog -lSDL2
endif
LDFLAGS :=

EXEC := pnc

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)


DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc/

.PHONY: all clean distclean doc cleandoc

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o$(EXEC) $(OBJ) $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o$@ -c $< $(LDLIBS)


clean:
	rm -rf $(OBJ)

distclean: clean cleandoc
	rm -rf $(EXEC)

doc:
	$(DOC_PRG) $(DOC_CFG)

cleandoc:
	rm -rf $(DOC_DIR)
