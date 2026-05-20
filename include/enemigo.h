#ifndef ENEMIGO_H
#define ENEMIGO_H


#include "entidades.h"

void inicializar_enemigos(Enemigo enemigos[], int* num_enemigos);


void mover_enemigos(
    Enemigo enemigos[],
    int num_enemigos,
    const Jugador* jugador,
    const Sala salas[]
);


void atacar_jugador(
    const Enemigo enemigos[],
    int num_enemigos,
    Jugador* jugador
);

#endif

