/*
 * Archivo: conjunto.c
 * Implementación de un conjunto genérico con capacidad fija.
 * Autoría: Tu Nombre
 */

#include <stdio.h>
#include <string.h>

#include "conjunto.h"

/* Inicializa el conjunto sobre un arreglo proporcionado por quien llama. */
void inicializarConjunto(Conjunto *conjunto, void *elementos, int capacidad,
                        size_t tamElemento, Comparador comparar) {
    conjunto->elementos = elementos;
    conjunto->cantidad = 0;
    conjunto->capacidad = capacidad;
    conjunto->tamElemento = tamElemento;
    conjunto->comparar = comparar;
}

/* Obtiene una posición utilizada para consultarla o modificarla. */
void *obtenerElemento(Conjunto *conjunto, int indice) {
    if (indice < 0 || indice >= conjunto->cantidad)
        return NULL;
    unsigned char *inicio = (unsigned char *)conjunto->elementos;
    return inicio + (size_t)indice * conjunto->tamElemento;
}

/* Busca con el comparador sólo en las posiciones utilizadas. */
int buscarElemento(const Conjunto *conjunto, const void *elemento) {
    const unsigned char *inicio = (const unsigned char *)conjunto->elementos;
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        const void *actual = inicio + (size_t)indice * conjunto->tamElemento;
        if (conjunto->comparar(actual, elemento) == 0)
            return indice;
    }
    return -1;
}

/* Agrega un elemento si no existe y queda espacio. */
int agregarElemento(Conjunto *conjunto, const void *elemento) {
    if (conjunto->cantidad >= conjunto->capacidad) return 0;
    if (buscarElemento(conjunto, elemento) != -1) return 0;

    unsigned char *inicio = (unsigned char *)conjunto->elementos;
    unsigned char *destino = inicio + (size_t)conjunto->cantidad * conjunto->tamElemento;

    memcpy(destino, elemento, conjunto->tamElemento);
    conjunto->cantidad++;
    return 1;
}

/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const void *elemento) {
    int indice = buscarElemento(conjunto, elemento);
    if (indice == -1) return 0;

    unsigned char *inicio = (unsigned char *)conjunto->elementos;
    for (int i = indice; i < conjunto->cantidad - 1; i++) {
        unsigned char *actual = inicio + (size_t)i * conjunto->tamElemento;
        unsigned char *siguiente = inicio + (size_t)(i + 1) * conjunto->tamElemento;
        memcpy(actual, siguiente, conjunto->tamElemento);
    }

    conjunto->cantidad--;
    return 1;
}

/* Sustituye un elemento sin introducir elementos repetidos. */
int reemplazarElemento(Conjunto *conjunto, const void *elemento,
                       const void *reemplazo) {
    int posExistente = buscarElemento(conjunto, elemento);
    if (posExistente == -1) return 0;

    int posReemplazo = buscarElemento(conjunto, reemplazo);
    if (posReemplazo != -1) return 0;

    unsigned char *destino = (unsigned char *)obtenerElemento(conjunto, posExistente);
    memcpy(destino, reemplazo, conjunto->tamElemento);
    return 1;
}

/* Deja el conjunto vacío y conserva su capacidad. */
void vaciarConjunto(Conjunto *conjunto) {
    conjunto->cantidad = 0;
}

/* Copia todos los elementos del origen. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    if (destino->capacidad < origen->cantidad) return -1;

    unsigned char *pOrigen = (unsigned char *)origen->elementos;
    unsigned char *pDestino = (unsigned char *)destino->elementos;

    memcpy(pDestino, pOrigen, (size_t)origen->cantidad * origen->tamElemento);
    destino->cantidad = origen->cantidad;
    return destino->cantidad;
}

/* Comprueba si todos los elementos de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    const unsigned char *inicioA = (const unsigned char *)conjuntoA->elementos;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elemA = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elemA) == -1) {
            return 0;
        }
    }
    return 1;
}

/* Comprueba si ambos conjuntos contienen los mismos elementos. */
int sonConjuntosIguales(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    if (conjuntoA->cantidad != conjuntoB->cantidad) return 0;
    return esSubconjunto(conjuntoA, conjuntoB);
}

