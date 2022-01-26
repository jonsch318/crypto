CC = gcc
SRC = src
SRCS = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*/*.c) $(wildcard $(SRC)/*/*/*.c)
OBJ = obj
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
DFLAGS = -g3 -Wall
FLAGS = -O3 -Wall -m64 -flto
LFLAGS = -lm -static -lgmp
BINDIR = bin
BIN = $(BINDIR)/crypto

ifeq ($(OS),Windows_NT)
RM = del /Q /F
CP = copy /Y
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f
endif

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(LFLAGS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY : clean run strip git-clean

ifeq ($(OS),Windows_NT)
OBJS := $(subst /,\, $(OBJS))
BIN := $(subst /,\, $(BIN)).exe
endif

clean:
	$(RM) $(BIN) $(OBJS)

git-clean:
	git clean -xdf

run: all
	$(BIN)

strip: all
	strip $(BIN)