#include "../include/jugador.h"
#include "../include/mapa.h"
#include "../include/constantes.h"
#include <stdio.h>

void inicializar_jugador(Jugador* jugador) {
    // El jugador empieza en la sala 0, posicion (2, 5)
    jugador->x = 2;
    jugador->y = 5;
    jugador->vida = VIDA_JUGADOR;
    jugador->sala_actual = 0;
    jugador->tiene_item = 0;
}

/*
  Mueve al jugador una celda en la direccion indicada.
  Si la celda de destino es una puerta, cambia de sala.
  Si es una pared, no se mueve.
  Devuelve 1 si cambio de sala, 0 si no.
*/
int mover_jugador(
    Jugador* jugador,
    char direccion,
    const Sala salas[],
    int /*num_salas*/
) {
    int nuevo_x = jugador->x;
    int nuevo_y = jugador->y;

    // Calculamos la nueva posicion segun la tecla
    if (direccion == TECLA_ARRIBA)  nuevo_y -= 1;
    if (direccion == TECLA_ABAJO)   nuevo_y += 1;
    if (direccion == TECLA_IZQ)     nuevo_x -= 1;
    if (direccion == TECLA_DER)     nuevo_x += 1;

    // Si es pared, no nos movemos
    if (es_pared(salas, jugador->sala_actual, nuevo_x, nuevo_y)) {
        return 0;
    }

    // Revisamos si la celda de destino es una puerta
    char celda = salas[jugador->sala_actual].mapa[nuevo_y][nuevo_x];

    if (celda == SIM_PUERTA) {
        // Buscamos a que sala lleva esta puerta
        int s, num_p;
        num_p = salas[jugador->sala_actual].num_puertas;

        for (s = 0; s < num_p; s++) {
            // Usamos puntero a la puerta para mostrar uso de punteros
            const Puerta* p = &salas[jugador->sala_actual].puertas[s];
            if (p->x == nuevo_x && p->y == nuevo_y) {
                // Cambiamos al jugador de sala
                jugador->sala_actual = p->sala_destino;
                jugador->x = p->x_destino;
                jugador->y = p->y_destino;
                return 1; // cambio de sala
            }
        }
    }

    // Movimiento normal (no es puerta ni pared)
    jugador->x = nuevo_x;
    jugador->y = nuevo_y;
    return 0;
}

