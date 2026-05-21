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

void inicializar_salas(Sala salas[], int num_salas) {
    int i;

    // Primero llenamos todas las salas con la base
    for (i = 0; i < num_salas; i++) {
        sala_base(salas[i].mapa);
        salas[i].num_puertas = 0;
        salas[i].tiene_meta = 0;
    }

    // ---- SALA 0: entrada, puerta derecha hacia sala 1 ----
    agregar_pared_interna(salas[0].mapa, 5, 2, 4, 1); // pared vertical corta
    salas[0].mapa[5][ANCHO_SALA - 1] = SIM_PUERTA;    // puerta derecha

    salas[0].puertas[0].x = ANCHO_SALA - 1;
    salas[0].puertas[0].y = 5;
    salas[0].puertas[0].sala_destino = 1;
    salas[0].puertas[0].x_destino = 1;
    salas[0].puertas[0].y_destino = 5;
    salas[0].num_puertas = 1;

    // ---- SALA 1: central, puertas: izquierda->0, derecha->2, abajo->3 ----
    agregar_pared_interna(salas[1].mapa, 8, 2, 3, 1);
    agregar_pared_interna(salas[1].mapa, 4, 4, 5, 0); // pared horizontal

    salas[1].mapa[5][0]            = SIM_PUERTA; // izquierda -> sala 0
    salas[1].mapa[5][ANCHO_SALA-1] = SIM_PUERTA; // derecha   -> sala 2
    salas[1].mapa[ALTO_SALA-1][10] = SIM_PUERTA; // abajo     -> sala 3

    salas[1].puertas[0].x = 0;           salas[1].puertas[0].y = 5;
    salas[1].puertas[0].sala_destino = 0;
    salas[1].puertas[0].x_destino = ANCHO_SALA - 2;
    salas[1].puertas[0].y_destino = 5;

    salas[1].puertas[1].x = ANCHO_SALA-1; salas[1].puertas[1].y = 5;
    salas[1].puertas[1].sala_destino = 2;
    salas[1].puertas[1].x_destino = 1;
    salas[1].puertas[1].y_destino = 5;

    salas[1].puertas[2].x = 10; salas[1].puertas[2].y = ALTO_SALA-1;
    salas[1].puertas[2].sala_destino = 3;
    salas[1].puertas[2].x_destino = 10;
    salas[1].puertas[2].y_destino = 1;

    salas[1].num_puertas = 3;

    // ---- SALA 2: puertas: izquierda->1, derecha->6 ----
    agregar_pared_interna(salas[2].mapa, 10, 3, 4, 1);

    salas[2].mapa[5][0]            = SIM_PUERTA; // izquierda -> sala 1
    salas[2].mapa[5][ANCHO_SALA-1] = SIM_PUERTA; // derecha   -> sala 6

    salas[2].puertas[0].x = 0; salas[2].puertas[0].y = 5;
    salas[2].puertas[0].sala_destino = 1;
    salas[2].puertas[0].x_destino = ANCHO_SALA - 2;
    salas[2].puertas[0].y_destino = 5;

    salas[2].puertas[1].x = ANCHO_SALA-1; salas[2].puertas[1].y = 5;
    salas[2].puertas[1].sala_destino = 6;
    salas[2].puertas[1].x_destino = 1;
    salas[2].puertas[1].y_destino = 5;

    salas[2].num_puertas = 2;

    // ---- SALA 3: puertas: arriba->1, derecha->4, abajo->5 ----
    agregar_pared_interna(salas[3].mapa, 5, 2, 6, 1);

    salas[3].mapa[0][10]           = SIM_PUERTA; // arriba   -> sala 1
    salas[3].mapa[5][ANCHO_SALA-1] = SIM_PUERTA; // derecha  -> sala 4
    salas[3].mapa[ALTO_SALA-1][10] = SIM_PUERTA; // abajo    -> sala 5

    salas[3].puertas[0].x = 10; salas[3].puertas[0].y = 0;
    salas[3].puertas[0].sala_destino = 1;
    salas[3].puertas[0].x_destino = 10;
    salas[3].puertas[0].y_destino = ALTO_SALA - 2;

    salas[3].puertas[1].x = ANCHO_SALA-1; salas[3].puertas[1].y = 5;
    salas[3].puertas[1].sala_destino = 4;
    salas[3].puertas[1].x_destino = 1;
    salas[3].puertas[1].y_destino = 5;

    salas[3].puertas[2].x = 10; salas[3].puertas[2].y = ALTO_SALA-1;
    salas[3].puertas[2].sala_destino = 5;
    salas[3].puertas[2].x_destino = 10;
    salas[3].puertas[2].y_destino = 1;

    salas[3].num_puertas = 3;

    // ---- SALA 4: puertas: izquierda->3 ----
    agregar_pared_interna(salas[4].mapa, 7, 2, 5, 1);
    agregar_pared_interna(salas[4].mapa, 12, 4, 4, 1);

    salas[4].mapa[5][0] = SIM_PUERTA; // izquierda -> sala 3

    salas[4].puertas[0].x = 0; salas[4].puertas[0].y = 5;
    salas[4].puertas[0].sala_destino = 3;
    salas[4].puertas[0].x_destino = ANCHO_SALA - 2;
    salas[4].puertas[0].y_destino = 5;

    salas[4].num_puertas = 1;

    // ---- SALA 5: puertas: arriba->3, derecha->7 ----
    agregar_pared_interna(salas[5].mapa, 4, 3, 3, 1);

    salas[5].mapa[0][10]           = SIM_PUERTA; // arriba  -> sala 3
    salas[5].mapa[5][ANCHO_SALA-1] = SIM_PUERTA; // derecha -> sala 7

    salas[5].puertas[0].x = 10; salas[5].puertas[0].y = 0;
    salas[5].puertas[0].sala_destino = 3;
    salas[5].puertas[0].x_destino = 10;
    salas[5].puertas[0].y_destino = ALTO_SALA - 2;

    salas[5].puertas[1].x = ANCHO_SALA-1; salas[5].puertas[1].y = 5;
    salas[5].puertas[1].sala_destino = 7;
    salas[5].puertas[1].x_destino = 1;
    salas[5].puertas[1].y_destino = 5;

    salas[5].num_puertas = 2;

    // ---- SALA 6: puertas: izquierda->2 ----
    agregar_pared_interna(salas[6].mapa, 9, 2, 4, 1);
    agregar_pared_interna(salas[6].mapa, 14, 4, 3, 1);

    salas[6].mapa[5][0] = SIM_PUERTA; // izquierda -> sala 2

    salas[6].puertas[0].x = 0; salas[6].puertas[0].y = 5;
    salas[6].puertas[0].sala_destino = 2;
    salas[6].puertas[0].x_destino = ANCHO_SALA - 2;
    salas[6].puertas[0].y_destino = 5;

    salas[6].num_puertas = 1;

    // ---- SALA 7: sala final con la META, puerta: izquierda->5 ----
    agregar_pared_interna(salas[7].mapa, 6, 2, 3, 1);

    salas[7].mapa[5][0]  = SIM_PUERTA; // izquierda -> sala 5
    salas[7].mapa[5][18] = SIM_META;   // escalera de salida
    salas[7].tiene_meta  = 1;

    salas[7].puertas[0].x = 0; salas[7].puertas[0].y = 5;
    salas[7].puertas[0].sala_destino = 5;
    salas[7].puertas[0].x_destino = ANCHO_SALA - 2;
    salas[7].puertas[0].y_destino = 5;

    salas[7].num_puertas = 1;
}


