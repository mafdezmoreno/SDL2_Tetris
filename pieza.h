#ifndef PIEZA_H
#define PIEZA_H

#include <vector>
#include <iostream>

// The 7 different kinds of parts that have the Tetris game
const std::vector<std::vector<std::vector<bool>>> tipos_piezas =
    {{{1, 1, 1},   
    { 1, 0, 0}},    // L
    {{1, 0, 0},   
    { 1, 1, 1}},    // J
    {{1, 1},   
    { 1, 1}},       //O
    {{1, 1, 1, 1}}, //I
    {{1, 1, 1},   
    { 0, 1, 0}},    //T
    {{0, 1, 1},   
    { 1, 1, 0}},    //S
    {{1, 1, 0},   
    { 0, 1, 1}},    //Z
    };

// To store the coordinates of the part (and each of its cells)
class Coordenada{
    public:
        Coordenada(){
            y_fila = 1;
            x_columna = 1;
        }
        Coordenada(int fila, int columna){
            y_fila = fila;
            x_columna = columna;
        }

        int y_fila;
        int x_columna;
};

class Pieza{

    public:

        Pieza(){  
            _inicializacion_pieza();
        }
        ~Pieza(){
            std::cout<< "PIEZA "<< this << " DESTRUIDA" << std::endl;
        }

        void pieza_a_coordenadas();        // Generates coordinates, from each of the cells of the part.
        void imprime_set_coordenadas();    // Print to terminal the coordinates of the part. To debug
        void Gira_Pieza_90();              // Rotates the part
        
        std::vector<std::vector<bool>> posiciones;  // Vector that contains the shape of the part
        std::vector<Coordenada> set_coordenadas;  // It will contain the list of coordinates to be rendered on the board
        Coordenada coordenada; // Coordinates of the part. Needed to set and render the part
        
        // To get the RGB code color
        int get_r();
        int get_g();
        int get_b();
    
    private:
        void _inicializacion_pieza(); // To initialize a new part
        void generador_aleatorio_pieza();  // To generete a random part

        int cod_color;
};

#endif