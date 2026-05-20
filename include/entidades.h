#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "constantes.h"


struct Jugador {
    int x;           
    int y;          
    int vida;
    int sala_actual; 
    bool tiene_item; 
};


enum TipoEnemigo {
    GOBLIN,   
    SLIME     
};
