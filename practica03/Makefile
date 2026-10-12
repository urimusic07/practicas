# Compilación y pruebas de la práctica 03.
CC = gcc
CFLAGS ?= -g
REQUISITOS_C = -std=c11 -Wall -Wextra -Wpedantic -Werror

.PHONY: all test clean
.DELETE_ON_ERROR:

all: build/practica03

# También compila el programa de ejemplo para revisar sus advertencias.
test: all build/test_practica03
	./build/test_practica03

build/practica03: src/main.c src/conjunto.c src/conjunto.h \
		src/estudiante.c src/estudiante.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) \
		src/main.c src/conjunto.c src/estudiante.c \
		$(LDFLAGS) $(LDLIBS) -o $@

build/test_practica03: tests/test_practica03.c src/conjunto.c src/conjunto.h \
		src/estudiante.c src/estudiante.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) \
		tests/test_practica03.c src/conjunto.c src/estudiante.c \
		$(LDFLAGS) $(LDLIBS) -o $@

build:
	mkdir -p $@

clean:
	$(RM) build/practica03 build/test_practica03
