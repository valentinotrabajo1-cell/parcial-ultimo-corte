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

int main() {
    // ---- Declaracion de arreglos estaticos de entidades ----
    // No usamos new/delete: todo en la pila (stack)
    Sala        salas[MAX_SALAS];
    Enemigo     enemigos[MAX_ENEMIGOS];
    Item        items[MAX_ITEMS];
    Jugador     jugador;
    Estadisticas stats;    // nuevo: estadisticas de la partida

    int num_enemigos = 0;

    // ---- Inicializacion del mundo ----
    inicializar_salas(salas, MAX_SALAS);
    inicializar_jugador(&jugador);
    inicializar_enemigos(enemigos, &num_enemigos);
    inicializar_estadisticas(&stats); // nuevo

    // La sala inicial ya fue visitada
    registrar_sala_visitada(jugador.sala_actual); // nuevo: minimapa

    // ---- Inicializacion de items (arreglo estatico) ----
    // Item 0: pocion en sala 0
    items[0].x = 5;  items[0].y = 3; items[0].sala = 0;
    items[0].visible = 1; items[0].simbolo = '!';

    // Item 1: pocion en sala 3
    items[1].x = 12; items[1].y = 6; items[1].sala = 3;
    items[1].visible = 1; items[1].simbolo = '!';

    // Item 2: pocion en sala 5
    items[2].x = 8;  items[2].y = 7; items[2].sala = 5;
    items[2].visible = 1; items[2].simbolo = '!';

    // Item 3: objeto clave en sala 4 (hay que buscarlo)
    items[3].x = 15; items[3].y = 7; items[3].sala = 4;
    items[3].visible = 1; items[3].simbolo = '*';

    // Items 4 y 5 se usan para soltar el objeto si el jugador lo deja caer
    items[4].x = 0;  items[4].y = 0; items[4].sala = 0;
    items[4].visible = 0; items[4].simbolo = '*';

    items[5].x = 0;  items[5].y = 0; items[5].sala = 0;
    items[5].visible = 0; items[5].simbolo = '*';

    // ---- Pantalla de bienvenida ----
    limpiar_pantalla();
    printf("\n");
    printf("  ==========================================\n");
    printf("  ||    DUNGEON CRAWLER - Parcial Final   ||\n");
    printf("  ==========================================\n");
    printf("  Objetivo: encontrar el objeto (*) en la\n");
    printf("  sala 4 y llevarlo a la salida (E) sala 7.\n");
    printf("\n");
    printf("  Controles:\n");
    printf("    W A S D = moverse\n");
    printf("    F       = atacar enemigos cercanos (NUEVO)\n");
    printf("    E       = recoger item (al pisarlo)\n");
    printf("    Q       = soltar item\n");
    printf("    M       = ver minimapa del dungeon (NUEVO)\n");
    printf("    X       = salir del juego\n");
    printf("\n");
    printf("  Leyenda:\n");
    printf("    @  = jugador      !  = pocion\n");
    printf("    G  = goblin(2hp)  *  = objeto clave\n");
    printf("    S  = slime(3hp)   E  = meta (salida)\n");
    printf("    D  = puerta\n");
    printf("\n");
    printf("  Tip: presiona F cerca de un enemigo para atacarlo.\n");
    printf("       Los enemigos te golpean si se acercan demasiado.\n");
    printf("\n");
    pausar();

    // ---- Game loop principal ----
    int jugando = 1;

    while (jugando) {
        limpiar_pantalla();

        // Dibujamos el mapa de la sala actual
        dibujar_sala(salas, jugador.sala_actual, &jugador,
                     enemigos, num_enemigos, items, MAX_ITEMS);

        // Mostramos el estado del jugador
        mostrar_estado(&jugador);

        // Leemos la tecla del usuario
        printf("\n  > ");
        char tecla = leer_tecla();
        printf("%c\n", tecla);

        // Procesamos la accion del jugador
        if (tecla == TECLA_SALIR) {
            printf("  Saliendo del juego...\n");
            jugando = 0;
            continue;
        }

        if (tecla == TECLA_MAPA) {
            // Mostrar el minimapa del dungeon
            mostrar_minimapa(jugador.sala_actual);
            pausar();

        } else if (tecla == TECLA_ATACAR) {
            // El jugador ataca a enemigos cercanos
            jugador_ataca(&jugador, enemigos, num_enemigos, &stats);
            sumar_turno(&stats); // atacar cuenta como un turno

            // Despues del ataque, los enemigos responden
            mover_enemigos(enemigos, num_enemigos, &jugador, salas);
            atacar_jugador(enemigos, num_enemigos, &jugador);

        } else if (tecla == TECLA_RECOGER) {
            // El jugador intenta recoger un item en su posicion
            revisar_item(&jugador, items, MAX_ITEMS);

        } else if (tecla == TECLA_SOLTAR) {
            soltar_item(&jugador, items, MAX_ITEMS);

        } else if (tecla == TECLA_ARRIBA || tecla == TECLA_ABAJO ||
                   tecla == TECLA_IZQ   || tecla == TECLA_DER) {
            // Movemos al jugador
            int cambio_sala = mover_jugador(&jugador, tecla, salas, MAX_SALAS);

            // Si cambio de sala, registramos la nueva sala en el minimapa
            if (cambio_sala) {
                registrar_sala_visitada(jugador.sala_actual);
            }

            // Despues de moverse, revisamos si piso un item
            revisar_item(&jugador, items, MAX_ITEMS);

            // Movemos los enemigos (IA de persecucion)
            mover_enemigos(enemigos, num_enemigos, &jugador, salas);

            // Los enemigos atacan si estan adyacentes al jugador
            atacar_jugador(enemigos, num_enemigos, &jugador);

            // Contamos el turno
            sumar_turno(&stats);
        }

        // ---- Verificacion de condiciones de fin ----
        if (verificar_victoria(&jugador, salas)) {
            limpiar_pantalla();
            dibujar_sala(salas, jugador.sala_actual, &jugador,
                         enemigos, num_enemigos, items, MAX_ITEMS);
            mostrar_victoria();
            mostrar_estadisticas(&stats); // nuevo: estadisticas al ganar
            jugando = 0;
        } else if (verificar_derrota(&jugador)) {
            limpiar_pantalla();
            dibujar_sala(salas, jugador.sala_actual, &jugador,
                         enemigos, num_enemigos, items, MAX_ITEMS);
            mostrar_derrota();
            mostrar_estadisticas(&stats); // nuevo: estadisticas al perder
            jugando = 0;
        }
    }

    return 0;
}
