# Algunas de las variables aquí referenciadas se encuentran en el fichero sdl2-config.cmake, que suele venir junto con las librerías de de sdl2.

# Este fichero, sdl2-config.cmake, hay que modificarlo para que sus variables apunten a las carpetas de librerias de SDL2. Esta librería se descarga de internet (), y la podemos descomprimir donde queramos.

# Importante: sdl2-config.cmake tiene que estar en una carpeta que sea un PATH del sistema.

# Important: Move window.png into build folder or compile evrerythin in the work folder

set(CC "gcc.exe")
set(CXX "g++.exe")

set (CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.7)

project(Tetris)

find_package(SDL2 REQUIRED)
find_package (Threads REQUIRED) #Para que encuentre las librerías necesarias de multi-hilo
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${CMAKE_PROJECT_NAME} main.cpp game_init.cpp game.cpp game_close.cpp texto.cpp tablero.cpp pieza.cpp)


## INCLUSIÓN DE LAS LIBRERIAS SLD2 NECESARIAS
# Este proyecto necesita las siguiente librerías, pero las primeras ya están predefinidas en sdl2-config.cmake, por tanto, en la siguietne línea solo hay que añadir las dos últimas:
# -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -SDL2_mixer                
set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_ttf -lSDL2_mixer Threads::Threads)
##Es necesario incluir aquí las librerias para compilar programas con varios hilos Threads::Threads (equivalente a pthread en linea de comandos)


## HABILITAR IMPRESIÓN POR TERMINAL: https://stackoverflow.com/questions/34539135/how-do-i-print-to-the-console-while-an-sdl-2-program-is-running
# Por defecto la sdl2-config.cmake tiene configuradas flags para impedir
# la impresión por consola. Esta pensado para que funcione como una app
# si tener que utilizar la consola. 
set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -mconsole)
# Por esta razón, al final de target_link_libraries link añado -mconsole, para forzar 
# la impresión por consola. En la versión final se debe eliminar esta flag


# Finalmente se añaden las librerias indicadass
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})