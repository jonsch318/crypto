SOURCE	= $(wildcard ./src/*.c) $(wildcard ./src/*/*.c)
OBJS	= $(SOURCE:.c=.o)
HEADER	= $(wildcard ./include/*.h)
OUT	= crypto.exe
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm -static -lgmp
ifeq ($(OS),Windows_NT)
	SHELL=cmd
	RM = del /S
	DEL_OBJS = *.o *.exe *.out
else
	RM = rm -f
	DEL_OBJS = $(OBJS) ./crypto
endif

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $< $(FLAGS) -o $@

.PHONY : clean
clean:
	$(RM) $(DEL_OBJS)