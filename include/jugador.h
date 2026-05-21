#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidades.h"


void inicializar_jugador(Jugador* jugador);


int mover_jugador(
    Jugador* jugador,
    char direccion,
    const Sala salas[],
    int num_salas
);


void revisar_item(Jugador* jugador, Item items[], int num_items);


void soltar_item(Jugador* jugador, Item items[], int num_items);


void mostrar_estado(const Jugador* jugador);

#endif

