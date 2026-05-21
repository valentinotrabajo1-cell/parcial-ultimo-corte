#ifndef PUNTUACION_H
#define PUNTUACION_H

#include "entidades.h"

void inicializar_estadisticas(Estadisticas* stats);


void sumar_turno(Estadisticas* stats);


void mostrar_estadisticas(const Estadisticas* stats);

#endif
