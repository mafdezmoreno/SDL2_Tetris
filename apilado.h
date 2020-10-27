#ifndef APILADO_H
#define APILADO_H

#include "pieza.h"
#include "tablero.h"
#include "main.h"

bool inicializar(); // Inicializa SDL y crea la ventana
void cerrar();      // Libera recursos previamente reservados
void Mueve_Pieza_Si_Se_Puede(SDL_Keycode tecla, Pieza &pieza, Tablero &tablero); //Mueve la pieza si no choca con bordes u otras piezas
void Actualiza_Pantalla(Pieza &pieza, Tablero &tablero_estatico, Pieza &siguiente_pieza);
void Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero);
void Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero);
Coordenada Mapeado_Coord_Tablero(Coordenada &coord);

bool cargar_texto();


#endif
