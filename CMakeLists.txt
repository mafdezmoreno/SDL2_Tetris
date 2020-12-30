# Windows: The `sdl2-config.cmake` file is inside the commpreses files that contents de dev libraries: https://libsdl.org/download-2.0.php. This file must be configured with the paths where the SDL2 libraries are extracted.
# Important: *.cmake config files should be in a system PATH folder (or inside cmake folder)

set(CC "gcc.exe")
set(CXX "g++.exe")

IF(APPLE) #Avoids conflicts with M1 arm
    IF("${CMAKE_OSX_ARCHITECTURES}" STREQUAL "")
        SET(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
    ENDIF()
ENDIF(APPLE)

set (CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.7)

project(Tetris)

# includes cmake/*.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp game_init.cpp game.cpp game_close.cpp texto.cpp tablero.cpp pieza.cpp)

set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ) # Includes the SLD2 libraries needed

set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -mconsole) # -mconsole, to force terminal printing 

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})