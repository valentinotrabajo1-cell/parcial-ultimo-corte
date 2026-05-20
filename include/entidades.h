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

struct Puerta {
    int x;             
    int y;
    int sala_destino;  
    int x_destino;     
    int y_destino;
};


struct Sala {
    char mapa[ALTO_SALA][ANCHO_SALA]; 
    Puerta puertas[4];                
    int num_puertas;
    bool tiene_meta;  
};


struct Estadisticas {
    int turnos;           
    int enemigos_matados; 
};



#endif


