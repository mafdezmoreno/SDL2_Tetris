#include "pieza.h"

void Pieza::pieza_a_coordenadas(){
    
    std::cout<< "Actualizadas coordenadas de la pieza: "<< this <<std::endl;  
    //std::cout<< "{y_fila,  x_columna}" <<std::endl; 
    set_coordenadas.clear(); //borra contenido anterior
    Coordenada buffer;
    for (int i = 0; i< posiciones.size(); i++){
        for (int j = 0; j<posiciones[0].size(); j++){
            if(posiciones[i][j]==true){
                buffer.y_fila = i + coordenada.y_fila;
                buffer.x_columna = j + coordenada.x_columna; 
                //std::cout<< "columna: " <<buffer.x_columna  << "  fila: "<< buffer.y_fila <<std::endl;
                std::cout<< "{" <<buffer.y_fila   << ", "<< buffer.x_columna << "}  ";
                set_coordenadas.emplace_back(buffer);
            }
            else
                std::cout<< "   _    ";
        }
        std::cout<<std::endl;
    } 
   // std::cout<<std::endl;  
}

void Pieza::imprime_set_coordenadas(){
    std::cout<< "El set de coordenadas de la pieza " << this << " a imprmir es: "<<std::endl;
    //std::cout<< "{y_fila,  x_columna}" <<std::endl; 
    for ( int i = 0 ; i < set_coordenadas.size() ; i++) {
        std::cout<< "{" <<set_coordenadas[i].y_fila   << ", "<< set_coordenadas[i].x_columna << "}  ";
        //std::cout<< "columna: " << set_coordenadas[i].x_columna<<std::endl;
        //std::cout<< "   fila: " << set_coordenadas[i].y_fila<<std::endl;
    }
    std::cout <<std::endl; 
    std::cout <<std::endl;
}