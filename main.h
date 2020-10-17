#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include "pieza.h"
#include "tablero.h"
#include <map>



// CONSTANTES
const int REJILLA = 20; //piexeles
const int MS_INTERVALO_MOV_INICIAL = 1000; //ms. intervalo movimiento pieza

const int COLUMNAS = 8;
const int FILAS = 12;

const int ANCHO_TABLERO = COLUMNAS;
const int ALTO_TABLERO = FILAS;

const int ANCHO = (COLUMNAS + 12) * REJILLA;
const int ALTO = (FILAS + 2) * REJILLA;

const uint8_t colores [16][3] = {{0,0,0},           //black 
                                {255,255,255},      //white
                                {0,255,255},        //aqua
                                {0,0,255},          //blue
                                {255,0,255},        // Fuchsia
                                {0x80,0x80,0x80},   //grey
                                {0,0x80,0},         //green
                                {0,255,0},          //Lime
                                {0x80,0,0},         //Maroon
                                {0,0,0x80},         //Navy
                                {0x80,0x80,0x80},   //Olive
                                {0x80,0,0x80},      //Purple
                                {255,0,0},          //Red
                                {0xC0,0xC0,0xC0},   //silver
                                {0,0x80,0x80},      //Teal      
                                {255,255,0}         //yellow
                                };

#endif