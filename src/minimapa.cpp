#include "../include/minimapa.h"
#include "../include/constantes.h"
#include <stdio.h>

/*
  minimapa.cpp
  ------------
  Implementacion del minimapa esquematico del dungeon.

  Usamos un arreglo estatico de enteros para saber que salas
  el jugador ya visito. 1 = visitada, 0 = no visitada.

  El mapa del dungeon se ve asi:

      Sala 0 -- Sala 1 -- Sala 2 -- Sala 6
                  |
                Sala 3 -- Sala 4
                  |
                Sala 5 -- Sala 7 (META)

  Lo dibujamos con caracteres ASCII sencillos.
*/


