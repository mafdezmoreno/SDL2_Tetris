#ifndef APILADO_H
#define APILADO_H

//Librerías

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "pieza.h"
#include "tablero.h"

// CONSTANTES
const int REJILLA = 20; //piexeles
const int MS_INTERVALO_MOV_INICIAL = 1000; //ms. intervalo movimiento pieza

const int COLUMNAS = 10;
const int FILAS = 15;

const int ANCHO_TABLERO = COLUMNAS;
const int ALTO_TABLERO = FILAS;

const int ANCHO = (COLUMNAS + 12) * REJILLA;
const int ALTO = (FILAS + 2) * REJILLA;


bool inicializar(); // Inicializa SDL y crea la ventana
void cerrar();      // Libera recursos previamente reservados
void Mueve_Pieza_Si_Se_Puede(SDL_Keycode tecla, Pieza &pieza, Tablero &tablero); //Mueve la pieza si no choca con bordes u otras piezas
void Actualiza_Pantalla(std::vector<int>const &coord, std::vector<std::vector<bool>> &posiciones_pieza);
std::vector<int> Mapeado_Coord_Tablero(Coordenada &coord);

#endif
