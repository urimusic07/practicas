/*
 * Archivo: estudiante.c
 * Operaciones propias de un estudiante.
 * Completen las funciones pendientes según estudiante.h.
 * Autoría: Molina Fuentes Uri Israel.
 */

#include <stdio.h>

#include "estudiante.h"

/* Compara el campo que identifica a cada estudiante. */
int compararEstudiantes(const Estudiante *estudianteA,
                        const Estudiante *estudianteB) {
    if (estudianteA->matricula == estudianteB->matricula){
        return 0;
    }
    return 1;
}
/* Modifica un campo mediante un apuntador a la estructura. */
void actualizarPromedio(Estudiante *estudiante, float nuevoPromedio) {
    estudiante-> promedio = nuevoPromedio;
}

/* Muestra los campos de un estudiante. */
void mostrarEstudiante(const Estudiante *estudiante) {
    printf("%d - %s - %s - %.2f", estudiante -> matricula, estudiante-> nombre.nombres ,estudiante->nombre.apellidos, estudiante->promedio );
}