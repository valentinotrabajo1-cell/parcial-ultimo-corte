#ifndef COMBATE_H
#define COMBATE_H

#include "entidades.h"


int jugador_ataca(
    const Jugador* jugador,
    Enemigo enemigos[],
    int num_enemigos,
    Estadisticas* stats
);

int calcular_distancia(int x1, int y1, int x2, int y2);

#endif


