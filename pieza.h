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
        void Gira_Pieza_90();
        
        //VARIABLES
        
        std::vector<std::vector<bool>> posiciones;
        std::vector<Coordenada> set_coordenadas; //contendrá la lista de coordenadas a renderizar en el tablero
        //std::vector<Coordenada> set_coordenadas_previo;
        Coordenada coordenada; //para posicionar/mover la pieza
        //Coordenada coordenada_previa; //para borrar posición anterior de la pieza 
        
        //obtener colores de la pieza
        int get_r();
        int get_g();
        int get_b();
    
    private:
        void _inicializacion_pieza();
        int cod_color;
};

#endif