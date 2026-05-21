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
