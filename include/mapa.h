#ifndef MAPA_H
#define MAPA_H

#include "entidades.h"


void inicializar_salas(Sala salas[], int num_salas);


void dibujar_sala(
    const Sala salas[],
    int sala_actual,
    const Jugador* jugador,
    const Enemigo enemigos[],
    int num_enemigos,
    const Item items[],
    int num_items
);


int es_pared(const Sala salas[], int sala, int x, int y);

#endif
