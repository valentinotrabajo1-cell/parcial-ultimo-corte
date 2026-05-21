#include "../include/combate.h"
#include "../include/constantes.h"
#include <stdio.h>

/*
  combate.cpp
  -----------
  Implementacion del sistema de combate activo.

  Cuando el jugador presiona 'F':
  1. Buscamos todos los enemigos vivos en la sala actual.
  2. Calculamos la distancia al jugador.
  3. Si el enemigo esta dentro del rango, le hacemos danio.
  4. Si el enemigo queda sin vida, muere (vivo = false).
*/
