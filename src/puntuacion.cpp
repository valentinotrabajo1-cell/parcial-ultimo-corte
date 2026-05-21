#include "../include/puntuacion.h"
#include "../include/constantes.h"
#include <stdio.h>

/*
  puntuacion.cpp
  --------------
  Sistema de estadisticas de la partida.

  Lleva dos contadores simples:
  - turnos: cuantas veces se movio el jugador
  - enemigos_matados: cuantos enemigos derroto el jugador

  Al terminar (victoria o derrota), se muestran las estadisticas.
*/

// Pone los contadores en cero al inicio del juego
void inicializar_estadisticas(Estadisticas* stats) {
    stats->turnos = 0;
    stats->enemigos_matados = 0;
}

// Suma un turno al contador
// Se llama cada vez que el jugador se mueve o ataca
void sumar_turno(Estadisticas* stats) {
    stats->turnos++;
}

// Muestra las estadisticas al finalizar la partida
void mostrar_estadisticas(const Estadisticas* stats) {
    printf("  ------------------------------------------\n");
    printf("  ESTADISTICAS DE LA PARTIDA:\n");
    printf("  ------------------------------------------\n");
    printf("  Turnos jugados:     %d\n", stats->turnos);
    printf("  Enemigos derrotados: %d\n", stats->enemigos_matados);
    printf("  ------------------------------------------\n\n");
}
