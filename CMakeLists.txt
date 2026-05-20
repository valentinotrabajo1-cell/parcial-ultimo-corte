cmake_minimum_required(VERSION 3.10)
project(DungeonCrawler)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

add_executable(dungeon
    main.cpp
    src/mapa.cpp
    src/jugador.cpp
    src/enemigo.cpp
    src/juego.cpp
    src/combate.cpp
    src/minimapa.cpp
    src/puntuacion.cpp
)