// -------------------------------------------------------
// Dibuja la sala actual en la consola
// -------------------------------------------------------
void dibujar_sala(
    const Sala salas[],
    int sala_actual,
    const Jugador* jugador,
    const Enemigo enemigos[],
    int num_enemigos,
    const Item items[],
    int num_items
) {
    int fila, col, i;

    // Copiamos el mapa base en un buffer temporal para no modificar el original
    char buffer[ALTO_SALA][ANCHO_SALA];
    for (fila = 0; fila < ALTO_SALA; fila++) {
        for (col = 0; col < ANCHO_SALA; col++) {
            buffer[fila][col] = salas[sala_actual].mapa[fila][col];
        }
    }

    // Ponemos los items visibles en el buffer
    for (i = 0; i < num_items; i++) {
        if (items[i].sala == sala_actual && items[i].visible) {
            buffer[items[i].y][items[i].x] = items[i].simbolo;
        }
    }

    // Ponemos los enemigos vivos de esta sala en el buffer
    for (i = 0; i < num_enemigos; i++) {
        if (enemigos[i].vivo && enemigos[i].sala == sala_actual) {
            char sim = (enemigos[i].tipo == GOBLIN) ? SIM_ENEMIGO_A : SIM_ENEMIGO_B;
            buffer[enemigos[i].y][enemigos[i].x] = sim;
        }
    }

    // Ponemos al jugador
    buffer[jugador->y][jugador->x] = SIM_JUGADOR;

    // Imprimimos el buffer
    printf("\n  Sala %d\n", sala_actual);
    printf("  ");
    for (col = 0; col < ANCHO_SALA; col++) printf("-");
    printf("\n");

    for (fila = 0; fila < ALTO_SALA; fila++) {
        printf("  ");
        for (col = 0; col < ANCHO_SALA; col++) {
            printf("%c", buffer[fila][col]);
        }
        printf("\n");
    }

    printf("  ");
    for (col = 0; col < ANCHO_SALA; col++) printf("-");
    printf("\n");
}

// Devuelve 1 si la celda es pared (no se puede pisar)
int es_pared(const Sala salas[], int sala, int x, int y) {
    if (x < 0 || x >= ANCHO_SALA || y < 0 || y >= ALTO_SALA) {
        return 1; // fuera de limites = pared
    }
    char celda = salas[sala].mapa[y][x];
    // Las puertas y la meta no son paredes
    if (celda == SIM_PUERTA || celda == SIM_META) {
        return 0;
    }
    return celda == SIM_PARED;
}
