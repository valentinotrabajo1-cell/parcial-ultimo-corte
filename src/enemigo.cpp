#include "../include/enemigo.h"
#include "../include/mapa.h"
#include "../include/constantes.h"
#include <stdio.h>

/*
  enemigo.cpp
  -----------
  Logica de los enemigos del dungeon.

  Los enemigos persiguen al jugador dentro de su sala.
  Con el nuevo sistema de combate activo:
  - Los enemigos ya NO hacen danio automatico al tocar al jugador.
  - En cambio, cada turno que el enemigo esta ADYACENTE al jugador,
    le hace un punto de danio (como "golpe de contacto" simple).
  - El jugador puede matarlos presionando 'F' cuando estan cerca.
*/

void inicializar_enemigos(Enemigo enemigos[], int* num_enemigos) {
    Enemigo* e = enemigos; // puntero al inicio del arreglo
    int idx = 0;

    // Goblin 1 en sala 1 (vida = VIDA_GOBLIN = 2 golpes)
    e[idx].x = 15; e[idx].y = 3; e[idx].vida = VIDA_GOBLIN;
    e[idx].sala = 1; e[idx].vivo = 1;
    e[idx].tipo = GOBLIN; e[idx].contador_turno = 0;
    idx++;

    // Goblin 2 en sala 3
    e[idx].x = 3; e[idx].y = 7; e[idx].vida = VIDA_GOBLIN;
    e[idx].sala = 3; e[idx].vivo = 1;
    e[idx].tipo = GOBLIN; e[idx].contador_turno = 0;
    idx++;

    // Goblin 3 en sala 6
    e[idx].x = 15; e[idx].y = 7; e[idx].vida = VIDA_GOBLIN;
    e[idx].sala = 6; e[idx].vivo = 1;
    e[idx].tipo = GOBLIN; e[idx].contador_turno = 0;
    idx++;

    // Goblin 4 en sala 4
    e[idx].x = 10; e[idx].y = 5; e[idx].vida = VIDA_GOBLIN;
    e[idx].sala = 4; e[idx].vivo = 1;
    e[idx].tipo = GOBLIN; e[idx].contador_turno = 0;
    idx++;

    // Slime 1 en sala 2 (vida = VIDA_SLIME = 3 golpes)
    e[idx].x = 5; e[idx].y = 3; e[idx].vida = VIDA_SLIME;
    e[idx].sala = 2; e[idx].vivo = 1;
    e[idx].tipo = SLIME; e[idx].contador_turno = 0;
    idx++;

    // Slime 2 en sala 5
    e[idx].x = 15; e[idx].y = 3; e[idx].vida = VIDA_SLIME;
    e[idx].sala = 5; e[idx].vivo = 1;
    e[idx].tipo = SLIME; e[idx].contador_turno = 0;
    idx++;

    // Slime 3 en sala 7 (sala final)
    e[idx].x = 10; e[idx].y = 3; e[idx].vida = VIDA_SLIME;
    e[idx].sala = 7; e[idx].vivo = 1;
    e[idx].tipo = SLIME; e[idx].contador_turno = 0;
    idx++;

    *num_enemigos = idx;
}

/*
  Mueve un enemigo un paso hacia el jugador.
  Logica simple: calcula diferencia en X e Y, mueve en el eje mayor.
  Si hay pared en esa direccion, intenta el otro eje.
*/
static void perseguir(Enemigo* enemigo, const Jugador* jugador, const Sala salas[]) {
    int diff_x = jugador->x - enemigo->x;
    int diff_y = jugador->y - enemigo->y;

    int dx = 0;
    int dy = 0;

    if (diff_x > 0) dx = 1;
    else if (diff_x < 0) dx = -1;

    if (diff_y > 0) dy = 1;
    else if (diff_y < 0) dy = -1;

    // Valor absoluto manual (sin <cmath>)
    int abs_dx = diff_x < 0 ? -diff_x : diff_x;
    int abs_dy = diff_y < 0 ? -diff_y : diff_y;

    int nuevo_x = enemigo->x;
    int nuevo_y = enemigo->y;

    if (abs_dx >= abs_dy) {
        // Intentar mover en X primero
        if (dx != 0 && !es_pared(salas, enemigo->sala, enemigo->x + dx, enemigo->y)) {
            nuevo_x = enemigo->x + dx;
        } else if (dy != 0 && !es_pared(salas, enemigo->sala, enemigo->x, enemigo->y + dy)) {
            nuevo_y = enemigo->y + dy;
        }
    } else {
        // Intentar mover en Y primero
        if (dy != 0 && !es_pared(salas, enemigo->sala, enemigo->x, enemigo->y + dy)) {
            nuevo_y = enemigo->y + dy;
        } else if (dx != 0 && !es_pared(salas, enemigo->sala, enemigo->x + dx, enemigo->y)) {
            nuevo_x = enemigo->x + dx;
        }
    }

    // Los enemigos no cruzan puertas ni la meta
    char celda = salas[enemigo->sala].mapa[nuevo_y][nuevo_x];
    if (celda == SIM_PUERTA || celda == SIM_META) {
        return;
    }

    enemigo->x = nuevo_x;
    enemigo->y = nuevo_y;
}

void mover_enemigos(
    Enemigo enemigos[],
    int num_enemigos,
    const Jugador* jugador,
    const Sala salas[]
) {
    int i;
    for (i = 0; i < num_enemigos; i++) {
        Enemigo* e = &enemigos[i];

        // Solo actuamos sobre enemigos vivos en la sala actual del jugador
        if (!e->vivo || e->sala != jugador->sala_actual) {
            continue;
        }

        if (e->tipo == GOBLIN) {
            // Goblin: persigue cada turno sin pausa
            perseguir(e, jugador, salas);
        } else {
            // Slime: se mueve lento, solo cada 2 turnos
            e->contador_turno++;
            if (e->contador_turno >= 2) {
                perseguir(e, jugador, salas);
                e->contador_turno = 0;
            }
        }
    }
}

/*
  atacar_jugador: los enemigos hacen danio al jugador si estan adyacentes.
  "Adyacente" significa distancia de Manhattan = 1 (justo al lado).
  Esto reemplaza el sistema anterior donde el danio era al pisar la misma celda.
  Ahora el jugador tiene que presionar 'F' para contraatacar.
*/
void atacar_jugador(
    const Enemigo enemigos[],
    int num_enemigos,
    Jugador* jugador
) {
    int i;
    for (i = 0; i < num_enemigos; i++) {
        const Enemigo* e = &enemigos[i];

        if (!e->vivo || e->sala != jugador->sala_actual) {
            continue;
        }

        // Calculamos distancia de Manhattan manualmente
        int diff_x = e->x - jugador->x;
        int diff_y = e->y - jugador->y;
        if (diff_x < 0) diff_x = -diff_x;
        if (diff_y < 0) diff_y = -diff_y;
        int distancia = diff_x + diff_y;

        // Si el enemigo esta en la misma celda o justo al lado, ataca
        if (distancia <= 1) {
            int dano = (e->tipo == GOBLIN) ? DANO_GOBLIN : DANO_SLIME;
            jugador->vida -= dano;

            if (e->tipo == GOBLIN) {
                printf("  [!] Un Goblin te ataco! Vida: %d\n", jugador->vida);
            } else {
                printf("  [!] Un Slime te ataco! Vida: %d\n", jugador->vida);
            }
        }
    }
}


