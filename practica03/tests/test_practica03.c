/*
 * Archivo: test_practica03.c
 * Pruebas unitarias sin dependencias externas para la práctica 03.
 * Este archivo forma parte de la infraestructura y no debe modificarse.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"

static int pruebas;
static int fallas;

#define COMPROBAR(condicion) do { \
    if (!(condicion)) { \
        printf("    %s:%d: falló %s\n", __FILE__, __LINE__, #condicion); \
        return 0; \
    } \
} while (0)

static void registrarResultado(const char nombre[], int pasa) {
    pruebas++;
    if (!pasa)
        fallas++;
    printf("[%s] %s\n", pasa ? "PASA" : "FALLA", nombre);
}

static int mismoEstudiante(const Estudiante *obtenido,
                           const Estudiante *esperado) {
    return obtenido->matricula == esperado->matricula &&
           strcmp(obtenido->nombre.nombres, esperado->nombre.nombres) == 0 &&
           strcmp(obtenido->nombre.apellidos,
                  esperado->nombre.apellidos) == 0 &&
           obtenido->promedio == esperado->promedio;
}

static int mismosEstudiantes(const Conjunto *conjunto,
                             const Estudiante esperados[], int cantidad) {
    if (conjunto->cantidad != cantidad)
        return 0;
    for (int indice = 0; indice < cantidad; indice++) {
        if (!mismoEstudiante(&conjunto->elementos[indice],
                            &esperados[indice]))
            return 0;
    }
    return 1;
}

static int testInicializarYBuscar(void) {
    Conjunto conjunto;
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante ausente = {.matricula = 999};
    inicializarConjunto(&conjunto, 3);
    COMPROBAR(conjunto.cantidad == 0);
    COMPROBAR(conjunto.capacidad == 3);
    COMPROBAR(obtenerElemento(&conjunto, 0) == NULL);
    conjunto.elementos[0] = ana;
    conjunto.elementos[1] = bruno;
    conjunto.cantidad = 2;
    COMPROBAR(buscarElemento(&conjunto, &ana) == 0);
    COMPROBAR(buscarElemento(&conjunto, &bruno) == 1);
    COMPROBAR(buscarElemento(&conjunto, &ausente) == -1);
    return 1;
}

static int testAgregarYCapacidad(void) {
    Conjunto conjunto;
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante repetida = {101, {"Otra", "Persona"}, 10.0f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    inicializarConjunto(&conjunto, 2);
    COMPROBAR(agregarElemento(&conjunto, &ana) == 1);
    COMPROBAR(agregarElemento(&conjunto, &repetida) == 0);
    COMPROBAR(agregarElemento(&conjunto, &bruno) == 1);
    COMPROBAR(agregarElemento(&conjunto, &carla) == 0);
    COMPROBAR(conjunto.cantidad == 2);
    COMPROBAR(mismoEstudiante(&conjunto.elementos[0], &ana));
    COMPROBAR(mismoEstudiante(&conjunto.elementos[1], &bruno));
    return 1;
}

static int testEliminar(void) {
    Conjunto conjunto;
    Estudiante datos[] = {
        {101, {"Ana", "López"}, 8.5f},
        {205, {"Bruno", "Pérez"}, 9.1f},
        {307, {"Carla", "Ruiz"}, 8.8f}
    };
    Estudiante esperado[] = {datos[0], datos[2]};
    Estudiante ausente = {.matricula = 999};
    inicializarConjunto(&conjunto, 3);
    for (int indice = 0; indice < 3; indice++)
        conjunto.elementos[indice] = datos[indice];
    conjunto.cantidad = 3;
    COMPROBAR(eliminarElemento(&conjunto, &datos[1]) == 1);
    COMPROBAR(mismosEstudiantes(&conjunto, esperado, 2));
    COMPROBAR(eliminarElemento(&conjunto, &ausente) == 0);
    COMPROBAR(conjunto.cantidad == 2);
    return 1;
}

static int testReemplazarYVaciar(void) {
    Conjunto conjunto;
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    inicializarConjunto(&conjunto, 3);
    conjunto.elementos[0] = ana;
    conjunto.elementos[1] = bruno;
    conjunto.cantidad = 2;
    COMPROBAR(reemplazarElemento(&conjunto, &bruno, &carla) == 1);
    COMPROBAR(mismoEstudiante(&conjunto.elementos[1], &carla));
    COMPROBAR(reemplazarElemento(&conjunto, &ana, &carla) == 0);
    COMPROBAR(conjunto.cantidad == 2);
    vaciarConjunto(&conjunto);
    COMPROBAR(conjunto.cantidad == 0);
    COMPROBAR(conjunto.capacidad == 3);
    return 1;
}

static int testCopiaSubconjuntoEIgualdad(void) {
    Conjunto origen;
    Conjunto copia;
    Conjunto pequeno;
    Conjunto subconjunto;
    Estudiante datos[] = {
        {101, {"Ana", "López"}, 8.5f},
        {205, {"Bruno", "Pérez"}, 9.1f},
        {307, {"Carla", "Ruiz"}, 8.8f}
    };
    inicializarConjunto(&origen, 3);
    inicializarConjunto(&copia, 3);
    inicializarConjunto(&pequeno, 2);
    inicializarConjunto(&subconjunto, 2);
    for (int indice = 0; indice < 3; indice++)
        origen.elementos[indice] = datos[indice];
    origen.cantidad = 3;
    subconjunto.elementos[0] = datos[0];
    subconjunto.elementos[1] = datos[2];
    subconjunto.cantidad = 2;
    COMPROBAR(copiarConjunto(&origen, &copia) == 3);
    COMPROBAR(sonConjuntosIguales(&origen, &copia) == 1);
    COMPROBAR(esSubconjunto(&subconjunto, &origen) == 1);
    COMPROBAR(esSubconjunto(&origen, &subconjunto) == 0);
    COMPROBAR(copiarConjunto(&origen, &pequeno) == -1);
    COMPROBAR(pequeno.cantidad == 0);
    return 1;
}

static int testOperacionesEntreConjuntos(void) {
    Conjunto a;
    Conjunto b;
    Conjunto resultado;
    Conjunto pequeno;
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    Estudiante diana = {409, {"Diana", "Soto"}, 9.4f};
    Estudiante unionEsperada[] = {ana, bruno, carla, diana};
    Estudiante interseccionEsperada[] = {bruno};
    Estudiante diferenciaEsperada[] = {ana, carla};
    inicializarConjunto(&a, 3);
    inicializarConjunto(&b, 2);
    inicializarConjunto(&resultado, 5);
    inicializarConjunto(&pequeno, 2);
    a.elementos[0] = ana;
    a.elementos[1] = bruno;
    a.elementos[2] = carla;
    a.cantidad = 3;
    b.elementos[0] = bruno;
    b.elementos[1] = diana;
    b.cantidad = 2;
    pequeno.elementos[0] = diana;
    pequeno.cantidad = 1;
    COMPROBAR(unirConjuntos(&a, &b, &pequeno) == -1);
    COMPROBAR(pequeno.cantidad == 1);
    COMPROBAR(mismoEstudiante(&pequeno.elementos[0], &diana));
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == 4);
    COMPROBAR(mismosEstudiantes(&resultado, unionEsperada, 4));
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 1);
    COMPROBAR(mismosEstudiantes(&resultado, interseccionEsperada, 1));
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 2);
    COMPROBAR(mismosEstudiantes(&resultado, diferenciaEsperada, 2));
    return 1;
}

static int testOperacionesDeEstudiante(void) {
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante mismaMatricula = {101, {"Otra", "Persona"}, 6.0f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    COMPROBAR(compararEstudiantes(&ana, &mismaMatricula) == 0);
    COMPROBAR(compararEstudiantes(&ana, &bruno) != 0);
    actualizarPromedio(&ana, 9.5f);
    COMPROBAR(ana.promedio == 9.5f);
    COMPROBAR(ana.matricula == 101);
    COMPROBAR(strcmp(ana.nombre.nombres, "Ana") == 0);
    return 1;
}

int main(void) {
    registrarResultado("inicializar y buscar", testInicializarYBuscar());
    registrarResultado("agregar y respetar capacidad",
                       testAgregarYCapacidad());
    registrarResultado("eliminar y conservar el orden", testEliminar());
    registrarResultado("reemplazar y vaciar", testReemplazarYVaciar());
    registrarResultado("copiar, subconjunto e igualdad",
                       testCopiaSubconjuntoEIgualdad());
    registrarResultado("unión, intersección y diferencia",
                       testOperacionesEntreConjuntos());
    registrarResultado("operaciones propias de estudiante",
                       testOperacionesDeEstudiante());

    printf("\nPruebas: %d; pasaron: %d; fallaron: %d.\n",
           pruebas, pruebas - fallas, fallas);
    return fallas == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