/* Calcula la unión conservando primero el orden de A. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    int elementosNuevos = 0;
    const unsigned char *inicioB = (const unsigned char *)conjuntoB->elementos;

    for (int i = 0; i < conjuntoB->cantidad; i++) {
        const void *elemB = inicioB + (size_t)i * conjuntoB->tamElemento;
        if (buscarElemento(conjuntoA, elemB) == -1) {
            elementosNuevos++;
        }
    }

    if (conjuntoA->cantidad + elementosNuevos > resultado->capacidad) {
        return -1;
    }

    vaciarConjunto(resultado);
    copiarConjunto(conjuntoA, resultado);

    for (int i = 0; i < conjuntoB->cantidad; i++) {
        const void *elemB = inicioB + (size_t)i * conjuntoB->tamElemento;
        if (buscarElemento(conjuntoA, elemB) == -1) {
            agregarElemento(resultado, elemB);
        }
    }

    return resultado->cantidad;
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    int coincidentes = 0;
    const unsigned char *inicioA = (const unsigned char *)conjuntoA->elementos;

    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elemA = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elemA) != -1) {
            coincidentes++;
        }
    }

    if (coincidentes > resultado->capacidad) {
        return -1;
    }

    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elemA = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elemA) != -1) {
            agregarElemento(resultado, elemA);
        }
    }

    return resultado->cantidad;
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    int diferentes = 0;
    const unsigned char *inicioA = (const unsigned char *)conjuntoA->elementos;

    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elemA = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elemA) == -1) {
            diferentes++;
        }
    }

    if (diferentes > resultado->capacidad) {
        return -1;
    }

    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elemA = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elemA) == -1) {
            agregarElemento(resultado, elemA);
        }
    }

    return resultado->cantidad;
}

/* Intercambia registros completos, no sólo sus campos de comparación. */
int intercambiarElementos(Conjunto *conjunto, int indiceA, int indiceB) {
    if (indiceA < 0 || indiceA >= conjunto->cantidad ||
        indiceB < 0 || indiceB >= conjunto->cantidad) {
        return 0;
    }
    if (indiceA == indiceB) return 1;

    unsigned char *elemA = (unsigned char *)obtenerElemento(conjunto, indiceA);
    unsigned char *elemB = (unsigned char *)obtenerElemento(conjunto, indiceB);

    for (size_t i = 0; i < conjunto->tamElemento; i++) {
        unsigned char temp = *(elemA + i);
        *(elemA + i) = *(elemB + i);
        *(elemB + i) = temp;
    }

    return 1;
}

/* Ordena con el mismo comparador que determina la pertenencia. */
void ordenarConjunto(Conjunto *conjunto) {
    if (conjunto->cantidad <= 1) return;

    for (int i = 0; i < conjunto->cantidad - 1; i++) {
        for (int j = 0; j < conjunto->cantidad - 1 - i; j++) {
            void *elemActual = obtenerElemento(conjunto, j);
            void *elemSiguiente = obtenerElemento(conjunto, j + 1);

            if (conjunto->comparar(elemActual, elemSiguiente) > 0) {
                intercambiarElementos(conjunto, j, j + 1);
            }
        }
    }
}

/* Busca mediante búsqueda binaria en un conjunto ya ordenado. */
int buscarElementoOrdenado(const Conjunto *conjunto, const void *elemento) {
    int izquierda = 0;
    int derecha = conjunto->cantidad - 1;
    const unsigned char *inicio = (const unsigned char *)conjunto->elementos;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        const void *elemMedio = inicio + (size_t)medio * conjunto->tamElemento;

        int comp = conjunto->comparar(elemMedio, elemento);
        if (comp == 0) return medio;
        if (comp < 0) izquierda = medio + 1;
        else derecha = medio - 1;
    }

    return -1;
}

/* Muestra el contenido mediante la función correspondiente al tipo. */
void mostrarConjunto(const Conjunto *conjunto, MostrarElemento mostrar) {
    const unsigned char *inicio = (const unsigned char *)conjunto->elementos;
    printf("{");
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        mostrar(inicio + (size_t)indice * conjunto->tamElemento);
    }
    printf("}\n");
}