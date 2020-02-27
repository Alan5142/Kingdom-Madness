# Proyecto de progra :)

## Instrucciones para compilar
Es importante tener instalado CMake, de lo contrario no será posiblecutado.

**Nota importante:** es importante poseer mingw de 64 bits o compilar el proyecto con MSVC (el compilador de Microsoft).
1. Tener esta carpeta cx
1. Tener instalado CMake y MinGW o MSVC
1. Debido a una dependencia con SFML, es necesario un compilador de C++ :( (como tal el proyecto no usa C++, hay un binding que permite llamar funciones de esta librería desde C)
1. Crear una carpeta para la compilación (usualmente llamada build o algo por el estilo)
1. Ir a esta carpeta 
    * Si se desea compilar para MinGW, ejecutar el comando `cmake .. -G "MinGW Makefiles"`, ir al paso 6
    * Si se desea compilar para MSVC, ejecutar el comando `cmake .. -G "Visual Studio XX YYYY"` donde XX es la versión y YYYY es el año (para mas información referirse al help de este comando `cmake .. -G --help`),
    ir al paso 8
1. Ejecutar make para generar el ejecutable (ir a paso 8)
1. Ejecutar Visual Studio y compilar el proyecto (ir a paso 8)
1. Disfrutar del juego cx