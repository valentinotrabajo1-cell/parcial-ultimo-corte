Innovaciones implementadas:

1. sistema de combate activo
para que se implemento: Se implemento para hacer el juego más interactivo y dinámico. En lugar de que jugador pierda vida automaticamente al tocar enemigos, ahora puede defendese y atacar con una tecla.
por qué se considero necesario: Se considero necesario porque mejora la experencia del jugador y agrega mayor dificultad y estrategia al juego.
como se llevo a cabo su implementación: Se agrego una lógica de combate agregando una tecla de ataque. los enemogos ahora tienen puntos de vida y reciban daño cuando el jugador ataca cerca de ellos. Ademas, se agregaron funciones para controlar el daño, eliminacion de enemigos y deteccion de rango de ataque.

2. minimapa del dungeon
Para qué se implementó: Se creó para ayudar al jugador a orientarse dentro del dungeon y recordar las habitaciones que ya ha explorado.
Por qué se consideró necesario: Se pensó que era fundamental porque mejora la navegación y facilita la exploración del mapa, especialmente cuando hay varias habitaciones interconectadas.
Cómo se llevó a cabo su implementación: Se utilizó un arreglo para guardar las habitaciones que se han visitado. Al presionar una tecla, el juego muestra un mapa esquemático en la consola, utilizando caracteres ASCII y símbolos simples para representar las salas y la posición actual del jugador.

3. Sistema de puntuación y contador de turnos
Para qué se implementó; Se implementó para añadir estadísticas al juego y así aumentar la rejugabilidad.
Por qué se consideró necesario: Se pensó que era útil porque permite evaluar el rendimiento del jugador durante la partida y añade un objetivo extra al completar el dungeon.
Cómo se llevó a cabo su implementación: Se incorporaron contadores dentro del ciclo del juego para registrar cuántos turnos se han realizado y cuántos enemigos han sido derrotados. Al final de la partida, las estadísticas se muestran en la pantalla.

Reglas Generales y Otras Instrucciones Importantes
El proyecto fue desarrollado completamente en C++.
El código se encuentra organizado en carpetas src e include.
Se utilizaron múltiples archivos .h y .cpp.
La compilación se realiza mediante Make y CMake.
El proyecto es compatible con Linux, Windows y macOS.
Se utilizaron arreglos estáticos para manejar entidades.
