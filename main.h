#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
//#include "pieza.h"
//#include "tablero.h"
#include "texto.h"


extern SDL_Window*   Ventana;     // Ventana
extern SDL_Renderer* Render; // Elementos a renderizar en interior
extern TTF_Font* Fuente_TTF;

//! Renderizado de Texto
extern Texto Texto_Puntuacion;
extern Texto Valor_Puntuacion;
extern Texto Texto_Nivel;
extern Texto Valor_Nivel;
extern Texto Nombre_Jugador;
extern Texto Texto_Jugador;
extern Texto pedir_nombre_jugador;
extern Texto Nombre_Jugador_Temp;
extern Texto pulsa_intro_continuar;

//Contabilización de puntuación
extern int puntuacion;
extern int nivel;


// CONSTANTES
const int REJILLA = 20; //píxeles

//dimensiones del tablero 
const int COLUMNAS = 8;
const int FILAS = 12;
const int ANCHO_TABLERO = COLUMNAS;
const int ALTO_TABLERO = FILAS;

//Dimensiones de la ventana. Se adaptan a las del tablero
const int ANCHO = (COLUMNAS + 12) * REJILLA;
const int ALTO = (FILAS + 2) * REJILLA;

//Tamaño de todo el texto que se va a renderizar
const int TEXT_SIZE = 16;

//Códigos de colores para piezas y renderizados
const int colores[16][3]     = {{0,0,0},            //0 black 
                                {255,255,255},      //1 white
                                {0xC0,0xC0,0xC0},   //2 silver
                                {0,255,255},        //3 aqua
                                {0,0,255},          //4 blue
                                {255,0,255},        //5 Fuchsia
                                {0x80,0x80,0x80},   //6 grey
                                {0,0x80,0},         //7 green
                                {0,255,0},          //8 Lime
                                {0x80,0,0},         //9 Maroon
                                {0,0,0x80},         //10 Navy
                                {0x80,0x80,0x80},   //11 Olive
                                {0x80,0,0x80},      //12 Purple
                                {255,0,0},          //13 Red
                                {0,0x80,0x80},      //14 Teal      
                                {255,255,0}         //15 yellow
                                };

#endif