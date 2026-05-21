#include "../include/jugador.h"
#include "../include/mapa.h"
#include "../include/constantes.h"
#include <stdio.h>

void inicializar_jugador(Jugador* jugador) {
    // El jugador empieza en la sala 0, posicion (2, 5)
    jugador->x = 2;
    jugador->y = 5;
    jugador->vida = VIDA_JUGADOR;
    jugador->sala_actual = 0;
    jugador->tiene_item = 0;
}

/*
  Mueve al jugador una celda en la direccion indicada.
  Si la celda de destino es una puerta, cambia de sala.
  Si es una pared, no se mueve.
  Devuelve 1 si cambio de sala, 0 si no.
*/
int mover_jugador(
    Jugador* jugador,
    char direccion,
    const Sala salas[],
    int /*num_salas*/
) {
    int nuevo_x = jugador->x;
    int nuevo_y = jugador->y;

    // Calculamos la nueva posicion segun la tecla
    if (direccion == TECLA_ARRIBA)  nuevo_y -= 1;
    if (direccion == TECLA_ABAJO)   nuevo_y += 1;
    if (direccion == TECLA_IZQ)     nuevo_x -= 1;
    if (direccion == TECLA_DER)     nuevo_x += 1;

    // Si es pared, no nos movemos
    if (es_pared(salas, jugador->sala_actual, nuevo_x, nuevo_y)) {
        return 0;
    }

    // Revisamos si la celda de destino es una puerta
    char celda = salas[jugador->sala_actual].mapa[nuevo_y][nuevo_x];

    if (celda == SIM_PUERTA) {
        // Buscamos a que sala lleva esta puerta
        int s, num_p;
        num_p = salas[jugador->sala_actual].num_puertas;

        for (s = 0; s < num_p; s++) {
            // Usamos puntero a la puerta para mostrar uso de punteros
            const Puerta* p = &salas[jugador->sala_actual].puertas[s];
            if (p->x == nuevo_x && p->y == nuevo_y) {
                // Cambiamos al jugador de sala
                jugador->sala_actual = p->sala_destino;
                jugador->x = p->x_destino;
                jugador->y = p->y_destino;
                return 1; // cambio de sala
            }
        }
    }

    // Movimiento normal (no es puerta ni pared)
    jugador->x = nuevo_x;
    jugador->y = nuevo_y;
    return 0;
}

*
  Revisa si el jugador esta sobre un item.
  Si el inventario esta libre, lo recoge.
  Los items de tipo curacion se aplican inmediatamente.
*/
void revisar_item(Jugador* jugador, Item items[], int num_items) {
    int i;
    for (i = 0; i < num_items; i++) {
        Item* it = &items[i]; // puntero al item
        if (it->sala == jugador->sala_actual &&
            it->visible &&
            it->x == jugador->x &&
            it->y == jugador->y)
        {
            if (it->simbolo == '!') {
                // Pocion de curacion: se aplica directo, no ocupa inventario
                jugador->vida += CURACION_ITEM;
                if (jugador->vida > VIDA_JUGADOR) jugador->vida = VIDA_JUGADOR;
                it->visible = 0;
                printf("  [!] Recogiste una pocion. Vida: %d\n", jugador->vida);
            } else if (!jugador->tiene_item) {
                // Objeto clave: va al inventario
                jugador->tiene_item = 1;
                it->visible = 0;
                printf("  [+] Recogiste un objeto clave. Guardado en inventario.\n");
            } else {
                printf("  [!] Inventario lleno. Suelta el objeto con '%c'.\n", TECLA_SOLTAR);
            }
        }
    }
}

/*
  Suelta el item del inventario en la posicion actual del jugador.
*/
void soltar_item(Jugador* jugador, Item items[], int num_items) {
    if (!jugador->tiene_item) {
        printf("  [-] No llevas ningun objeto.\n");
        return;
    }

    int i;
    for (i = 0; i < num_items; i++) {
        Item* it = &items[i];
        // Buscamos el primer item no visible para soltarlo ahi
        if (!it->visible && it->simbolo == '*') {
            it->x = jugador->x;
            it->y = jugador->y;
            it->sala = jugador->sala_actual;
            it->visible = 1;
            jugador->tiene_item = 0;
            printf("  [-] Soltaste el objeto en (%d,%d).\n", it->x, it->y);
            return;void mostrar_estado(const Jugador* jugador) {
    int i;
    printf("  Vida: ");
    for (i = 0; i < jugador->vida; i++) printf("*");
    for (i = jugador->vida; i < VIDA_JUGADOR; i++) printf("-");
    printf(" (%d/%d)", jugador->vida, VIDA_JUGADOR);

    if (jugador->tiene_item) {
        printf("  | Inventario: [Objeto clave]");
    } else {
        printf("  | Inventario: [vacio]");
    }

    printf("  | Sala: %d\n", jugador->sala_actual);
    printf("  Controles: [W/A/S/D] mover  [F] atacar  [E] recoger  [Q] soltar  [M] mapa  [X] salir\n");
    printf("  Leyenda: @ jugador  G goblin(vida:2)  S slime(vida:3)  ! pocion  * objeto  E meta\n");
}
        }
    }
}

