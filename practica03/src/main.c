/*
 * Archivo: main.c
 * Práctica 03: conjunto de estudiantes.
 * Programa de ejemplo; las pruebas automáticas se ejecutan con make test.
 */

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"

int main(void) {
    Conjunto estudiantes;
    Estudiante ana = {101, {"Ana", "López Ruiz"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez Solís"}, 9.1f};
    Estudiante criterio = {.matricula = 205};

    inicializarConjunto(&estudiantes, CAPACIDAD_CONJUNTO);

    printf("Tamaño de los campos: %zu bytes\n",
           sizeof ana.matricula + sizeof ana.nombre + sizeof ana.promedio);
    printf("Tamaño de Estudiante: %zu bytes\n", sizeof(Estudiante));

    printf("\nAgregar 101. Estado esperado: 1\n");
    printf("Estado obtenido: %d\n", agregarElemento(&estudiantes, &ana));
    printf("Agregar 205. Estado esperado: 1\n");
    printf("Estado obtenido: %d\n", agregarElemento(&estudiantes, &bruno));
    printf("Agregar otra vez 101. Estado esperado: 0\n");
    printf("Estado obtenido: %d\n", agregarElemento(&estudiantes, &ana));

    printf("\nRegistros del conjunto:\n");
    mostrarConjunto(&estudiantes);

    printf("\nBuscar 205. Índice esperado: 1\n");
    int indice = buscarElemento(&estudiantes, &criterio);
    printf("Índice obtenido: %d\n", indice);
    if (indice >= 0) {
        Estudiante *encontrado = obtenerElemento(&estudiantes, indice);
        actualizarPromedio(encontrado, 9.5f);
        printf("Registro con promedio actualizado:\n");
        mostrarEstudiante(encontrado);
    }

    criterio.matricula = 101;
    printf("\nEliminar 101. Estado esperado: 1\n");
    printf("Estado obtenido: %d\n",
           eliminarElemento(&estudiantes, &criterio));
    printf("Registros restantes:\n");
    mostrarConjunto(&estudiantes);

    return EXIT_SUCCESS;
}
