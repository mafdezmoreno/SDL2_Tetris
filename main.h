#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include "pieza.h"
#include "tablero.h"
#include <map>



// CONSTANTES
const int REJILLA = 20; //píxeles
const int MS_INTERVALO_MOV_INICIAL = 1000; //ms. intervalo movimiento pieza

const int COLUMNAS = 8;
const int FILAS = 12;

const int ANCHO_TABLERO = COLUMNAS;
const int ALTO_TABLERO = FILAS;

const int ANCHO = (COLUMNAS + 12) * REJILLA;
const int ALTO = (FILAS + 2) * REJILLA;

const int colores[16][3] = {{0,0,0},           //0 black 
                                {255,255,255},      //1 white
                                {0,255,255},        //2 aqua
                                {0,0,255},          //3 blue
                                {255,0,255},        //4 Fuchsia
                                {0x80,0x80,0x80},   //5 grey
                                {0,0x80,0},         //6 green
                                {0,255,0},          //7 Lime
                                {0x80,0,0},         //8 Maroon
                                {0,0,0x80},         //9 Navy
                                {0x80,0x80,0x80},   //10 Olive
                                {0x80,0,0x80},      //11 Purple
                                {255,0,0},          //12 Red
                                {0xC0,0xC0,0xC0},   //13 silver
                                {0,0x80,0x80},      //14 Teal      
                                {255,255,0}         //15 yellow
                                };

#endif