#include "../include/mapa.h"
#include "../include/constantes.h"
#include <stdio.h>
#include <string.h>

/*
  Cada sala se construye como una cuadricula de caracteres.
  '#' = pared, '.' = suelo, 'D' = puerta, 'E' = meta.

  El dungeon tiene 6 salas conectadas asi:
      [0] -- [1] -- [2]
               |
              [3] -- [4]
               |
              [5]

  Las salas 0..5 son las minimas requeridas.
  Ademas se agregan 2 extra (6 y 7) para dar mas profundidad.

      [0] -- [1] -- [2] -- [6]
               |
              [3] -- [4]
               |
              [5] -- [7]  <-- sala con la meta (escalera)
*/


