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

