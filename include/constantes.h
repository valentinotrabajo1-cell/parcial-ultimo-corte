#ifndef CONSTANTES_H
#define CONSTANTES_H


#define ANCHO_SALA   20
#define ALTO_SALA    10

#define MAX_ENEMIGOS 10
#define MAX_ITEMS    6
#define MAX_SALAS    8

#define SIM_PARED      '#'
#define SIM_SUELO      '.'
#define SIM_JUGADOR    '@'
#define SIM_ITEM       '!'
#define SIM_ENEMIGO_A  'G'   
#define SIM_ENEMIGO_B  'S'   
#define SIM_PUERTA     'D'
#define SIM_META       'E'  




#define TECLA_ARRIBA   'w'
#define TECLA_ABAJO    's'
#define TECLA_IZQ      'a'
#define TECLA_DER      'd'
#define TECLA_RECOGER  'e'
#define TECLA_SOLTAR   'q'
#define TECLA_SALIR    'x'
#define TECLA_ATACAR   'f'   // Nueva: atacar enemigos cercanos
#define TECLA_MAPA     'm'   // Nueva: mostrar minimapa


#define VIDA_JUGADOR       5
#define DANO_GOBLIN        1
#define DANO_SLIME         1
#define CURACION_ITEM      2


#define VIDA_GOBLIN        2   // El goblin necesita 2 golpes para morir
#define VIDA_SLIME         3   // El slime necesita 3 golpes para morir
#define DANO_JUGADOR       1   // El jugador hace 1 punto de dano por golpe


#define RANGO_ATAQUE       2

#endif
