#ifndef PIEZA_H
#define PIEZA_H

#include <vector>
#include <iostream>

const std::vector<std::vector<std::vector<bool>>> tipos_piezas =
    {{{1, 1, 1},   
    { 1, 0, 0}}, // L
    {{1, 0, 0},   
    { 1, 1, 1}}, // J
    {{1, 1},   
    { 1, 1}}, //O
    {{1, 1, 1, 1}}, //I
    {{1, 1, 1},   
    { 0, 1, 0}}, //T
    {{0, 1, 1},   
    { 1, 1, 0}},//S
    {{1, 1, 0},   
    { 0, 1, 1}},//Z
    }; //7 tipos diferentes


class Coordenada{
    public:
        Coordenada(){
            y_fila = 0;
            x_columna = 1;
        }
        Coordenada(int fila, int columna){
            y_fila = fila;
            x_columna = columna;
        }

        int y_fila;
        int x_columna;
};

//! TO DO: implementar posicionado de piezas aleatoria en la primera fila
class Pieza{
    public:
        //FUNCIONES
        Pieza(){  
            _inicializacion_pieza();
        }
        ~Pieza(){
            std::cout<< "PIEZA "<< this << " DESTRUIDA" << std::endl;
        }

        void pieza_a_coordenadas();        //genera Coordenadas, de cada uno de los cubos de la pieza
        void imprime_set_coordenadas();    //imprime variable set_coordenadas
        void generador_aleatorio_pieza();  //selecciona una pieza aleatoria de tipos_piezas
        std::vector<std::vector<bool>> Gira_Pieza_90(std::vector<std::vector<bool>> pieza);
        
        //VARIABLES
        int cod_color; 
        std::vector<std::vector<bool>> posiciones;// = {{1, 1, 1},  // pieza tetris L de ejemplo para renderizar
                                                  //  { 1, 0, 0}}; // dos FILA, 3 COLUMNA
        
        
        std::vector<Coordenada> set_coordenadas; //contendrá la lista de coordenadas a renderizar en el tablero
        std::vector<Coordenada> set_coordenadas_previo;
        Coordenada coordenada; //para posicionar/mover la pieza
        Coordenada coordenada_previa; //para borrar posición anterior de la pieza 
        void _inicializacion_pieza();
};

#endif