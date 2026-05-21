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

