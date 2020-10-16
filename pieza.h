#ifndef PIEZA_H
#define PIEZA_H

#include <vector>
#include <iostream>

class Coordenada{
    public:
        Coordenada(){
            y_fila = 1;
            x_columna = 1;
        }

        int y_fila;
        int x_columna;
};

class Pieza{
    public:
        //FUNCIONES
        Pieza(){
            
            //! TO DO: implementar posicionado de piezas aleatoria en la primera fila

            coordenada.y_fila = 0;
            coordenada.x_columna = 0;
            coordenada_previa.y_fila = 0;
            coordenada_previa.x_columna = 0;
            std::cout<<"Pieza inicializada"<<std::endl;
            std::cout <<std::endl;
            pieza_a_coordenadas();
        }
        Pieza(int y, int x){
            coordenada.y_fila = y;
            coordenada.x_columna = x;
            coordenada_previa.y_fila = y;
            coordenada_previa.x_columna = x;
            std::cout<<"Pieza inicializada"<<std::endl;
            std::cout <<std::endl;
            pieza_a_coordenadas();
        }
        ~Pieza(){
            std::cout<< "Pieza "<< this << " destruida" << std::endl;
        }

        void pieza_a_coordenadas(); //genera Coordenadas, de cada uno de los cubos de la pieza
        void imprime_set_coordenadas();    //imprime variable set_coordenadas
        
        //VARIABLES

        //! TO DO: implementar generación de piezas aleatoria
        std::vector<std::vector<bool>> posiciones = {{1, 1, 1},  // pieza tetris L de ejemplo para renderizar
                                                    { 1, 0, 0}}; // dos FILA, 3 COLUMNA
        
        
        std::vector<Coordenada> set_coordenadas; //contendrá la lista de coordenadas a renderizar en el tablero
        std::vector<Coordenada> set_coordenadas_previo;
        Coordenada coordenada; //para posicionar/mover la pieza
        Coordenada coordenada_previa; //para borrar posición anterior de la pieza

};

#endif