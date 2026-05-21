#include "../include/mapa.h"
#include "../include/constantes.h"
#include <stdio.h>
#include <string.h>

/*
  Cada sala se construye como una cuadricula de caracteres.
  '#' = pared, '.' = suelo, 'D' = puerta, 'E' = meta.

  El dungeon tiene 6 salas conectadas asi:
      [0] -- [1] -- [2]
               |
              [3] -- [4]
               |
              [5]

  Las salas 0..5 son las minimas requeridas.
  Ademas se agregan 2 extra (6 y 7) para dar mas profundidad.

      [0] -- [1] -- [2] -- [6]
               |
              [3] -- [4]
               |
              [5] -- [7]  <-- sala con la meta (escalera)
*/

// Llena una sala con paredes en los bordes y suelo en el interior
static void sala_base(char mapa[ALTO_SALA][ANCHO_SALA]) {
    int fila, col;
    for (fila = 0; fila < ALTO_SALA; fila++) {
        for (col = 0; col < ANCHO_SALA; col++) {
            // Borde = pared, interior = suelo
            if (fila == 0 || fila == ALTO_SALA - 1 ||
                col == 0 || col == ANCHO_SALA - 1) {
                mapa[fila][col] = SIM_PARED;
            } else {
                mapa[fila][col] = SIM_SUELO;
            }
        }
    }
}

// Agrega una columna de obstaculos internos para hacer la sala interesante
static void agregar_pared_interna(
    char mapa[ALTO_SALA][ANCHO_SALA],
    int col_inicio, int fila_inicio, int longitud, int vertical
) {
    int i;
    for (i = 0; i < longitud; i++) {
        int f = vertical ? (fila_inicio + i) : fila_inicio;
        int c = vertical ? col_inicio : (col_inicio + i);
        if (f > 0 && f < ALTO_SALA - 1 && c > 0 && c < ANCHO_SALA - 1) {
            mapa[f][c] = SIM_PARED;
        }
    }
}
