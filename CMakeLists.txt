# Algunas de las variables aquí referenciadas se encuentran en el fichero sdl2-config.cmake, que suele venir junto con las librerías de de sdl2.

# Este fichero, sdl2-config.cmake, hay que modificarlo para que sus variables apunten a las carpetas de librerias de SDL2. Esta librería se descarga de internet (), y la podemos descomprimir donde queramos.

# Importante: sdl2-config.cmake tiene que estar en una carpeta que sea un PATH del sistema.

# Important: Move window.png into build folder or compile evrerythin in the work folder

set(CC "gcc.exe")
set(CXX "g++.exe")

## set(CMAKE_OSX_ARCHITECTURES "x86_64") #Avoids conflicts with M1 arm

IF(APPLE)
    IF("${CMAKE_OSX_ARCHITECTURES}" STREQUAL "")
        SET(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
    ENDIF()
ENDIF(APPLE)

set (CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.7)

project(Tetris)

# includes cmake/*.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR} /Library/Frameworks/SDL2.framework /Library/Frameworks/SDL2_ttf.framework ) 

add_executable(${CMAKE_PROJECT_NAME} main.cpp game_init.cpp game.cpp game_close.cpp texto.cpp tablero.cpp pieza.cpp)


## INCLUSIÓN DE LAS LIBRERIAS SLD2 NECESARIAS
set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ) 


## HABILITAR IMPRESIÓN POR TERMINAL: https://stackoverflow.com/questions/34539135/how-do-i-print-to-the-console-while-an-sdl-2-program-is-running
# Por defecto la sdl2-config.cmake tiene configuradas flags para impedir
# la impresión por consola. Esta pensado para que funcione como una app
# si tener que utilizar la consola. 
set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -mconsole)
# Por esta razón, al final de target_link_libraries link añado -mconsole, para forzar 
# la impresión por consola. En la versión final se debe eliminar esta flag

# Finalmente se añaden las librerias indicadass
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})