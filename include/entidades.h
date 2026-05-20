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
};struct Enemigo {
    int x;
    int y;
    int vida;
    int sala;           
    bool vivo;
    TipoEnemigo tipo;
    int contador_turno; 
};


struct Item {
    int x;
    int y;
    int sala;
    bool visible;       
    char simbolo;
};




