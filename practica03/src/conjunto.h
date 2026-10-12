/*
 * Archivo: conjunto.h
 * Conjunto de estudiantes con almacenamiento de capacidad fija.
 *
 * Las operaciones conservan los contratos del conjunto de enteros de la
 * práctica 2. La matrícula determina si dos estudiantes representan el mismo
 * elemento. En operaciones con resultado, éste debe ser distinto de las
 * entradas.
 */

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stddef.h>

#include "estudiante.h"

#define CAPACIDAD_CONJUNTO 10
#define CAPACIDAD_RESULTADO (2 * CAPACIDAD_CONJUNTO)

/* Una estructura que contiene un arreglo de estructuras Estudiante. */
typedef struct Conjunto {
    Estudiante elementos[CAPACIDAD_RESULTADO];
    int cantidad;
    int capacidad;
} Conjunto;

/* Inicializa un conjunto vacío con una capacidad válida. */
void inicializarConjunto(Conjunto *conjunto, int capacidad);

/* Regresa el estudiante de una posición utilizada, o NULL si no existe. */
Estudiante *obtenerElemento(Conjunto *conjunto, int indice);

/* Regresa el índice del estudiante, o -1 si no pertenece al conjunto. */
int buscarElemento(const Conjunto *conjunto, const Estudiante *estudiante);

/* Regresa 1 si agrega el estudiante; 0 si está repetido o no queda espacio. */
int agregarElemento(Conjunto *conjunto, const Estudiante *estudiante);

/* Regresa 1 si elimina el estudiante; 0 si no pertenece al conjunto. */
int eliminarElemento(Conjunto *conjunto, const Estudiante *estudiante);

/* Sustituye un estudiante sin cambiar la cantidad ni repetir matrículas. */
int reemplazarElemento(Conjunto *conjunto, const Estudiante *estudiante,
                       const Estudiante *reemplazo);

/* Deja el conjunto vacío sin modificar su capacidad. */
void vaciarConjunto(Conjunto *conjunto);

/* Copia el origen; no modifica el destino si falta capacidad. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino);

/* Indica si todos los estudiantes de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB);

/* Indica si ambos conjuntos contienen las mismas matrículas. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB);

/* Calcula la unión; no modifica resultado si falta capacidad. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado);

/* Calcula la intersección; no modifica resultado si falta capacidad. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado);

/* Calcula A-B; no modifica resultado si falta capacidad. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado);

/*
 * Muestra los estudiantes en su orden actual, separados por comas y entre
 * llaves. Cada estudiante termina con un salto de línea.
 */
void mostrarConjunto(const Conjunto *conjunto);

#endif
