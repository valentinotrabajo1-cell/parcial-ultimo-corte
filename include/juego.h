#ifndef JUEGO_H
#define JUEGO_H

#include "entidades.h"


int verificar_victoria(const Jugador* jugador, const Sala salas[]);


int verificar_derrota(const Jugador* jugador);


void mostrar_victoria();


void mostrar_derrota();


void limpiar_pantalla();


void pausar();


char leer_tecla();

#endif
