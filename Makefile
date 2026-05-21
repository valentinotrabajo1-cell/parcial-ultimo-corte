# ====================================================
# Makefile para DungeonCrawler
# Compatible con Linux, macOS y Windows (con MinGW)
# ====================================================

# Compilador y opciones
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Nombre del ejecutable
ifeq ($(OS), Windows_NT)
    TARGET = dungeon.exe
    RM     = del /Q
else
    TARGET = dungeon
    RM     = rm -f
endif

# Lista de archivos objeto (incluye los nuevos modulos)
OBJETOS = main.o \
          src/mapa.o \
          src/jugador.o \
          src/enemigo.o \
          src/juego.o \
          src/combate.o \
          src/minimapa.o \
          src/puntuacion.o

# Regla principal: compilar todo
all: $(TARGET)

# Enlazar todos los .o en el ejecutable final
$(TARGET): $(OBJETOS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJETOS)
	@echo "Compilacion exitosa. Ejecutar con: ./$(TARGET)"

# ---- Reglas de compilacion ----

main.o: main.cpp include/constantes.h include/entidades.h \
        include/combate.h include/minimapa.h include/puntuacion.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

src/mapa.o: src/mapa.cpp include/mapa.h include/entidades.h include/constantes.h
	$(CXX) $(CXXFLAGS) -c src/mapa.cpp -o src/mapa.o

src/jugador.o: src/jugador.cpp include/jugador.h include/entidades.h include/constantes.h
	$(CXX) $(CXXFLAGS) -c src/jugador.cpp -o src/jugador.o

src/enemigo.o: src/enemigo.cpp include/enemigo.h include/entidades.h include/constantes.h
	$(CXX) $(CXXFLAGS) -c src/enemigo.cpp -o src/enemigo.o

src/juego.o: src/juego.cpp include/juego.h include/entidades.h include/constantes.h
	$(CXX) $(CXXFLAGS) -c src/juego.cpp -o src/juego.o

src/combate.o: src/combate.cpp include/combate.h include/entidades.h include/constantes.h
	$(CXX) $(CXXFLAGS) -c src/combate.cpp -o src/combate.o

src/minimapa.o: src/minimapa.cpp include/minimapa.h include/entidades.h include/constantes.h
	$(CXX) $(CXXFLAGS) -c src/minimapa.cpp -o src/minimapa.o

src/puntuacion.o: src/puntuacion.cpp include/puntuacion.h include/entidades.h
	$(CXX) $(CXXFLAGS) -c src/puntuacion.cpp -o src/puntuacion.o

# Limpiar archivos compilados
clean:
	$(RM) $(OBJETOS) $(TARGET)
	@echo "Limpieza completa."

# Regla de ayuda
help:
	@echo "Opciones disponibles:"
	@echo "  make        -> Compila el proyecto"
	@echo "  make clean  -> Borra los archivos compilados"
	@echo "  make help   -> Muestra esta ayuda"

.PHONY: all clean help

