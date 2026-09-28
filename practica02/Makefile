# Compilación y pruebas de la práctica 02.
CC = gcc
CFLAGS ?= -g
REQUISITOS_C = -std=c11 -Wall -Wextra -Wpedantic -Werror

.PHONY: all test clean
.DELETE_ON_ERROR:

all: build/practica02

# También compila el programa de ejemplo para revisar sus advertencias.
test: all build/test_conjunto
	./build/test_conjunto

build/practica02: src/main.c src/conjunto.c src/conjunto.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) src/main.c src/conjunto.c $(LDFLAGS) $(LDLIBS) -o $@

build/test_conjunto: tests/test_conjunto.c src/conjunto.c src/conjunto.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) tests/test_conjunto.c src/conjunto.c $(LDFLAGS) $(LDLIBS) -o $@

build:
	mkdir -p $@

clean:
	$(RM) build/practica02 build/test_conjunto
