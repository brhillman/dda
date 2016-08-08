CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm

SRC = \
	src/main.c \
	src/seed.c \
	src/initialize.c \
	src/grow.c \
	src/monomers.c \
	src/islands.c \
	src/new.c \
	src/walk.c \
	src/proper.c \
	src/redirect.c \
	src/check.c \
	src/deposit.c \
	src/append_name.c \
	src/dout.c \
	src/fheader.c \
	src/header.c \
	src/write_morph.c \
	src/write_sizes.c \
	src/display.c

OBJ = \
	obj/main.o \
	obj/seed.o \
	obj/initialize.o \
	obj/grow.o \
	obj/monomers.o \
	obj/islands.o \
	obj/new.o \
	obj/walk.o \
	obj/proper.o \
	obj/redirect.o \
	obj/check.o \
	obj/deposit.o \
	obj/append_name.o \
	obj/dout.o \
	obj/fheader.o \
	obj/header.o \
	obj/write_morph.o \
	obj/write_sizes.o \
	obj/display.o

BIN = bin/dda

HEADERS = src/globals.h

bin/dda: $(HEADERS) $(OBJ) 
	$(CC) $(LDFLAGS) $(OBJ) -o bin/dda

obj/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ) $(BIN)
