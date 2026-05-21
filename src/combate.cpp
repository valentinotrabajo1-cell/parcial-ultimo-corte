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

// Calcula distancia de Manhattan entre dos puntos
// Es la suma de la diferencia absoluta en X mas la diferencia absoluta en Y
// Ejemplo: (2,3) a (5,6) = |5-2| + |6-3| = 3 + 3 = 6
int calcular_distancia(int x1, int y1, int x2, int y2) {
    int diff_x = x2 - x1;
    int diff_y = y2 - y1;

    // Valor absoluto manual (sin usar abs() de <cmath>)
    if (diff_x < 0) diff_x = -diff_x;
    if (diff_y < 0) diff_y = -diff_y;

    return diff_x + diff_y;
}

