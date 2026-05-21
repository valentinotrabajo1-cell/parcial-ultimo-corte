#include "../include/juego.h"
#include "../include/constantes.h"
#include <stdio.h>
#include <stdlib.h>

// Incluimos los encabezados necesarios segun el sistema operativo
#ifdef _WIN32
    #include <conio.h>    // para _getch() en Windows
#else
    #include <termios.h>  // para configurar la terminal en Linux/Mac
    #include <unistd.h>
#endif

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\n  Presiona ENTER para continuar...");
    int c;
    // Vaciamos el buffer de entrada antes de esperar
    while ((c = getchar()) != '\n' && c != EOF) {}
    getchar();
}

/*
  Lee una tecla sin necesitar Enter.
  En Windows: _getch().
  En Linux/Mac: configuramos la terminal en modo raw temporalmente.
*/
char leer_tecla() {
#ifdef _WIN32
    return (char)_getch();
#else
    struct termios configuracion_vieja, configuracion_nueva;
    char tecla;

    // Guardamos la configuracion actual de la terminal
    tcgetattr(STDIN_FILENO, &configuracion_vieja);
    configuracion_nueva = configuracion_vieja;

    // Desactivamos el modo de linea y el eco
    configuracion_nueva.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &configuracion_nueva);

    tecla = (char)getchar();

    // Restauramos la configuracion original
    tcsetattr(STDIN_FILENO, TCSANOW, &configuracion_vieja);

    return tecla;
#endif
}

int verificar_victoria(const Jugador* jugador, const Sala salas[]) {
    // Puntero a la sala actual para acceder a sus datos
    const Sala* sala_ptr = &salas[jugador->sala_actual];

    if (!sala_ptr->tiene_meta) {
        return 0;
    }

    // El jugador gana si pisa la meta Y tiene el objeto clave
    char celda = sala_ptr->mapa[jugador->y][jugador->x];
    if (celda == SIM_META && jugador->tiene_item) {
        return 1;
    }
    return 0;
}

int verificar_derrota(const Jugador* jugador) {
    return jugador->vida <= 0;
}
