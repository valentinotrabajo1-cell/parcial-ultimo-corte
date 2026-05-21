#include <stdio.h>
#include "include/constantes.h"
#include "include/entidades.h"
#include "include/mapa.h"
#include "include/jugador.h"
#include "include/enemigo.h"
#include "include/juego.h"
#include "include/combate.h"
#include "include/minimapa.h"
#include "include/puntuacion.h"

/*
  =====================================================
  DUNGEON CRAWLER  -  Parcial Final
  =====================================================
  Juego inspirado en Adventure (Atari 2600, 1980).

  Objetivo: encuentra el objeto clave (*) y llega
            a la escalera de salida (E) en la sala 7.

  El mapa de salas:
    [0] -- [1] -- [2] -- [6]
            |
           [3] -- [4]
            |
           [5] -- [7]  <- sala con la meta

  Tipos de enemigos:
    G = Goblin: persigue cada turno (vida: 2 golpes)
    S = Slime : persigue cada 2 turnos (vida: 3 golpes)

  Nuevas funcionalidades:
    F = atacar enemigos cercanos (rango 2 celdas)
    M = mostrar minimapa del dungeon
    Las estadisticas se muestran al ganar o perder.
  =====================================================
*/
