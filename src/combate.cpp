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

/*
  jugador_ataca: el jugador golpea a todos los enemigos cercanos.
  Devuelve cuantos enemigos mato este ataque (puede ser 0, 1 o mas).
*/
int jugador_ataca(
    const Jugador* jugador,
    Enemigo enemigos[],
    int num_enemigos,
    Estadisticas* stats
) {
    int i;
    int enemigos_matados = 0;
    int ataco_alguien = 0; // para saber si habia alguien cerca

    for (i = 0; i < num_enemigos; i++) {
        Enemigo* e = &enemigos[i]; // puntero al enemigo actual

        // Solo atacamos enemigos vivos en la sala del jugador
        if (!e->vivo || e->sala != jugador->sala_actual) {
            continue;
        }

        // Calculamos la distancia al enemigo
        int distancia = calcular_distancia(jugador->x, jugador->y, e->x, e->y);

        // Si esta dentro del rango de ataque, lo golpeamos
        if (distancia <= RANGO_ATAQUE) {
            ataco_alguien = 1;
            e->vida -= DANO_JUGADOR;

            if (e->tipo == GOBLIN) {
                printf("  [F] Atacaste al Goblin! Le quedan %d de vida.\n", e->vida);
            } else {
                printf("  [F] Atacaste al Slime! Le quedan %d de vida.\n", e->vida);
            }

            // Revisamos si el enemigo murio
            if (e->vida <= 0) {
                e->vivo = 0;
                enemigos_matados++;
                stats->enemigos_matados++;

                if (e->tipo == GOBLIN) {
                    printf("  [!] El Goblin fue derrotado!\n");
                } else {
                    printf("  [!] El Slime fue derrotado!\n");
                }
            }
        }
    }

    // Si no habia nadie cerca, avisamos al jugador
    if (!ataco_alguien) {
        printf("  [F] No hay enemigos cerca para atacar.\n");
    }

    return enemigos_matados;
}
