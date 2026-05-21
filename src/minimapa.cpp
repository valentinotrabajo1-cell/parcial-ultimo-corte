#include "../include/minimapa.h"
#include "../include/constantes.h"
#include <stdio.h>

/*
  minimapa.cpp
  ------------
  Implementacion del minimapa esquematico del dungeon.

  Usamos un arreglo estatico de enteros para saber que salas
  el jugador ya visito. 1 = visitada, 0 = no visitada.

  El mapa del dungeon se ve asi:

      Sala 0 -- Sala 1 -- Sala 2 -- Sala 6
                  |
                Sala 3 -- Sala 4
                  |
                Sala 5 -- Sala 7 (META)

  Lo dibujamos con caracteres ASCII sencillos.
*/

// Arreglo estatico: registra si cada sala fue visitada
// Indice = numero de sala, valor = 1 si visitada, 0 si no
static int salas_visitadas[MAX_SALAS] = {0, 0, 0, 0, 0, 0, 0, 0};

// Marca una sala como visitada
void registrar_sala_visitada(int sala) {
    if (sala >= 0 && sala < MAX_SALAS) {
        salas_visitadas[sala] = 1;
    }
}

/*
  Devuelve el texto que se muestra para una sala:
  - Si es la sala actual del jugador: "[N]"
  - Si fue visitada: " N "
  - Si no fue visitada: " ? "
*/
static void imprimir_sala(int numero_sala, int sala_actual) {
    if (numero_sala == sala_actual) {
        printf("[%d]", numero_sala); // sala donde esta el jugador
    } else if (salas_visitadas[numero_sala]) {
        printf(" %d ", numero_sala); // sala visitada
    } else {
        printf(" ? "); // sala desconocida
    }
}

/*
  Muestra el minimapa completo en pantalla.
  El layout refleja la conexion real de las salas:

  [0] -- [1] -- [2] -- [6]
                 |
               [3] -- [4]
                 |
               [5] -- [7]  <- META
*/
void mostrar_minimapa(int sala_actual) {
    printf("\n  ============ MAPA DEL DUNGEON ============\n");
    printf("\n");

    // Fila 1: sala 0 -- sala 1 -- sala 2 -- sala 6
    printf("  ");
    imprimir_sala(0, sala_actual);
    printf("--");
    imprimir_sala(1, sala_actual);
    printf("--");
    imprimir_sala(2, sala_actual);
    printf("--");
    imprimir_sala(6, sala_actual);
    printf("\n");

    // Conexion vertical entre sala 1 y sala 3
    printf("           |  \n");

    // Fila 2: sala 3 -- sala 4
    printf("         ");
    imprimir_sala(3, sala_actual);
    printf("--");
    imprimir_sala(4, sala_actual);
    printf("\n");

    // Conexion vertical entre sala 3 y sala 5
    printf("           |  \n");

    // Fila 3: sala 5 -- sala 7 (META)
    printf("         ");
    imprimir_sala(5, sala_actual);
    printf("--");
    imprimir_sala(7, sala_actual);
    printf(" <- META\n");

    printf("\n");
    printf("  Leyenda: [N]=estas aqui  N=visitada  ?=sin explorar\n");
    printf("  ==========================================\n\n");
}
